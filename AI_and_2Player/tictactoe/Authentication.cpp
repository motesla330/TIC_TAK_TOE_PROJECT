// Copyright [year] <MahmoudIsmail>

#include "Authentication.h"
#include <chrono>  // For std::chrono::seconds, minutes
#include <cstdlib>  // For system()
#include <ctime>  // For time()
#include <fstream>
#include <iomanip>  // For std::quoted if needed, though manual escaping is done here
#include <iostream>
#include <openssl/sha.h>
#include <regex>
#include <thread>  // For std::this_thread::sleep_for
#include <QDialog>
#include <QMessageBox>
using namespace std;

std::string escapeJsonString(const std::string &input) {
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

// Constructor
Authentication::Authentication() {
    // Get API key from environment variable
   /* const char* key = std::getenv("SENDGRID_API_KEY");
    if (key) {
        apiKey = std::string(key);
    } else {
        std::cerr << "Error: SENDGRID_API_KEY environment variable not set!\n";
    }
*/
}

// Hashing password using openssl
string Authentication::HashingPassword(const string &PassWord) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char *>(PassWord.c_str()),
           PassWord.length(), hash);

    char hex_output[2 * SHA256_DIGEST_LENGTH + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        sprintf(hex_output + (i * 2), "%02x", hash[i]);
    }
    hex_output[2 * SHA256_DIGEST_LENGTH] = '\0'; // null-terminate the string

    return string(hex_output);
}

// get data from the user
void Authentication::SignUp(const string &username, const string &password,
                            const string &email) {
    UserName = username;
    PassWord = password;
    HashedPassword = HashingPassword(PassWord);
    Email = email;
}

// push data to the database
void Authentication::PushNewAccount(string *&username, string *&hashpassword,
                                    string *&email) {
    username = &UserName;
    hashpassword = &HashedPassword;
    email = &Email;
}

// Sign in with username and password
void Authentication::SignIn(const string &username, const string &password) {
    UserName = username;
    PassWord = password;
    HashedPassword = HashingPassword(PassWord);
}

// push signed in data to the database
void Authentication::PushSignedInData(string *&username) {
    username = &UserName;
}

// Makes sure that the user has an account
void Authentication::IsHereConnect(const string &hashedpassword, const bool &ishere) {
    if (ishere) {
        HashedPasswordFromDatabase = hashedpassword;
        IsHere = true;
    } else {
        IsHere = false;
    }
}

// for wrong password entered
void Authentication::GetPassword(const string &password) {
    HashedPassword = HashingPassword(password);
}

