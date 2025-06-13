//#pragma once
#include <string>
#include <unordered_map>
#include <chrono>
#include <memory>
#include <mutex>
#include <functional>
#include <random>
#include <fstream>
#include <thread>
#include <atomic>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

// Forward declarations
class SessionData;
class SessionManager;

// Session state enumeration
enum class SessionState {
    ACTIVE,
    EXPIRED,
    TERMINATED,
    SUSPENDED
};

// Session configuration structure
struct SessionConfig {
    std::chrono::minutes defaultTimeout{30};
    std::chrono::minutes maxTimeout{480}; // 8 hours
    std::chrono::minutes cleanupInterval{5};
    size_t maxSessions{1000};
    bool persistSessions{false};
    std::string persistenceFile{"sessions.dat"};
    bool enableAutoCleanup{true};
};

// Session data container
class SessionData {
public:
    SessionData(const std::string& sessionId, const std::string& userId = "")
        : id_(sessionId), userId_(userId), state_(SessionState::ACTIVE),
          createdAt_(std::chrono::steady_clock::now()),
          lastAccessedAt_(std::chrono::steady_clock::now()),
          timeout_(std::chrono::minutes(30)) {}

    // Getters
    const std::string& getId() const { return id_; }
    const std::string& getUserId() const { return userId_; }
    SessionState getState() const { return state_; }
    std::chrono::steady_clock::time_point getCreatedAt() const { return createdAt_; }
    std::chrono::steady_clock::time_point getLastAccessedAt() const { return lastAccessedAt_; }
    std::chrono::minutes getTimeout() const { return timeout_; }

    // Session data management
    template<typename T>
    void setAttribute(const std::string& key, const T& value) {
        std::lock_guard<std::mutex> lock(dataMutex_);
        attributes_[key] = std::to_string(value);
        touch();
    }

    void setAttribute(const std::string& key, const std::string& value) {
        std::lock_guard<std::mutex> lock(dataMutex_);
        attributes_[key] = value;
        touch();
    }

    std::string getAttribute(const std::string& key, const std::string& defaultValue = "") const {
        std::lock_guard<std::mutex> lock(dataMutex_);
        auto it = attributes_.find(key);
        return (it != attributes_.end()) ? it->second : defaultValue;
    }

    bool hasAttribute(const std::string& key) const {
        std::lock_guard<std::mutex> lock(dataMutex_);
        return attributes_.find(key) != attributes_.end();
    }

    void removeAttribute(const std::string& key) {
        std::lock_guard<std::mutex> lock(dataMutex_);
        attributes_.erase(key);
        touch();
    }

    std::vector<std::string> getAttributeKeys() const {
        std::lock_guard<std::mutex> lock(dataMutex_);
        std::vector<std::string> keys;
        for (const auto& pair : attributes_) {
            keys.push_back(pair.first);
        }
        return keys;
    }

    // Session state management
    void setState(SessionState state) { 
        state_ = state; 
        if (state == SessionState::ACTIVE) {
            touch();
        }
    }

    void setTimeout(std::chrono::minutes timeout) { timeout_ = timeout; }

    void touch() { lastAccessedAt_ = std::chrono::steady_clock::now(); }

    bool isExpired() const {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::minutes>(now - lastAccessedAt_);
        return elapsed >= timeout_;
    }

    bool isValid() const {
        return state_ == SessionState::ACTIVE && !isExpired();
    }

    // Serialization for persistence
    std::string serialize() const {
        std::lock_guard<std::mutex> lock(dataMutex_);
        std::string result = id_ + "|" + userId_ + "|" + std::to_string(static_cast<int>(state_)) + "|";
        result += std::to_string(std::chrono::duration_cast<std::chrono::seconds>(createdAt_.time_since_epoch()).count()) + "|";
        result += std::to_string(std::chrono::duration_cast<std::chrono::seconds>(lastAccessedAt_.time_since_epoch()).count()) + "|";
        result += std::to_string(timeout_.count()) + "|";
        
        for (const auto& attr : attributes_) {
            result += attr.first + "=" + attr.second + ";";
        }
        return result;
    }

