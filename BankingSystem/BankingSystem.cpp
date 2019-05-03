// This will be a fully functional banking system. Version 2 for MPA2 adds a menu with several options.
// More features to come!
// Last modified: Brandon Jinright, September 27, 2018, 7:48pm

#include "pch.h"
#include "Records.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <istream>
#include <cmath>
#include <fstream>
#include <cctype>
#include <vector>

using namespace std;

//global variables
string FIRST_NAME;
string LAST_NAME;
string USER_NAME;
string PASSWORD;

static double accountBal = 0;
double deposit;
double withdraw;

int hundred;
int fifty;
int twenty;
int ten;
int five;
int one;

//function prototypes
void adminLogin();
void adminPanel();
void adminSearchUsers(string[], string[]);
void adminSortUsers(string[], string[]);
void adminViewAccounts(string[], string[]);
void depositMoney();
void loginUser();
void logoutUser();
void menuSelection();
void registerUser();
void createPassword(string);
void viewAccount();
void welcomeScreen();
void withdrawMoney();
void resetPassword();
bool checkPassword(char[]);
void swap(string&, string&);
void bubbleSortNames(string[], string[]);
void bubbleSortMoney(string[], string[]);
void createRecords();

int main()
{
	const int ONE = 1,
		TWO = 2;
	int selection;

	welcomeScreen();

	cout << "Are you a new user? \n\n1. Yes\n2. No\n\n";
	cout << "Please enter selection: ";
	cin >> selection;
	cin.ignore();

	switch (selection) {
	case ONE:
		registerUser();

	case TWO:
		loginUser();
	}

	return 0;
}

void adminLogin() {

	const string USER_ADMIN = "admin";
	const string PASS_ADMIN = "pass";
	string userCheck, passCheck;

	cout << "Please enter username: ";
	cin >> userCheck;
	cout << "Please enter password: ";
	cin >> passCheck;

	if (userCheck == USER_ADMIN && passCheck == PASS_ADMIN) {
		cout << "Success! \n\n";

		adminPanel();
	}
	else {
		cout << "Wrong username or password. Please try again. \n\n";
		adminLogin();
	}

}

void adminPanel() {

	int choice;
	int records = 6;
	int i = 0;
	string names[6];
	string money[6];

	fstream inputFile;
	inputFile.open("records.txt");

	while (i < records) {

		getline(inputFile, names[i]);
		getline(inputFile, money[i]);

		i++;
	}

	cout << "\n\n1. View Accounts\n";
	cout << "2. Search Users\n";
	cout << "3. Sort Users\n";
	cout << "4. Create Records\n";
	cout << "5. Back to main menu\n\n";
	cout << "Please enter your choice: ";
	cin >> choice;

	switch (choice) {

	case 1:
		adminViewAccounts(names, money);

	case 2:
		adminSearchUsers(names, money);

	case 3:
		adminSortUsers(names, money);

	case 4:
		createRecords();

	case 5:
		menuSelection();

	default:
		cout << "Invalid choice!";

	}

	inputFile.close();
}

void adminSearchUsers(string names[], string money[]) {
	ofstream outputFile;
	outputFile.open("search_data.txt");

	string value;

	outputFile << "\n\nPlease enter name to search for: ";
	cout << "\n\nPlease enter name to search for: ";
	cin >> value;

	outputFile << "Searching for " << value << " . . .\n\n";
	cout << "Searching for " << value << " . . .\n\n";

	const int SIZE = 6;
	int index = 0;
	int position = -1;
	bool found = false;

	//search for name
	while (index < SIZE && !found) {
		if (names[index] == value) {
			found = true;
			position = index;

			outputFile << "Name matches at position " << index << "." << endl;
			outputFile << names[index] << ", $" << money[index];
			cout << "Name matches at position " << index << "." << endl;
			cout << names[index] << ", $" << money[index];
		} if (names[index] != value) {
			found = false;
			outputFile << "Name does not match at position " << index << "." << endl;
			cout << "Name does not match at position " << index << "." << endl;
		}

		index++;
	}

	outputFile.close();

	adminPanel();
}

