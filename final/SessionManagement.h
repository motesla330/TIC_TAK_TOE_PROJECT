// Copyright 2025 <MahmoudIsmail>

#ifndef SESSION_MANAGER_HPP
#define SESSION_MANAGER_HPP

#include <chrono>
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
  void GenerateUuidV4();
  void GenerateUserId(const std::string& username);
  static TimePoint now();
  static TimePoint calculate_expiry();
  bool is_expired() const;
  void DestroySession();
  void SetExpireTimeFromDatabase(TimePoint expirFromDB);
  TimePoint GetExpireTime() const;
  bool SessionState() const;
  std::string GetToken() const;
  unsigned int GetUserId() const;
  void StartSession(const std::string& username);
};

#endif
