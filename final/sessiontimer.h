// Copyright 2025 MahmoudIsmail

#ifndef FINAL_SESSIONTIMER_H_
#define FINAL_SESSIONTIMER_H_

#include <QObject>
#include <QTimer>
#include <chrono>

// Use chrono time_point for tracking expected timeout time
using TimePoint = std::chrono::system_clock::time_point;

class SessionTimer : public QObject {
Q_OBJECT

 public:
  static SessionTimer& instance();               // Access singleton instance
  void start();                                  // Start with default 1 min
  void reset();                                  // Reset using last timeout
  void updateTimeout(int milliseconds);          // Change timeout + restart
  void stop();                                   // Stop the timer
  int currentTimeout() const;                    // Return current timeout in ms
  TimePoint timeoutAt() const;                   // Return when session expires

 signals:
  void sessionExpired();                         // Connect to logout handler

 private:
  SessionTimer();                                // Private constructor
  QTimer* timer_;                                // Internal Qt timer
  int timeoutMs_;                                // Timeout duration in ms
};

#endif  // FINAL_SESSIONTIMER_H_
