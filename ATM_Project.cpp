
#include <iostream>
#include "MyString.h"
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;
using namespace MyString;

const string ClientsFileName = "ClientsData.txt";

struct stClient {
    string AccountNumber, Name, PhoneNumber;
    string PINCode;
    double AccountBalance;
    bool MarkForDelete = false;
};

stClient CurrentClient;

void Login();
void ShowATMMainManueScreen();
void ShowCheckBalanceScreen();
void GoBackToATMMainMenu();
void ShowAmountExceedsBalanceMessage();
void ShowQuickWithdrawScreen();
void NormalWithdrawScreen();
bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <stClient>& vClients);


bool UpdateClientByAccountNumber(string AccountNumber);

stClient ConvertLineToRecord(string S1, string Seperator = "#//#") {
    vector <string> vString;
    stClient Client;

    vString = SplitString(S1, Seperator);

    Client.AccountNumber = vString[0];
    Client.PINCode = vString[1];
    Client.Name = vString[2];
    Client.PhoneNumber = vString[3];
    Client.AccountBalance = stod(vString[4]);

    return Client;
}

string ConvertRecordToLine(stClient ClientData, string Seperator = "#//#") {

    string S1 = "";
    S1 = ClientData.AccountNumber + Seperator;
    S1 += ClientData.PINCode + Seperator;
    S1 += ClientData.Name + Seperator;
    S1 += ClientData.PhoneNumber + Seperator;
    S1 += to_string(ClientData.AccountBalance);

    return S1;
}


vector<stClient> LoadClientsDataFromFile(string FileName) {

    vector <stClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open()) {

        string Line;
        stClient Client;

        while (getline(MyFile, Line)) {
            Client = ConvertLineToRecord(Line);
            vClients.push_back(Client);
        }

        MyFile.close();
    }

    return vClients;
}

bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode,stClient &Client) {

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);

    for (stClient C : vClients) {
        if (C.AccountNumber == AccountNumber && C.PINCode == PinCode) {
            Client = C;
            return true;
        }
    }
    return false;
}

bool LoadClientInfo(string AccountNumber, string PinCode) {

    if (FindClientByAccountNumberAndPinCode(AccountNumber, PinCode,CurrentClient))
        return true;
    else
        return false;
}

vector <stClient> SaveClientsDataToFile(string FileName,vector <stClient>& vClients) {

    fstream MyFile;

    MyFile.open(FileName, ios::out);

    string DataLine;
    if (MyFile.is_open()) {
        for (stClient& C : vClients) {
            if (C.MarkForDelete == false) {
                DataLine = ConvertRecordToLine(C);
                          MyFile << DataLine << endl;

            }
        }
        MyFile.close();
    }

    return vClients;
}

bool UpdateClientByAccountNumber(string AccountNumber) {

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    //stClient Client;
    //char Answer = 'n';

  /*  if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
        PrintClientCard(Client);*/

        //cout << "\n\nAre you sure you want to update this client? y/n? ";
        //cin >> Answer;

       // if (toupper(Answer) == 'Y') {

            for (stClient& C : vClients) {
                if (C.AccountNumber == AccountNumber) {
                    C.AccountBalance = CurrentClient.AccountBalance;
                    break;
                }
            }

            SaveClientsDataToFile(ClientsFileName, vClients);

            //cout << "\n\nClient Updated Sucssefuly.\n";

            return true;
        //}

      //  return false;
 }


//Quick Withdraw
enum enQuickWithdrawOptions
{
    e20 = 1, e50 = 2, e100 = 3, e200  = 4,
    e400 = 5, e600 = 6, e800 = 7, e1000 = 8, eExit = 9
};

short getQuickWithDrawAmount(short QuickWithDrawOption)
{
    switch (QuickWithDrawOption) {
    case 1:
        return  20;
    case 2:
        return 50;
    case 3:
        return 100;
    case 4:
        return 200;
    case 5:
        return 400;
    case 6:
        return 600;
    case 7:
        return 800;
    case 8:
        return 1000;
    default:
        return 0;
    }
}

