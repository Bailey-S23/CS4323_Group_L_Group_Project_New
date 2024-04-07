#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <mutex>
#include <thread>
#include <condition_variable>

// Define a struct to represent a transaction
struct Transaction {
    std::string accNum;
    std::string type;
    double amount;
    std::string recipientAccNum; // Only used for Transfer transactions
};

// Function to process a single transaction
void processTransaction(const Transaction& transaction, std::mutex& mtx, std::unordered_map<std::string, double>& accountBalances, std::condition_variable& cv) {
    // Acquire the lock to ensure synchronized access
    std::unique_lock<std::mutex> lock(mtx);

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
        // Print account balance
        std::cout << "Account " << transaction.accNum << " balance: $" << accountBalances[transaction.accNum] << std::endl;
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

    // Notify the main thread that transaction is complete
    cv.notify_all();
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

    // Read the number of transactions
    int numTransactions;
    inputFile >> numTransactions;

    // Read transactions from the input file
    std::vector<Transaction> transactions;
    std::string line;
    std::getline(inputFile, line); // Consume the newline character
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        Transaction transaction;
        if (iss >> transaction.accNum >> transaction.type) {
            if (transaction.type == "Withdraw" || transaction.type == "Deposit" ||
                transaction.type == "Transfer") {
                // Extract the transaction amount
                iss >> transaction.amount;
            } else if (transaction.type == "Transfer") {
                // Extract the transfer amount and recipient account number
                iss >> transaction.amount >> transaction.recipientAccNum;
            }

            // Add the transaction to the vector
            transactions.push_back(transaction);
        }
    }

    // Close the input file
    inputFile.close();

    // Create a mutex for synchronization
    std::mutex mtx;

    // Create a condition variable for synchronization
    std::condition_variable cv;

    // Create a vector to hold threads
    std::vector<std::thread> threads;

    // Run transactions in a thread pool
    for (const auto& transaction : transactions) {
        // Create a thread for each transaction
        threads.emplace_back(processTransaction, std::cref(transaction), std::ref(mtx), std::ref(accountBalances), std::ref(cv));
    }

    // Wait for all transactions to complete
    for (auto& thread : threads) {
        thread.join();
    }

    // Print final account balances
    std::cout << "Final account balances:" << std::endl;
    for (const auto& pair : accountBalances) {
        std::cout << "Account " << pair.first << " balance: $" << pair.second << std::endl;
    }

    return 0;
}
