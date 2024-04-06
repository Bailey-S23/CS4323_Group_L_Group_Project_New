#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <chrono> // For sleep in demonstration

// Define a struct to represent a transaction
struct Transaction {
    std::string accNum;
    std::string type;
    double amount;
    std::string recipientAccNum; // Only used for Transfer transactions
};

// Function to process a single transaction
void processTransaction(const Transaction& transaction, std::mutex& mtx, std::unordered_map<std::string, double>& accountBalances) {
    // Acquire the lock to ensure synchronized access
    std::lock_guard<std::mutex> lock(mtx);

    // Perform the transaction based on its type
    if (transaction.type == "Withdraw") {
        if (accountBalances.find(transaction.accNum) != accountBalances.end()) {
            if (accountBalances[transaction.accNum] >= transaction.amount) {
                accountBalances[transaction.accNum] -= transaction.amount;
            } else {
                std::cerr << "Insufficient funds for withdrawal from account " << transaction.accNum << std::endl;
            }
        } else {
            std::cerr << "Account " << transaction.accNum << " does not exist for withdrawal" << std::endl;
        }
    } else if (transaction.type == "Create") {
        if (accountBalances.find(transaction.accNum) == accountBalances.end()) {
            accountBalances[transaction.accNum] = transaction.amount;
        } else {
            std::cerr << "Account " << transaction.accNum << " already exists" << std::endl;
        }
    } else if (transaction.type == "Inquiry") {
        // Do nothing for inquiry
    } else if (transaction.type == "Deposit") {
        accountBalances[transaction.accNum] += transaction.amount;
    } else if (transaction.type == "Transfer") {
        if (accountBalances.find(transaction.accNum) != accountBalances.end() &&
            accountBalances.find(transaction.recipientAccNum) != accountBalances.end()) {
            if (accountBalances[transaction.accNum] >= transaction.amount) {
                accountBalances[transaction.accNum] -= transaction.amount;
                accountBalances[transaction.recipientAccNum] += transaction.amount;
            } else {
                std::cerr << "Insufficient funds for transfer from account " << transaction.accNum << std::endl;
            }
        } else {
            std::cerr << "One or both accounts involved in transfer do not exist" << std::endl;
        }
    } else if (transaction.type == "Close") {
        accountBalances.erase(transaction.accNum);
    }
}

int main() {
    // Initialize account balances
    std::unordered_map<std::string, double> accountBalances;

    // Open the input file
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open input file." << std::endl;
        return 1;
    }

    // Process transactions for each user
    std::string line;
    std::mutex mtx; // Mutex for synchronization
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        Transaction transaction;
        if (iss >> transaction.accNum >> transaction.type) {
            if (transaction.type == "Withdraw" || transaction.type == "Deposit" ||
                transaction.type == "Transfer") {
                // Extract the transaction amount
                iss >> transaction.amount;
            } else if (transaction.type == "Create") {
                // Extract the initial deposit amount
                iss >> transaction.amount;
            } else if (transaction.type == "Transfer") {
                // Extract the transfer amount and recipient account number
                iss >> transaction.amount >> transaction.recipientAccNum;
            }

            // Process the transaction in a separate thread
            std::thread t(processTransaction, transaction, std::ref(mtx), std::ref(accountBalances));
            t.join(); // Join the thread to ensure sequential processing
        }
    }

    // Close the input file
    inputFile.close();

    // Print account balances
    std::cout << "Final account balances:" << std::endl;
    for (const auto& pair : accountBalances) {
        std::cout << "Account " << pair.first << ": $" << pair.second << std::endl;
    }

    return 0;
}