void adminSortUsers(string names[], string money[]) {
	ofstream outputFile;
	outputFile.open("sort_accounts.txt");

	int size = 6;
	//sort by name
	bubbleSortNames(names, money);
	outputFile << "\nSorting by name . . .\n\n";
	for (int i = 0; i < size; i++) {
		outputFile << names[i] << endl;
	}

	cout << "\nSorting by name . . .\n\n";
	for (int i = 0; i < size; i++) {
		cout << names[i] << endl;
	}

	//sort by acc value
	bubbleSortMoney(names, money);
	outputFile << "\n\nSorting by account value . . .\n\n";
	for (int x = 0; x < size; x++) {
		outputFile << money[x] << endl;
	}

	cout << "\n\nSorting by account value . . .\n\n";
	for (int x = 0; x < size; x++) {
		cout << money[x] << endl;
	}

	outputFile.close();

	adminPanel();
}

void bubbleSortNames(string names[], string money[]) {
	int maxElement;
	int index;
	int size = 6;

	for (maxElement = size - 1; maxElement > 0; maxElement--) {
		for (index = 0; index < maxElement; index++) {
			if (names[index] > names[index + 1]) {
				swap(names[index], names[index + 1]);
			}
		}
	}
}

void bubbleSortMoney(string names[], string money[]) {

	int maxElement;
	int index;
	int size = 6;

	for (maxElement = size - 1; maxElement > 0; maxElement--) {
		for (index = 0; index < maxElement; index++) {
			if (money[index] > money[index + 1]) {
				swap(money[index], money[index + 1]);
			}
		}
	}

}

void swap(string &a, string&b) {
	string temp = a;
	a = b;
	b = temp;
}

void adminViewAccounts(string names[], string money[]) {

	ofstream outputFile;
	outputFile.open("account_data.txt");

	int i = 0;
	int records;

	do {
		outputFile << "How many names would you like to read? (1-6)\n";
		cout << "How many names would you like to read? (1-6)";
		cin >> records;
	} while (records < 1 || records>6);

	while (i < records) {
		outputFile << names[i] << endl;
		outputFile << money[i] << endl << endl << endl;
		cout << names[i] << endl;
		cout << money[i] << endl << endl << endl;
		i++;
	}
	outputFile.close();

	adminPanel();

}

void depositMoney() {

	do {
		cout << "How much would you like your deposit to be? \nPlease enter denominations below. (# of bills)";
		cout << "\nAmount must not be negative.\n";
		cout << "\n100s ";
		cin >> hundred;
		cout << "50s ";
		cin >> fifty;
		cout << "20s ";
		cin >> twenty;
		cout << "10s ";
		cin >> ten;
		cout << "5s ";
		cin >> five;
		cout << "1s ";
		cin >> one;

		hundred = 100 * hundred;
		fifty = 50 * fifty;
		twenty = 20 * twenty;
		ten = 10 * ten;
		five = 5 * five;
		one = 1 * one;

		deposit = hundred + fifty + twenty + ten + five + one;
		accountBal = accountBal + deposit;
	} while (hundred < 0 || fifty < 0 || twenty < 0 || ten < 0 || five < 0 || one < 0);
	cout << fixed << showpoint << setprecision(2) << "\n\n\nYour new account balance is $" << accountBal << endl << endl;

	menuSelection();
}

void loginUser() {
	fstream inFile;
	inFile.open("create_password.txt");

	string usernameCheck;
	string passwordCheck;
	string filePassCheck;
	inFile >> filePassCheck;

	int attempts = 0;

	while (attempts < 3) {
		cout << "\n\nPlease enter username: ";
		getline(cin, usernameCheck);
		cout << "Please enter password: ";
		getline(cin, passwordCheck);

		if (usernameCheck == USER_NAME && passwordCheck == filePassCheck) {
			cout << "\nSuccess!\n\n";
			menuSelection();
		}
		else {
			cout << "\nPlease try again.\n\n";
			attempts++;
			continue;
		}
	} if (attempts == 3) {
		int resetSelection = 0;

		cout << "Maximum attempts (3) allowed. Would you like to reset your password?" << endl << endl;
		cout << "1. Yes\n2. No";
		cout << "\n\nPlease enter selection: ";
		cin >> resetSelection;
		switch (resetSelection) {
		case 1:
			resetPassword();

		case 2:
			cout << "Program will now terminate. Have a nice day!";
			exit(0);

		default:
			cout << "Invalid selection.";
		}

	}
}

