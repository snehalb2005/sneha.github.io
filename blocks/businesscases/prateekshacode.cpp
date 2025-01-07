/*CASE 3 
    
#include <climits>
#include <iostream>
#include <string>

using namespace std;

const int INF = INT_MAX;
const int MAX_LOCATIONS = 9;

// KMP Pattern Matching Algorithm
void computeLPSArray(string pattern, int M, int lps[])
{
    int length = 0;
    lps[0] = 0;
    int i = 1;

    while (i < M) 
    {
        if (pattern[i] == pattern[length]) 
        {
            length++;
            lps[i] = length;
            i++;
         } else 
        {
            if (length != 0)
            {
                length = lps[length - 1];
            } else 
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

bool KMPSearch(string pattern, string txt)
{
    int M = pattern.length();
    int N = txt.length();

    int lps[M];
    computeLPSArray(pattern, M, lps);

    int i = 0;
    int j = 0;
    while (i < N) {
        if (pattern[j] == txt[i]) 
        {
            j++;
            i++;
        }

        if (j == M) 
        {
            return true;
        } else if (i < N && pattern[j] != txt[i]) 
        {
            if (j != 0)
            {
                j = lps[j - 1];
            } else 
            {
                i = i + 1;
            }
        }
    }
    return false;
}

void dijkstra(int graph[MAX_LOCATIONS][MAX_LOCATIONS], int src, int dist[], int pred[])
{
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
            if (!visited[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) 
            {
                dist[v] = dist[u] + graph[u][v];
                pred[v] = u;
            }
        }
    }
}

void print_path(int pred[], int destination) 
{
    if (pred[destination] == -1) 
    {
        cout << destination;
        return;
    }
    print_path(pred, pred[destination]);
    cout << " -> " << destination;
}

void merge(pair<int, string> arr[], int left, int mid, int right) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    pair<int, string> L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i].first <= R[j].first) 
        {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) 
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(pair<int, string> arr[], int left, int right) 
{
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int main() {
    int graph[MAX_LOCATIONS][MAX_LOCATIONS] = {
        {0, 4, 3, 2, 0, 0, 0, 0, 0},
        {4, 0, 1, 2, 5, 3, 0, 0, 0},
        {3, 1, 0, 7, 2, 4, 0, 0, 0},
        {2, 2, 7, 0, 0, 2, 5, 0, 0},
        {0, 5, 2, 0, 0, 1, 0, 0, 3},
        {0, 3, 4, 2, 1, 0, 6, 2, 1},
        {0, 0, 0, 5, 0, 6, 0, 3, 4},
        {0, 0, 0, 0, 0, 2, 3, 0, 4},
        {0, 0, 0, 0, 3, 1, 4, 4, 0}
    };

    string location_names[MAX_LOCATIONS] = { "Hidden Lake", "Famous Museum", "National Park", "French Art Gallery Museum", "Local History Museum", "Mahatma Gandhi Ashram", "Metro Station", "The Divine Restaurant", "Thakur's Dhaba" };

    int source, destination;
    cout << "Enter source location (0-8):\n";
    for (int i = 0; i < MAX_LOCATIONS; ++i) {
        cout << i << ": " << location_names[i] << endl;
    }
    cin >> source;

    int dist[MAX_LOCATIONS], pred[MAX_LOCATIONS];
    dijkstra(graph, source, dist, pred);

    pair<int, string> sorted_locations[MAX_LOCATIONS];
    for (int i = 0; i < MAX_LOCATIONS; ++i) {
        sorted_locations[i] = { dist[i], location_names[i] };
    }

    mergeSort(sorted_locations, 0, MAX_LOCATIONS - 1);

    cout << "Locations sorted by ascending distance from " << location_names[source] << ":\n";
    for (int i = 0; i < MAX_LOCATIONS; ++i) {
        if (sorted_locations[i].first != INF) {
            cout << sorted_locations[i].second << " - " << sorted_locations[i].first << " kms\n";
        }
    }

    cout << "\nEnter destination location (0-8): ";
    cin >> destination;

    if (dist[destination] == INF) {
        cout << "There is no path from " << location_names[source] << " to " << location_names[destination] << endl;
    } else {
        cout << "Minimum shortest path distance from " << location_names[source] << " to " << location_names[destination] << " is " << dist[destination] << " kms" << endl;
        cout << "Path: ";
        print_path(pred, destination);
        cout << endl;
    }

    return 0;
}


//case 4 Poor accessibility for tourists and citizens with special needs#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
#include <algorithm>
using namespace std;

// Function to display the main menu
void displayMenu() 
{
    cout << "\nWelcome to Smart City Special Cab Service\n";
    cout << "1. Book a cab to a location\n";
    cout << "2. Order medicine delivery\n";
    cout << "3. Exit\n";
    cout << "Please enter your choice: ";
}

// Function to find the minimum key value
int minKey(vector<int> &key, vector<bool> &mstSet, int n) 
{
    int min = INT_MAX, min_index;
    for (int v = 0; v < n; v++) {
        if (!mstSet[v] && key[v] < min) {
            min = key[v], min_index = v;
        }
    }
    return min_index;
}

// Function to find and display the MST using Prim's Algorithm
void primMST(vector<vector<int>> &graph, int src, int dest) 
{
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

// Boyer-Moore pattern matching algorithm
int boyerMooreSearch(const string &text, const string &pattern) 
{
    int m = pattern.size();
    int n = text.size();

    if (m > n) return -1;

    vector<int> badChar(256, -1);
    for (int i = 0; i < m; i++) {
        badChar[pattern[i]] = i;
    }

    int shift = 0;
    while (shift <= (n - m)) {
        int j = m - 1;

        while (j >= 0 && pattern[j] == text[shift + j]) {
            j--;
        }

        if (j < 0) {
            return shift;
        } else {
            shift += max(1, j - badChar[text[shift + j]]);
        }
    }

    return -1;
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
void orderMedicine() 
{
    vector<pair<string, int>> medicines = {
        {"Paracetamol", 50},
        {"Ibuprofen", 100},
        {"Antibiotic", 200},
        {"Vitamin C", 150},
        {"Cough Syrup", 90}
    };

    cout << "\nEnter the name of the medicine: ";
    string medicine;
    cin.ignore();  // To clear the input buffer
    getline(cin, medicine);

    bool found = false;
    for (const auto &item : medicines) {
        if (boyerMooreSearch(item.first, medicine) != -1) {
            cout << "Order placed for " << item.first << " costing Rs." << item.second << ".\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Medicine not found. Please try again.\n";
    }
}

int main() 
{
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
