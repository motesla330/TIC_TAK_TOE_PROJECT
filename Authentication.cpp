#include <iostream>
#include <string>
#include <openssl/sha.h>
#include <regex>
#include <fstream>
#include <cstdlib> // For system()
#include <ctime>   // For time()
#include <iomanip> // For std::quoted if needed, though manual escaping is done here
#include <chrono>  // For std::chrono::seconds, minutes
#include <thread> // For std::this_thread::sleep_for

using namespace std;

string escapeJsonString(const std::string& input) {
    string output;
    for (char c : input) {
        if (c == '"') {
            output += "\\\"";
        } else if (c == '\\') {
            output += "\\\\";
        } else if (c == '\n') {
            output += "\\n";
        } else if (c == '\r') {
            output += "\\r";
        } else if (c == '\t') {
            output += "\\t";
        } else {
            output += c;
        }
    }
    return output;
}


class Authentication {
private:
    string UserName;
    string PassWord;
    string HashedPassword;
    string Email;
    int VerificationCode;
    string HashedPasswordFromDatabase;
    bool IsHere = false;
    string apiKey = "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";

public:

//Hashing password using openssl
    string HashingPassword(const string &PassWord) {

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(reinterpret_cast<const unsigned char*>(PassWord.c_str()), PassWord.length(), hash);

        char hex_output[2 * SHA256_DIGEST_LENGTH + 1];
        for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
            sprintf(hex_output + (i * 2), "%02x", hash[i]);
        }
        hex_output[2 * SHA256_DIGEST_LENGTH] = '\0';  // null-terminate the string

        return string(hex_output);
    }

//get data from the user
    void SignUp (const string &username, const string &password, const string &email) {
        UserName = username;
        PassWord = password;
        HashedPassword = HashingPassword(PassWord);
        Email = email;
    }

//push data to the database
    void PushNewAccount (string* &username , string* &hashpassword, string* &email) {
        username = &UserName;
        hashpassword = &HashedPassword;
        email = &Email;
    }

//Sign in with username and password
    void SignIn (const string &username, const string &password) {
        UserName = username;
        PassWord = password;
        HashedPassword = HashingPassword(PassWord);
    }

//push signed in data to the database
    void PushSignedInData (string* &username , string* &hashpassword) {
        username = &UserName;
        hashpassword = &HashedPassword;
    }

//Makes sure that the user has an account
    void IsHereConnect (const string &hashedpassword , const bool &ishere) {
        if (ishere) {
            HashedPasswordFromDatabase = hashedpassword;
            IsHere = true;
        }
        else {
            IsHere = false;
        }
    }

//for wrong password entered
    void GetPassword (const string &password) {
        HashedPassword = HashingPassword(password);
    }

