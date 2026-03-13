# Cruise Management System (C++)

A console-based Cruise Management System developed in C++.
The system simulates the booking workflow of a cruise reservation platform where users can enter passenger information, select travel options, and generate booking details along with billing information.

The project demonstrates core programming concepts such as modular program design, file handling, and structured data management in C++.



## Key Features

* Passenger booking system
* Multi-passenger booking support
* Destination selection (USA / Europe / Asia)
* Deck selection (Top / Middle / Bottom)
* Cabin type selection (AC / Non-AC)
* Automatic fare calculation
* Ticket generation in HTML format
* File-based data storage for booking records
* Simple console interface for user interaction



## Technologies Used

* C++
* Standard Library
* File Handling
* Console Input / Output
* Modular Programming using Header Files



## Project Structure


CruiseProject
│
├── main.cpp            # Main application logic
├── personal.h          # Passenger information module
├── travel.h            # Travel selection and pricing module
│
├── data
│   ├── bookings.txt
│   ├── logs.txt
│   └── counter.txt
│
├── ticket.html         # Generated ticket file
├── bill.txt            # Generated billing file
│
├── README.md
└── .gitignore


## How to Compile

Use a C++ compiler such as **g++**.

```
g++ main.cpp -o cruise
```


## How to Run

After compilation run:

```
./cruise
```

The program will prompt the user to enter:

* Family name
* Address
* Phone number
* Number of passengers
* Passenger details
* Destination
* Deck preference
* Cabin type

After completing the booking, the system displays the booking details and generates ticket and billing files.

---

## Example Ticket Output

```
==============================
        CRUISE TICKET
==============================

Family Name: Kumar
Address: Bhilai
Phone: 9876543212

Passengers:

Name        Age        Passport
Raj         25         P123
Rani        22         P124

Destination: USA
Deck: Middle
Cabin: AC

Total Passengers: 2
Total Amount: Rs 512000
```

---

## Learning Objectives

This project helps demonstrate:

* File-based data persistence
* Modular C++ program design
* Reservation system workflow
* Console-based application development
* Structured project organization

---

## Possible Future Improvements

* Graphical User Interface (GUI)
* Database integration
* Online reservation system
* Payment processing integration
* Admin dashboard for booking management

---


## Future Improvements

Possible upgrades for the system:

• Graphical User Interface (GUI)  
• Database integration (MySQL / SQLite)  
• Online booking portal  
• Admin dashboard for managing bookings  
• Payment system integration  

---

## Author

Shirish Patel  
Bhilai Institute of Technology, Durg


## License

This project is intended for educational purposes.
