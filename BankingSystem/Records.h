#pragma once
#include <string>
#include <iostream>

using namespace std;

#ifndef RECORDS_H
#define RECORDS_H

class Records {
private:
	string fullName[5];
	string ageRange[5];
	string address[5];
	string cityStateZip[5];
	string phoneNumber[5];
public:
	void setFullName(string name[], int i);
	void setAgeRange(string age[], int i);
	void setAddress(string address[], int i);
	void setCityStateZip(string cityStateZip[], int i);
	void setPhoneNumber(string phoneNumber[], int i);
	string* getFullName();
	string* getAgeRange();
	string* getAddress();
	string* getCityStateZip();
	string* getPhoneNumber();
};

void Records::setFullName(string name[], int i) {
	for (int i = 0; i < 5; i++) {
		fullName[i] = name[i];
	}
}

void Records::setAgeRange(string age[], int i) {
	for (int i = 0; i < 5; i++) {
		ageRange[i] = age[i];
	}
}

void Records::setAddress(string addressLoc[], int i) {
	for (int i = 0; i < 5; i++) {
		address[i] = addressLoc[i];
	}
}

void Records::setCityStateZip(string cityStateZipLoc[], int i) {
	for (int i = 0; i < 5; i++) {
		cityStateZip[i] = cityStateZipLoc[i];
	}
}

void Records::setPhoneNumber(string phone[], int i) {
	for (int i = 0; i < 5; i++) {
		phoneNumber[i] = phone[i];
	}
}

string* Records::getFullName() {
	return fullName;
}

string* Records::getAgeRange() {
	return ageRange;
}

string* Records::getAddress() {
	return address;
}

string* Records::getCityStateZip() {
	return cityStateZip;
}

string* Records::getPhoneNumber() {
	return phoneNumber;
}
#endif
