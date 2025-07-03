// Copyright [year] <MahmoudIsmail>

#ifndef AUTHENTICATION_H_
#define AUTHENTICATION_H_

#include <string>

class Authentication {
 private:
  std::string PassWord;
  std::string HashedPassword;
  std::string Email;
  int VerificationCode;
  std::string HashedPasswordFromDatabase;
  bool IsHere = false;
  std::string apiKey =
      "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";
  int generateVerificationCode();  // from tesla

 public:
  // Constructor
  Authentication();
  std::string UserName;

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
  bool IsHereInterface() const;

  // Validation methods
  bool FieldsIsValidNew() const ;
  bool FieldsIsValidOld() const ;
  bool UsernameIsValid() const ;
  bool PasswordLongIsValid() const ;
  bool PasswordComplexityIsValid() const ;
  bool EmailIsValid() const ;

  // all fields are valid for sign up
  void IsValidForSignUP();

  // all fields are valid for sign in
  void IsValidForSignIn();

  // Verification Code: sending the verification mail
  void VerificationMail();

  // Verification Code: Getting the verification code and make sure that it is
  // equal to the sent one
  bool IsVerificationCodeValid(const int &inputCode) const;

  // Password Reset: Getting username and email, for verification
  void GetUsernameEmail(const std::string &username, const std::string &email);

  // Password Reset: pass username & email to the database for verification
  void PushUsername(std::string *&username, std::string *&email);

  // Password Reset: Verification code via email
  bool VerCodeNewPassword(const bool &ishere);

  // Password Reset: Take the new password
  void PasswordReset(const std::string &newpassword, const bool &correctcode);

  // Password Reset: Push to the database
  void PushNewPassword(std::string *&newHashedpassword, std::string *&username);

  // from tesla
  /*bool SendEmailPowerShell() const;
  bool SendEmailCurl();
  bool SendEmailPython();
  void VerificationMailSMTP() const;*/
};

// Utility function for JSON string escaping
std::string escapeJsonString(const std::string &input);

#endif  // FINAL_AUTHENTICATION_H_
