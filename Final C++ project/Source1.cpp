#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Define a class for the items sold in the chocolate shop.
class Item {
public:
    string name;    // Name of the item.
    int quantity;   // How many of these items we have.
    double price;   // How much does one item cost.

    // Constructor to initialize an item with its details.
    Item(string n, int q, double p) : name(n), quantity(q), price(p) {}
};

// Define a class for the companies associated with the shop.
class Company {
public:
    string name;     // Name of the company.
    double balance;  // How much money this company has.

    // Constructor to initialize a company with its details.
    Company(string n, double b) : name(n), balance(b) {}
};

// Main class to manage the chocolate shop operations.
class ChocolateShop {
private:
    vector<Item> items;       // List to keep all the items in the shop.
    vector<Company> companies;// List to keep all the associated companies.

public:
    // Method to check the user's username and password.
    void authenticateUser() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        // If the credentials are wrong, end the program.
        if (username != "zaid" || password != "12345") {
            cout << "Invalid username or password. Exiting program.\n";
            exit(0);
        }
    }

    // Method to add new items to the shop's inventory.
    void addItem() {
        string name;
        int quantity;
        double price;
        cout << "Enter item name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);
        cout << "Enter quantity: ";
        cin >> quantity;
        cout << "Enter price: ";
        cin >> price;

        items.push_back(Item(name, quantity, price));
        cout << "Item added successfully.\n";
    }

    // Method to change the price of an existing item.
    void changeItemPrice() {
        string name;
        double newPrice;
        cout << "Enter item name to change price: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);
        cout << "Enter new price: ";
        cin >> newPrice;

        for (auto& item : items) {
            if (item.name == name) {
                item.price = newPrice;
                cout << "Price updated successfully.\n";
                return;
            }
        }
        cout << "Item not found.\n";
    }

    // Method to update the financial balance of a company.
    void changeCompanyBalance() {
        string name;
        double newBalance;
        cout << "Enter company name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);
        cout << "Enter new balance: ";
        cin >> newBalance;

        for (auto& company : companies) {
            if (company.name == name) {
                company.balance = newBalance;
                cout << "Balance updated successfully.\n";
                return;
            }
        }
        cout << "Company not found.\n";
    }

    // Method to calculate the total sales for a specific item or all items from one company.
    void calculateSales() {
        string name;
        cout << "Enter item or company name to calculate total sales: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);
        double totalSales = 0;

        // Search for the item in the inventory.
        for (const auto& item : items) {
            if (item.name == name) {
                totalSales = item.price * item.quantity;
                cout << "Total sales for " << name << ": $" << totalSales << "\n";
                return;
            }
        }

        // If item not found, search for the company.
        for (const auto& company : companies) {
            if (company.name == name) {
                totalSales = company.balance; // For simplicity, using the company's balance as sales.
                cout << "Total sales for " << name << ": $" << totalSales << "\n";
                return;
            }
        }

        cout << "No matching item or company found.\n";
    }

    // Method to load items from a file into the shop's inventory.
    void loadItemsFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name;
            int quantity;
            double price;
            getline(ss, name, ',');
            ss >> quantity >> ws >> price;
            items.push_back(Item(name, quantity, price));
        }
        file.close();
    }

    // Method to load company data from a file.
    void loadCompaniesFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name;
            double balance;
            getline(ss, name, ',');
            ss >> balance;
            companies.push_back(Company(name, balance));
        }
        file.close();
    }

    // Method to display all the items in the inventory.
    void displayItems() const {
        cout << "\nAvailable Items:\n";
        for (const auto& item : items) {
            cout << "Name: " << item.name << ", Quantity: " << item.quantity << ", Price: $" << item.price << endl;
        }
    }

    // Method to display all the companies associated with the shop.
    void displayCompanies() const {
        cout << "\nAssociated Companies:\n";
        for (const auto& company : companies) {
            cout << "Name: " << company.name << ", Balance: $" << company.balance << endl;
        }
    }
};

// Main function: the starting point of the program.
int main() {
    ChocolateShop shop;
    shop.authenticateUser();
    shop.loadItemsFromFile("chocolates.txt");
    shop.loadCompaniesFromFile("companies.txt");

    int choice;
    do {
        cout << "\nChocolate Shop Management System\n";
        cout << "1. Display Items\n";
        cout << "2. Display Companies\n";
        cout << "3. Add Item\n";
        cout << "4. Change Item Price\n";
        cout << "5. Change Company Balance\n";
        cout << "6. Calculate Total Sales\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: shop.displayItems(); break;
        case 2: shop.displayCompanies(); break;
        case 3: shop.addItem(); break;
        case 4: shop.changeItemPrice(); break;
        case 5: shop.changeCompanyBalance(); break;
        case 6: shop.calculateSales(); break;
        case 0: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice, please try again.\n"; break;
        }
    } while (choice != 0);

    return 0;
}