int WithdrawBalance(short Amount, int Balance) {
    return Balance - Amount;
}

bool CheckWithdrawAmount(short Amount, int Balance) {
    if (Amount > Balance)
        return false;
    else
        return true;
}

short ReadQuickWithdrawOption() {
    short num = 0;
    cout << "Choose what do you want to do? [1 to 9]? ";
    cin >> num;

    while (num <= 0 || num > 9) {
        cout << "\nInvalid Input, Please try again.\n";
        cout << "Choose what do you want to do? [1 to 9]? ";
        cin >> num;
    }

    return num;
}

bool QuickWithdraw(short Amount, int Balance) {

    char Answer = 'n';
   /* if (!CheckWithdrawAmount(Amount, Balance)) {
        cout << "\nAmount [ " << Amount << " ] exceeds your balance ( " << Balance << " ).\n";
        return false;
    }*/
    //else {
        cout << "\n\nAre you sure you want to perform this transaction? y/n? ";
        cin >> Answer;

        if (tolower(Answer) == 'y') {
            CurrentClient.AccountBalance = WithdrawBalance(Amount, Balance);
            UpdateClientByAccountNumber(CurrentClient.AccountNumber);
            //vector<stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
            
            //SaveClientsDataToFile(ClientsFileName, CurrentClient);

            cout << "\n\nDone Sucssufully. New Balance is : " << CurrentClient.AccountBalance << endl;
            return true;
        }

        return false;
}

void PerformQuickWithdrawMenueOption(short Option) {

    if (Option == 9) {
        GoBackToATMMainMenu();
        return;
    }

    short WithdrawBalance = getQuickWithDrawAmount(Option);
    if (WithdrawBalance > CurrentClient.AccountBalance) {
        ShowAmountExceedsBalanceMessage();
        ShowQuickWithdrawScreen();
        return;
    }

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithdrawBalance*-1, vClients);
    CurrentClient.AccountBalance -= WithdrawBalance;
}

void ShowQuickWithdrawScreen() {
    system("cls");
    cout << "=========================================================\n";
    cout << "\t\t Quick Withdraw Screen\n";
    cout << "=========================================================\n";

    cout << "\t [1] 20."  << right << setw(15) << "[2] 50. \n";
    cout << "\t [3] 100." << right << setw(15) << "[4] 200. \n";
    cout << "\t [5] 400." << right << setw(15) << "[6] 600. \n";
    cout << "\t [7] 800. " << right << setw(15) << "[8] 1000. \n";
    cout << "\t [9] Exit.\n";
    cout << "=========================================================\n";
    cout << "\nYour Balance is: " << CurrentClient.AccountBalance << endl;
    PerformQuickWithdrawMenueOption((enQuickWithdrawOptions)ReadQuickWithdrawOption());
}


//Deposit Screen

int ReadDepositAmount() {
    int amount;
    do {
        cout << "\nEnter a positive Deposit Amount? ";
        cin >> amount;
    } while (amount <= 0);

    return amount;
}

void PerformDepositOption() {

    int DepositAmount = ReadDepositAmount();
    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, DepositAmount, vClients);
    
    CurrentClient.AccountBalance += DepositAmount;
}

void ShowDepositScreen() {
    cout << "=========================================================\n";
    cout << "\t\t Deposit Screen\n";
    cout << "=========================================================\n";
    PerformDepositOption();
}

//Normal Withdraw
int ReadWithdrawAmount() {
    int number;
    do {
        cout << "\nEnter an amount multiple of 5`s ? ";
        cin >> number;

    } while (number % 5 != 0);

    return number;
}

bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <stClient>& vClients)
{
    char Answer = 'n';
    cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
    cin >> Answer;
    if (Answer == 'y' || Answer == 'Y') {
        for (stClient& C : vClients) {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveClientsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully. New balance is: " << C.AccountBalance;
                return true;
            }
        } return false;
    }
}

void ShowAmountExceedsBalanceMessage() {
    cout << "\nThe amount exceeds your balance, make another choice.";
    cout << "\nPress any key to continue\n";
    system("pause >0");
}

