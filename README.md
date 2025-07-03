# TIC_TAC_TOE_PROJECT
Local Tic Tac Toe Game with the following features:
- Authentication system & session management.
- Supports 1 Vs 1 & 1 Vs AI opponent modes.
- Strong game logic & board management.
- Strong database for players' data (username, hashed password, etc.) & each player has their game history and statistics, with the option of replaying matches.
- It was all brought together in a comprehensive graphical user interface (GUI) developed with Qt Creator.

For more details: https://drive.google.com/drive/folders/1fW-EhcfmvG5rjMPEE2OfAR3TPTOG_jET?fbclid=IwAR1TijX9QFM21MrZ6TGsVVuSFAcw9kS2024g5At9Y1cFVco3V1VChGA6P8Q
Enjoy and give your feedback.

# How to Build and Run the Project

## Prerequisites

1. **Qt Creator IDE**
   - Download and install Qt Creator from the official Qt website
   - Search "Qt Creator download" in your preferred search engine to find the latest version

2. **OpenSSL Library**
   - Download OpenSSL from the official OpenSSL website
   - Install it on your system (typically installs to `C:\Program Files\OpenSSL-Win64\` on Windows)

## Setup Instructions

### Step 1: Download the Project
1. Navigate to the main branch of this repository
2. Download the `final` folder to your local machine
3. Extract the contents if downloaded as a zip file

### Step 2: Open Project in Qt Creator
1. Launch Qt Creator
2. Open the `final` folder in Qt Creator
3. Select the `test.pro` file to open the project
4. The project will now be loaded in Qt Creator

### Step 3: Configure OpenSSL Paths
1. Open the `test.pro` file in the project
2. Navigate to lines 63-65, where you'll find:
   ```pro
   # Adjust paths based on your installation directory
   INCLUDEPATH += "C:/Program Files/OpenSSL-Win64/include"
   LIBS += -L"F:\Data Structure Project\TIC_TAK_TOE_PROJECT\final\OpenSSL-Win64\lib" -lcrypto -lssl
   ```

3. **Update the Include Path (Line 64):**
   - Locate your OpenSSL installation directory (usually `C:\Program Files\OpenSSL-Win64\`)
   - Copy the path to the `include` folder
   - Replace the path in line 64 with your actual OpenSSL include path

4. **Update the Library Path (Line 65):**
   - Copy the path to the `lib` folder in your OpenSSL installation
   - Replace the path in line 65 with your actual OpenSSL lib path

### Step 4: Build and Run
1. Save the `test.pro` file after making the path changes
2. Build and run the project using one of these methods:
   - Click the **Run** button in the left sidebar of Qt Creator
   - Press **Ctrl+R** keyboard shortcut
   - Use the Build menu to build first, then run

## Example Configuration

If OpenSSL is installed in the default location, your paths should look like:
```pro
INCLUDEPATH += "C:/Program Files/OpenSSL-Win64/include"
LIBS += -L"C:/Program Files/OpenSSL-Win64/lib" -lcrypto -lssl
```

## Troubleshooting

- Ensure OpenSSL is properly installed and accessible
- Verify that the paths in `test.pro` match your actual OpenSSL installation directory
- Make sure Qt Creator has the necessary build tools configured
- Check that all required Qt modules are installed


# Known Issues
# Game Replay Feature

- Issue: The replay (review game) functionality currently has a display bug where the game review shows moves in flipped button positions
- Impact: While the replay feature works, the visual representation may not accurately reflect the original game positions
- Status: This is a minor UI issue that doesn't affect core gameplay functionality
- For Developers: This is a relatively straightforward fix involving coordinate mapping in the replay system. Consider using AI tools like ChatGPT or other AI assistants to help debug the position mapping logic if needed

## Notes

- The project requires OpenSSL for cryptographic functionality
- Paths may vary depending on your OpenSSL installation method and location
- Always use forward slashes (`/`) or double backslashes (`\\`) in Qt project file paths