    static std::unique_ptr<SessionData> deserialize(const std::string& data) {
        std::vector<std::string> parts;
        std::string temp;
        for (char c : data) {
            if (c == '|') {
                parts.push_back(temp);
                temp.clear();
            } else {
                temp += c;
            }
        }
        parts.push_back(temp);

        if (parts.size() < 6) return nullptr;

        auto session = std::make_unique<SessionData>(parts[0], parts[1]);
        session->state_ = static_cast<SessionState>(std::stoi(parts[2]));
        
        // Restore timestamps (simplified - using current time base)
        session->timeout_ = std::chrono::minutes(std::stoi(parts[5]));
        
        // Parse attributes
        if (parts.size() > 6 && !parts[6].empty()) {
            std::string attrData = parts[6];
            size_t pos = 0;
            while (pos < attrData.length()) {
                size_t eqPos = attrData.find('=', pos);
                size_t semiPos = attrData.find(';', pos);
                if (eqPos != std::string::npos && semiPos != std::string::npos) {
                    std::string key = attrData.substr(pos, eqPos - pos);
                    std::string value = attrData.substr(eqPos + 1, semiPos - eqPos - 1);
                    session->attributes_[key] = value;
                    pos = semiPos + 1;
                } else {
                    break;
                }
            }
        }

        return session;
    }

private:
    std::string id_;
    std::string userId_;
    SessionState state_;
    std::chrono::steady_clock::time_point createdAt_;
    std::chrono::steady_clock::time_point lastAccessedAt_;
    std::chrono::minutes timeout_;
    std::unordered_map<std::string, std::string> attributes_;
    mutable std::mutex dataMutex_;
};

// Session event callbacks
using SessionEventCallback = std::function<void(const std::string& sessionId, const SessionData& session)>;

// Main Session Manager class
class SessionManager {
public:
    explicit SessionManager(const SessionConfig& config = SessionConfig{})
        : config_(config), running_(false), generator_(std::random_device{}()) {
        
        if (config_.enableAutoCleanup) {
            startCleanupThread();
        }
        
        if (config_.persistSessions) {
            loadSessions();
        }
    }

    ~SessionManager() {
        shutdown();
    }

    // Session lifecycle management
    std::string createSession(const std::string& userId = "") {
        std::lock_guard<std::mutex> lock(sessionsMutex_);
        
        // Check session limit
        if (sessions_.size() >= config_.maxSessions) {
            cleanupExpiredSessions();
            if (sessions_.size() >= config_.maxSessions) {
                throw std::runtime_error("Maximum number of sessions reached");
            }
        }

        std::string sessionId = generateSessionId();
        auto session = std::make_unique<SessionData>(sessionId, userId);
        session->setTimeout(config_.defaultTimeout);
        
        sessions_[sessionId] = std::move(session);
        
        // Trigger callback
        if (onSessionCreated_) {
            onSessionCreated_(sessionId, *sessions_[sessionId]);
        }
        
        return sessionId;
    }

    bool validateSession(const std::string& sessionId) {
        std::lock_guard<std::mutex> lock(sessionsMutex_);
        auto it = sessions_.find(sessionId);
        
        if (it == sessions_.end()) {
            return false;
        }
        
        if (!it->second->isValid()) {
            // Session expired
            if (onSessionExpired_) {
                onSessionExpired_(sessionId, *it->second);
            }
            it->second->setState(SessionState::EXPIRED);
            return false;
        }
        
        it->second->touch();
        return true;
    }

    std::shared_ptr<SessionData> getSession(const std::string& sessionId) {
        std::lock_guard<std::mutex> lock(sessionsMutex_);
        auto it = sessions_.find(sessionId);
        
        if (it == sessions_.end() || !it->second->isValid()) {
            return nullptr;
        }
        
        it->second->touch();
        return std::shared_ptr<SessionData>(it->second.get(), [](SessionData*) {});
    }

    bool terminateSession(const std::string& sessionId) {
        std::lock_guard<std::mutex> lock(sessionsMutex_);
        auto it = sessions_.find(sessionId);
        
        if (it == sessions_.end()) {
            return false;
        }
        
        it->second->setState(SessionState::TERMINATED);
        
        if (onSessionTerminated_) {
            onSessionTerminated_(sessionId, *it->second);
        }
        
        sessions_.erase(it);
        return true;
    }

    bool suspendSession(const std::string& sessionId) {
        std::lock_guard<std::mutex> lock(sessionsMutex_);
        auto it = sessions_.find(sessionId);
        
        if (it == sessions_.end()) {
            return false;
        }
        
        it->second->setState(SessionState::SUSPENDED);
        return true;
    }

