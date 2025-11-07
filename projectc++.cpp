// Hotel Management System 
// Author: Ronak Kumar Goyal
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

// ------------------- Base Class -------------------
class Person
{
protected:
    string name;
    string phone;

public:
    Person() {}
    Person(string n, string p) : name(n), phone(p) {}
    virtual void showDetails()
    {
        cout << "Name: " << name << "\nPhone: " << phone << endl;
    }
};

// ------------------- Derived Class (Guest) -------------------
class Guest : public Person
{
    int roomNo;
    int days;

public:
    Guest() : Person(), roomNo(0), days(0) {}
    Guest(string n, string p, int r, int d) : Person(n, p), roomNo(r), days(d) {}
    int getRoom() { return roomNo; }
    int getDays() { return days; }
    void showDetails() override
    {
        cout << left << setw(15) << name
             << setw(12) << phone
             << setw(8) << roomNo
             << setw(5) << days << endl;
    }
};

// ------------------- Room Class -------------------
class Room
{
    int roomNo;
    string type;
    float price;
    bool isAvailable;

public:
    Room() : roomNo(0), price(0), isAvailable(true) {}
    Room(int no, string t, float p, bool a = true)
    {
        roomNo = no;
        type = t;
        price = p;
        isAvailable = a;
    }
    void displayRoom()
    {
        cout << left << setw(8) << roomNo
             << setw(12) << type
             << setw(10) << price
             << setw(12) << (isAvailable ? "Yes" : "No") << endl;
    }
    int getNo() { return roomNo; }
    string getType() { return type; }
    float getPrice() { return price; }
    bool available() { return isAvailable; }
    void setAvailability(bool status) { isAvailable = status; }
};

// ------------------- Hotel Management Class -------------------
class Hotel
{
    Room rooms[10];
    int roomCount;

public:
    Hotel()
    {
        roomCount = 5;
        rooms[0] = Room(101, "Single", 1000);
        rooms[1] = Room(102, "Single", 1000);
        rooms[2] = Room(201, "Double", 1800);
        rooms[3] = Room(301, "Deluxe", 2500);
        rooms[4] = Room(401, "Suite", 4000);
    }

    void listRooms()
    {
        cout << "\n--- Room List ---\n";
        cout << left << setw(8) << "No" << setw(12) << "Type"
             << setw(10) << "Price" << setw(12) << "Available" << endl;
        for (int i = 0; i < roomCount; i++)
            rooms[i].displayRoom();
    }

    int findRoom(int rno)
    {
        for (int i = 0; i < roomCount; i++)
            if (rooms[i].getNo() == rno)
                return i;
        return -1;
    }

    void setBooked(int index) { rooms[index].setAvailability(false); }
    void setAvailable(int index) { rooms[index].setAvailability(true); }
    Room getRoom(int index) { return rooms[index]; }
};

// ------------------- File Handling for Guest Data -------------------
class GuestFileHandler
{
public:
    void saveGuest(Guest g)
    {
        ofstream fout("guests.txt", ios::app);
        fout << g.getRoom() << "," << g.getDays() << endl;
        fout.close();
    }

    void showGuests()
    {
        ifstream fin("guests.txt");
        if (!fin)
        {
            cout << "No guest records found.\n";
            return;
        }
        string line;
        cout << "\nSaved Guest Records:\n";
        while (getline(fin, line))
            cout << line << endl;
        fin.close();
    }
};

// ------------------- Main Program -------------------
int main()
{
    Hotel h;
    GuestFileHandler fileHandler;

    int choice;
    Guest guests[50];
    int guestCount = 0;

    cout << "===== HOTEL MANAGEMENT SYSTEM =====\n";
    do
    {
        cout << "\n1. View Rooms"
             << "\n2. Book Room"
             << "\n3. Show Guests"
             << "\n4. Checkout"
             << "\n5. Exit"
             << "\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1)
        {
            h.listRooms();
        }
        else if (choice == 2)
        {
            h.listRooms();
            cout << "Enter room number to book: ";
            int rno;
            cin >> rno;
            cin.ignore();

            int idx = h.findRoom(rno);
            if (idx == -1)
            {
                cout << "Invalid room number.\n";
                continue;
            }
            Room r = h.getRoom(idx);
            if (!r.available())
            {
                cout << "Room already booked.\n";
                continue;
            }

            string name, phone;
            int days;
            cout << "Enter guest name: ";
            getline(cin, name);
            cout << "Enter phone: ";
            getline(cin, phone);
            cout << "Enter number of days: ";
            cin >> days;

            Guest g(name, phone, rno, days);
            guests[guestCount++] = g;
            h.setBooked(idx);
            fileHandler.saveGuest(g);

            float amount = r.getPrice() * days;
            cout << "\nBooking Successful!\n";
            cout << "Guest: " << name << "\nRoom: " << rno
                 << "\nTotal Amount: Rs. " << amount << endl;
        }
        else if (choice == 3)
        {
            cout << "\n--- Current Guests ---\n";
            cout << left << setw(15) << "Name" << setw(12) << "Phone"
                 << setw(8) << "Room" << setw(5) << "Days" << endl;
            for (int i = 0; i < guestCount; i++)
                guests[i].showDetails();

            fileHandler.showGuests();
        }
        else if (choice == 4)
        {
            int rno;
            cout << "Enter room number to checkout: ";
            cin >> rno;
            int idx = h.findRoom(rno);
            if (idx != -1)
            {
                h.setAvailable(idx);
                cout << "Room " << rno << " is now available.\n";
            }
        }
        else if (choice == 5)
        {
            cout << "Thank you for using Hotel Management System!\n";
        }
        else
        {
            cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
