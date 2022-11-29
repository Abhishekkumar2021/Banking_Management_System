#include <bits/stdc++.h>
using namespace std;


class Account
{
private:
    int accountNumber;
    float balance;

public:
    Account(int accountNumber, float balance)
    {
        this->accountNumber = accountNumber;
        this->balance = balance;
    }
    void deposit(float amount)
    {
        balance += amount;
    }
    void withdraw(float amount)
    {
        if (balance - amount < 500)
        {
            cout << "Insufficient Balance" << endl;
        }
        else
        {
            balance -= amount;
        }
    }
    int getBalance()
    {
        return balance;
    }
    void display()
    {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: " << balance << endl;
    }
    int getAccountNumber()
    {
        return accountNumber;
    }
};

class Transaction
{
private:
    string time;
    string type;
    float amount;
    float balance;
    string description;

public:
    Transaction(string time, string type, float amount, float balance, string description)
    {
        this->time = time;
        this->type = type;
        this->amount = amount;
        this->balance = balance;
        this->description = description;
    }
    void display()
    {
        cout << "Time: " << time << endl;
        cout << "Type: " << type << endl;
        cout << "Amount: " << amount << endl;
        cout << "Balance: " << balance << endl;
        cout << "Description: " << description << endl;
    }
    string getTime(){
        return time;
    }
    string getType(){
        return type;
    }
    float getAmount(){
        return amount;
    }
    float getBalance(){
        return balance;
    }
    string getDescription(){
        return description;
    }

};

class Customer
{
private:
    string name;
    string username;
    string email;
    string password;
    Account account;
    vector<Transaction> transactions;

public:
    Customer(string name, string username, string password, string email, Account account) : account(account)
    {
        this->name = name;
        this->username = username;
        this->password = password;
        this->email = email;
    }
    void display()
    {
        cout << "Name: " << name << endl;
        cout << "Username: " << username << endl;
        cout << "Password: " << password << endl;
        cout << "Email: " << email << endl;
        account.display();
    }
    void deposit(float amount)
    {
        account.deposit(amount);
        time_t now = time(0);
        char *dt = ctime(&now);
        Transaction transaction(dt, "Deposit", amount, account.getBalance(), "Deposit");
        transactions.push_back(transaction);
    }
    void withdraw(float amount)
    {
        account.withdraw(amount);
        time_t now = time(0);
        char *dt = ctime(&now);
        Transaction transaction(dt, "Withdraw", amount, account.getBalance(), "Withdraw");
        transactions.push_back(transaction);
    }
    void changePassword(string password)
    {
        this->password = password;
    }
    string getName()
    {
        return name;
    }
    string getUsername()
    {
        return username;
    }
    string getPassword()
    {
        return password;
    }
    string getEmail()
    {
        return email;
    }
    Account getAccount()
    {
        return account;
    }
    vector<Transaction> getTransactions()
    {
        return transactions;
    }
    float getBalance()
    {
        return account.getBalance();
    }
    bool checkPassword(string password){
        return this->password == password;
    }
    Transaction getTransaction(int index){
        if(index < transactions.size()){
            return transactions[index];
        }
        cout << "Invalid Index" << endl;
        return Transaction("","",0,0,"");
    }
    int getTransactionSize(){
        return transactions.size();
    }
};

class Bank
{
private:
    vector<Customer> customers;
    int nextAccountNumber;

public:
    Bank()
    {
        nextAccountNumber = 1;
    }
    void addCustomer(Customer customer)
    {
        customers.push_back(customer);
        nextAccountNumber++;
    }
    void displayCustomers()
    {
        for (int i = 0; i < customers.size(); i++)
        {
            customers[i].display();
        }
    }
    void displayCustomer(string username)
    {
        for (int i = 0; i < customers.size(); i++)
        {
            if (customers[i].getUsername() == username)
            {
                customers[i].display();
            }
        }
    }
    void deposit(string username, float amount)
    {
        for (int i = 0; i < customers.size(); i++)
        {
            if (customers[i].getUsername() == username)
            {
                customers[i].deposit(amount);
            }
        }
    }
    void withdraw(string username, float amount)
    {
        for (int i = 0; i < customers.size(); i++)
        {
            if (customers[i].getUsername() == username)
            {
                customers[i].withdraw(amount);
            }
        }
    }
    void changePassword(string username, string password, string newPassword)
    {
        for (int i = 0; i < customers.size(); i++)
        {
            if (customers[i].getUsername() == username && customers[i].checkPassword(password))
            {
                customers[i].changePassword(newPassword);
            }
        }
    }