// to ensure that the password entered is correct
bool Authentication::IsHereInterface() {
    if (IsHere) {
        if (HashedPassword == HashedPasswordFromDatabase) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

bool Authentication::FieldsIsValidNew() {
    if (UserName.empty() || PassWord.empty() || Email.empty()) {
        return false;
    }
    return true;
}

bool Authentication::FieldsIsValidOld() {
    if (UserName.empty() || PassWord.empty()) {
        return false;
    }
    return true;
}

bool Authentication::UsernameIsValid() {
    if (UserName.length() < 5) {
        return false;
    }
    return true;
}

bool Authentication::PasswordLongIsValid() {
    if (PassWord.length() < 8) {
        return false;
    }
    return true;
}

bool Authentication::PasswordComplexityIsValid() {
    bool hasUpper = false, hasLower = false, hasDigit = false,
        hasSpecial = false;
    string specials = "!@#$%^&*()-_=+[]{}|;:,.<>?";
    for (char ch : PassWord) {
        if (isupper(ch))
            hasUpper = true;
        else if (islower(ch))
            hasLower = true;
        else if (isdigit(ch))
            hasDigit = true;
        else if (specials.find(ch) != std::string::npos)
            hasSpecial = true;
    }
    return hasUpper && hasLower && hasDigit && hasSpecial;
}

bool Authentication::EmailIsValid() {
    regex email_regex(R"(\w+@\w+\.\w+)");
    return regex_match(Email, email_regex);
}

// all fields are valid for sign up
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

// all fields are valid for sign in
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

// Verification Code : sending the verification mail
void Authentication::VerificationMail() {
    srand(time(0));
    VerificationCode = rand() % 10000; // Generate and store the code
    string fromEmail = "mahmoud.abdallah04@eng-st.cu.edu.eg";
    string toEmail = Email; // Use the email provided by the user
    string codeStr = std::to_string(VerificationCode);
    qDebug()<<Email;
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

    // Replace placeholders in the HTML content
    size_t pos = htmlContentTemplate.find("{USERNAME}");
    if (pos != std::string::npos) {
        htmlContentTemplate.replace(pos, std::string("{USERNAME}").length(),
                                    UserName);
    }
    pos = htmlContentTemplate.find("{VERIFICATION_CODE}");
    if (pos != std::string::npos) {
        htmlContentTemplate.replace(
            pos, std::string("{VERIFICATION_CODE}").length(), codeStr);
    }

    // Escape the HTML content for JSON
    std::string escapedHtmlContent = escapeJsonString(htmlContentTemplate);

    // Build JSON payload
    std::string jsonPayload =
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

    // Write JSON to temporary file
    std::ofstream outFile("payload.json");
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open payload.json for writing.\n";
        return;
    }
    outFile << jsonPayload;
    outFile.close();

    // Build cURL command
    std::string cmd = "curl -s --tlsv1.3 --connect-timeout 30 "
                      "-X POST https://api.sendgrid.com/v3/mail/send "
                      "-H \"Authorization: Bearer " + apiKey + "\" "
                                 "-H \"Content-Type: application/json\" "
                                 "--data-binary @payload.json";
    qDebug()<< "Sending email...\n";
    int result = system(cmd.c_str());

    if (result == 0) {
        cout << "Email sent successfully!\n";
    } else {
        cout
            << "Failed to send email. Check API key and payload. cURL exit code: "
            << result << "\n";
    }

}

// Verification Code : Getting the verification code and make sure that is
// equal the sent one
bool Authentication::IsVerificationCodeValid(const int &inputCode) {
    return inputCode == VerificationCode;
}

// Password Reset : Getting username and email, for verification
void Authentication::GetUsernameEmail(const string &username, const string &email) {
    UserName = username;
    Email = email;
}

// Password Reset : pass username & email to the database for verification
void Authentication::PushUsername(string *&username, string *&email) {
    username = &UserName;
    email = &Email;
}

// Password Reset : Verification code via email
bool Authentication::VerCodeNewPassword(const bool &ishere) {
    if (ishere) {
        VerificationMail();
        return true;
    } else {
        return false;
    }
}

// password Reset : Take the new password
void Authentication::PasswordReset(const string &newpassword, const bool &correctcode) {
    if (correctcode == true) {
        PassWord = newpassword;
        HashedPassword = HashingPassword(PassWord);
    } else {
        cout << "Operation ended without any changes" << endl;
    }
}

// password Reset : Push to the database
void Authentication::PushNewPassword(string *&newHashedpassword, string *&username) {
    newHashedpassword = &HashedPassword;
    username = &UserName;
}

// anthor may from tesla
// SMTP Email Function - Simplified version avoiding Windows socket issues

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <random>
#include <cstdlib>

// Generate 6-digit verification code
int Authentication::generateVerificationCode() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(100000, 999999);
    return dis(gen);
}

