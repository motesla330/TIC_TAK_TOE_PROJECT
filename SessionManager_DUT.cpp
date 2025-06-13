#include <iostream>
#include <string>
#include <random>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <unordered_map>

using namespace std;

class SessionManager {

private:
    string Token;
    unsigned int UserId;
    chrono::system_clock::time_point Now;
    chrono::system_clock::time_point Expiry;
    chrono::system_clock::time_point LastActivity;
    bool RemeberMe;

public:

    void generate_uuid_v4() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, 15);

        const char* hex_chars = "0123456789abcdef";
        stringstream ss;
        
        // Format: xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx
        for (int i = 0; i < 36; i++) {
            if (i == 8 || i == 13 || i == 18 || i == 23) {
                ss << '-';
            } else if (i == 14) {
                ss << '4';  // UUID version 4
            } else if (i == 19) {
                ss << hex_chars[dis(gen) & 0x3 | 0x8];  // Variant 10xx
            } else {
                ss << hex_chars[dis(gen)];
            }
        }
        Token = ss.str();
    }
    
    void generate_user_id(const string& username) {
        // Combine credentials with a game-specific salt
        string combined = "TicTacToeSalt42_" + username;
        
        // Use std::hash to create a consistent numeric ID
        size_t hash = std::hash<std::string>{}(combined);
        
        // Convert to a positive integer in a reasonable range
        unsigned int user_id = static_cast<unsigned int>(hash % 1000000);
        
        // Ensure ID is at least 6 digits for display purposes
        UserId = 100000 + (user_id % 900000);
    }

    //get time now
    static chrono::system_clock::time_point now() {
        return chrono::system_clock::now();
    }

    //converts time to readable form
    static string time_to_string (const chrono::system_clock::time_point& tp) {
        auto in_time_t = std::chrono::system_clock::to_time_t(tp);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
        return ss.str();
    }

    template<typename Duration>
    static chrono::system_clock::time_point add_time (
        const chrono::system_clock::time_point& tp,
        Duration duration) {
        return tp + duration;
    }
    void print_session_data() const {
        cout << "Token: " << Token << endl;
        cout << "User ID: " << UserId << endl;
    }

};

int main() {
    SessionManager session;

    string username = "TestUser";
    session.generate_uuid_v4();
    session.generate_user_id(username);

    auto current_time = SessionManager::now();
    auto future_time = SessionManager::add_time(current_time, chrono::hours(1));

    cout << "Current time: " << SessionManager::time_to_string(current_time) << endl;
    cout << "Time after 1 hour: " << SessionManager::time_to_string(future_time) << endl;

    session.print_session_data();

    return 0;
}


//g++ SessionManager_DUT.cpp -o session_Manager.exe
//.\session_Manager.exe