// Copyright 2025 <MahmoudIsmail>

#include "Authentication.h"

#include <openssl/sha.h>
#include <QDialog>
#include <QMessageBox>

#include <cstdio>      // For snprintf
#include <cstdlib>     // For system()
#include <ctime>       // For time()

#include <chrono>      // For std::chrono
#include <fstream>
#include <iomanip>     // For std::quoted if needed
#include <iostream>
#include <random>      // For thread-safe random
#include <regex>
#include <string>
#include <thread>      // For std::this_thread::sleep_for



using std::cin;
using std::cout;
using std::endl;
using std::regex;
using std::regex_match;
using std::string;

// Helper: thread-safe verification code generator
static int generateVerificationCode() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1000, 9999);  // 4-digit code
  return dis(gen);
}

std::string escapeJsonString(const std::string &input) {
  string output;
  for (char c : input) {
    if (c == '\"') {
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

Authentication::Authentication() {
  // Constructor: API key can be set via environment or secure store
  // Example:
  // const char* key = std::getenv("SENDGRID_API_KEY");
  // if (key) { apiKey = std::string(key); }
}

string Authentication::HashingPassword(const string &PassWord) {
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256(reinterpret_cast<const unsigned char *>(PassWord.c_str()),
         PassWord.length(), hash);

  char hex_output[2 * SHA256_DIGEST_LENGTH + 1];
  for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
    std::snprintf(hex_output + (i * 2),
                  sizeof(hex_output) - (i * 2),
                  "%02x", hash[i]);
  }
  hex_output[2 * SHA256_DIGEST_LENGTH] = '\0';  // null-terminate

  return string(hex_output);
}

void Authentication::SignUp(const string &username,
                            const string &password,
                            const string &email) {
  UserName = username;
  PassWord = password;
  HashedPassword = HashingPassword(PassWord);
  Email = email;
}

void Authentication::PushNewAccount(string *&username,
                                    string *&hashpassword,
                                    string *&email) {
  username = &UserName;
  hashpassword = &HashedPassword;
  email = &Email;
}

void Authentication::SignIn(const string &username,
                            const string &password) {
  UserName = username;
  PassWord = password;
  HashedPassword = HashingPassword(PassWord);
}

void Authentication::PushSignedInData(string *&username) {
  username = &UserName;
}

void Authentication::IsHereConnect(const string &hashedpassword,
                                   const bool &ishere) {
  IsHere = ishere;
  if (IsHere) {
    HashedPasswordFromDatabase = hashedpassword;
  }
}

void Authentication::GetPassword(const string &password) {
  HashedPassword = HashingPassword(password);
}

bool Authentication::IsHereInterface() const {
  return IsHere && HashedPassword == HashedPasswordFromDatabase;
}

bool Authentication::FieldsIsValidNew() const {
  return !(UserName.empty() || PassWord.empty() || Email.empty());
}

bool Authentication::FieldsIsValidOld() const {
  return !(UserName.empty() || PassWord.empty());
}

bool Authentication::UsernameIsValid() const {
  return UserName.length() >= 5;
}

bool Authentication::PasswordLongIsValid() const {
  return PassWord.length() >= 8;
}

bool Authentication::PasswordComplexityIsValid() const {
  bool hasUpper = false;
  bool hasLower = false;
  bool hasDigit = false;
  bool hasSpecial = false;
  string specials = "!@#$%^&*()-_=+[]{}|;:,.<>?";
  for (char ch : PassWord) {
    if (std::isupper(static_cast<unsigned char>(ch))) {
      hasUpper = true;
    } else if (std::islower(static_cast<unsigned char>(ch))) {
      hasLower = true;
    } else if (std::isdigit(static_cast<unsigned char>(ch))) {
      hasDigit = true;
    } else if (specials.find(ch) != string::npos) {
      hasSpecial = true;
    }
  }
  return hasUpper && hasLower && hasDigit && hasSpecial;
}

bool Authentication::EmailIsValid() const {
  regex email_regex(R"(\\w+@\\w+\\.\\w+)");
  return regex_match(Email, email_regex);
}

void Authentication::IsValidForSignUP() {
  while (!FieldsIsValidNew()) {
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
    cout << "Password must contain at least one uppercase letter, one "
            "lowercase letter, one digit, and one special character."
         << endl;
    cin >> PassWord;
  }
  while (!EmailIsValid()) {
    cout << "Invalid email format. Please enter a valid email: " << endl;
    cin >> Email;
  }
  cout << "All fields are valid!" << endl;
}

void Authentication::IsValidForSignIn() {
  while (!FieldsIsValidOld()) {
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

void Authentication::VerificationMail() {
  VerificationCode = generateVerificationCode();  // Thread-safe random
  string fromEmail = "mahmoud.abdallah04@eng-st.cu.edu.eg";
  string toEmail = Email;
  string codeStr = std::to_string(VerificationCode);

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
              <p>Here's your one‑time verification code:</p>
              <p style="text-align:center; margin: 20px 0;">
              <code style="display:inline-block; background:#f0f0f0; padding:10px 16px; font-size:18px; color:#d32f2f; border-radius:4px;">
                  {VERIFICATION_CODE}
              </code>
              </p>
              <p>If you didn't ask for this, ignore it.</p>
          </div>
          </div>
      </body>
      </html>
      )html";

  size_t pos = htmlContentTemplate.find("{USERNAME}");
  if (pos != string::npos) {
    htmlContentTemplate.replace(pos, 10, UserName);
  }
  pos = htmlContentTemplate.find("{VERIFICATION_CODE}");
  if (pos != string::npos) {
    htmlContentTemplate.replace(pos, 19, codeStr);
  }

  string escapedHtmlContent = escapeJsonString(htmlContentTemplate);

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

  std::ofstream outFile("payload.json");
  if (!outFile.is_open()) {
    std::cerr << "Error: Could not open payload.json for writing." << endl;
    return;
  }
  outFile << jsonPayload;
  outFile.close();

  std::string cmd =
      "curl -s --tlsv1.3 --connect-timeout 30 "
      "-X POST https://api.sendgrid.com/v3/mail/send "
      "-H \"Authorization: Bearer " + apiKey + "\" "
      "-H \"Content-Type: application/json\" "
      "--data-binary @payload.json";
  cout << "Sending email..." << endl;
  int result = system(cmd.c_str());

  if (result == 0) {
    cout << "Email sent successfully!" << endl;
  } else {
    cout << "Failed to send email. Check API key and payload. cURL exit code: "
         << result << endl;
  }
}

bool Authentication::IsVerificationCodeValid(const int &inputCode) const {
  return inputCode == VerificationCode;
}

void Authentication::GetUsernameEmail(const string &username,
                                      const string &email) {
  UserName = username;
  Email = email;
}

void Authentication::PushUsername(string *&username, string *&email) {
  username = &UserName;
  email = &Email;
}

bool Authentication::VerCodeNewPassword(const bool &ishere) {
  if (ishere) {
    VerificationMail();
    return true;
  }
  return false;
}

void Authentication::PasswordReset(const string &newpassword,
                                   const bool &correctcode) {
  if (correctcode) {
    PassWord = newpassword;
    HashedPassword = HashingPassword(PassWord);
  } else {
    cout << "Operation ended without any changes" << endl;
  }
}

void Authentication::PushNewPassword(string *&newHashedpassword,
                                     string *&username) {
  newHashedpassword = &HashedPassword;
  username = &UserName;
}