    void displayTransactions(string username)
    {
        for (int i = 0; i < customers.size(); i++)
        {
            if (customers[i].getUsername() == username)
            {
                for (int j = 0; j < customers[i].getTransactions().size(); j++)
                {
                    customers[i].getTransactions()[j].display();
                }
            }
        }
    }
    int getNextAccountNumber()
    {
        return nextAccountNumber;
    }

    void deleteCustomer(string username, string password)
    {
        for (int i = 0; i < customers.size(); i++)
        {
            if (customers[i].getUsername() == username)
            {
                if (customers[i].checkPassword(password))
                {
                    customers.erase(customers.begin() + i);
                }
            }
        }
    }
    float getBalance(string username)
    {
        for (int i = 0; i < customers.size(); i++)
        {
            if (customers[i].getUsername() == username)
            {
                return customers[i].getBalance();
            }
        }
        return 0;
    }
    bool userExist(string username, string password){
        for (int i = 0; i < customers.size(); i++)
        {
            if (customers[i].getUsername() == username && customers[i].checkPassword(password))
            {
                return true;
            }
        }
        return false;
    }
    int getNumberOfCustomers(){
        return customers.size();
    }
    Customer getCustomer(int i){
        return customers[i];
    }
    int getCustomerIndex(string username){
        for (int i = 0; i < customers.size(); i++)
        {
            if (customers[i].getUsername() == username)
            {
                return i;
            }
        }
        return -1;
    }
};

class Database{
    ofstream customerWrite;
    ifstream customerRead;
    ofstream accountWrite;
    ifstream accountRead;
    public:
    Database(){
        customerWrite.open("customer.dat", ios::app);
        customerRead.open("customer.dat");
        accountWrite.open("account.dat", ios::app);
        accountRead.open("account.dat");
    }
    ~Database(){
        customerWrite.close();
        customerRead.close();
        accountWrite.close();
        accountRead.close();
    }
    void fetchFromFile(Bank &bank){
        string name, username, password, email;
        int accountNumber;
        float balance;
        while(customerRead >> name >> username >> password >> email){
            accountRead >> accountNumber >> balance;
            Account account(accountNumber, balance);
            Customer customer(name, username, password, email, account);
            bank.addCustomer(customer);
        }
        for(int i = 0; i < bank.getNumberOfCustomers(); i++){
            string time, type, description;
            float amount, balance;
            ifstream transactionRead;
            transactionRead.open(bank.getCustomer(i).getAccount().getAccountNumber() + ".dat");
            while(transactionRead >> time >> type >> amount >> balance >> description){
                Transaction transaction(time, type, amount, balance, description);
                bank.getCustomer(i).getTransactions().push_back(transaction);
            }
        }
    }
    void addCustomer(Customer customer){
        customerWrite << customer.getName() << " " << customer.getUsername() << " " << customer.getPassword() << " " << customer.getEmail() << endl;
        accountWrite << customer.getAccount().getAccountNumber() << " " << customer.getAccount().getBalance() << endl;
    }
    void addTransaction(Customer customer, Transaction transaction){
        ofstream transactionWrite;
        transactionWrite.open(to_string(customer.getAccount().getAccountNumber()) + ".dat", ios::app);
        transactionWrite  << transaction.getTime() << " " << transaction.getType() << " " << transaction.getAmount() << " " << transaction.getBalance() << " " << transaction.getDescription() << endl;
        transactionWrite.close();
    }
    void deleteCustomer(Customer customer){
        ofstream tempCustomerWrite;
        tempCustomerWrite.open("tempCustomer.dat");
        ifstream tempCustomerRead;
        tempCustomerRead.open("tempCustomer.dat");
        ofstream tempAccountWrite;
        tempAccountWrite.open("tempAccount.dat");
        ifstream tempAccountRead;
        tempAccountRead.open("tempAccount.dat");
        string name, username, password, email;
        int accountNumber;
        float balance;
        while(customerRead >> name >> username >> password >> email){
            accountRead >> accountNumber >> balance;
            if(customer.getAccount().getAccountNumber() != accountNumber){
                tempCustomerWrite << name << " " << username << " " << password << " " << email << endl;
                tempAccountWrite << accountNumber << " " << balance << endl;
            }
        }
        customerWrite.close();
        customerRead.close();
        accountWrite.close();
        accountRead.close();
        remove("customer.dat");
        remove("account.dat");
        rename("tempCustomer.dat", "customer.dat");
        rename("tempAccount.dat", "account.dat");
        customerWrite.open("customer.dat", ios::app);
        customerRead.open("customer.dat");
        accountWrite.open("account.dat", ios::app);
        accountRead.open("account.dat");
    }
    void changePassword(Customer customer, string newPassword){
        ofstream tempCustomerWrite;
        tempCustomerWrite.open("tempCustomer.dat");
        ifstream tempCustomerRead;
        tempCustomerRead.open("tempCustomer.dat");
        ofstream tempAccountWrite;
        tempAccountWrite.open("tempAccount.dat");
        ifstream tempAccountRead;
        tempAccountRead.open("tempAccount.dat");
        string name, username, password, email;
        int accountNumber;
        float balance;
        while(customerRead >> name >> username >> password >> email){
            accountRead >> accountNumber >> balance;
            if(customer.getAccount().getAccountNumber() == accountNumber){
                tempCustomerWrite << name << " " << username << " " << newPassword << " " << email << endl;
                tempAccountWrite << accountNumber << " " << balance << endl;
            }
            else{
                tempCustomerWrite << name << " " << username << " " << password << " " << email << endl;
                tempAccountWrite << accountNumber << " " << balance << endl;
            }
        }
        customerWrite.close();
        customerRead.close();
        accountWrite.close();
        accountRead.close();
        remove("customer.dat");
        remove("account.dat");
        rename("tempCustomer.dat", "customer.dat");
        rename("tempAccount.dat", "account.dat");
        customerWrite.open("customer.dat", ios::app);
        customerRead.open("customer.dat");
        accountWrite.open("account.dat", ios::app);
        accountRead.open("account.dat");
    }

};

