#ifndef TRAVEL_H
#define TRAVEL_H

#include <iostream>
using namespace std;

class TravelDetails {
    int destination;
    int deck;
    int cabin;
    int people;

public:
    void input() {
        cout << "Destination (1-USA 2-Europe 3-Asia): ";
        cin >> destination;

        cout << "Deck (1-Top 2-Middle 3-Bottom): ";
        cin >> deck;

        cout << "Cabin (1-AC 2-Non AC): ";
        cin >> cabin;
    }

    void acceptPeople(int p) {
        people = p;
    }

    void bill() {
        int baseCost = (destination == 1) ? 250000 :
                       (destination == 2) ? 130000 : 75000;

        int deckCost = (deck == 1) ? 7500 :
                       (deck == 2) ? 5000 : 1000;

        int cabinCost = (cabin == 1) ? 5000 : 2000;

        int total = people * (baseCost + deckCost + cabinCost);

        cout << "\n------ BILL ------";
        cout << "\nPeople charged: " << people;
        cout << "\nTotal Amount: Rs " << total << "\n";
    }
};

#endif
