// Copyright [year] <MahmoudIsmail>

#include "Headers/Authentication.h"

#include <openssl/sha.h>

#include <cstdio>      // For snprintf
#include <cstdlib>     // For system()
#include <ctime>       // For time()
#include <chrono>      // For std::chrono
#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <random>      // Used for thread-safe random numbers
#include <string>
#include <thread>      // For std::this_thread::sleep_for

using std::cin;
using std::cout;
using std::endl;
using std::regex;
using std::regex_match;
using std::string;

std::string escapeJsonString(const std::string& input) {
  string output;
  for (char c : input) {
    switch (c) {
      case '"': output += "\\\""; break;
      case '\\': output += "\\\\"; break;
      case '\n': output += "\\n"; break;
      case '\r': output += "\\r"; break;
      case '\t': output += "\\t"; break;
      default: output += c; break;
    }
  }
  return output;
}

Authentication::Authentication() {
  apiKey =
      "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";
}

string Authentication::HashingPassword(const string& PassWord) {
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256(reinterpret_cast<const unsigned char*>(PassWord.c_str()),
         PassWord.length(), hash);

  char hex_output[2 * SHA256_DIGEST_LENGTH + 1];
  for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
    snprintf(hex_output + (i * 2),
    sizeof(hex_output + (i * 2)), "%02x", hash[i]);
  }
  hex_output[2 * SHA256_DIGEST_LENGTH] = '\0';

  return string(hex_output);
}

void Authentication::SignUp(const string& username, const string& password,
                            const string& email) {
  UserName = username;
  PassWord = password;
  HashedPassword = HashingPassword(PassWord);
  Email = email;
}

void Authentication::PushNewAccount(string*& username, string*& hashpassword,
                                    string*& email) {
  username = &UserName;
  hashpassword = &HashedPassword;
  email = &Email;
}

void Authentication::SignIn(const string& username, const string& password) {
  UserName = username;
  PassWord = password;
  HashedPassword = HashingPassword(PassWord);
}

void Authentication::PushSignedInData(string*& username) {
  username = &UserName;
}

void Authentication::IsHereConnect(const string& hashedpassword,
                                   const bool& ishere) {
  IsHere = ishere;
  if (ishere) {
    HashedPasswordFromDatabase = hashedpassword;
  }
}

void Authentication::GetPassword(const string& password) {
  HashedPassword = HashingPassword(password);
}

bool Authentication::IsHereInterface() {
  return IsHere && HashedPassword == HashedPasswordFromDatabase;
}

bool Authentication::FieldsIsValidNew() {
  return !(UserName.empty() || PassWord.empty() || Email.empty());
}

bool Authentication::FieldsIsValidOld() {
  return !(UserName.empty() || PassWord.empty());
}

bool Authentication::UsernameIsValid() {
  return UserName.length() >= 5;
}

bool Authentication::PasswordLongIsValid() {
  return PassWord.length() >= 8;
}

bool Authentication::PasswordComplexityIsValid() {
  bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
  string specials = "!@#$%^&*()-_=+[]{}|;:,.<>?";

  for (char ch : PassWord) {
    if (isupper(ch)) hasUpper = true;
    else if (islower(ch)) hasLower = true;
    else if (isdigit(ch)) hasDigit = true;
    else if (specials.find(ch) != string::npos) hasSpecial = true;
  }

  return hasUpper && hasLower && hasDigit && hasSpecial;
}

bool Authentication::EmailIsValid() {
  regex email_regex(R"(\w+@\w+\.\w+)");
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
  // ✅ Thread-safe random number generator
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1000, 9999);  // 4-digit code
  VerificationCode = dis(gen);

  string fromEmail = "mahmoud.abdallah04@eng-st.cu.edu.eg";
  string toEmail = Email;
  string codeStr = std::to_string(VerificationCode);

  string htmlTemplate = R"html(
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

  size_t pos = htmlTemplate.find("{USERNAME}");
  if (pos != string::npos) {
    htmlTemplate.replace(pos, 10, UserName);
  }
  pos = htmlTemplate.find("{VERIFICATION_CODE}");
  if (pos != string::npos) {
    htmlTemplate.replace(pos, 19, codeStr);
  }

  string escapedHtmlContent = escapeJsonString(htmlTemplate);

  string jsonPayload =
      "{\n"
      "  \"personalizations\": [\n"
      "    {\n"
      "      \"to\": [\n"
      "        {\"email\": \"" +
      toEmail +
      "\"}\n"
      "      ]\n"
      "    }\n"
      "  ],\n"
      "  \"from\": {\"email\": \"" +
      fromEmail +
      "\"},\n"
      "  \"subject\": \"New Account Verification Code\",\n"
      "  \"content\": [\n"
      "    {\n"
      "      \"type\": \"text/html\",\n"
      "      \"value\": \"" +
      escapedHtmlContent +
      "\"\n"
      "    }\n"
      "  ]\n"
      "}";

  std::ofstream outFile("payload.json");
  if (!outFile.is_open()) {
    std::cerr << "Error: Could not open payload.json for writing.\n";
    return;
  }
  outFile << jsonPayload;
  outFile.close();

  string cmd =
      "curl -s -X POST https://api.sendgrid.com/v3/mail/send "
      "-H \"Authorization: Bearer " +
      apiKey +
      "\" -H \"Content-Type: application/json\" --data-binary @payload.json";

  cout << "Sending email...\n";
  int result = system(cmd.c_str());

  if (result == 0) {
    cout << "Email sent successfully!\n";
  } else {
    cout << "Failed to send email. Check API key and payload. Exit code: "
         << result << "\n";
  }
}

bool Authentication::IsVerificationCodeValid(const int& inputCode) {
  return inputCode == VerificationCode;
}

void Authentication::GetUsernameEmail(const string& username,
                                      const string& email) {
  UserName = username;
  Email = email;
}

void Authentication::PushUsername(string*& username, string*& email) {
  username = &UserName;
  email = &Email;
}

bool Authentication::VerCodeNewPassword(const bool& ishere) {
  if (ishere) {
    VerificationMail();
    return true;
  }
  return false;
}

void Authentication::PasswordReset(const string& newpassword,
                                   const bool& correctcode) {
  if (correctcode) {
    PassWord = newpassword;
    HashedPassword = HashingPassword(PassWord);
  } else {
    cout << "Operation ended without any changes" << endl;
  }
}

void Authentication::PushNewPassword(string*& newHashedpassword,
                                     string*& username) {
  newHashedpassword = &HashedPassword;
  username = &UserName;
}