// PowerShell SMTP method (Windows) - Enhanced version
bool Authentication::SendEmailPowerShell() {
    // Generate 6-digit verification code
    VerificationCode = generateVerificationCode();

    std::string fromEmail = "mo.kota330@gmail.com";  // Replace with your email
    std::string password = "lkfc hjvg hdst cvon";      // Replace with your app password
    std::string subject = "Your Verification Code";

    std::string body =
        "<html><body style='font-family: Arial, sans-serif; background-color: #f4f4f4; padding: 20px;'>"
        "<div style='max-width: 600px; margin: 0 auto; background-color: white; border-radius: 10px; padding: 30px; box-shadow: 0 0 10px rgba(0,0,0,0.1);'>"
        "<h2 style='color: #333; text-align: center; margin-bottom: 30px;'>Email Verification</h2>"
        "<p style='color: #666; font-size: 16px;'>Hello <strong style='color: #007acc;'>" + UserName + "</strong>,</p>"
                     "<p style='color: #666; font-size: 16px;'>Your verification code is:</p>"
                     "<div style='text-align: center; margin: 30px 0;'>"
                     "<span style='background-color: #007acc; color: white; padding: 15px 25px; font-size: 24px; font-weight: bold; border-radius: 5px; letter-spacing: 3px;'>" + std::to_string(VerificationCode) + "</span>"
                                             "</div>"
                                             "<p style='color: #666; font-size: 14px;'>This code will expire in 10 minutes.</p>"
                                             "<p style='color: #666; font-size: 14px;'>If you didn't request this code, please ignore this email.</p>"
                                             "</div>"
                                             "</body></html>";

    // Create PowerShell script with better error handling
    std::string psScript =
        "$ErrorActionPreference = 'Stop'\n"
        "try {\n"
        "    $SMTPServer = 'smtp.gmail.com'\n"
        "    $Port = 587\n"
        "    $Username = '" + fromEmail + "'\n"
                      "    $Password = ConvertTo-SecureString '" + password + "' -AsPlainText -Force\n"
                     "    $Credential = New-Object System.Management.Automation.PSCredential($Username, $Password)\n"
                     "    $From = '" + fromEmail + "'\n"
                      "    $To = '" + Email + "'\n"
                  "    $Subject = '" + subject + "'\n"
                    "    $Body = @'\n" + body + "\n'@\n"
                 "    \n"
                 "    Send-MailMessage -SmtpServer $SMTPServer -Port $Port -UseSsl -Credential $Credential -From $From -To $To -Subject $Subject -Body $Body -BodyAsHtml -ErrorAction Stop\n"
                 "    Write-Host 'SUCCESS: Email sent successfully!'\n"
                 "    exit 0\n"
                 "} catch {\n"
                 "    Write-Host 'ERROR: Failed to send email -' $_.Exception.Message\n"
                 "    exit 1\n"
                 "}\n";

    // Write PowerShell script to file
    std::ofstream psFile("send_verification_email.ps1");
    if (!psFile.is_open()) {
        std::cerr << "Error: Could not create PowerShell script file" << std::endl;
        return false;
    }

    psFile << psScript;
    psFile.close();

    // Execute PowerShell script
    std::string command = "powershell -ExecutionPolicy Bypass -File send_verification_email.ps1";
    std::cout << "Sending verification email to " << Email << "..." << std::endl;

    int result = system(command.c_str());

    // Clean up script file
    remove("send_verification_email.ps1");

    if (result == 0) {
        std::cout << "✓ Verification email sent successfully!" << std::endl;
        std::cout << "Please check your email for the 6-digit verification code." << std::endl;
        return true;
    } else {
        std::cerr << "✗ Failed to send verification email. Please check your email configuration." << std::endl;
        return false;
    }
}

