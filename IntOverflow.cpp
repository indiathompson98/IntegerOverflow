#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef unsigned char byte;

class cashRegister
{
public:
    int getCurrentBalance() const;

    void acceptAmount(int amountIn);

    cashRegister(int cashIn = 500);

private:
    int cashOnHand; //variable to store the cash
                    //in the register
};

class dispenserType
{
public:
    int getNoOfItems() const;

    int getCost() const;

    string getName(int qty) const;

    void makeSale();

    dispenserType(string name, string plural, int setNoOfItems = 50, int setCost = 50);

private:
    int numberOfItems; //variable to store the number of items in the dispenser
    int cost;          //variable to store the cost of an item
    string name;
    string plural;
};

class AutoTellerMachine
{ //Object to represent each customer                  who uses the ATM program
public:
    void CreateNewAccount(string newUsername, string newPassword);
    void AccountLogin(string loginUsername, string loginPassword);
    void SetAccountLogin(int setAccountLocation);
    void AccountMenu();
    int GetAccountLogin() const;
    string GetUsername(int accountID) const;

private:
    int loggedInAccountLocation;
    string username;
    string password;
};

AutoTellerMachine account;
vector<AutoTellerMachine> AccountList; //This vector allows for multiple accounts to be stored so that if more than one person uses the account, all information is retained

void AccountMenu();
void UserMenu();
void showSelection();

void AutoTellerMachine::SetAccountLogin(int setAccountLocation)
{
    loggedInAccountLocation = setAccountLocation;
    return;
}

int AutoTellerMachine::GetAccountLogin() const
{

    return loggedInAccountLocation;
}

void AutoTellerMachine::CreateNewAccount(string newUsername, string newPassword)
{ //Adds the new information to the vector to give the account personalized info

    int accountListSize = AccountList.size();

    AccountList.at(accountListSize - 1).username = newUsername;
    AccountList.at(accountListSize - 1).password = newPassword;
}

