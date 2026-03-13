#ifndef PERSONAL_H
#define PERSONAL_H

#include <iostream>
using namespace std;

class PersonalDetails {
    int travelCode;
    int age[20];
    char name[20][20];
    char address[50];
    char phone[15];
    char passport[10][10];
    char familyName[30];
    int numPeople;
    int chargeable;

public:
    PersonalDetails() {
        chargeable = 0;
        numPeople = 0;
    }

    void input(int code) {
    travelCode = code;
    chargeable = 0;

    cout << "Family Name: ";
    cin >> familyName;

    cout << "Address: ";
    cin >> address;

    cout << "Phone: ";
    cin >> phone;

    cout << "Number of people: ";
    cin >> numPeople;

    for (int i = 0; i < numPeople; i++) {
        cout << "\nPassenger " << i + 1 << " name: ";
        cin >> name[i];

        cout << "Age: ";
        cin >> age[i];

        cout << "Passport No: ";
        cin >> passport[i];

        if (age[i] > 5) chargeable++;
    }
}


    void display() {
        cout << "\nFamily: " << familyName
             << "\nAddress: " << address
             << "\nPhone: " << phone << "\n";

        cout << "\nName\tAge\tPassport\n";
        for (int i = 0; i < numPeople; i++) {
            cout << name[i] << "\t" << age[i] << "\t" << passport[i] << "\n";
        }
    }

    int getChargeable() { return chargeable; }
};

#endif