// Cross-platform curl-based SMTP method
bool Authentication::SendEmailCurl() {
    // Generate 6-digit verification code
    VerificationCode = generateVerificationCode();

    std::string fromEmail = "mo.kota330@gmail.com";  // Replace with your email
    std::string password = "lkfc hjvg hdst cvon";      // Replace with your app password
    std::string subject = "Your Verification Code";

    // Create email content
    std::string emailContent =
        "To: " + Email + "\r\n"
                         "From: Your App <" + fromEmail + ">\r\n"
                      "Subject: " + subject + "\r\n"
                    "MIME-Version: 1.0\r\n"
                    "Content-Type: text/html; charset=UTF-8\r\n"
                    "\r\n"
                    "<html><body style='font-family: Arial, sans-serif; background-color: #f4f4f4; padding: 20px;'>"
                    "<div style='max-width: 600px; margin: 0 auto; background-color: white; border-radius: 10px; padding: 30px; box-shadow: 0 0 10px rgba(0,0,0,0.1);'>"
                    "<h2 style='color: #333; text-align: center; margin-bottom: 30px;'>Email Verification</h2>"
                    "<p style='color: #666; font-size: 16px;'>Hello <strong style='color: #007acc;'>" + UserName + "</strong>,</p>"
                     "<p style='color: #666; font-size: 16px;'>Your verification code is:</p>"
                     "<div style='text-align: center; margin: 30px 0;'>"
                     "<span style='background-color: #007acc; color: white; padding: 15px 25px; font-size: 24px; font-weight: bold; border-radius: 5px; letter-spacing: 3px;'>" + std::to_string(VerificationCode) + "</span>"
                                             "</div>"
                                             "<p style='color: #666; font-size: 14px;'>This code will expire in 10 minutes.</p>"
                                             "<p style='color: #666; font-size: 14px;'>If you didn't request this code, please ignore this email.</p>"
                                             "</div>"
                                             "</body></html>\r\n";

    // Write email content to file
    std::ofstream emailFile("email_content.txt");
    if (!emailFile.is_open()) {
        std::cerr << "Error: Could not create email content file" << std::endl;
        return false;
    }
    emailFile << emailContent;
    emailFile.close();

    // Create curl command for Gmail SMTP
    std::string curlCommand =
        "curl --url \"smtps://smtp.gmail.com:465\" "
        "--ssl-reqd "
        "--mail-from \"" + fromEmail + "\" "
                      "--mail-rcpt \"" + Email + "\" "
                  "--user \"" + fromEmail + ":" + password + "\" "
                                       "--upload-file email_content.txt "
                                       "--silent --show-error";

    std::cout << "Sending verification email via SMTP..." << std::endl;

    int result = system(curlCommand.c_str());

    // Clean up email file
    remove("email_content.txt");

    if (result == 0) {
        std::cout << "✓ Verification email sent successfully via SMTP!" << std::endl;
        std::cout << "Please check your email for the 6-digit verification code." << std::endl;
        return true;
    } else {
        std::cerr << "✗ Failed to send email via SMTP. Curl exit code: " << result << std::endl;
        return false;
    }
}

