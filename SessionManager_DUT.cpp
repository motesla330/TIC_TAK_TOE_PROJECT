// Copyright [year] <MahmoudIsmail>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <optional>
#include <random>
#include <sstream>
#include <string>
#include <unordered_map>

class SessionManager {
 private:
  std::string token_;
  unsigned int user_id_;
  std::chrono::system_clock::time_point now_;
  std::chrono::system_clock::time_point expiry_;
  std::chrono::system_clock::time_point last_activity_;
  bool remember_me_;

 public:
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
        ss << '4';
      } else if (i == 19) {
        ss << hex_chars[(dis(gen) & 0x3) | 0x8];
      } else {
        ss << hex_chars[dis(gen)];
      }
    }
    token_ = ss.str();
  }

  void GenerateUserId(const std::string &username) {
    std::string combined = "TicTacToeSalt42_" + username;
    size_t hash = std::hash<std::string>{}(combined);
    unsigned int user_id = static_cast<unsigned int>(hash % 1000000);
    user_id_ = 100000 + (user_id % 900000);
  }

  static std::chrono::system_clock::time_point Now() {
    return std::chrono::system_clock::now();
  }

  static std::string
  TimeToString(const std::chrono::system_clock::time_point &tp) {
    auto in_time_t = std::chrono::system_clock::to_time_t(tp);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
  }

  template <typename Duration>
  static std::chrono::system_clock::time_point
  AddTime(const std::chrono::system_clock::time_point &tp, Duration duration) {
    return tp + duration;
  }

  void PrintSessionData() const {
    std::cout << "Token: " << token_ << std::endl;
    std::cout << "User ID: " << user_id_ << std::endl;
  }

  std::optional<std::chrono::minutes>
  CheckExpiration(const std::chrono::system_clock::time_point &reference_time,
                  bool update_time) {
    std::chrono::system_clock::time_point current_time;

    if (update_time) {
      current_time = reference_time;
    } else {
      current_time = std::chrono::system_clock::now();
    }

    auto expiry_time = reference_time + std::chrono::minutes(30);

    if (current_time >= expiry_time) {
      return std::nullopt;
    }

    return std::chrono::duration_cast<std::chrono::minutes>(expiry_time -
                                                            current_time);
  }
};

int main() {
  SessionManager session;

  session.GenerateUuidV4();
  session.GenerateUserId("PlayerOne");

  session.PrintSessionData();

  auto now = SessionManager::Now();
  std::cout << "Now: " << SessionManager::TimeToString(now) << std::endl;

  auto simulated_future =
      SessionManager::AddTime(now, std::chrono::minutes(10));
  auto result1 = session.CheckExpiration(simulated_future, true);
  std::cout << "[Simulated Future (+10 min), updateTime = true] -> ";
  if (result1) {
    std::cout << "Session valid. Time left: " << result1.value().count()
              << " minutes\n";
  } else {
    std::cout << "Session expired.\n";
  }

  auto result2 = session.CheckExpiration(now, false);
  std::cout << "[System Time, updateTime = false] -> ";
  if (result2) {
    std::cout << "Session valid. Time left: " << result2.value().count()
              << " minutes\n";
  } else {
    std::cout << "Session expired.\n";
  }

  auto past_time = SessionManager::AddTime(now, -std::chrono::minutes(31));
  auto result3 = session.CheckExpiration(past_time, true);
  std::cout << "[Past (-31 min), updateTime = true] -> ";
  if (result3) {
    std::cout << "Session valid. Time left: " << result3.value().count()
              << " minutes\n";
  } else {
    std::cout << "Session expired.\n";
  }

  return 0;
}
