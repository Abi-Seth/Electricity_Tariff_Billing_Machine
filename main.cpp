#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <ctime>
#include <random>
#include <fstream>

using namespace std;

void addDataToFile(string filename, string data) {
    ofstream outfile;
    outfile.open(filename, ios::app);
    outfile << data << endl;
    outfile.close();
}

void deleteLineInFile(string filename, string line_value) {
    ifstream infile;
    infile.open(filename);
    string line;
    stringstream ss;
    while (getline(infile, line)) {
        if (line.find(line_value) != string::npos) {
            continue;
        }
        ss << line << endl;
    }
    infile.close();

    ofstream outfile;
    outfile.open(filename, ios::out);
    outfile << ss.str() << endl;
    outfile.close();
}

bool isDuplicateLineInFile(string filename, string line_value) {
    ifstream infile;
    infile.open(filename);
    string line;
    while (getline(infile, line)) {
        if (line.find(line_value) != string::npos) {
            return true;
        }
    }
    infile.close();
    return false;
}

string transformAccountCatergory(int id) {
    string transformed_category;
    string category = (id == 1) ? "Residential" :
        (id == 2) ? "Non-residential" :
        (id == 3) ? "Telecom Towers" :
        (id == 4) ? "Water Treatment plants and Water pumping stations" :
        (id == 5) ? "Hotels" :
        (id == 6) ? "Health Facilities" :
        (id == 7) ? "Broadcasters" :
        (id == 8) ? "Commercial Data Centers" : "";

    for (char c : category) {
        if (c == ' ' || c == '-') {
            transformed_category += '_';
        } else {
            transformed_category += ::toupper(c);
        }
    }

    return transformed_category;
}

string generateMeterNumber() {
    string numberString;

    time_t timestamp = time(nullptr);
    numberString += to_string(timestamp);

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, 9);

    while (numberString.length() < 10) {
        int digit = distribution(generator);
        numberString += to_string(digit);
    }

    return numberString;
}

bool checkValidNumberValues(const string& str) {
    try {
        size_t pos;
        int number = stoi(str, &pos);
        return (pos == str.length()) ? true : false;
    } catch (const exception&) {
        return false;
    }
}

vector<string> captureAccountDetails() {
    vector<string> account{};

    cout << "ENTER THESE DETAILS ABOUT YOU: " << endl << endl;

    retryNames:
    string accountNames;
    cout << "Your Full Names: ";
    getline(cin >> ws, accountNames);

    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    fflush(stdin);

    if (accountNames.empty()) {
        cout << "Account Names cannot be empty!" << endl;
        goto retryNames;
    }

    retryID:
    string identityCardNumber;
    cout << "National ID: ";
    getline(cin >> ws, identityCardNumber);

    if (identityCardNumber.empty()) {
        cout << "National ID cannot be empty!" << endl;
        goto retryID;
    } else if (identityCardNumber.length() != 16) {
        cout << "National ID should be a series of 16 numbers!" << endl;
        goto retryID;
    }
    // else if (
    //     !checkValidNumberValues(identityCardNumber) || (identityCardNumber.length() != 16)
    // ) {
    //     cout << "National ID should be a series of 16 numbers!" << endl;
    //     goto retryID;
    // }
    account.push_back(accountNames);
    account.push_back(identityCardNumber);

    return account;
}

vector<string> registerNewMeterNumber() {
    vector<string> newMeterAccount{};
    cout << "REGISTRATION PROCESS STARTED" << endl << endl;

    int category;

    do {
        cout << "==================================================================" <<endl;
        cout << "*                C H O O S E    C A T E G O R Y                  *" <<endl;
        cout << "==================================================================" <<endl;
        cout << "1. Residential" << endl;
        cout << "2. Non-residential" << endl;
        cout << "3. Telecom Towers" << endl;
        cout << "4. Water Treatment plants and Water pumping stations" << endl;
        cout << "5. Hotels" << endl;
        cout << "6. Health Facilities" << endl;
        cout << "7. Broadcasters" << endl;
        cout << "8. Commercial Data Centers" << endl;
        cout << "0. Exit" << endl;
        cout << "==================================================================" <<endl;

        cout << "Shell >";
        cin >> category;

        system("cls");

        if (category == 0) {
            continue;
        } else if (category < 9 && category > 0) {
            string catergory_name = transformAccountCatergory(category);
            newMeterAccount = captureAccountDetails();
            newMeterAccount.push_back(catergory_name);
            newMeterAccount.push_back(generateMeterNumber());
            return newMeterAccount;
        } else {
            cout << "Invalid category entered. Try again!" << endl;
        }
    } while (category != 0);
    return newMeterAccount;
}

vector<string> payElectricityBills() {
    vector<string> billDetails{};
    cout << "ELECTRICITY BILL PAYMENT" << endl << endl;

    retryMeterNumber:
    string meterNumber;
    cout << "Enter your Cash Power Number: ";
    getline(cin >> ws, meterNumber);

    fflush(stdin);

    if (meterNumber.empty()) {
        cout << "Cash Power Number is required!" << endl;
        goto retryMeterNumber;
    }

    retryAmount:
    string amount;
    cout << "Enter your Amount: ";
    getline(cin >> ws, amount);

    if (amount.empty()) {
        cout << "Amount is required!" << endl;
        goto retryAmount;
    }

    billDetails.push_back(meterNumber);
    billDetails.push_back(amount);

    return billDetails;
}

int calculateUnits(vector<string> billDetails) {
    int units = 0;
    
    return units;
}

int helperMenu() {
    cout << "Type 3 and press enter to see the help manual" << endl;

    string command_input;
    int command;

    do {
        cout << "Shell >";
        getline(cin, command_input);

        system("cls");

        istringstream iss(command_input);
        if (!(iss >> command)) {
            cout << "Invalid command! Please use numbers only" << endl;
            continue;
        }

        if (command == 1) {
            vector<string> account = registerNewMeterNumber();
            if (!isDuplicateLineInFile("accounts.csv", account.at(3))) {
                string account_user =
                    account.at(0).append(",")
                    .append(account.at(1)).append(",")
                    .append(account.at(2)).append(",")
                    .append(account.at(3));
                addDataToFile("accounts.csv", account_user);
                cout << "Account for " << account.at(0) << " successfully created!";
            } else {
                cout << "Sorry, Meter for ID: " << account.at(3) << " is already registered!";
            }
        } else if (command == 2) {
            vector<string> billDetails = payElectricityBills();
            int units = calculateUnits(billDetails);
        } else if (command == 3) {
            cout << "==================================================================" <<endl;
            cout << "*                      H E L P   M E N U                         *" <<endl;
            cout << "==================================================================" <<endl;
            cout << "1. Register New Meter Number" <<endl;
            cout << "2. Buy Electricity" <<endl;
            cout << "3. Help" <<endl;
            cout << "0. Exit Application" <<endl;
            cout << "==================================================================" <<endl;
        } else if (command == 0) {
            return 0;
        } else {
            cout << "Invalid command entered. Try again!" << endl;
        }

    } while (command != 0);

    return 0;
}

int main() {
    cout << "==================================================================" << endl;
    cout << "*           Welcome to the Electricity Billing Machine           *" << endl;
    cout << "------------------------------------------------------------------" << endl;
    cout << "              Developed in preparation end of Year 3              " << endl;
    cout << "==================================================================" << endl;

    helperMenu();

    cout << "==================================================================" << endl;
    cout << "*                      Bye! See you soon...                      *" << endl;
    cout << "==================================================================" << endl;

    return 0;
}