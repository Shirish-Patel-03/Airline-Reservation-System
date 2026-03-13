#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>

using namespace std;

string DATA_FILE = "data/bookings.txt";
string COUNTER_FILE = "data/counter.txt";
string LOG_FILE = "data/logs.txt";

// Capacity limits
int USA_CAP = 50;
int EUROPE_CAP = 40;
int ASIA_CAP = 60;

// ---------------- LOGGING ----------------
void logAction(string action) {
    ofstream log(LOG_FILE, ios::app);
    log << action << endl;
    log.close();
}

// ---------------- LOGIN ----------------
bool login() {
    string user, pass;
    cout << "===== ADMIN LOGIN =====\n";
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pass;

    if(user == "admin" && pass == "1234") {
        logAction("Admin logged in.");
        return true;
    }
    return false;
}

// ---------------- BOOKING ID ----------------
int generateBookingID() {
    ifstream in(COUNTER_FILE);
    int id = 1000;
    if(in.is_open()) {
        in >> id;
        in.close();
    }
    id++;
    ofstream out(COUNTER_FILE);
    out << id;
    out.close();
    return id;
}

// ---------------- CHECK CAPACITY ----------------
bool checkCapacity(int destination, int passengers) {
    int current = 0;
    ifstream file(DATA_FILE);
    string line;

    while(getline(file, line)) {
        if(line.find("Destination:") != string::npos) {
            int dest = stoi(line.substr(line.find(":")+1));
            if(dest == destination) {
                getline(file, line);
                if(line.find("Passengers:") != string::npos) {
                    current += stoi(line.substr(line.find(":")+1));
                }
            }
        }
    }
    file.close();

    int limit = (destination == 1) ? USA_CAP :
                (destination == 2) ? EUROPE_CAP : ASIA_CAP;

    return (current + passengers <= limit);
}

// ---------------- REVENUE SUMMARY ----------------
void revenueSummary() {
    ifstream file(DATA_FILE);
    string line;
    int totalRevenue = 0, bookings = 0;

    while(getline(file, line)) {
        if(line.find("Total:") != string::npos) {
            totalRevenue += stoi(line.substr(line.find(":")+1));
            bookings++;
        }
    }
    file.close();

    cout << "\n--- REVENUE SUMMARY ---\n";
    cout << "Total Bookings: " << bookings << endl;
    cout << "Total Revenue: Rs " << totalRevenue << endl;
}

// ---------------- UPDATE STATUS ----------------
void updateStatus() {
    int id;
    cout << "Enter Booking ID: ";
    cin >> id;

    ifstream in(DATA_FILE);
    ofstream temp("data/temp.txt");
    string line;
    bool found = false;

    while(getline(in, line)) {
        if(line == "BookingID:" + to_string(id)) {
            found = true;
            temp << line << endl;
            getline(in, line); temp << line << endl;
            getline(in, line); temp << line << endl;
            getline(in, line); temp << line << endl;
            getline(in, line); temp << line << endl;
            getline(in, line); temp << line << endl;

            cout << "New Status (Confirmed/Cancelled/Completed): ";
            string status;
            cin >> status;
            temp << "Status:" << status << endl;
            logAction("Status updated for Booking ID " + to_string(id));
            continue;
        }
        temp << line << endl;
    }

    in.close();
    temp.close();
    remove(DATA_FILE.c_str());
    rename("data/temp.txt", DATA_FILE.c_str());

    if(found)
        cout << "Status updated.\n";
    else
        cout << "Booking not found.\n";
}

// ---------------- NEW BOOKING ----------------
void newBooking() {
    int id = generateBookingID();

    string family, phone;
    int people;

    cout << "Family Name: ";
    cin >> family;
    cout << "Phone: ";
    cin >> phone;
    cout << "Number of Passengers: ";
    cin >> people;

    int destination;
    cout << "Destination (1-USA 2-Europe 3-Asia): ";
    cin >> destination;

    if(!checkCapacity(destination, people)) {
        cout << "Capacity exceeded! Booking denied.\n";
        return;
    }

    vector<int> ages(people);
    for(int i = 0; i < people; i++) {
        cout << "Passenger " << i+1 << " Age: ";
        cin >> ages[i];
    }

    int basePrice = (destination == 1) ? 200000 :
                    (destination == 2) ? 150000 : 100000;

    int charged = 0;
    for(int age : ages) {
        if(age > 5) charged++;
    }

    int total = charged * basePrice;
    if(people > 4)
        total *= 0.9;

    ofstream file(DATA_FILE, ios::app);
    file << "BookingID:" << id << endl;
    file << "Family:" << family << endl;
    file << "Phone:" << phone << endl;
    file << "Destination:" << destination << endl;
    file << "Passengers:" << people << endl;
    file << "Total:" << total << endl;
    file << "Status:Confirmed" << endl;
    file << "===" << endl;
    file.close();

    ofstream ticket("tickets/ticket_" + to_string(id) + ".html");
    ticket << "<h1>Cruise Ticket</h1>";
    ticket << "<p>Booking ID: " << id << "</p>";
    ticket << "<p>Status: Confirmed</p>";
    ticket << "<p>Total: Rs " << total << "</p>";
    ticket.close();

    logAction("New booking created ID " + to_string(id));
    cout << "Booking successful! ID: " << id << endl;
}

// ---------------- DELETE BOOKING ----------------
void deleteBooking() {
    int id;
    cout << "Enter Booking ID to delete: ";
    cin >> id;

    ifstream in(DATA_FILE);
    ofstream temp("data/temp.txt");

    string line;
    bool skip = false;

    while(getline(in, line)) {
        if(line == "BookingID:" + to_string(id)) {
            skip = true;
            remove(("tickets/ticket_" + to_string(id) + ".html").c_str());
            logAction("Booking deleted ID " + to_string(id));
            continue;
        }
        if(skip && line == "===") {
            skip = false;
            continue;
        }
        if(!skip)
            temp << line << endl;
    }

    in.close();
    temp.close();
    remove(DATA_FILE.c_str());
    rename("data/temp.txt", DATA_FILE.c_str());

    cout << "Booking deleted.\n";
}

// ---------------- MAIN ----------------
int main() {
    if(!login()) return 0;

    int choice;
    do {
        cout << "\n===== CRUISE MANAGEMENT SYSTEM =====\n";
        cout << "1. New Booking\n";
        cout << "2. Revenue Summary\n";
        cout << "3. Update Booking Status\n";
        cout << "4. Delete Booking\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch(choice) {
            case 1: newBooking(); break;
            case 2: revenueSummary(); break;
            case 3: updateStatus(); break;
            case 4: deleteBooking(); break;
        }

    } while(choice != 5);

    return 0;
}
