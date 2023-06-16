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

vector<string> retrieveAccountDetails(string filename, string account_id) {
    vector<string> account{};
    ifstream infile;
    infile.open(filename);
    string line;
    while (getline(infile, line)) {
        if (line.find(account_id) != string::npos) {
            size_t pos = 0;
            while ((pos = line.find(",")) != string::npos) {
                account.push_back(line.substr(0, pos));
                line.erase(0, pos+1);
            }
        }
    }
    return account;
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

string generateDigitNumbers(int random_limit) {
    string numberString;

    time_t timestamp = time(nullptr);
    numberString += to_string(timestamp);

    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, random_limit - 1);

    while (numberString.length() < random_limit) {
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
            vector<string> account = captureAccountDetails();
            newMeterAccount.push_back(account.at(0));
            newMeterAccount.push_back(account.at(1));
            newMeterAccount.push_back(catergory_name);
            newMeterAccount.push_back(generateDigitNumbers(10));
            return newMeterAccount;
        } else {
            cout << "Invalid category entered. Try again!" << endl;
        }
    } while (category != 0);
    return newMeterAccount;
}

vector<string> payElectricityAccountDetails() {
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

int calculateAmountUnitsPerCategory(string account_category, int bill_amount) {
    if (account_category.compare("RESIDENTIAL") == 0) {
        if ((bill_amount / 89) <= 15) {
            return bill_amount / 89;
        } else if (
            (bill_amount / 89) > 15 &&
            (bill_amount / 89) <= 50
        ) {
            return 15 + ((bill_amount - (15 * 89)) / 212);
        } else if (
            (bill_amount / 89) > 15 &&
            ((bill_amount - (15 * 89)) / 212) > 50
        ) {
            return 15 + (35 * 212) + ((
                bill_amount - ((15 * 89) + (35 * 212))) / 249
            );
        } else {
            return 0;
        }
    } else if (account_category.compare("NON_RESIDENTIAL") == 0) {
        if ((bill_amount / 227) > 100) {
            int amount = bill_amount;
            int units = 0;
            while (amount > 0) {
                if ((amount / 227) > 100) {
                    const int temp_amount = amount - (227 * 100);
                    units += 100;
                    amount = temp_amount;
                }
                if (units > 0) {
                    units += (amount / 255);
                }
            }
            return units;
        } else {
            return bill_amount / 227;
        }
    } else if (account_category.compare("TELECOM_TOWERS") == 0) {
        return bill_amount / 201;
    } else if (account_category.compare(
        "WATER_TREATMENT_PLANTS_AND_WATER_PUMPING_STATIONS") == 0
    ) {
        return bill_amount / 126;
    } else if (account_category.compare("HOTELS") == 0) {
        return bill_amount / 157;
    } else if (account_category.compare("HEALTH_FACILITIES") == 0) {
        return bill_amount / 186;
    } else if (account_category.compare("BROADCASTERS") == 0) {
        return bill_amount / 192;
    } else if (account_category.compare("COMMERCIAL_DATA_CENTERS") == 0) {
        return bill_amount / 179;
    }

    return 0;
}

string insertHyphens(const string& input) {
    string result;
    int count = 0;

    for (char c : input) {
        if (count == 5) {
            result += '-';
            count = 0;
        }

        result += c;
        count++;
    }

    return result;
}

vector<string> calculateUnits(vector<string> accountToBeBilled, vector<string> billDetails) {
    vector<string> bill{};
    int units = calculateAmountUnitsPerCategory(
        accountToBeBilled.at(2), stoi(billDetails.at(1)
    ));
    // apply discount logic
    string token = generateDigitNumbers(20);
    bill.push_back(to_string(units));
    bill.push_back(token);
    return bill;
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
                cout << "Account for " << 
                    account_user.substr(0, account_user.find(",")) <<
                    " successfully created!" << endl;
            } else {
                cout << "Sorry, Meter for ID: " << account.at(3) << " is already registered!" << endl;
            }
        } else if (command == 2) {
            vector<string> billDetails = payElectricityAccountDetails();
            vector<string> accountToBeBilled = retrieveAccountDetails("accounts.csv", billDetails.at(0));
            if (accountToBeBilled.empty()) {
                cout << "Your account doesn't exist! Create it first." << endl;
            } else {
                vector<string> bill = calculateUnits(accountToBeBilled, billDetails);
                string data = billDetails.at(0).append(",")
                    .append(bill.at(0)).append(",")
                    .append(bill.at(1)).append(",")
                    .append("Unused");
                addDataToFile("tokens.csv", data);
                cout << "==================================================================" <<endl;
                cout << "*               E L E C R I L I T Y     B I L L                  *" <<endl;
                cout << "==================================================================" <<endl;
                cout << "CUSTOMER NAME           : " << accountToBeBilled.at(0) <<endl;
                cout << "AMOUNT                  : " << billDetails.at(1) <<endl;
                cout << "ADDITIONAL CHARGES      : " << "0.00" <<endl;
                cout << "UNIT BOUGHT             : " << bill.at(0) <<endl;
                cout << "TOKEN                   : " << insertHyphens(bill.at(1)) <<endl;
                cout << "TOKEN STATUS            : " << "UNUSED" <<endl;
                cout << "==================================================================" <<endl;
            }
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