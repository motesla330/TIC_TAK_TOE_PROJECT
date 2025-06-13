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

    const char* hex_chars = "0123456789abcdef";
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

  void GenerateUserId(const std::string& username) {
    std::string combined = "TicTacToeSalt42_" + username;
    size_t hash = std::hash<std::string>{}(combined);
    unsigned int user_id = static_cast<unsigned int>(hash % 1000000);
    user_id_ = 100000 + (user_id % 900000);
  }

  static std::chrono::system_clock::time_point Now() {
    return std::chrono::system_clock::now();
  }

  static std::string TimeToString(
      const std::chrono::system_clock::time_point& tp) {
    auto in_time_t = std::chrono::system_clock::to_time_t(tp);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
  }

  template <typename Duration>
  static std::chrono::system_clock::time_point AddTime(
      const std::chrono::system_clock::time_point& tp, Duration duration) {
    return tp + duration;
  }

  void PrintSessionData() const {
    std::cout << "Token: " << token_ << std::endl;
    std::cout << "User ID: " << user_id_ << std::endl;
  }

  std::optional<std::chrono::minutes> CheckExpiration(
      const std::chrono::system_clock::time_point& expiry_time) {
    auto now = std::chrono::system_clock::now();

    if (now >= expiry_time) {
      return std::nullopt;
    }

    return std::chrono::duration_cast<std::chrono::minutes>(expiry_time - now);
  }
};

int main() {
  SessionManager session;

  std::string username = "PlayerOne";
  session.GenerateUuidV4();
  session.GenerateUserId(username);

  auto now = SessionManager::Now();
  std::cout << "Current Time: " << SessionManager::TimeToString(now)
            << std::endl;

  auto expiry = SessionManager::AddTime(now, std::chrono::minutes(10));
  std::cout << "Session Expiry Time: " << SessionManager::TimeToString(expiry)
            << std::endl;

  session.PrintSessionData();

  auto time_left = session.CheckExpiration(expiry);
  if (time_left) {
    std::cout << "Session is valid. Time until expiration: "
              << time_left.value().count() << " minute(s)" << std::endl;
  } else {
    std::cout << "Session expired." << std::endl;
  }

  auto past_time = SessionManager::AddTime(now, std::chrono::minutes(-5));
  auto expired_check = session.CheckExpiration(past_time);
  if (expired_check) {
    std::cout << "Time until expiration (should not happen): "
              << expired_check.value().count() << " minute(s)" << std::endl;
  } else {
    std::cout << "Correctly detected expired session (past time)."
              << std::endl;
  }

  return 0;
}






//g++ SessionManager_DUT.cpp -o session_Manager.exe
//.\session_Manager.exe