    bool resumeSession(const std::string& sessionId) {
        std::lock_guard<std::mutex> lock(sessionsMutex_);
        auto it = sessions_.find(sessionId);
        
        if (it == sessions_.end() || it->second->getState() != SessionState::SUSPENDED) {
            return false;
        }
        
        it->second->setState(SessionState::ACTIVE);
        return true;
    }

    void extendSession(const std::string& sessionId, std::chrono::minutes additionalTime) {
        std::lock_guard<std::mutex> lock(sessionsMutex_);
        auto it = sessions_.find(sessionId);
        
        if (it != sessions_.end()) {
            auto newTimeout = it->second->getTimeout() + additionalTime;
            if (newTimeout <= config_.maxTimeout) {
                it->second->setTimeout(newTimeout);
                it->second->touch();
            }
        }
    }

    // Bulk operations
    std::vector<std::string> getActiveSessions() const {
        std::lock_guard<std::mutex> lock(sessionsMutex_);
        std::vector<std::string> active;
        
        for (const auto& pair : sessions_) {
            if (pair.second->isValid()) {
                active.push_back(pair.first);
            }
        }
        
        return active;
    }

    std::vector<std::string> getSessionsByUser(const std::string& userId) const {
        std::lock_guard<std::mutex> lock(sessionsMutex_);
        std::vector<std::string> userSessions;
        
        for (const auto& pair : sessions_) {
            if (pair.second->getUserId() == userId && pair.second->isValid()) {
                userSessions.push_back(pair.first);
            }
        }
        
        return userSessions;
    }

    void terminateUserSessions(const std::string& userId) {
        auto userSessions = getSessionsByUser(userId);
        for (const auto& sessionId : userSessions) {
            terminateSession(sessionId);
        }
    }

    size_t getActiveSessionCount() const {
        return getActiveSessions().size();
    }

    // Cleanup operations
    size_t cleanupExpiredSessions() {
        std::lock_guard<std::mutex> lock(sessionsMutex_);
        size_t cleaned = 0;
        
        auto it = sessions_.begin();
        while (it != sessions_.end()) {
            if (!it->second->isValid()) {
                if (onSessionExpired_) {
                    onSessionExpired_(it->first, *it->second);
                }
                it = sessions_.erase(it);
                ++cleaned;
            } else {
                ++it;
            }
        }
        
        return cleaned;
    }

    void cleanupAllSessions() {
        std::lock_guard<std::mutex> lock(sessionsMutex_);
        
        for (const auto& pair : sessions_) {
            if (onSessionTerminated_) {
                onSessionTerminated_(pair.first, *pair.second);
            }
        }
        
        sessions_.clear();
    }

    // Event handling
    void setOnSessionCreated(SessionEventCallback callback) {
        onSessionCreated_ = callback;
    }

    void setOnSessionExpired(SessionEventCallback callback) {
        onSessionExpired_ = callback;
    }

    void setOnSessionTerminated(SessionEventCallback callback) {
        onSessionTerminated_ = callback;
    }

    // Configuration
    void updateConfig(const SessionConfig& config) {
        config_ = config;
        
        if (config_.enableAutoCleanup && !running_) {
            startCleanupThread();
        } else if (!config_.enableAutoCleanup && running_) {
            stopCleanupThread();
        }
    }

    SessionConfig getConfig() const { return config_; }

    // Persistence
    void saveSessions() const {
        if (!config_.persistSessions) return;
        
        std::lock_guard<std::mutex> lock(sessionsMutex_);
        std::ofstream file(config_.persistenceFile, std::ios::binary);
        
        if (!file.is_open()) {
            throw std::runtime_error("Cannot open sessions file for writing");
        }
        
        size_t count = sessions_.size();
        file.write(reinterpret_cast<const char*>(&count), sizeof(count));
        
        for (const auto& pair : sessions_) {
            std::string data = pair.second->serialize();
            size_t size = data.size();
            file.write(reinterpret_cast<const char*>(&size), sizeof(size));
            file.write(data.c_str(), size);
        }
    }

