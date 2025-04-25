#include <iostream>
#include <string>
using namespace std;

const int MAX_BUCKETS = 10;
const int MAX_TRACKS = 10
const int INFO_FIELDS = 4;

class MusicLibrary {
private:
    string library[MAX_BUCKETS][MAX_TRACKS][INFO_FIELDS];
    int trackCount[MAX_BUCKETS] = {0};
    int hashSize;

    // Hash function
    int getHash(string key) {
        unsigned long hash = 5381;
        for (char c : key) {
            hash = ((hash << 5) + hash) + c;
        }
        return hash % hashSize;
    }

public:
    MusicLibrary(int size) {
        hashSize = size <= MAX_BUCKETS ? size : MAX_BUCKETS;
    }

    void addTrack() {
        if (isFull()) {
            cout << "Library is full!\n";
            return;
        }

        string title, artist, album, duration;
        cout << "Enter track title: ";
        getline(cin >> ws, title); // Fix added here
        cout << "Enter artist: ";
        getline(cin, artist);
        cout << "Enter album: ";
        getline(cin, album);
        cout << "Enter duration (seconds): ";
        getline(cin, duration);

        int bucket = getHash(title);
        int originalBucket = bucket;

        while (trackCount[bucket] >= MAX_TRACKS) {
            bucket = (bucket + 1) % hashSize;
            if (bucket == originalBucket) {
                cout << "No space available after rehashing!\n";
                return;
            }
        }

        int idx = trackCount[bucket];
        library[bucket][idx][0] = title;
        library[bucket][idx][1] = artist;
        library[bucket][idx][2] = album;
        library[bucket][idx][3] = duration;
        trackCount[bucket]++;
        cout << "Track added at bucket " << bucket << "!\n";
    }

    void searchTrack() {
        string title;
        cout << "Enter track title to search: ";
        getline(cin >> ws, title); // Fix added here
        int bucket = getHash(title);
        int originalBucket = bucket;

        for (int i = 0; i < hashSize; i++) {
            for (int j = 0; j < trackCount[bucket]; j++) {
                if (library[bucket][j][0] == title) {
                    cout << "\nTrack Found:\n";
                    cout << "Title: " << library[bucket][j][0] << "\n";
                    cout << "Artist: " << library[bucket][j][1] << "\n";
                    cout << "Album: " << library[bucket][j][2] << "\n";
                    cout << "Duration: " << library[bucket][j][3] << " seconds\n";
                    return;
                }
            }
            bucket = (bucket + 1) % hashSize;
            if (bucket == originalBucket) break;
        }

        cout << "Track not found!\n";
    }

    void displayAll() {
        cout << "\nMusic Library Contents:\n";
        for (int i = 0; i < hashSize; i++) {
            for (int j = 0; j < trackCount[i]; j++) {
                cout << "Bucket " << i << ": "
                     << library[i][j][0] << " - "
                     << library[i][j][1] << " ("
                     << library[i][j][3] << "s)\n";
            }
        }
    }

    void updateTrack() {
        string title;
        cout << "Enter title to update: ";
        getline(cin >> ws, title); // Fix added here
        int bucket = getHash(title);
        int originalBucket = bucket;

        for (int i = 0; i < hashSize; i++) {
            for (int j = 0; j < trackCount[bucket]; j++) {
                if (library[bucket][j][0] == title) {
                    cout << "Enter new artist: ";
                    getline(cin, library[bucket][j][1]);
                    cout << "Enter new album: ";
                    getline(cin, library[bucket][j][2]);
                    cout << "Enter new duration: ";
                    getline(cin, library[bucket][j][3]);
                    cout << "Track updated successfully!\n";
                    return;
                }
            }
            bucket = (bucket + 1) % hashSize;
            if (bucket == originalBucket) break;
        }

        cout << "Track not found for update!\n";
    }

    void deleteTrack() {
        string title;
        cout << "Enter title to delete: ";
        getline(cin >> ws, title); // Fix added here
        int bucket = getHash(title);
        int originalBucket = bucket;

        for (int i = 0; i < hashSize; i++) {
            for (int j = 0; j < trackCount[bucket]; j++) {
                if (library[bucket][j][0] == title) {
                    for (int k = j; k < trackCount[bucket] - 1; k++) {
                        for (int f = 0; f < INFO_FIELDS; f++) {
                            library[bucket][k][f] = library[bucket][k + 1][f];
                        }
                    }
                    trackCount[bucket]--;
                    cout << "Track deleted successfully!\n";
                    return;
                }
            }
            bucket = (bucket + 1) % hashSize;
            if (bucket == originalBucket) break;
        }

        cout << "Track not found for deletion!\n";
    }

    bool isFull() {
        for (int i = 0; i < hashSize; i++) {
            if (trackCount[i] < MAX_TRACKS) return false;
        }
        return true;
    }
};

int main() {
    int size;
    cout << "Enter hash table size (max " << MAX_BUCKETS << "): ";
    cin >> size;
    cin.ignore();

    MusicLibrary lib(size);
    int choice;

    do {
        cout << "\nMenu:\n1. Add\n2. Search\n3. Display\n4. Update\n5. Delete\n6. Exit\nChoice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: lib.addTrack(); break;
            case 2: lib.searchTrack(); break;
            case 3: lib.displayAll(); break;
            case 4: lib.updateTrack(); break;
            case 5: lib.deleteTrack(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}
