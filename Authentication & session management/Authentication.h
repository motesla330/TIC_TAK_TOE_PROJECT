// Copyright [year] <MahmoudIsmail>

#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <string>

class Authentication {
private:
  std::string UserName;
  std::string PassWord;
  std::string HashedPassword;
  std::string Email;
  int VerificationCode;
  std::string HashedPasswordFromDatabase;
  bool IsHere = false;
  std::string apiKey;

public:
  // Constructor
  Authentication();

  // Hashing password using openssl
  std::string HashingPassword(const std::string &PassWord);

  // get data from the user
  void SignUp(const std::string &username, const std::string &password,
              const std::string &email);

  // push data to the database
  void PushNewAccount(std::string *&username, std::string *&hashpassword,
                      std::string *&email);

  // Sign in with username and password
  void SignIn(const std::string &username, const std::string &password);

  // push signed in data to the database
  void PushSignedInData(std::string *&username);

  // Makes sure that the user has an account
  void IsHereConnect(const std::string &hashedpassword, const bool &ishere);

  // for wrong password entered
  void GetPassword(const std::string &password);

  // to ensure that the password entered is correct
  bool IsHereInterface();

  // Validation methods
  bool FieldsIsValidNew();
  bool FieldsIsValidOld();
  bool UsernameIsValid();
  bool PasswordLongIsValid();
  bool PasswordComplexityIsValid();
  bool EmailIsValid();

  // all fields are valid for sign up
  void IsValidForSignUP();

  // all fields are valid for sign in
  void IsValidForSignIn();

  // Verification Code : sending the verification mail
  void VerificationMail();

  // Verification Code : Getting the verification code and make sure that is
  // equal the sent one
  bool IsVerificationCodeValid(const int &inputCode);

  // Password Reset : Getting username and email, for verification
  void GetUsernameEmail(const std::string &username, const std::string &email);

  // Password Reset : pass username & email to the database for verification
  void PushUsername(std::string *&username, std::string *&email);

  // Password Reset : Verification code via email
  bool VerCodeNewPassword(const bool &ishere);

  // password Reset : Take the new password
  void PasswordReset(const std::string &newpassword, const bool &correctcode);

  // password Reset : Push to the database
  void PushNewPassword(std::string *&newHashedpassword, std::string *&username);
};

// Utility function for JSON string escaping
std::string escapeJsonString(const std::string &input);

#endif // AUTHENTICATION_H