class Menu
{
public:
    static void mainMenu()
    {
        cout << "\n*********************************" << endl;
        cout << "Welcome to the Banking System\n";
        cout << "1. Admin\n";
        cout << "2. Customer\n";
        cout << "3. Exit\n";
        cout << "*********************************" << endl;
        cout << "Enter your choice: ";
    }

    static void adminMenu()
    {
        cout << "\n*********************************" << endl;
        cout << "Welcome to the Admin Menu\n";
        cout << "1. Add Customer\n";
        cout << "2. Delete Customer\n";
        cout << "3. Modify Customer\n";
        cout << "4. View Customer\n";
        cout << "5. View All Customers\n";
        cout << "6. Exit\n";
        cout << "*********************************" << endl;
        cout << "Enter your choice: ";
    }

    static void userMenu()
    {
        cout << "\n*********************************" << endl;
        cout << "Welcome to the Customer Menu\n";
        cout << "1. Create Account\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "*********************************" << endl;
        cout << "Enter your choice: ";
    }

    static void afterLoginMenu()
    {
        cout << "\n*********************************" << endl;
        cout << "Welcome to the Customer Menu\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Change Password\n";
        cout << "4. Check Balance\n";
        cout << "5. View Transactions\n";
        cout << "6. Custome details\n";
        cout << "7. Logout\n";
        cout << "*********************************" << endl;
        cout << "Enter your choice: ";
    }
};

void signalHandler(int signum)
{
    cout << "\nBye Bye\n";
    exit(signum);
}