    void loadSessions() {
        if (!config_.persistSessions) return;
        
        std::ifstream file(config_.persistenceFile, std::ios::binary);
        if (!file.is_open()) return; // File doesn't exist yet
        
        std::lock_guard<std::mutex> lock(sessionsMutex_);
        sessions_.clear();
        
        size_t count;
        file.read(reinterpret_cast<char*>(&count), sizeof(count));
        
        for (size_t i = 0; i < count; ++i) {
            size_t size;
            file.read(reinterpret_cast<char*>(&size), sizeof(size));
            
            std::string data(size, '\0');
            file.read(&data[0], size);
            
            auto session = SessionData::deserialize(data);
            if (session && session->isValid()) {
                sessions_[session->getId()] = std::move(session);
            }
        }
    }

    // Statistics
    struct SessionStats {
        size_t totalSessions{0};
        size_t activeSessions{0};
        size_t expiredSessions{0};
        size_t suspendedSessions{0};
        std::chrono::steady_clock::time_point oldestSession;
        std::chrono::steady_clock::time_point newestSession;
    };

    SessionStats getStatistics() const {
        std::lock_guard<std::mutex> lock(sessionsMutex_);
        SessionStats stats;
        
        stats.totalSessions = sessions_.size();
        auto now = std::chrono::steady_clock::now();
        stats.oldestSession = now;
        stats.newestSession = std::chrono::steady_clock::time_point::min();
        
        for (const auto& pair : sessions_) {
            const auto& session = pair.second;
            
            if (session->isValid()) {
                stats.activeSessions++;
            } else if (session->isExpired()) {
                stats.expiredSessions++;
            } else if (session->getState() == SessionState::SUSPENDED) {
                stats.suspendedSessions++;
            }
            
            if (session->getCreatedAt() < stats.oldestSession) {
                stats.oldestSession = session->getCreatedAt();
            }
            if (session->getCreatedAt() > stats.newestSession) {
                stats.newestSession = session->getCreatedAt();
            }
        }
        
        return stats;
    }

    void shutdown() {
        if (config_.persistSessions) {
            saveSessions();
        }
        stopCleanupThread();
    }

private:
    SessionConfig config_;
    std::unordered_map<std::string, std::unique_ptr<SessionData>> sessions_;
    mutable std::mutex sessionsMutex_;
    
    // Event callbacks
    SessionEventCallback onSessionCreated_;
    SessionEventCallback onSessionExpired_;
    SessionEventCallback onSessionTerminated_;
    
    // Cleanup thread
    std::atomic<bool> running_;
    std::thread cleanupThread_;
    
    // Random generation
    std::random_device rd_;
    std::mt19937 generator_;

    std::string generateSessionId() {
        const std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        std::uniform_int_distribution<> dis(0, chars.size() - 1);
        
        std::string sessionId;
        sessionId.reserve(32);
        
        for (int i = 0; i < 32; ++i) {
            sessionId += chars[dis(generator_)];
        }
        
        return sessionId;
    }

    void startCleanupThread() {
        if (running_) return;
        
        running_ = true;
        cleanupThread_ = std::thread([this]() {
            while (running_) {
                std::this_thread::sleep_for(config_.cleanupInterval);
                if (running_) {
                    cleanupExpiredSessions();
                }
            }
        });
    }

    void stopCleanupThread() {
        if (!running_) return;
        
        running_ = false;
        if (cleanupThread_.joinable()) {
            cleanupThread_.join();
        }
    }
};

// Usage example

int main() {
    SessionConfig config;
    config.defaultTimeout = std::chrono::minutes(15);
    config.maxSessions = 500;
    config.persistSessions = true;
    
    SessionManager manager(config);
    
    // Set up event handlers
    manager.setOnSessionCreated([](const std::string& id, const SessionData& session) {
        cout << "Session created: " << id << endl;
    });
    
    manager.setOnSessionExpired([](const std::string& id, const SessionData& session) {
        cout << "Session expired: " << id << endl;
    });
    
    // Create and use sessions
    std::string sessionId = manager.createSession("user123");
    
    if (auto session = manager.getSession(sessionId)) {
        session->setAttribute("username", "john_doe");
        session->setAttribute("login_time", std::chrono::system_clock::now());
        
        cout << "Username: " << session->getAttribute("username") << std::endl;
    }
    
    // Validate session
    if (manager.validateSession(sessionId)) {
        cout << "Session is valid" << std::endl;
    }
    
    // Get statistics
    auto stats = manager.getStatistics();
    cout << "Active sessions: " << stats.activeSessions << std::endl;
    
    return 0;
}
