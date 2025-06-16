// copyright 2025 <mahmoudismail>

#include "SessionManagement.hpp"
#include <functional>
#include <random>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>

void SessionManager::GenerateUuidV4() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 15);

  const char* hex_chars = "0123456789abcdef";
  std::stringstream ss;

  for (int i = 0; i < 36; i++) {
    if (i == 8 || i == 13 || i == 18 || i == 23) {
      ss << '-';
    } else if (i == 14) {
      ss << '4';  // UUID v4
    } else if (i == 19) {
      ss << hex_chars[(dis(gen) & 0x3) | 0x8];  // variant bits
    } else {
      ss << hex_chars[dis(gen)];
    }
  }
  token_ = ss.str();
  Created_ = true;
}

void SessionManager::GenerateUserId(const std::string& username) {
  std::string combined = "TicTacToeSalt42_" + username;
  size_t hash = std::hash<std::string>{}(combined);
  unsigned int user_id = static_cast<unsigned int>(hash % 1000000);
  user_id_ = 100000 + (user_id % 900000);  // 6-digit ID
}

TimePoint SessionManager::now() {
  return std::chrono::system_clock::now();
}

TimePoint SessionManager::calculate_expiry() {
  return now() + std::chrono::minutes(5);
}

bool SessionManager::is_expired() const {
  return now() >= ExpireTime;
}

void SessionManager::DestroySession() {
  token_.clear();
  user_id_ = 0;
  Created_ = false;
  ExpireTime = TimePoint{};
  ExpireTime_FromDatabase = TimePoint{};
}

void SessionManager::SetExpireTimeFromDatabase(TimePoint expirFromDB) {
  ExpireTime_FromDatabase = expirFromDB;
}

TimePoint SessionManager::GetExpireTime() const {
  return ExpireTime;
}

bool SessionManager::SessionState() const {
  return Created_;
}

std::string SessionManager::GetToken() const {
  return token_;
}

unsigned int SessionManager::GetUserId() const {
  return user_id_;
}

void SessionManager::StartSession(const std::string& username) {
  GenerateUuidV4();
  GenerateUserId(username);
  ExpireTime = calculate_expiry();
  Created_ = true;
}