//to ensure that the password entered is correct
    bool IsHereInterface () {
        if (IsHere) {
            if (HashedPassword == HashedPasswordFromDatabase) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }

    bool FieldsIsValid () {
        if (UserName.empty() || PassWord.empty() || Email.empty()) {
            return false;
        }
        return true;
    }

    bool UsernameIsValid () {
        if (UserName.length() < 5) {
            return false;
        }
        return true;
    }

    bool PasswordLongIsValid () {
        if (PassWord.length() < 8) {
            return false;
        }
        return true;
    }

    bool PasswordComplexityIsValid () {
        bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
        string specials = "!@#$%^&*()-_=+[]{}|;:,.<>?";
        for (char ch : PassWord) {
            if (isupper(ch)) hasUpper = true;
            else if (islower(ch)) hasLower = true;
            else if (isdigit(ch)) hasDigit = true;
            else if (specials.find(ch) != std::string::npos) hasSpecial = true;
        }
        return hasUpper && hasLower && hasDigit && hasSpecial;
    }

    bool EmailIsValid () {
        regex email_regex(R"(\w+@\w+\.\w+)");
        return regex_match (Email, email_regex);
    }

//all fields are valid for sign in
    void IsValidForSignUP () {
        while (!FieldsIsValid()) {
            cout << "All fields are required." << endl;
            cout << "Enter username: ";
            cin >> UserName;
            cout << "Enter password: ";
            cin >> PassWord;
            cout << "Enter email: ";
            cin >> Email;
        }
        while (!UsernameIsValid()) {
            cout << "Username is too short, try another one" << endl;
            cin >> UserName;
        }
        while (!PasswordLongIsValid()) {
            cout << "Password must be at least 8 characters long." << endl;
            cin >> PassWord;
        }
        while (!PasswordComplexityIsValid()) {
            cout << "Password must contain at least one uppercase letter, one lowercase letter, one digit, and one special character." << endl;
            cin >> PassWord;
        }
        while (!EmailIsValid()) {
            cout << "Invalid email format. Please enter a valid email: " << endl;
            cin >> Email;
        }

        cout << "All fields are valid!" << endl;
    }

//all fields are valid for sign in
    void IsValidForSignIn () {
        while (!FieldsIsValid()) {
            cout << "All fields are required." << endl;
            cout << "Enter username: ";
            cin >> UserName;
            cout << "Enter password: ";
            cin >> PassWord;
        }
        while (!UsernameIsValid()) {
            cout << "Username is too short, try another one" << endl;
            cin >> UserName;
        }
        while (!PasswordLongIsValid()) {
            cout << "Password must be at least 8 characters long." << endl;
            cin >> PassWord;
        }
        cout << "All fields are valid!" << endl;
    }

//Verification Code : sending the verification mail
    void VerificationMail () {
        srand(time(0));
        VerificationCode = rand() % 10000; // Generate and store the code
        string fromEmail = "mahmoud.abdallah04@eng-st.cu.edu.eg";
        string toEmail = Email; // Use the email provided by the user
        string codeStr = std::to_string(VerificationCode);

        // Your HTML content with placeholders
        std::string htmlContentTemplate = R"html(
        <!DOCTYPE html>
        <html>
        <body style="font-family: Verdana, sans-serif; background: #fafafa; padding: 20px;">
            <div style="max-width: 600px; margin: auto; background: #ffffff; border: 1px solid #ddd; border-radius: 6px;">
            <div style="background: #007acc; color: #fff; padding: 12px; text-align: center;">
                <h2 style="margin:0;">YourAppName Email Verification</h2>
            </div>
            <div style="padding: 20px; color: #333;">
                <p>Hey <span style="color: #007acc;"><strong>{USERNAME}</strong></span>,</p>
                <p>Here’s your one‑time verification code:</p>
                <p style="text-align:center; margin: 20px 0;">
                <code style="display:inline-block; background:#f0f0f0; padding:10px 16px; font-size:18px; color:#d32f2f; border-radius:4px;">
                    {VERIFICATION_CODE}
                </code>
                </p>
                <p>If you didn’t ask for this, ignore it.</p>
            </div>
            </div>
        </body>
        </html>
        )html";

        // Replace placeholders in the HTML content
        size_t pos = htmlContentTemplate.find("{USERNAME}");
        if (pos != std::string::npos) {
            htmlContentTemplate.replace(pos, std::string("{USERNAME}").length(), UserName);
        }
        pos = htmlContentTemplate.find("{VERIFICATION_CODE}");
        if (pos != std::string::npos) {
                htmlContentTemplate.replace(pos, std::string("{VERIFICATION_CODE}").length(), codeStr);
        }

        // Escape the HTML content for JSON
        std::string escapedHtmlContent = escapeJsonString(htmlContentTemplate);

        // Build JSON payload
        std::string jsonPayload =
            "{\n"
            "  \"personalizations\": [\n"
            "    {\n"
            "      \"to\": [\n"
            "        {\"email\": \"" + toEmail + "\"}\n"
            "      ]\n"
            "    }\n"
            "  ],\n"
            "  \"from\": {\"email\": \"" + fromEmail + "\"},\n"
            "  \"subject\": \"New Account Verification Code\",\n"
            "  \"content\": [\n"
            "    {\n"
            "      \"type\": \"text/html\",\n"
            "      \"value\": \"" + escapedHtmlContent + "\"\n"
            "    }\n"
            "  ]\n"
            "}";

        // Write JSON to temporary file
        std::ofstream outFile("payload.json");
        if (!outFile.is_open()) {
            std::cerr << "Error: Could not open payload.json for writing.\n";
            return;
        }
        outFile << jsonPayload;
        outFile.close();

        // Build cURL command
        std::string cmd = "curl -s -X POST https://api.sendgrid.com/v3/mail/send "
                        "-H \"Authorization: Bearer " + apiKey + "\" "
                        "-H \"Content-Type: application/json\" "
                        "--data-binary @payload.json";

        std::cout << "Sending email...\n";
        int result = system(cmd.c_str());

        if (result == 0) {
            cout << "Email sent successfully!\n";
        } else {
            cout << "Failed to send email. Check API key and payload. cURL exit code: " << result << "\n";
        }
    }

//Verification Code : Getting the verification code and make sure that is equal the sent one
    bool IsVerificationCodeValid(const int &inputCode) {
        return inputCode == VerificationCode;
    }

//Password Reset : Getting username and email, for verification
    void GetUsernameEmail (const string &username , const string &email) {
        UserName = username;
        Email = email;
    }

//Password Reset : pass username & email to the database for verification
    void PushUsername (string* &username , string* &email) {
        username = &UserName;
        email = &Email;
    }

//Password Reset : Verification code via email
    bool VerCodeNewPassword (const bool &ishere) {
        if (ishere) {
            VerificationMail();
            return true;
        }
        else {
            return false;
        }
    }

//password Reset : Take the new password
    void PasswordReset (const string &newpassword , const bool &correctcode) {
        if (correctcode == true) {
            PassWord = newpassword;
            HashedPassword = HashingPassword(PassWord);
        }
        else {
            cout << "Operation ended without any changes"<<endl;
        }
    }

//password Reset : Push to the database
    void PushNewPassword (string* &newHashedpassword , string* &username) {
        newHashedpassword = &HashedPassword;
        username = &UserName;
    }

};

///g++ Authentication.cpp -o Auth.exe