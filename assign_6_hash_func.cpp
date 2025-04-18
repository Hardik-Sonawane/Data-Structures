#include <iostream>
#include <string>
using namespace std;

int hashSize; // Will be taken as input
const int MAX_TRACKS = 5; // Max per bucket (small for testing)
const int INFO_FIELDS = 4;

class MusicLibrary {
private:
    string*** library;        // 3D dynamic array
    int* trackCount;          // Track counts per bucket

    // Hash function (djb2)
    int getHash(string key) {
        unsigned long hash = 5381;
        for (char c : key) {
            hash = ((hash << 5) + hash) + c;
        }
        return hash % hashSize;
    }

    // Rehashing (double hashing method)
    int getRehash(string key, int attempt) {
        int h1 = getHash(key);
        int h2 = 7 - (h1 % 7);  // Second hash function
        return (h1 + attempt * h2) % hashSize;
    }

public:
    MusicLibrary(int size) {
        hashSize = size;
        library = new string**[hashSize];
        trackCount = new int[hashSize];

        for (int i = 0; i < hashSize; i++) {
            library[i] = new string*[MAX_TRACKS];
            trackCount[i] = 0;
            for (int j = 0; j < MAX_TRACKS; j++) {
                library[i][j] = new string[INFO_FIELDS];
            }
        }
    }

    void addTrack() {
        string title, artist, album, duration;
        cout << "Enter Title: ";
        cin.ignore();
        getline(cin, title);
        cout << "Enter Artist: ";
        getline(cin, artist);
        cout << "Enter Album: ";
        getline(cin, album);
        cout << "Enter Duration: ";
        getline(cin, duration);

        int index = getHash(title);
        int attempt = 0;

        // Rehashing if bucket is full
        while (trackCount[index] >= MAX_TRACKS && attempt < hashSize) {
            attempt++;
            index = getRehash(title, attempt);
        }

        if (trackCount[index] < MAX_TRACKS) {
            int pos = trackCount[index];
            library[index][pos][0] = title;
            library[index][pos][1] = artist;
            library[index][pos][2] = album;
            library[index][pos][3] = duration;
            trackCount[index]++;
            cout << "Track added at index " << index << "\n";
        } else {
            cout << "Library is full, can't add track.\n";
        }
    }

    void searchTrack() {
        string title;
        cout << "Enter title to search: ";
        cin.ignore();
        getline(cin, title);

        int index = getHash(title);
        int attempt = 0;
        bool found = false;

        while (attempt < hashSize) {
            for (int i = 0; i < trackCount[index]; i++) {
                if (library[index][i][0] == title) {
                    cout << "\nTrack Found at index " << index << ":\n";
                    cout << "Title: " << library[index][i][0] << "\n";
                    cout << "Artist: " << library[index][i][1] << "\n";
                    cout << "Album: " << library[index][i][2] << "\n";
                    cout << "Duration: " << library[index][i][3] << "\n";
                    found = true;
                    return;
                }
            }
            attempt++;
            index = getRehash(title, attempt);
        }

        if (!found) cout << "Track not found.\n";
    }

    void updateTrack() {
        string title;
        cout << "Enter title to update: ";
        cin.ignore();
        getline(cin, title);

        int index = getHash(title);
        int attempt = 0;
        bool updated = false;

        while (attempt < hashSize) {
            for (int i = 0; i < trackCount[index]; i++) {
                if (library[index][i][0] == title) {
                    cout << "Enter new Artist: ";
                    getline(cin, library[index][i][1]);
                    cout << "Enter new Album: ";
                    getline(cin, library[index][i][2]);
                    cout << "Enter new Duration: ";
                    getline(cin, library[index][i][3]);
                    cout << "Track updated.\n";
                    updated = true;
                    return;
                }
            }
            attempt++;
            index = getRehash(title, attempt);
        }

        if (!updated) cout << "Track not found to update.\n";
    }

    void deleteTrack() {
        string title;
        cout << "Enter title to delete: ";
        cin.ignore();
        getline(cin, title);

        int index = getHash(title);
        int attempt = 0;
        bool deleted = false;

        while (attempt < hashSize) {
            for (int i = 0; i < trackCount[index]; i++) {
                if (library[index][i][0] == title) {
                    for (int j = i; j < trackCount[index] - 1; j++) {
                        for (int k = 0; k < INFO_FIELDS; k++) {
                            library[index][j][k] = library[index][j + 1][k];
                        }
                    }
                    trackCount[index]--;
                    cout << "Track deleted.\n";
                    deleted = true;
                    return;
                }
            }
            attempt++;
            index = getRehash(title, attempt);
        }

        if (!deleted) cout << "Track not found to delete.\n";
    }

    void displayAll() {
        cout << "\n--- Music Library ---\n";
        for (int i = 0; i < hashSize; i++) {
            if (trackCount[i] > 0) {
                cout << "Bucket " << i << ":\n";
                for (int j = 0; j < trackCount[i]; j++) {
                    cout << "  - " << library[i][j][0]
                         << " | " << library[i][j][1]
                         << " | " << library[i][j][2]
                         << " | " << library[i][j][3] << "\n";
                }
            }
        }
    }

    ~MusicLibrary() {
        for (int i = 0; i < hashSize; i++) {
            for (int j = 0; j < MAX_TRACKS; j++) {
                delete[] library[i][j];
            }
            delete[] library[i];
        }
        delete[] library;
        delete[] trackCount;
    }
};

int main() {
    int size;
    cout << "Enter size of hash table: ";
    cin >> size;

    MusicLibrary lib(size);
    int choice;

    do {
        cout << "\n1. Add Track\n2. Search Track\n3. Update Track\n4. Delete Track\n5. Display All\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: lib.addTrack(); break;
            case 2: lib.searchTrack(); break;
            case 3: lib.updateTrack(); break;
            case 4: lib.deleteTrack(); break;
            case 5: lib.displayAll(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 6);

    return 0;
}
