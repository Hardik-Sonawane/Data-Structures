#include <iostream>
#include <climits>

using namespace std;

class JobTravel {
public:
    int dist[100][100];  
    char city[100];      
    bool visited[100];  
    int parent[100];    
    int numCities, totalCost;

    JobTravel() {
        cout << "Enter number of cities: ";
        cin >> numCities;

        for (int i = 0; i < numCities; i++) {
            city[i] = '\0';  // Initialize with null character
            visited[i] = false;
            parent[i] = -1;
            for (int j = 0; j < numCities; j++) {
                dist[i][j] = INT_MAX;  // Initialize distances to infinity
            }
        }

        cout << "Enter travel distances between cities (from to distance):\n";
        char from, to; 
        int d, idx = 0;
        for (int i = 0; i < numCities * (numCities - 1) / 2; i++) {
            cin >> from >> to >> d;

            int x = getCityIndex(from, idx);
            int y = getCityIndex(to, idx);

            dist[x][y] = d;
            dist[y][x] = d;
        }

        findMST();
    }

    int getCityIndex(char name, int &idx) {
        for (int i = 0; i < idx; i++) {
            if (city[i] == name)
                return i;
        }
        city[idx] = name;
        return idx++;
    }

    void findMST() {
        int key[100];
        totalCost = 0;

        for (int i = 0; i < numCities; i++) {
            key[i] = INT_MAX;
        }

        key[0] = 0;
        parent[0] = -1;

        for (int count = 0; count < numCities - 1; count++) {
            int u = getMinKeyVertex(key);
            visited[u] = true;

            for (int v = 0; v < numCities; v++) {
                if (!visited[v] && dist[u][v] < key[v]) {
                    key[v] = dist[u][v];
                    parent[v] = u;
                }
            }
        }

        printMST();
    }

    int getMinKeyVertex(int key[]) {
        int min = INT_MAX, minIndex = -1;

        for (int i = 0; i < numCities; i++) {
            if (!visited[i] && key[i] < min) {
                min = key[i];
                minIndex = i;
            }
        }
        return minIndex;
    }

    void printMST() {
        cout << "\nMinimum Travel Plan (MST):\n";
        totalCost = 0;
        for (int i = 1; i < numCities; i++) {
            cout << city[parent[i]] << " -> " << city[i] 
                 << " (Distance: " << dist[parent[i]][i] << ")\n";
            totalCost += dist[parent[i]][i];
        }
        cout << "Total Travel Distance: " << totalCost << endl;
    }
};

int main() {
    JobTravel jt;
    return 0;
} 