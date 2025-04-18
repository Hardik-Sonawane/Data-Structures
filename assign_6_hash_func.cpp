#include <iostream>
#include <string>
using namespace std;

const int MAX_BUCKETS = 100;      // Max size of hash table
const int MAX_TRACKS = 50;        // Max tracks per bucket
const int INFO_FIELDS = 4;        // title, artist, album, duration

class MusicLibrary {
private:
    string library[MAX_BUCKETS][MAX_TRACKS][INFO_FIELDS];
    int trackCount[MAX_BUCKETS] = {0};
    int hashSize;

    int getHash(string key) {
        unsigned long hash = 5381;
        for (char c : key) {
            hash = ((hash << 5) + hash) + c;
        }
        return hash % hashSize;
    }

public:
    MusicLibrary(int size) {
        hashSize = size;
    }

    void addTrack() {
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
        int pos = trackCount[bucket];

        if (pos >= MAX_TRACKS) {
            cout << "Bucket is full. Cannot add more tracks.\n";
            return;
        }

        library[bucket][pos][0] = title;
        library[bucket][pos][1] = artist;
        library[bucket][pos][2] = album;
        library[bucket][pos][3] = duration;

        trackCount[bucket]++;
        cout << "Track added at bucket " << bucket << " successfully!\n";
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

        if (!found) cout << "Track not found!\n";
    }

    void updateTrack() {
        string title;
        cout << "Enter track title to update: ";
        getline(cin, title);

        int bucket = getHash(title);
        bool found = false;

        for (int i = 0; i < trackCount[bucket]; i++) {
            if (library[bucket][i][0] == title) {
                cout << "Enter new artist: ";
                getline(cin, library[bucket][i][1]);
                cout << "Enter new album: ";
                getline(cin, library[bucket][i][2]);
                cout << "Enter new duration (seconds): ";
                getline(cin, library[bucket][i][3]);

                cout << "Track updated successfully!\n";
                found = true;
                break;
            }
        }

        if (!found) cout << "Track not found!\n";
    }

    void deleteTrack() {
        string title;
        cout << "Enter track title to delete: ";
        getline(cin, title);

        int bucket = getHash(title);
        bool found = false;

        for (int i = 0; i < trackCount[bucket]; i++) {
            if (library[bucket][i][0] == title) {
                for (int j = i; j < trackCount[bucket] - 1; j++) {
                    for (int k = 0; k < INFO_FIELDS; k++) {
                        library[bucket][j][k] = library[bucket][j + 1][k];
                    }
                }
                trackCount[bucket]--;
                cout << "Track deleted successfully!\n";
                found = true;
                break;
            }
        }

        if (!found) cout << "Track not found!\n";
    }

    void displayAll() {
        cout << "\nMusic Library Contents:\n";
        for (int bucket = 0; bucket < hashSize; bucket++) {
            for (int i = 0; i < trackCount[bucket]; i++) {
                cout << "• " << library[bucket][i][0] << " - " << library[bucket][i][1]
                     << " | Album: " << library[bucket][i][2]
                     << " | Duration: " << library[bucket][i][3] << "s\n";
            }
        }
    }
};

int main() {
    int size;
    cout << "Enter hash table size: ";
    cin >> size;
    cin.ignore(); // clear newline

    MusicLibrary lib(size);
    int choice;

    do {
        cout << "\nMusic Library System\n"
             << "1. Add Track\n"
             << "2. Search Track\n"
             << "3. Update Track\n"
             << "4. Delete Track\n"
             << "5. Display All Tracks\n"
             << "6. Exit\n"
             << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // clear input buffer

        switch (choice) {
            case 1: lib.addTrack(); break;
            case 2: lib.searchTrack(); break;
            case 3: lib.updateTrack(); break;
            case 4: lib.deleteTrack(); break;
            case 5: lib.displayAll(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
