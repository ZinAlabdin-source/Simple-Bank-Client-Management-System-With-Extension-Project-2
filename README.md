# 🏦 Simple Bank Client Management System (C++)

A robust **console-based banking application** written in pure C++ that allows you to manage client records, perform financial transactions, and persist data in a local text file. Designed as a learning project to master procedural programming, file handling, and user-input validation.

![C++](https://img.shields.io/badge/C++-17-blue.svg) ![Platform](https://img.shields.io/badge/platform-Windows-lightgrey) ![License](https://img.shields.io/badge/license-MIT-green)

---

## 📌 Features

### 🔹 Client Management (CRUD)
- **Create** new clients with duplicate account-number prevention.
- **Read** all clients in a formatted table or view a single client card.
- **Update** client details (leave fields empty to keep old values).
- **Delete** clients using a safe "Mark for Delete" technique.

### 🔹 Financial Transactions
- **Deposit** money into an account (with positive-amount validation).
- **Withdraw** money (checks for sufficient balance, prevents negative amounts).
- **View total balances** of all clients.

### 🔹 Data Persistence
- All records are stored in a plain text file (`ZDFile.txt`) using `#//#` as separator.
- Automatic **sorting** of clients by account number after every change.
- Robust **input validation** – the program never crashes on invalid entries.

### 🔹 User Experience
- Clean, menu-driven interface with screen headers.
- Confirmation prompts for critical actions (delete, update, transactions).
- Ability to cancel operations at any time.
- Input loops that ask again on invalid data instead of exiting.

---

## 🎮 Demo Screens (Textual Representation)

**Main Menu**
=========================================
Main Menu Screen
=========================================
[1] Show All Clients
[2] Add New Client
[3] Delete A Client
[4] Update A Client
[5] Find A Client
[6] Transactions Menu
[0] Exit
=========================================


**Client Card**
======================================
Client Details Screen
======================================
Account Number: A150
Pin Code: 1234
Name: Zin Alabdin
Phone: 0501234567
Balance: 5270.5
======================================


**All Clients Table**
==========================================================================================
Client List (2) Client(s)
==========================================================================================
| Account Number | Pin Code | Client Name | Phone Number | Balance |
==========================================================================================
| A150 | 1234 | Zin Alabdin | 0501234567 | 5270.5 |
| B200 | 5678 | Ali Ahmad | 0512345678 | 12000 |
==========================================================================================


---

## 🗂️ Project Structure
📁 C++ Bank Pro 1/
├── main.cpp # The entire application source code
├── ZDFile.txt # Data file (auto-created on first client addition)
├── .gitignore # Git ignore rules for executables and object files
└── README.md # This file


---

## ⚙️ How to Run

### Prerequisites
- A C++ compiler supporting **C++11** or later (e.g., MinGW, Visual Studio, GCC).
- **Windows** operating system (the program uses `system("cls")` and `system("pause>0")` for console management – see notes below).

### Steps
1. **Clone** the repository:
   ```bash
   git clone https://github.com/ZinAlabdin-source/Simple-Bank-Client-Management-System-Project-1.git
Navigate to the project folder and open main.cpp in your IDE.

Compile the code. For example, with g++:

g++ main.cpp -o BankSystem.exe
Run the executable:

BankSystem.exe
Use the menu numbers to navigate and enjoy!

Note for non-Windows users: Replace system("cls") with system("clear") and remove system("pause>0") if you are on Linux/macOS. The rest of the code is cross‑platform.

🔐 Data File Format
Each line in ZDFile.txt represents one client with fields separated by #//#:

AccountNumber#//#PinCode#//#Name#//#PhoneNumber#//#Balance
Example:

A150#//#1234#//#Zin Alabdin#//#0501234567#//#5270.5
The file is rewritten entirely on every save operation, and only records not marked for deletion are kept.

🧠 Technical Highlights
Procedural programming: The entire application uses functions and structures (no classes), making it a perfect demonstration of structured C++.

Bubble Sort algorithm for client ordering.

Soft deletion via a Mark_For_Delete flag – a common technique in database systems.

Robust input handling: Safe_String_To_Double with try-catch for numeric conversions, cin.fail() checks for menu choices, and loops that re-prompt on bad input.

Console manipulation: Uses setw, left, iomanip for table formatting and system("cls") for screen clearing.

📚 Learning Outcomes
This project serves as a comprehensive exercise in:

C++ file I/O (fstream, ios::in, ios::out, ios::app).

vector and struct for dynamic data management.

String tokenization (find, substr, erase).

Enum types for menu readability.

Input validation and defensive programming.

Separation of concerns through small, single-purpose functions.

🚀 Future Improvements (Ideas)
Add a login system with admin PIN.

Encrypt the data file for security.

Implement a GUI using a framework like Qt.

Port to Linux/macOS by abstracting OS-specific commands.

Use actual database files (SQLite) instead of text.

📄 License
This project is licensed under the MIT License – feel free to use, modify, and distribute it for educational or personal purposes.

👤 Author
Zin Alabdin
GitHub Profile

⭐ If you find this project helpful, please give it a star on GitHub!