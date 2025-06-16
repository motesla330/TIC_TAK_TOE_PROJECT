// session_manager_test.cpp
// Copyright 2025 <MahmoudIsmail>
#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>

using TimePoint = std::chrono::system_clock::time_point;

class SessionManager {
 private:
  std::string token_;
  unsigned int user_id_ = 0;
  TimePoint ExpireTime{};
  TimePoint ExpireTime_FromDatabase{};
  bool Created_ = false;

 public:
  // Generate a random UUIDv4-like token string: 36 chars with hyphens
  void GenerateUuidV4() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 15);

    const char *hex_chars = "0123456789abcdef";
    std::stringstream ss;

    for (int i = 0; i < 36; i++) {
      if (i == 8 || i == 13 || i == 18 || i == 23) {
        ss << '-';
      } else if (i == 14) {
        // UUID version 4
        ss << '4';
      } else if (i == 19) {
        // variant: two most significant bits = 10
        ss << hex_chars[(dis(gen) & 0x3) | 0x8];
      } else {
        ss << hex_chars[dis(gen)];
      }
    }
    token_ = ss.str();
    Created_ = true;
  }

  // Generate a pseudo user ID based on username, salted+hashed
  void GenerateUserId(const std::string &username) {
    std::string combined = "TicTacToeSalt42_" + username;
    size_t hash = std::hash<std::string>{}(combined);
    unsigned int user_id = static_cast<unsigned int>(hash % 1000000);
    // Ensure 6-digit-ish ID between 100000 and 999999
    user_id_ = 100000 + (user_id % 900000);
  }

  // Get current time point
  static TimePoint now() { return std::chrono::system_clock::now(); }

  // Compute expiry: now + 5 minutes
  static TimePoint calculate_expiry() {
    return now() + std::chrono::minutes(5);
  }

  // Check if expired: now >= ExpireTime
  bool is_expired() const {
    // If ExpireTime was never set, ExpireTime is epoch (time_point{}), so
    // likely immediately expired.
    return now() >= ExpireTime;
  }

  // Destroy session: clear token and user_id, mark Created_ false, clear
  // ExpireTime
  void DestroySession() {
    token_.clear();
    user_id_ = 0;
    Created_ = false;
    ExpireTime = TimePoint{};  // epoch
    ExpireTime_FromDatabase = TimePoint{};
  }

  // Load expiry from “database”: store both ExpireTime_FromDatabase and
  // ExpireTime
  void SetExpireTimeFromDatabase(TimePoint expirFromDB) {
    ExpireTime_FromDatabase = expirFromDB;
  }

  // Getter for ExpireTime
  TimePoint GetExpireTime() const { return ExpireTime; }

  // Getter for session state: whether token was created
  bool SessionState() const { return Created_; }

  // Getter for token
  std::string GetToken() const { return token_; }

  // Getter for user_id
  unsigned int GetUserId() const { return user_id_; }

  // Convenience: start a session with username: generate token, user ID, and
  // set expiry
  void StartSession(const std::string &username) {
    GenerateUuidV4();
    GenerateUserId(username);
    ExpireTime = calculate_expiry();
    Created_ = true;
  }
};
