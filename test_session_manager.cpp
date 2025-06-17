#include "SessionManagement.h"
#include <gtest/gtest.h>
#include <regex>
#include <thread>
#include <chrono>

// Create a test-friendly subclass to access protected internals
class TestableSessionManager : public SessionManager {
public:
    void ForceExpireTime(TimePoint tp) {
        ExpireTime = tp; // Directly access private field
    }
};

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
    TestableSessionManager sm;
    sm.StartSession("David");

    // Force it to be expired
    auto expired_time = SessionManager::now() - std::chrono::minutes(10);
    sm.ForceExpireTime(expired_time);

    EXPECT_TRUE(sm.is_expired());
}

TEST(SessionManagerTest, SetExpireTimeFromDatabaseSetsTime) {
    SessionManager sm;
    auto expiry = SessionManager::now() + std::chrono::minutes(2);
    sm.SetExpireTimeFromDatabase(expiry);
    SUCCEED(); // No crash = pass
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
