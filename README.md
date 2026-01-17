# Banking Automation System

A **console-based Banking Automation System** developed in **C++** that simulates essential banking operations such as account creation, deposits, withdrawals, and viewing account details.  
This project is intended for **learning and portfolio purposes**, demonstrating strong fundamentals of C++ programming.

---

## 📌 Project Description

The Banking Automation System is a menu-driven application that mimics basic banking functionality.  
It allows users to manage bank accounts through a simple text interface and stores account data locally using file handling.

The project focuses on:
- Core C++ programming
- Object-Oriented Programming (OOP)
- File handling for data persistence
- Logical problem-solving using real-world scenarios

---

## ✨ Features

- Create a new bank account
- Display account details
- Deposit money into an account
- Withdraw money from an account
- Store account data persistently using files
- Menu-driven user interaction

---

## 🛠️ Technologies Used

- **Programming Language:** C++
- **Concepts:**  
  - Object-Oriented Programming  
  - File Handling (`fstream`)  
  - Conditional logic and loops  
- **Platform:** Console / Terminal based

---

## 📂 Project Structure

BankingAutomation/

├── bank.cpp # Main source file containing banking logic

├── pop.dat # Data file storing account information

├── README.md # Project documentation

> Note: Compiled executables (`.exe`) should ideally be excluded using `.gitignore`.

---

## ▶️ How to Compile and Run

### Using g++ Compiler

1. Open a terminal in the project directory
2. Compile the program:

```bash
g++ bank.cpp -o BankingAutomation
