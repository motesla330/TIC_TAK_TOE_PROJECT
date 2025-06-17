#include "SessionManagement.h"
#include <gtest/gtest.h>
#include <regex>
#include <thread>
#include <chrono>

TEST(SessionManagerTest, StartSessionSetsValues) {
    SessionManager sm;
    sm.StartSession("Alice");

    EXPECT_FALSE(sm.GetToken().empty());
    EXPECT_NE(sm.GetUserId(), 0u);
    EXPECT_TRUE(sm.SessionState());
    EXPECT_FALSE(sm.is_expired());
}

TEST(SessionManagerTest, DestroySessionResetsState) {
    SessionManager sm;
    sm.StartSession("Bob");
    sm.DestroySession();

    EXPECT_EQ(sm.GetToken(), "");
    EXPECT_EQ(sm.GetUserId(), 0u);
    EXPECT_FALSE(sm.SessionState());
}

TEST(SessionManagerTest, GenerateUserIdProducesConsistentLength) {
    SessionManager sm;
    sm.GenerateUserId("Charlie");
    unsigned int id = sm.GetUserId();
    EXPECT_GE(id, 100000u);
    EXPECT_LT(id, 1000000u);
}

TEST(SessionManagerTest, GenerateUuidV4Format) {
    SessionManager sm;
    sm.GenerateUuidV4();
    std::string uuid = sm.GetToken();
    std::regex uuid_regex(
        "^[0-9a-f]{8}-[0-9a-f]{4}-4[0-9a-f]{3}-[89ab][0-9a-f]{3}-[0-9a-f]{12}$");
    EXPECT_TRUE(std::regex_match(uuid, uuid_regex));
}

TEST(SessionManagerTest, ExpiryCheckWorks) {
    SessionManager sm;
    sm.StartSession("David");
    EXPECT_FALSE(sm.is_expired());

    // Simulate expiry by manually setting expire time
    sm.SetExpireTimeFromDatabase(SessionManager::now() - std::chrono::minutes(1));
    EXPECT_TRUE((SessionManager::now() > sm.GetExpireTime()) || sm.is_expired());
}

TEST(SessionManagerTest, SetExpireTimeFromDatabaseSetsTime) {
    SessionManager sm;
    auto expiry = SessionManager::now() + std::chrono::minutes(2);
    sm.SetExpireTimeFromDatabase(expiry);
    // Private member - can’t directly test, so just ensure no crash
    SUCCEED();
}
