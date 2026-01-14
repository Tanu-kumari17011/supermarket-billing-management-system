#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

class Shopping {
private:
    int pcode;
    float price;
    float discount;
    string pname;

public:
    void menu();
    void adminMenu();
    void buyerMenu();

    void initializeProducts();
    void showProducts();

    void addProduct();
    void editProduct();
    void deleteProduct();

    void buyProduct();
};

// INITIALIZE DEFAULT PRODUCTS 
void Shopping::initializeProducts() {
    ifstream in("database.txt");
    if (in.peek() != EOF) {
        in.close();
        return;
    }
    in.close();

    ofstream out("database.txt");
    out << "101 Rice 50 5\n";
    out << "102 Sugar 40 10\n";
    out << "103 Milk 30 5\n";
    out << "104 Bread 20 2\n";
    out.close();
}

// DISPLAY PRODUCTS 
void Shopping::showProducts() {
    ifstream in("database.txt");
    cout << "\n-------------------------------------------------\n";
    cout << "CODE\tNAME\tPRICE\tDISCOUNT\n";
    cout << "-------------------------------------------------\n";

    int c;
    float p, d;
    string n;

    while (in >> c >> n >> p >> d) {
        cout << c << "\t" << n << "\t" << p << "\t" << d << "%\n";
    }
    in.close();
    cout << "-------------------------------------------------\n";
}

//MAIN MENU
void Shopping::menu() {
    initializeProducts();

    int choice;
    string email, pass;

    while (true) {
        cout << "\n========== SUPERMARKET BILLING SYSTEM ==========\n";
        cout << "1. Administrator\n";
        cout << "2. Buyer\n";
        cout << "3. Exit\n";
        cout << "Choose option: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Email: ";
            cin >> email;
            cout << "Password: ";
            cin >> pass;

            if (email == "admin@gmail.com" && pass == "admin123")
                adminMenu();
            else
                cout << "? Invalid credentials!\n";
            break;

        case 2:
            buyerMenu();
            break;

        case 3:
            exit(0);

        default:
            cout << "Invalid choice!\n";
        }
    }
}

//ADMIN MENU 
void Shopping::adminMenu() {
    int choice;

    while (true) {
        cout << "\n========== ADMIN MENU ==========\n";
        cout << "1. Add Product\n";
        cout << "2. Edit Product\n";
        cout << "3. Delete Product\n";
        cout << "4. View Products\n";
        cout << "5. Back\n";
        cout << "Choose option: ";
        cin >> choice;

        switch (choice) {
        case 1: addProduct(); break;
        case 2: editProduct(); break;
        case 3: deleteProduct(); break;
        case 4: showProducts(); break;
        case 5: return;
        default: cout << "Invalid choice!\n";
        }
    }
}

// ADD PRODUCT (DUPLICATE CHECK) 
void Shopping::addProduct() {
    int code;
    float p, d;
    string name;
    bool exists = false;

    cout << "\nEnter Product Code: ";
    cin >> code;

    ifstream in("database.txt");
    int c; float pr, di; string na;
    while (in >> c >> na >> pr >> di) {
        if (c == code) {
            exists = true;
            break;
        }
    }
    in.close();

    if (exists) {
        cout << "? Product code already exists!\n";
        return;
    }

    cout << "Enter Product Name: ";
    cin >> name;
    cout << "Enter Price: ";
    cin >> p;
    cout << "Enter Discount: ";
    cin >> d;

    ofstream out("database.txt", ios::app);
    out << code << " " << name << " " << p << " " << d << "\n";
    out.close();

    cout << "? Product added successfully!\n";
}

/* ================= EDIT PRODUCT ================= */
void Shopping::editProduct() {
    int key;
    bool found = false;

    cout << "Enter product code to edit: ";
    cin >> key;

    ifstream in("database.txt");
    ofstream out("temp.txt");

    int c; float p, d; string n;
    while (in >> c >> n >> p >> d) {
        if (c == key) {
            cout << "New Name: ";
            cin >> n;
            cout << "New Price: ";
            cin >> p;
            cout << "New Discount: ";
            cin >> d;
            found = true;
        }
        out << c << " " << n << " " << p << " " << d << "\n";
    }
    in.close();
    out.close();

    remove("database.txt");
    rename("temp.txt", "database.txt");

    if (found)
        cout << "? Product updated!\n";
    else
        cout << "? Product not found!\n";
}

//DELETE PRODUCT 
void Shopping::deleteProduct() {
    int key;
    bool found = false;

    cout << "Enter product code to delete: ";
    cin >> key;

    ifstream in("database.txt");
    ofstream out("temp.txt");

    int c; float p, d; string n;
    while (in >> c >> n >> p >> d) {
        if (c == key) {
            found = true;
            continue;
        }
        out << c << " " << n << " " << p << " " << d << "\n";
    }
    in.close();
    out.close();

    remove("database.txt");
    rename("temp.txt", "database.txt");

    if (found)
        cout << "? Product deleted!\n";
    else
        cout << "? Product not found!\n";
}

// BUYER
void Shopping::buyerMenu() {
    showProducts();

    int code, qty;
    char ch;
    float total = 0;

    do {
        cout << "Enter product code: ";
        cin >> code;
        cout << "Enter quantity: ";
        cin >> qty;

        ifstream in("database.txt");
        int c; float p, d; string n;
        while (in >> c >> n >> p >> d) {
            if (c == code) {
                float amt = p * qty;
                float finalAmt = amt - (amt * d / 100);
                total += finalAmt;

                cout << n << " | Amount: " << finalAmt << "\n";
            }
        }
        in.close();

        cout << "Buy more? (y/n): ";
        cin >> ch;

    } while (ch == 'y');

    cout << "\nTOTAL BILL = " << total << "\n";
}

// MAIN 
int main() {
    Shopping shop;
    shop.menu();
    return 0;
}