void AutoTellerMachine::AccountLogin(string loginUsername, string loginPassword)
{
    int accountListSize = AccountList.size();
    bool successfulLogin = false;
    int accountLocation = 0;
    for (int i = 0; i < accountListSize; i++)
    {
        if (loginUsername == AccountList.at(i).username)
        {
            if (loginPassword == AccountList.at(i).password)
            {
                successfulLogin = true;
                accountLocation = i;
            }
        }
    }
    if (successfulLogin != true)
    {
        cout << endl
             << "******** LOGIN FAILED! ********" << endl
             << endl;
        UserMenu();
    }
    else if (successfulLogin == true)
    {
        SetAccountLogin(accountLocation);
        cout << endl
             << "Access Granted - " << AccountList.at(loggedInAccountLocation).username << endl;
        showSelection();
    }
    return;
}
int cashRegister::getCurrentBalance() const
{
    return cashOnHand;
}
void cashRegister::acceptAmount(int amountIn)
{
    cashOnHand = cashOnHand + amountIn;
}
cashRegister::cashRegister(int cashIn)
{
    if (cashIn >= 0)
        cashOnHand = cashIn;
    else
        cashOnHand = 500;
}
int dispenserType::getNoOfItems() const
{
    return numberOfItems;
}
int dispenserType::getCost() const
{
    return cost;
}
string dispenserType::getName(int qty) const
{
    if (qty < 2) {
        return name;
    }
    return plural;
}
void dispenserType::makeSale()
{
    numberOfItems--;
}
dispenserType::dispenserType(string name, string plural, int setNoOfItems, int setCost)
{
    if (setNoOfItems >= 0)
        numberOfItems = setNoOfItems;
    else
        numberOfItems = 50;
    if (setCost >= 0)
        cost = setCost;
    else
        cost = 50;

    this->name = name;
    this->plural = plural;
}
void UserMenu() //implements a user interface that allows the user to make selections based on what they want to do
{
    char userSelection;
    string createUserId;
    string createUserPass;
    string usernameCheck;
    string passwordCheck;
    cout << "l -> Login" << endl;
    cout << "c -> Create New Account" << endl;
    cout << "q -> Quit" << endl
         << endl
         << ">";
    cin >> userSelection;

    if ((userSelection == 'l') || (userSelection == 'L'))
    { //Checks to make sure the login is valid and if not, couts an error statement
        cout << endl
             << "Please enter your user name: " << endl;
        cin >> usernameCheck;
        cout << "Please enter your password: " << endl;
        cin >> passwordCheck;

        account.AccountLogin(usernameCheck, passwordCheck);
    }
    else if ((userSelection == 'c') || (userSelection == 'C'))
    { //Captures info for a new account
        cout << endl
             << "Please enter your user name: " << endl;
        cin >> createUserId;
        cout << "Please enter your password: " << endl;
        cin >> createUserPass;
        AccountList.push_back(account); //This creates a new object in the vector to be filled with the information gathered
        account.CreateNewAccount(createUserId, createUserPass);
        cout << endl
             << "Thank You! Your account has been created!" << endl
             << endl;
        UserMenu();
    }
    else if ((userSelection == 'q') || (userSelection == 'Q'))
    { //Exits the entire program
        cout << endl
             << "You selected quit!" << endl
             << endl;
    }
    else
    {
        cout << endl
             << "Invalid selection." << endl;
        UserMenu();
    }
    return;
}
void showSelection()
{
    cout << "To select an item, enter " << endl;
    cout << "1 for Candy" << endl;
    cout << "2 for Chips" << endl;
    cout << "3 for Gum" << endl;
    cout << "4 for Cookies" << endl;
    cout << "9 to exit" << endl;
} //end showSelection
void sellProduct(dispenserType &product, cashRegister &pCounter)
{
    int amount;  //variable to hold the amount entered
    int amount2; //variable to hold the extra amount needed
    int qty;     // quantity of item
   
    byte finalCost;
    cout << "Enter quantity:";
    cin >> qty;

    finalCost = qty * product.getCost();
    if (qty > 0) //if the dispenser is not empty
    {
        cout << "Please deposit " << (int)finalCost << " cents" << endl;
        cin >> amount;
        while (amount < finalCost) //User is prompted to enter money until enough is entered
        {
            cout << "Please deposit another " << (int)(finalCost - amount) << " cents" << endl;
            cin >> amount2;
            amount = amount + amount2;
        }
        if (amount >= finalCost)
        {
            pCounter.acceptAmount(amount);
            product.makeSale();
            if (amount > finalCost) //if amount entered is greater than total it returns the proper change
            {
                cout << (amount - finalCost) << " cents is your change." << endl;
            }
            cout << "Collect your " << qty << " " << product.getName(qty) << " at India's Online Shop Warehouse and "
                 << "enjoy." << endl;
        }
        else
            cout << "The amount is not enough. "
                 << "Collect what you deposited." << endl;
        cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl
             << endl;
    }
    else
        cout << "Sorry, this item is sold out." << endl;
} //end sellProduct
int main()
{
    cashRegister counter;
    dispenserType candy("candy", "candies", 100, 50);
    dispenserType chips("chips", "chips", 100, 65);
    dispenserType gum("gum", "gums", 75, 45);
    dispenserType cookies("cookie", "cookies", 100, 85);
    int choice; //variable to hold the selection
    cout << "*** Welcome to India's Online Snack Shop ***" << endl;
    cout << "Please select an option from the menu below: " << endl
         << endl;
    UserMenu();
    cin >> choice;
    while (choice != 9)
    {
        switch (choice)
        {
        case 1:
            sellProduct(candy, counter);
            break;
        case 2:
            sellProduct(chips, counter);
            break;
        case 3:
            sellProduct(gum, counter);
            break;
        case 4:
            sellProduct(cookies, counter);
            break;
        default:
            cout << "Invalid selection." << endl;
        } //end switch
        showSelection();
        cin >> choice;
    } //end while
    return 0;
} //end main
