#include <iostream>
using namespace std;

// ======= ADJACENCY MATRIX =========
int **matrix = nullptr;
char* cities[20];  
int n;

void insertMatrix() {
    cout << "Enter the total number of cities: ";
    cin >> n;

    matrix = new int*[n];
    for (int i = 0; i < n; i++) {
        matrix[i] = new int[n]();
    }

    for (int i = 0; i < n; i++) {
        cout << "Enter the name of city " << i + 1 << ": ";
        cities[i] = new char[20];
        cin >> cities[i];
    }

    int ch;
    do {
        string scity, ecity;
        int roe, col, flightTime;

        cout << "Enter starting city: ";
        cin >> scity;
        cout << "Enter ending city: ";
        cin >> ecity;
        cout << "Enter flight time (in min): ";
        cin >> flightTime;

        bool found1 = false, found2 = false;
        for (int i = 0; i < n; i++) {
            if (scity == cities[i]) {
                roe = i;
                found1 = true;
            }
            if (ecity == cities[i]) {
                col = i;
                found2 = true;
            }
        }

        if (found1 && found2) {
            matrix[roe][col] = flightTime;
            matrix[col][roe] = flightTime;
        } else {
            cout << "Invalid city name!\n";
        }

        cout << "Insert more? (1 for Yes, 0 for No): ";
        cin >> ch;
    } while (ch == 1);
}

void displayMatrix() {
    cout << "Cities: ";
    for (int i = 0; i < n; i++) {
        cout << cities[i] << " ";
    }
    cout << "\n";

    for (int i = 0; i < n; i++) {
        cout << cities[i] << " -> ";
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

// ======= ADJACENCY LIST =========
class Node {
public:
    string city, airport;
    int time;
    Node* next;

    Node(string cityName, string airportName, int flightTime = 0) {
        city = cityName;
        airport = airportName;
        time = flightTime;
        next = nullptr;
    }
};

Node* cityList[20];  

void insertList() {
    cout << "Enter the total number of cities: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        string cityName, airportName;
        cout << "\nEnter city " << i + 1 << ": ";
        cin >> cityName;
        cout << "Enter airport name: ";
        cin >> airportName;

        cityList[i] = new Node(cityName, airportName);

        int connections;
        cout << "Number of connected cities: ";
        cin >> connections;

        Node* temp = cityList[i];
        for (int j = 0; j < connections; j++) {
            string connectedCity;
            int flightTime;
            cout << "Enter adjacent city " << j + 1 << ": ";
            cin >> connectedCity;
            cout << "Enter flight time (min): ";
            cin >> flightTime;

            temp->next = new Node(connectedCity, "", flightTime);
            temp = temp->next;
        }
    }
}

void displayList() {
    cout << "\nFlight Connections:\n";
    for (int i = 0; i < n; i++) {
        cout << cityList[i]->city << " (" << cityList[i]->airport << ") -> ";
        Node* temp = cityList[i]->next;
        while (temp) {
            cout << temp->city << " (" << temp->time << " min) -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }
}

// ======= MAIN MENU =========
int main() {
    int choice;
    do {
        cout << "\nSelect an operation:\n";
        cout << "1. Adjacency Matrix\n";
        cout << "2. Adjacency List\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                insertMatrix();
                displayMatrix();
                break;
            case 2:
                insertList();
                displayList();
                break;
            case 3:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 3);

    return 0;
}