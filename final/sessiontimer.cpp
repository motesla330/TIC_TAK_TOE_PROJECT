#include "SessionTimer.h"

SessionTimer::SessionTimer()
    : timeoutMs_(60000) // Default timeout: 1 minute = 60000 ms
{
    timer_ = new QTimer(this);
    timer_->setSingleShot(true); // Fire only once
    connect(timer_, &QTimer::timeout, this, &SessionTimer::sessionExpired);
}

SessionTimer& SessionTimer::instance() {
    static SessionTimer instance;
    return instance;
}

void SessionTimer::start() {
    timer_->start(timeoutMs_); // Start with current timeout
}

void SessionTimer::reset() {
    if (timer_->isActive()) {
        timer_->stop(); // Restart timer cleanly
    }
    timer_->start(timeoutMs_);
}

void SessionTimer::updateTimeout(int milliseconds) {
    timeoutMs_ = milliseconds;
    reset();
}

void SessionTimer::stop() {
    timer_->stop();
}

int SessionTimer::currentTimeout() const {
    return timeoutMs_;
}

TimePoint SessionTimer::timeoutAt() const {
    return std::chrono::system_clock::now() + std::chrono::milliseconds(timeoutMs_);
}