int main()
{
    Database database;
    signal(SIGINT, signalHandler);
    Bank bank;
    database.fetchFromFile(bank);
    while (true)
    {
        int choice;
        Menu::mainMenu();
        cin >> choice;
        switch (choice)
        {
            // Admin
            case 1:
            {
                string adminPassword;
                cout << "Enter the admin password: ";
                cin >> adminPassword;
                if (adminPassword == "admin")
                {
                    while(true){
                        int adminChoice;
                        Menu::adminMenu();
                        cin >> adminChoice;
                        switch (adminChoice)
                        {
                            // Add Customer
                            case 1:
                            {
                                string name, username, password,email;
                                cout << "Enter the name: ";
                                cin.ignore();
                                getline(cin, name);
                                cout << "Enter the username: ";
                                cin >> username;
                                cout << "Enter the password: ";
                                cin >> password;
                                cout << "Enter email address: ";
                                cin >> email;
                                Account account(bank.getNextAccountNumber(), 0);
                                Customer customer(name, username, password, email, account);
                                bank.addCustomer(customer);
                                database.addCustomer(customer);
                                cout << "Succesfully created the account\n";
                                break;
                            }
                            // Delete Customer
                            case 2:
                            {
                                string username, password;
                                cout << "Enter the username: ";
                                cin >> username;
                                cout << "Enter the password: ";
                                cin >> password;
                                bank.deleteCustomer(username, password);
                                database.deleteCustomer(bank.getCustomer(bank.getCustomerIndex(username)));
                                cout << "Succesfully deleted the account\n";
                                break;
                            }
                            // Modify Customer
                            case 3:
                            {
                                string username, password, newPassword;
                                cout << "Enter the username: ";
                                cin >> username;
                                cout << "Enter the current password: ";
                                cin >> password;
                                cout << "Enter the new password: ";
                                cin >> newPassword;
                                bank.changePassword(username, password, newPassword);
                                database.changePassword(bank.getCustomer(bank.getCustomerIndex(username)), newPassword);
                                cout << "Succesfully changed the password\n";
                                break;
                            }
                            // View Customer
                            case 4:
                            {
                                string username;
                                cout << "Enter the username: ";
                                cin >> username;
                                bank.displayCustomer(username);
                                break;
                            }
                            // View All Customers
                            case 5:
                            {
                                bank.displayCustomers();
                                break;
                            }
                            // Exit
                            case 6:
                            {   
                                goto end; 
                                break;
                            }
                            // Default
                            default:
                            {
                                cout << "Invalid choice\n";
                                break;
                            }
                        }
                    }
                    end:
                    break;
                }
                else
                {
                    cout << "Invalid password\n";
                }   
                break;
            }
            // Customer
            case 2:
            {
                while(true){
                    int userChoice;
                    Menu::userMenu();
                    cin >> userChoice;
                    switch (userChoice)
                    {
                        // Create Account
                        case 1:
                        {
                            string name, username, password,email;
                            cout << "Enter the name: ";
                            cin >> name;
                            cout << "Enter the username: ";
                            cin >> username;
                            cout << "Enter the password: ";
                            cin >> password;
                            cout << "Enter email address: ";
                            cin >> email;
                            Account account(bank.getNextAccountNumber(), 0);
                            Customer customer(name, username, password, email, account);
                            bank.addCustomer(customer);
                            database.addCustomer(customer);
                            cout << "Succesfully created the account\n";
                            break;
                        }
                        // Login
                        case 2:
                        {
                            string username, password;
                            cout << "Enter the username: ";
                            cin >> username;
                            cout << "Enter the password: ";
                            cin >> password;
                            if(!bank.userExist(username, password)){
                                cout << "Invalid credentials!\n";
                                break;
                            }
                            int afterLoginChoice;
                            while (true)
                            {
                                Menu::afterLoginMenu();
                                cin >> afterLoginChoice;
                                switch (afterLoginChoice)
                                {
                                    // Deposit
                                    case 1:
                                    {
                                        float amount;
                                        cout << "Enter the amount to deposit: ";
                                        cin >> amount;
                                        bank.deposit(username, amount);
                                        Customer customer = bank.getCustomer(bank.getCustomerIndex(username));
                                        database.addTransaction(customer, customer.getTransaction(customer.getTransactionSize()-1));
                                        cout << "Succesfully deposited the amount\n";
                                        break;
                                    }
                                    // Withdraw
                                    case 2:
                                    {
                                        float amount;
                                        cout << "Enter the amount to withdraw: ";
                                        cin >> amount;
                                        bank.withdraw(username, amount);
                                        Customer customer = bank.getCustomer(bank.getCustomerIndex(username));
                                        database.addTransaction(customer, customer.getTransaction(customer.getTransactionSize()-1));
                                        cout << "Succesfully withdrew the amount\n";
                                        break;
                                    }
                                    // Change Password
                                    case 3:
                                    {
                                        string newPassword;
                                        cout << "Enter the new password: ";
                                        cin >> newPassword;
                                        bank.changePassword(username, password, newPassword);
                                        database.changePassword(bank.getCustomer(bank.getCustomerIndex(username)), newPassword);
                                        break;
                                    }
                                    // Check Balance
                                    case 4:
                                    {
                                        cout << "Your balance is: " << bank.getBalance(username) << endl;
                                        break;
                                    }
                                    // View Transactions
                                    case 5:
                                    {
                                        bank.displayTransactions(username);
                                        break;
                                    }
                                    // Customer details
                                    case 6:
                                    {
                                        bank.displayCustomer(username);
                                        break;
                                    }
                                    // Logout
                                    case 7:
                                    {
                                        goto out;
                                    }
                                    // Default
                                    default:
                                    {
                                        cout << "Invalid choice\n";
                                        break;
                                    }
                                }
                            }
                            out:
                            break;
                        }
                        // Exit
                        case 3:{
                            goto leave;
                            break;
                        }
                        // Default
                        default:
                        {
                            cout << "Invalid choice\n";
                            break;
                        }
                    }
                }
                leave:
                break;
            }
            // Exit
            case 3:
            {
                exit(0);
                break;
            }
            // Default
            default:
            {
                cout << "Invalid choice\n";
                break;
            }
        }
    }
}

/*
Ques - How to open a file with read and write both permission in C++?
Ans - 
    ofstream fout;
    fout.open("file.dat", ios::out | ios::app);
    fout.close();
*/
