#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdexcept>
#include <ctime>
using namespace std;

class Account {
private:
    string username;
    string password;
    double balance;
    vector<string> history;

    string getTimestamp() {
        time_t now = time(0);
        char* dt = ctime(&now);
        string ts(dt);
        ts.pop_back(); // remove newline
        return ts;
    }

public:
    Account(string u = "", string p = "", double b = 0.0) {
        username = u;
        password = p;
        balance = b;
    }

    string getUsername() { return username; }
    bool checkPassword(string pass) { return pass == password; }
    double getBalance() { return balance; }

    void deposit(double amount) {
        if (amount <= 0) throw invalid_argument("Deposit must be positive!");
        balance += amount;
        history.push_back("Deposited " + to_string(amount) + " | " + getTimestamp());
    }

    void withdraw(double amount) {
        if (amount <= 0) throw invalid_argument("Withdraw must be positive!");
        if (amount > balance) throw runtime_error("Insufficient balance!");
        balance -= amount;
        history.push_back("Withdrew " + to_string(amount) + " | " + getTimestamp());
    }

    void transfer(Account &receiver, double amount) {
        if (amount <= 0) throw invalid_argument("Transfer must be positive!");
        if (amount > balance) throw runtime_error("Insufficient balance!");
        balance -= amount;
        receiver.balance += amount;
        history.push_back("Transferred " + to_string(amount) + " to " + receiver.username + " | " + getTimestamp());
        receiver.history.push_back("Received " + to_string(amount) + " from " + username + " | " + getTimestamp());
    }

    void showHistory() {
        cout << "\nTransaction History of " << username << ":\n";
        if (history.empty()) {
            cout << "No transactions yet.\n";
        } else {
            for (auto &h : history) cout << h << endl;
        }
    }

    void saveToFile() {
        ofstream fout(username + ".dat");
        fout << username << endl << password << endl << balance << endl;
        fout.close();
    }

    bool loadFromFile(string u) {
        ifstream fin(u + ".dat");
        if (!fin) return false;
        username = u;
        fin >> password >> balance;
        fin.close();
        return true;
    }
};

// ----------- MAIN SYSTEM -------------
int main() {
    Account user1, user2;
    string uname, pass;

    cout << "==== Banking System Simulation ====\n";
    cout << "1. Register\n2. Login\nChoose: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << "Enter username: "; cin >> uname;
        cout << "Enter password: "; cin >> pass;
        user1 = Account(uname, pass, 0.0);
        user1.saveToFile();
        cout << "Account created successfully!\n";
    } 
    else if (choice == 2) {
        cout << "Enter username: "; cin >> uname;
        cout << "Enter password: "; cin >> pass;
        if (!user1.loadFromFile(uname)) {
            cout << "User not found!\n"; return 0;
        }
        if (!user1.checkPassword(pass)) {
            cout << "Invalid password!\n"; return 0;
        }
        cout << "Login successful!\n";
    } 
    else {
        cout << "Invalid option!\n";
        return 0;
    }

    // ------- Banking Menu ---------
    while (true) {
        cout << "\n--- Banking Menu ---\n";
        cout << "1. Deposit\n2. Withdraw\n3. Transfer\n4. Show Balance\n5. Show History\n6. Exit\nChoice: ";
        cin >> choice;
        try {
            if (choice == 1) {
                double amt; cout << "Enter amount: "; cin >> amt;
                user1.deposit(amt);
                cout << "Deposit successful!\n";
            } 
            else if (choice == 2) {
                double amt; cout << "Enter amount: "; cin >> amt;
                user1.withdraw(amt);
                cout << "Withdrawal successful!\n";
            } 
            else if (choice == 3) {
                string recv; cout << "Enter receiver username: "; cin >> recv;
                if (!user2.loadFromFile(recv)) {
                    cout << "Receiver not found!\n"; continue;
                }
                double amt; cout << "Enter amount: "; cin >> amt;
                user1.transfer(user2, amt);
                cout << "Transfer successful!\n";
                user2.saveToFile();
            } 
            else if (choice == 4) {
                cout << "Balance: " << user1.getBalance() << endl;
            } 
            else if (choice == 5) {
                user1.showHistory();
            } 
            else if (choice == 6) {
                user1.saveToFile();
                cout << "Exiting... Goodbye!\n";
                break;
            } 
            else {
                cout << "Invalid choice!\n";
            }
        } catch (exception &e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    return 0;
}