void logoutUser() {
	cout << "\nYou will now be logged out . . .\n\n";
	exit(0);
}

void menuSelection() {
	const int ONE = 1,
		TWO = 2,
		THREE = 3,
		FOUR = 4,
		FIVE = 5;
	int selectionMenu;

	cout << "\n\n1. Deposit Money\n";
	cout << "2. Withdraw Money\n";
	cout << "3. View Account\n";
	cout << "4. Admin Login\n";
	cout << "5. Logout\n\n";
	cout << "Please enter selection: ";
	cin >> selectionMenu;

	switch (selectionMenu) {
	case ONE:
		depositMoney();

	case TWO:
		withdrawMoney();

	case THREE:
		viewAccount();

	case FOUR:
		adminLogin();

	case FIVE:
		logoutUser();
	}
}

void registerUser() {

	cout << "\n\nWhat is your first name? ";
	getline(cin, FIRST_NAME);
	cout << "What is your last name? ";
	getline(cin, LAST_NAME);
	cout << "Please choose a username: ";
	getline(cin, USER_NAME);
	cout << "Please choose a password: ";
	getline(cin, PASSWORD);

	int length = PASSWORD.length();

	if (length < 10 || length > 20) {
		cout << "\nPassword must be at least 10 characters long but no more than 20 characters long.\n\n";
		registerUser();
	}
	else {
		cout << "\nYou have been registered. Returning to main-menu.\n\n";
		createPassword(PASSWORD);
		main();
	}

}

void createPassword(string PASSWORD) {
	fstream outFile;
	outFile.open("create_password.txt", fstream::out);
	outFile << PASSWORD;
	outFile.close();
}

void viewAccount() {

	cout << "\n\n\nHi, " << FIRST_NAME << " " << LAST_NAME << "!" << endl;
	cout << fixed << showpoint << setprecision(2) << "Your current account balance is $" << accountBal << "\n\n\n";

	menuSelection();
}

void welcomeScreen() {
	cout << "Welcome to the Banking System! This system is the second release version\n";
	cout << "for the online banking system. You will need to register first and then you may login.\n";
	cout << "Once logged in you may deposit and withdraw money, view account, and logout of your account.\n";
	cout << "More features will be added in the future. Thank you!\n";
	cout << "Modified by: Brandon Jinright, September 27, 2018 - 6:28pm\n\n\n";
}

void withdrawMoney() {
	do {
		cout << "How much would you like your withdrawl to be? \nPlease enter denominations below. (# of bills)";
		cout << "\nAmount must not be negative.\n";
		cout << "\n100s ";
		cin >> hundred;
		cout << "50s ";
		cin >> fifty;
		cout << "20s ";
		cin >> twenty;
		cout << "10s ";
		cin >> ten;
		cout << "5s ";
		cin >> five;
		cout << "1s ";
		cin >> one;

		hundred = 100 * hundred;
		fifty = 50 * fifty;
		twenty = 20 * twenty;
		ten = 10 * ten;
		five = 5 * five;
		one = 1 * one;

		withdraw = hundred + fifty + twenty + ten + five + one;
		accountBal = accountBal - withdraw;
	} while (hundred < 0 || fifty < 0 || twenty < 0 || ten < 0 || five < 0 || one < 0);
	cout << fixed << showpoint << setprecision(2) << "\n\n\nYour new account balance is $" << accountBal << endl << endl;

	menuSelection();
}