// Python-based email method (requires Python with smtplib)
bool Authentication::SendEmailPython() {
    // Generate 6-digit verification code
    VerificationCode = generateVerificationCode();

    std::string fromEmail = "mo.kota330@gmail.com";  // Replace with your email
    std::string password = "lkfc hjvg hdst cvon";      // Replace with your app password

    // Create Python script
    std::string pythonScript =
        "import smtplib\n"
        "from email.mime.text import MIMEText\n"
        "from email.mime.multipart import MIMEMultipart\n"
        "import sys\n"
        "\n"
        "def send_email():\n"
        "    try:\n"
        "        # Email configuration\n"
        "        smtp_server = 'smtp.gmail.com'\n"
        "        smtp_port = 587\n"
        "        sender_email = '" + fromEmail + "'\n"
                      "        sender_password = '" + password + "'\n"
                     "        recipient_email = '" + Email + "'\n"
                  "        \n"
                  "        # Create message\n"
                  "        message = MIMEMultipart('alternative')\n"
                  "        message['Subject'] = 'Your Verification Code'\n"
                  "        message['From'] = f'Your App <{sender_email}>'\n"
                  "        message['To'] = recipient_email\n"
                  "        \n"
                  "        # HTML content\n"
                  "        html = '''\n"
                  "        <html>\n"
                  "          <body style='font-family: Arial, sans-serif; background-color: #f4f4f4; padding: 20px;'>\n"
                  "            <div style='max-width: 600px; margin: 0 auto; background-color: white; border-radius: 10px; padding: 30px; box-shadow: 0 0 10px rgba(0,0,0,0.1);'>\n"
                  "              <h2 style='color: #333; text-align: center; margin-bottom: 30px;'>Email Verification</h2>\n"
                  "              <p style='color: #666; font-size: 16px;'>Hello <strong style='color: #007acc;'>" + UserName + "</strong>,</p>\n"
                     "              <p style='color: #666; font-size: 16px;'>Your verification code is:</p>\n"
                     "              <div style='text-align: center; margin: 30px 0;'>\n"
                     "                <span style='background-color: #007acc; color: white; padding: 15px 25px; font-size: 24px; font-weight: bold; border-radius: 5px; letter-spacing: 3px;'>" + std::to_string(VerificationCode) + "</span>\n"
                                             "              </div>\n"
                                             "              <p style='color: #666; font-size: 14px;'>This code will expire in 10 minutes.</p>\n"
                                             "              <p style='color: #666; font-size: 14px;'>If you didn't request this code, please ignore this email.</p>\n"
                                             "            </div>\n"
                                             "          </body>\n"
                                             "        </html>\n"
                                             "        '''\n"
                                             "        \n"
                                             "        # Attach HTML content\n"
                                             "        html_part = MIMEText(html, 'html')\n"
                                             "        message.attach(html_part)\n"
                                             "        \n"
                                             "        # Send email\n"
                                             "        with smtplib.SMTP(smtp_server, smtp_port) as server:\n"
                                             "            server.starttls()\n"
                                             "            server.login(sender_email, sender_password)\n"
                                             "            server.send_message(message)\n"
                                             "        \n"
                                             "        print('SUCCESS: Email sent successfully!')\n"
                                             "        return True\n"
                                             "        \n"
                                             "    except Exception as e:\n"
                                             "        print(f'ERROR: Failed to send email - {str(e)}')\n"
                                             "        return False\n"
                                             "\n"
                                             "if __name__ == '__main__':\n"
                                             "    success = send_email()\n"
                                             "    sys.exit(0 if success else 1)\n";

    // Write Python script to file
    std::ofstream pyFile("send_email.py");
    if (!pyFile.is_open()) {
        std::cerr << "Error: Could not create Python script file" << std::endl;
        return false;
    }
    pyFile << pythonScript;
    pyFile.close();

    // Execute Python script
    std::string command = "python send_email.py";
    std::cout << "Sending verification email via Python..." << std::endl;

    int result = system(command.c_str());

    // Clean up script file
    remove("send_email.py");

    if (result == 0) {
        std::cout << "✓ Verification email sent successfully!" << std::endl;
        std::cout << "Please check your email for the 6-digit verification code." << std::endl;
        return true;
    } else {
        std::cerr << "✗ Failed to send email via Python. Make sure Python is installed." << std::endl;
        return false;
    }
}

// Modified version of your existing VerificationMail function
void Authentication::VerificationMailSMTP() {
    std::cout << "Attempting to send verification email..." << std::endl;

    // Try different methods in order of preference
    if (SendEmailPowerShell()) {
        std::cout << "Email sent via PowerShell method" << std::endl;
        return;
    }

    std::cout << "PowerShell method failed, trying curl..." << std::endl;
    if (SendEmailCurl()) {
        std::cout << "Email sent via curl method" << std::endl;
        return;
    }

    std::cout << "Curl method failed, trying Python..." << std::endl;
    if (SendEmailPython()) {
        std::cout << "Email sent via Python method" << std::endl;
        return;
    }

    // If all methods fail, fall back to your original API method
    std::cout << "All SMTP methods failed, using API method..." << std::endl;
    VerificationMail(); // Your original method
}

// Add these declarations to your Authentication.h file:
/*
private:
    int generateVerificationCode();
public:
    bool SendEmailPowerShell();
    bool SendEmailCurl();
    bool SendEmailPython();
    void VerificationMailSMTP();
*/
