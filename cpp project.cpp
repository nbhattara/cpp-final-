#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>

using namespace std;

class EntranceForm {
private:
    static int symbolcounter;

    char fname[100];
    char lname[100];
    int age;
    string email;
    string address;
    string phnum;
    string dob;
    string gender;
    string gfname;
    string glname;
    int symbol;

public:
    EntranceForm() {}

    bool isNumeric(const string& str) {
        for (size_t i = 0; i < str.length(); ++i) {
            if (!isdigit(str[i])) {
                return false;
            }
        }
        return true;
    }

    bool isValidDate(const string& str) {
        for (size_t i = 0; i < str.length(); ++i) {
            if (!isdigit(str[i]) && str[i] != '-') {
                return false;
            }
        }
        return true;
    }

    void fillForm() {
        ofstream outFile("entrants.txt", ios::app);

        if (!outFile) {
            cerr << "Unable to open file!" << endl;
            return;
        }

        symbol = symbolcounter++;

        cout << "\t\tFill Out The Form......\n\n";
        cout << "\t\tEnter your Full Name:\n";
        cout << "\t\tEnter First Name: ";
        cin>>fname;
        
        cout << "\t\tEnter Last Name: ";
        cin>>lname;

        cout << "\t\tEnter your age: ";
        cin >> age;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\t\tEnter your email: ";
        cin >> email;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\t\tEnter Your Address: ";
        getline(cin, address);

        cout << "\t\tEnter your phone number (exactly 10 digits): ";
        cin >> phnum;
        while (phnum.length() != 10 || !isNumeric(phnum)) {
            cout << "\t\tInvalid phone number. Please enter exactly 10 digits: ";
            cin >> phnum;
        }

        cout << "\t\tEnter your date of birth (DOB) in yy-mm-dd format: ";
        cin >> dob;
        while (!isValidDate(dob)) {
            cout << "\t\tInvalid date format. Please enter in yy-mm-dd format: ";
            cin >> dob;
        }

        cout << "\t\tEnter your gender (m/f): ";
    	cin >> gender;
    	while (gender != "m" && gender != "f") {
        cout << "\t\tInvalid gender. Please enter 'm' for Male or 'f' for Female: ";
        cin >> gender;
    }

        cout << "\t\tEnter your Guardian Full Name: \n";
        cout << "\t\tEnter First Name: ";
        cin >> gfname;

        cout << "\t\tEnter Last Name: ";
        cin >> glname;

        outFile << "\t\tSymbol Number: " << symbol << endl;
        outFile << "\t\tName: " << fname << " " << lname << endl;
        outFile << "\t\tAge: " << age << endl;
        outFile << "\t\tEmail: " << email << endl;
        outFile << "\t\tAddress: " << address << endl;
        outFile << "\t\tPhone Number: " << phnum << endl;
        outFile << "\t\tDate of Birth (DOB): " << dob << endl;
        outFile << "\t\tGender: " << gender << endl;
        outFile << "\t\tGuardian Name: " << gfname << " " << glname << endl;
        outFile << "---------------------------------------" << endl;

        cout << "______________________________________________________________________________________" << endl;
        cout << "|                       Form submitted successfully!                                 |" << endl;
        cout << "|____________________________________________________________________________________|" << endl;

        outFile.close();
    }

    void display() {
        cout << "\t\tSymbol Number: " << symbol << endl;
        cout << "\t\tName: " << fname << " " << lname << endl;
        cout << "\t\tAge: " << age << endl;
        cout << "\t\tEmail: " << email << endl;
        cout << "\t\tAddress: " << address << endl;
        cout << "\t\tPhone Number: " << phnum << endl;
        cout << "\t\tDate of Birth (DOB): " << dob << endl;
        cout << "\t\tGender: " << gender << endl;
        cout << "\t\tGuardian Name: " << gfname << " " << glname << endl;
        cout << "--------------------------------------------------------------------------------------------------" << endl;
        cout << "                       Press the ENTER key to Return to main menu...                              " << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        clearscreen();
    }

    void search(int searchsymbol) {
        ifstream inFile("entrants.txt");

        if (!inFile) {
            cerr << "        Unable to open file!           " << endl;
            return;
        }

        bool found = false;
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string token;
            ss >> token;
            if (token == "Symbol" && ss >> token >> symbol) {
                if (symbol == searchsymbol) {
                    cout << "                 Entrant Information:                                          " << endl;
                    cout << line << endl;
                    for (int i = 0; i < 8; ++i) {
                        getline(inFile, line);
                        cout << line << endl;
                    }
                    cout << "------------------------------------------------------------------------------" << endl;
                    found = true;
                    break;
                }
            }
        }

        if (!found) {
            cout << "                   Data not found!!                         " << endl;
        }
        cout << "------------------------------------------------------------------------------" << endl;
        cout << "             Press the ENTER key to return to the main menu...                ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        clearscreen();
    }
    void saveSymbolCounter() {
        ofstream outFile("symbolcounter.txt");
        if (outFile.is_open()) {
            outFile << symbolcounter;
            outFile.close();
        }
    }

    void loadSymbolCounter() {
        ifstream inFile("symbolcounter.txt");
        if (inFile.is_open()) {
            inFile >> symbolcounter;
            inFile.close();
        }
    }

    void clearscreen() {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }
};

int EntranceForm::symbolcounter = 20200;

int main() {
    EntranceForm form;
    form.loadSymbolCounter();
    int choice, searchsymbol;

    do {
        cout << "   ............................................................................   " << endl;
        cout << "   |               Welcome to the Entrance Form!                              |   " << endl;
        cout << "   |..........................................................................|   " << endl;
        cout << "   |            1. Fill out the form                                          |   " << endl;
        cout << "   |            2. Display Information                                        |   " << endl;
        cout << "   |            3. Search Your Information                                    |   " << endl;
        cout << "   |            4. Exit                                                       |   " << endl;
        cout << "   |..........................................................................|   " << endl;
        cout << "\t\t\tEnter your choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            form.fillForm();
            break;
        case 2:
            form.display();
            break;
        case 3:
            cout << "\t\t\tEnter Your Symbol Number to search: ";
            cin >> searchsymbol;
            form.search(searchsymbol);
            break;
        case 4:
        	form.saveSymbolCounter();
            cout << "                         Exiting program...                                        " << endl;
            break;
        default:
            cout << "                         Invalid Input!! Please try again.                         " << endl;
            break;
        }

    } while (choice != 4);

    return 0;
}