void PerformNormalWithdrawOption() {

    int WithdrawBalance = ReadWithdrawAmount();
    if (WithdrawBalance > CurrentClient.AccountBalance) {
        ShowAmountExceedsBalanceMessage();
        NormalWithdrawScreen();
        return;
    }

    vector <stClient> vClients = LoadClientsDataFromFile(ClientsFileName);
    DepositBalanceToClientByAccountNumber(CurrentClient.AccountNumber, WithdrawBalance * -1, vClients);
    CurrentClient.AccountBalance -= WithdrawBalance;
}

void NormalWithdrawScreen() {

    system("cls");
    cout << "=========================================================\n";
    cout << "\t\t Normal Withdraw Screen\n";
    cout << "=========================================================\n";
    PerformNormalWithdrawOption();
}

//Check Balance
void ShowCheckBalanceScreen() {
    //system("cls");
    cout << "=========================================================\n";
    cout << "\t\t Check Balance Screen\n";
    cout << "=========================================================\n";

    cout << "Your Balance is : " << CurrentClient.AccountBalance << endl;
}

//ATM Main Manue SCreen

enum enATMManueOptions
{
    eQuickWithdraw = 1, eNormalWithdraw = 2,
    eDeposit = 3, eCheckBalanse = 4, eLogout = 5
};

void GoBackToATMMainMenu() {

    cout << "\n\nPress any key to go back to Main Menu...";
    system("pause>0");
    ShowATMMainManueScreen();
}

short ReadATMMainMenuOption() {
    short num = 0;
    cout << "Choose what do you want to do? [1 to 5]? ";
    cin >> num;

    while (num <= 0 || num > 5) {
        cout << "\nInvalid Input, Please try again.\n";
        cout << "Choose what do you want to do? [1 to 5]? ";
        cin >> num;
    }

    return num;
}

void PerformATMMainMenuOptions(enATMManueOptions Option) {

    switch (Option)
    {
    case enATMManueOptions::eQuickWithdraw: {
        system("cls");
        ShowQuickWithdrawScreen();
        GoBackToATMMainMenu();
        break;
    }
    case enATMManueOptions::eNormalWithdraw: {
        system("cls");
        NormalWithdrawScreen();
        GoBackToATMMainMenu();
        break;
    }
    case enATMManueOptions::eDeposit: {
        system("cls");
        ShowDepositScreen();
        GoBackToATMMainMenu();
        break;
    }
    case enATMManueOptions::eCheckBalanse: {
        system("cls");
        ShowCheckBalanceScreen();
        GoBackToATMMainMenu();
        break;
    }
    case enATMManueOptions::eLogout: {
        system("cls");
        Login();
        break;
    }
    }
}

void ShowATMMainManueScreen() {
    short Option = 0;
    system("cls");
    cout << "=========================================================\n";
    cout << "\t\t ATM Main Menu Screen\n";
    cout << "=========================================================\n";

    cout << "\t [1] Quick Withdraw. \n";
    cout << "\t [2] Normal Withdraw. \n";
    cout << "\t [3] Deposit. \n";
    cout << "\t [4] Check Balance. \n";
    cout << "\t [5] Logout. \n";
    cout << "=========================================================\n";
    PerformATMMainMenuOptions((enATMManueOptions)ReadATMMainMenuOption());
}

void Login() {
    bool LoginFailed = false;
    string AccountNumber,PinCode;

    do {

        system("cls");
        cout << "=========================================================\n";
        cout << "\t\t Login Screen\n";
        cout << "=========================================================\n";

        if (LoginFailed) {
            cout << "\nInvalide AccountNumber / PIN Code!\n";
        }
        cout << "\nEnter AccountNumber? ";
        cin >> AccountNumber;
        cout << "\nEnter PIN Code? ";
        cin >> PinCode;

        LoginFailed = !LoadClientInfo(AccountNumber,PinCode);

    } while (LoginFailed);

    ShowATMMainManueScreen();

}

int main()
{
    Login();

    system("pause >0");
}