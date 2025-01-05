/*CASE 3 The smart city planning there are national parks, amusement parks,
//ashrams ,malls,jewellery markets and various other tourist spots. but the tourists
//face difficulty in reaching to those places and also to reach to hotels and restaurants
//for their stay.*/
#include <iostream>
#include <climits>

using namespace std;

const int INF = INT_MAX;
const int MAX_LOCATIONS = 7;

void dijkstra(int graph[MAX_LOCATIONS][MAX_LOCATIONS], int src, int dist[], int pred[]) {
    bool visited[MAX_LOCATIONS];

    for (int i = 0; i < MAX_LOCATIONS; ++i) {
        dist[i] = INF;
        pred[i] = -1;
        visited[i] = false;
    }

    dist[src] = 0;

    for (int count = 0; count < MAX_LOCATIONS - 1; ++count) {
        int u = -1;

        for (int i = 0; i < MAX_LOCATIONS; ++i) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                u = i;
            }
        }

        visited[u] = true;

        for (int v = 0; v < MAX_LOCATIONS; ++v) {
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                pred[v] = u;
            }
        }
    }
}

void print_path(int pred[], int destination) {
    if (pred[destination] == -1) {
        cout << destination;
        return;
    }
    print_path(pred, pred[destination]);
    cout << " -> " << destination;
}

int main() {
    int graph[MAX_LOCATIONS][MAX_LOCATIONS] = {
        {0, 4, 3, 0, 0, 0, 0},
        {4, 0, 0, 2, 5, 0, 0},
        {3, 0, 0, 7, 0, 0, 0},
        {0, 2, 7, 0, 0, 2, 0},
        {0, 5, 0, 0, 0, 1, 0},
        {0, 0, 0, 2, 1, 0, 6},
        {0, 0, 0, 0, 0, 6, 0}
    };

    int source, destination;
    cout << "Enter source location (0-6)\n0:National Park\n1:Ashram\n2:Main Market\n3.Restaurants\n4.Railway Station\n5.Lakes and Ponds\n6.Museum:\n";
    cin >> source;
    cout << "Enter destination location (0-6): ";
    cin >> destination;

    string location_names[MAX_LOCATIONS] = { "National Park", "Ashram", "Main Market", "Restaurants", "Railway Station", "Lakes and Ponds", "Museum" };
    int dist[MAX_LOCATIONS], pred[MAX_LOCATIONS];
    dijkstra(graph, source, dist, pred);

    if (dist[destination] == INF) {
        cout << "There is no path from " << location_names[source] << " to " << location_names[destination] << endl;
    } else {
        cout << "Minimum shortest path distance from " << location_names[source] << " to " << location_names[destination] << " is " << dist[destination] << "kms"<<endl;
        cout << "Path: ";
        print_path(pred, destination);
        cout << endl;
    }

    return 0;
}
/*case 4:
*/
#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
#include<algorithm>
using namespace std;

// Function to display the main menu
void displayMenu() {
    cout << "\nWelcome to Smart City Special Cab Service\n";
    cout << "1. Book a cab to a location\n";
    cout << "2. Order medicine delivery\n";
    cout << "3. Exit\n";
    cout << "Please enter your choice: ";
}

// Function to find the minimum key value
int minKey(vector<int> &key, vector<bool> &mstSet, int n) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < n; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v], min_index = v;
        }
    }
    return min_index;
}

// Function to find and display the MST using Prim's Algorithm
void primMST(vector<vector<int>> &graph, int src, int dest) {
    int n = graph.size();
    vector<int> parent(n);
    vector<int> key(n, INT_MAX);
    vector<bool> mstSet(n, false);

    key[src] = 0;
    parent[src] = -1;

    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet, n);
        mstSet[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    cout << "\nOptimal Route (MST Path):\n";
    int totalDistance = 0;
    int current = dest;
    vector<int> path;
    while (current != -1) {
        path.push_back(current);
        current = parent[current];
    }
    reverse(path.begin(), path.end());

    for (size_t i = 0; i < path.size(); ++i) {
        if (i > 0) cout << " -> ";
        cout << path[i];
        if (i > 0) totalDistance += graph[path[i - 1]][path[i]];
    }
    cout << "\nTotal Distance: " << totalDistance << " km\n";
}

// Function to simulate cab booking
void bookCab() {
    vector<vector<int>> distances = {
        {0, 2, 3, 6, 5, 4}, // Home
        {2, 0, 4, 6, 8, 7}, // Hospital
        {3, 4, 0, 3, 5, 6}, // Park
        {6, 6, 3, 0, 4, 6}, // Museum
        {5, 8, 5, 4, 0, 2}, // Railway Station
        {4, 7, 6, 6, 2, 0}  // Workplace
    };

    cout << "\nAvailable locations:\n";
    cout << "0. Home\n";
    cout << "1. Hospital\n";
    cout << "2. Park\n";
    cout << "3. Museum\n";
    cout << "4. Railway Station\n";
    cout << "5. Workplace\n";

    int source, destination;
    cout << "Enter the number corresponding to your source location: ";
    cin >> source;
    cout << "Enter the number corresponding to your destination location: ";
    cin >> destination;

    if (source < 0 || source > 5 || destination < 0 || destination > 5 || source == destination) {
        cout << "Invalid choice. Please select valid source and destination locations.\n";
        return;
    }

    primMST(distances, source, destination);
}

// Function to simulate medicine delivery
void orderMedicine() {
    cout << "\nEnter the name of the medicine: ";
    string medicine;
    cin.ignore();  // To clear the input buffer
    getline(cin, medicine);
    cout << "Order placed for " << medicine << ".\n";
}

int main() {
    int choice;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                bookCab();
                break;
            case 2:
                orderMedicine();
                break;
            case 3:
                cout << "Thank you for using our service. Have a great day!\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 3);

    return 0;
}