void resetPassword() {

	char newPassword[20];

	cout << "\n New password must contain one uppercase letter, one lowercase letter, \n";
	cout << "one digit from 0-9, one special or punctuation character, and password \n";
	cout << "must be at least 10 characters long but less than 20 characters long.\n\n";

	cout << "Please enter new password: ";
	cin >> newPassword;


	checkPassword(newPassword);



}

bool checkPassword(char newPassword[]) {
	bool isUpperCase = false;
	bool isLowerCase = false;
	bool isNumber = false;
	bool isSpecialChar = false;
	bool size = false;

	int stringSize = strlen(newPassword);
	if (stringSize < 10 || stringSize>20) {
		cout << "\nPassword must be greater than 10 characters but less than 20 characters.\n";
		size = false;
		resetPassword();
	}
	else {
		size = true;
	}

	int charSize = strlen(newPassword);

	for (int count = 0; count < charSize; count++) {
		if (isupper(newPassword[count]))
			isUpperCase = true;
	}

	for (int count = 0; count < charSize; count++) {
		if (islower(newPassword[count]))
			isLowerCase = true;
	}

	for (int count = 0; count < charSize; count++) {
		if (isdigit(newPassword[count]))
			isNumber = true;
	}

	for (int count = 0; count < charSize; count++) {
		if (ispunct(newPassword[count]))
			isSpecialChar = true;
	}

	if (isUpperCase == true && isLowerCase == true && isNumber == true && isSpecialChar == true) {
		cout << "Password meets the criteria! Now returning to main-menu.\n";
		PASSWORD = newPassword;
		main();
	}
	else {
		cout << "Password does not meet the criteria. Please try again. \n\n";
		resetPassword();
	}

	return 0;
}

void createRecords() {

	ofstream outFile;
	outFile.open("customerRecords.txt");

	cout << "Please enter up to 5 records. If you are done enter NA in the field." << endl << endl;

	Records customerRecords;
	std::string fullName[5];
	std::string ageRange[5];
	std::string address[5];
	std::string cityStateZip[5];
	std::string phoneNumber[5];

	for (int i = 0; i < 5; i++) {
		cin.ignore();
		cout << "Please enter full name for customer #" << (i + 1) << ": ";
		std::getline(cin, fullName[i]);
		customerRecords.setFullName(fullName, i);
		cout << "Please enter age for customer #" << (i + 1) << ": ";
		std::getline(cin, ageRange[i]);
		customerRecords.setAgeRange(ageRange, i);
		cout << "Please enter address for customer #" << (i + 1) << ": ";
		std::getline(cin, address[i]);
		customerRecords.setAddress(address, i);
		cout << "Please enter city, state zip code for customer #" << (i + 1) << ": ";
		std::getline(cin, cityStateZip[i]);
		customerRecords.setCityStateZip(cityStateZip, i);
		cout << "Please enter phone number for customer #" << (i + 1) << ": ";
		std::getline(cin, phoneNumber[i]);
		customerRecords.setPhoneNumber(phoneNumber, i);
	}

	string* fullNames = customerRecords.getFullName();
	string* addressDup = customerRecords.getAddress();
	string* ages = customerRecords.getAgeRange();
	string* locations = customerRecords.getCityStateZip();
	string* phoneNumbers = customerRecords.getPhoneNumber();

	cout << "Name" << "\t" << "Age" << "\t" << "Address" << "\t" << "City, State Zip" << "\t" << "Phone Number" << endl;
	cout << "-----------------------------------------------------------------------" << endl;
	for (int x = 0; x < 5; x++) {
		cout << fullNames[x] << "\t" << ages[x] << "\t" << addressDup[x];
		cout << "\t" << locations[x] << "\t" << phoneNumbers[x] << endl;
	}

	outFile << "Name" << "\t" << "Age" << "\t" << "Address" << "\t" << "City, State Zip" << "\t" << "Phone Number" << endl;
	outFile << "-----------------------------------------------------------------------" << endl;
	for (int x = 0; x < 5; x++) {
		outFile << fullNames[x] << "\t" << ages[x] << "\t" << addressDup[x];
		outFile << "\t" << locations[x] << "\t" << phoneNumbers[x] << endl;
	}

	outFile.close();

}