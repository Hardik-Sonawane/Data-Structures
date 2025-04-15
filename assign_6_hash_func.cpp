#include <iostream>
#include <string>
using namespace std;

const int HASH_SIZE = 10;       // Number of buckets in hash table
const int MAX_TRACKS = 50;      // Maximum tracks per bucket
const int INFO_FIELDS = 4;      // title, artist, album, duration

class MusicLibrary {
private:
    string library[HASH_SIZE][MAX_TRACKS][INFO_FIELDS]; // 3D storage array
    int trackCount[HASH_SIZE] = {0};                    // Tracks count per bucket

    // Improved hash function
    int getHash(string key) {
        unsigned long hash = 5381;
        for (char c : key) {
            hash = (hash << 5) + hash + c; // djb2 hash algorithm
        }
        return hash % HASH_SIZE;
    }

public:
    void addTrack() {
        if (isFull()) {
            cout << "Library is full!\n";
            return;
        }

        string title, artist, album, duration;
        
        cout << "Enter track title: ";
        getline(cin, title);
        cout << "Enter artist: ";
        getline(cin, artist);
        cout << "Enter album: ";
        getline(cin, album);
        cout << "Enter duration (seconds): ";
        getline(cin, duration);

        int bucket = getHash(title);
        
        library[bucket][trackCount[bucket]][0] = title;
        library[bucket][trackCount[bucket]][1] = artist;
        library[bucket][trackCount[bucket]][2] = album;
        library[bucket][trackCount[bucket]][3] = duration;
        
        trackCount[bucket]++;
        cout << "Track added successfully!\n";
    }

    void searchTrack() {
        string title;
        cout << "Enter track title to search: ";
        getline(cin, title);

        int bucket = getHash(title);
        bool found = false;

        for (int i = 0; i < trackCount[bucket]; i++) {
            if (library[bucket][i][0] == title) {
                cout << "\nTrack Found:\n"
                     << "Title: " << library[bucket][i][0] << "\n"
                     << "Artist: " << library[bucket][i][1] << "\n"
                     << "Album: " << library[bucket][i][2] << "\n"
                     << "Duration: " << library[bucket][i][3] << " seconds\n";
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Track not found!\n";
        }
    }

    void displayAll() {
        cout << "\nMusic Library Contents:\n";
        for (int bucket = 0; bucket < HASH_SIZE; bucket++) {
            for (int track = 0; track < trackCount[bucket]; track++) {
                cout << "• " << library[bucket][track][0] << " - " 
                     << library[bucket][track][1] << " (" 
                     << library[bucket][track][3] << "s)\n";
            }
        }
    }

    bool isFull() {
        for (int i = 0; i < HASH_SIZE; i++) {
            if (trackCount[i] < MAX_TRACKS) {
                return false;
            }
        }
        return true;
    }
};

int main() {
    MusicLibrary lib;
    int choice;

    do {
        cout << "\nMusic Library System\n"
             << "1. Add Track\n"
             << "2. Search Track\n"
             << "3. Display All Tracks\n"
             << "4. Exit\n"
             << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch(choice) {
            case 1: lib.addTrack(); break;
            case 2: lib.searchTrack(); break;
            case 3: lib.displayAll(); break;
            case 4: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}