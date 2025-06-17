// session_manager_test.cpp
// Copyright 2025 <MahmoudIsmail>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

// Alias for readability
using TimePoint = std::chrono::system_clock::time_point;

class SessionManager {
 private:
  std::string token_;
  unsigned int user_id_ = 0;
  TimePoint expire_time_;
  TimePoint expire_time_from_database_;
  bool created_ = false;

 public:
  // Generate a random UUID v4–like token string (36 chars with hyphens).
  void GenerateUuidV4() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);

    const char *hex_chars = "0123456789abcdef";
    std::stringstream ss;

    // Format: xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx
    for (int i = 0; i < 36; i++) {
      if (i == 8 || i == 13 || i == 18 || i == 23) {
        ss << '-';
      } else if (i == 14) {
        // UUID version 4
        ss << '4';
      } else if (i == 19) {
        // Variant: two most significant bits = 10
        ss << hex_chars[(dis(gen) & 0x3) | 0x8];
      } else {
        ss << hex_chars[dis(gen)];
      }
    }
    token_ = ss.str();
    created_ = true;
  }

  // Generate a pseudo user ID based on username, salted + hashed.
  void GenerateUserId(const std::string &username) {
    const std::string salt = "TicTacToeSalt42_";
    std::string combined = salt + username;
    size_t hash = std::hash<std::string>{}(combined);
    unsigned int raw_id = static_cast<unsigned int>(hash % 1000000u);
    // Ensure a 6-digit-ish ID between 100000 and 999999.
    user_id_ = 100000u + (raw_id % 900000u);
  }

  // Get current time point.
  static TimePoint Now() { return std::chrono::system_clock::now(); }

  // Compute expiry time: now + 5 minutes.
  static TimePoint CalculateExpiry() { return Now() + std::chrono::minutes(5); }

  // Check if expired: now >= expire_time_.
  bool IsExpired() const {
    // If expire_time_ was never set, it's epoch => expired immediately.
    return Now() >= expire_time_;
  }

  // Destroy session: clear token, user_id; mark created = false; reset times.
  void DestroySession() {
    token_.clear();
    user_id_ = 0;
    created_ = false;
    expire_time_ = TimePoint{};  // epoch
    expire_time_from_database_ = TimePoint{};
  }

  // Load expiry from “database”: set both
  // expire_time_from_database_ and expire_time_.
  void SetExpireTimeFromDatabase(TimePoint expiry_from_db) {
    expire_time_from_database_ = expiry_from_db;
    expire_time_ = expiry_from_db;
  }

  // Getter for expire_time_.
  TimePoint GetExpireTime() const { return expire_time_; }

  // Getter for session state: whether token was created.
  bool SessionState() const { return created_; }

  // Getter for token.
  const std::string &GetToken() const { return token_; }

  // Getter for user_id.
  unsigned int GetUserId() const { return user_id_; }

  // Convenience: start a session with username:
  // generate token, user ID, and set expiry.
  void StartSession(const std::string &username) {
    GenerateUuidV4();
    GenerateUserId(username);
    expire_time_ = CalculateExpiry();
    created_ = true;
  }
};

// Example main to test:
int main() {
  SessionManager session;
  session.StartSession("PlayerOne");

  std::cout << "Token: " << session.GetToken() << "\n";
  std::cout << "User ID: " << session.GetUserId() << "\n";

  TimePoint now = SessionManager::Now();
  std::time_t now_c = std::chrono::system_clock::to_time_t(now);
  std::cout << "Now: " << std::put_time(std::localtime(&now_c), "%F %T")
            << "\n";

  bool expired = session.IsExpired();
  std::cout << "IsExpired immediately after start? " << (expired ? "yes" : "no")
            << "\n";

  return 0;
}
// <newline here>  <- ensure there is exactly one newline at end of file
