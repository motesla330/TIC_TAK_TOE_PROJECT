#include "Authentication.h"
#include <gtest/gtest.h>
#include <string>

class AuthenticationTest : public ::testing::Test {
protected:
    Authentication auth;
};

TEST_F(AuthenticationTest, HashingProducesConsistentResults) {
    std::string pass = "SecureP@ssw0rd";
    EXPECT_EQ(auth.HashingPassword(pass), auth.HashingPassword(pass));
}

TEST_F(AuthenticationTest, SignUpStoresCorrectData) {
    auth.SignUp("TestUser", "P@ssw0rd123!", "test@example.com");

    std::string *uname, *hpass, *email;
    auth.PushNewAccount(uname, hpass, email);

    EXPECT_EQ(*uname, "TestUser");
    EXPECT_EQ(*email, "test@example.com");
    EXPECT_EQ(*hpass, auth.HashingPassword("P@ssw0rd123!"));
}

TEST_F(AuthenticationTest, SignInUpdatesCredentialsCorrectly) {
    auth.SignIn("ExistingUser", "Password123!");
    std::string *uname;
    auth.PushSignedInData(uname);
    EXPECT_EQ(*uname, "ExistingUser");
}

TEST_F(AuthenticationTest, UsernameValidation) {
    auth.SignUp("Usr", "ValidPass1!", "valid@em.com");
    EXPECT_FALSE(auth.UsernameIsValid());

    auth.SignUp("ValidUser", "ValidPass1!", "valid@em.com");
    EXPECT_TRUE(auth.UsernameIsValid());
}

TEST_F(AuthenticationTest, PasswordLengthValidation) {
    auth.SignUp("User", "short1!", "test@e.com");
    EXPECT_FALSE(auth.PasswordLongIsValid());

    auth.SignUp("User", "LongEnough1!", "test@e.com");
    EXPECT_TRUE(auth.PasswordLongIsValid());
}

TEST_F(AuthenticationTest, PasswordComplexityValidation) {
    auth.SignUp("User", "password", "test@e.com");
    EXPECT_FALSE(auth.PasswordComplexityIsValid());

    auth.SignUp("User", "P@ssw0rd", "test@e.com");
    EXPECT_TRUE(auth.PasswordComplexityIsValid());
}

TEST_F(AuthenticationTest, EmailValidation) {
    auth.SignUp("User", "P@ssw0rd", "bademail");
    EXPECT_FALSE(auth.EmailIsValid());

    auth.SignUp("User", "P@ssw0rd", "good@email.com");
    EXPECT_TRUE(auth.EmailIsValid());
}

TEST_F(AuthenticationTest, FieldValidationNew) {
    auth.SignUp("", "", "");
    EXPECT_FALSE(auth.FieldsIsValidNew());

    auth.SignUp("User", "P@ssword", "email@domain.com");
    EXPECT_TRUE(auth.FieldsIsValidNew());
}

TEST_F(AuthenticationTest, FieldValidationOld) {
    auth.SignIn("", "");
    EXPECT_FALSE(auth.FieldsIsValidOld());

    auth.SignIn("User", "P@ssword");
    EXPECT_TRUE(auth.FieldsIsValidOld());
}

TEST_F(AuthenticationTest, IsHereInterfaceCorrectComparison) {
    auth.SignIn("User", "MyP@ssword");
    std::string correctHash = auth.HashingPassword("MyP@ssword");
    auth.IsHereConnect(correctHash, true);
    EXPECT_TRUE(auth.IsHereInterface());

    auth.GetPassword("WrongPass");
    EXPECT_FALSE(auth.IsHereInterface());
}

TEST_F(AuthenticationTest, PasswordResetWorksWithCorrectCode) {
    auth.SignIn("User", "OldPassword@1");
    std::string oldHash = auth.HashingPassword("OldPassword@1");

    auth.PasswordReset("NewPassword@1", true);
    std::string newHash = auth.HashingPassword("NewPassword@1");

    std::string *newPass, *username;
    auth.PushNewPassword(newPass, username);

    EXPECT_NE(*newPass, oldHash);
    EXPECT_EQ(*newPass, newHash);
    EXPECT_EQ(*username, "User");
}
