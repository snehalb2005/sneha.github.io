//case 5
//difficulty in itinerary Planning
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// Trie Node Definition
class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    vector<pair<string, int>> suggestions; // Pair of suggestion and ranking
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

// Trie Class Definition
class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    // Insert a key with its suggestions and rankings into the Trie
    void insert(const string& key, const vector<pair<string, int>>& suggestions) {
        TrieNode* node = root;
        for (char ch : key) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->isEndOfWord = true;
        node->suggestions = suggestions;
    }

    // Search for suggestions for a given prefix
    vector<pair<string, int>> search(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            if (node->children.find(ch) == node->children.end()) {
                return {}; // No suggestions found
            }
            node = node->children[ch];
        }
        return node->isEndOfWord ? node->suggestions : vector<pair<string, int>>{};
    }

    // Helper function to get all suggestions from the Trie
    void getAllSuggestions(TrieNode* node, unordered_set<string>& allSuggestions, unordered_map<string, int>& allSuggestionsWithRanks) {
        if (node->isEndOfWord) {
            for (const auto& suggestion : node->suggestions) {
                allSuggestions.insert(suggestion.first); // Insert only unique suggestions
                allSuggestionsWithRanks[suggestion.first] = suggestion.second; // Store ranks as well
            }
        }
        for (auto& child : node->children) {
            getAllSuggestions(child.second, allSuggestions, allSuggestionsWithRanks);
        }
    }

    // Public method to access root node for getting all suggestions
    TrieNode* getRoot() {
        return root;
    }
};

// Merge Sort Function to rank suggestions
void merge(vector<pair<string, int>>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<pair<string, int>> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].second >= R[j].second) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
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

void mergeSort(vector<pair<string, int>>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Main Function
int main() {
    Trie trie;

    // Insert categories with suggestions and their rankings
    trie.insert("holy", {{"Ashrams", 5}, {"Temples", 3}});
    trie.insert("historic", {{"Ashrams", 5}, {"Temples", 3}});
    trie.insert("gallery", {{"Museums", 5}, {"Art Gallery", 2}});
    trie.insert("exhibition", {{"Museums", 5}, {"Art Gallery", 2}});
    trie.insert("nature", {{"National Parks", 5}, {"Lalpari Lake", 4}, {"Farms", 3}});
    trie.insert("wildlife", {{"National Parks", 5}, {"Lalpari Lake", 4}, {"Farms", 3}});
    trie.insert("shopping", {{"Malls", 4}, {"Main Market", 3}, {"Jewelry Streets", 2}});
    trie.insert("kids", {{"Amusement Parks", 5}, {"Malls", 3}, {"Parks", 2}});
    trie.insert("food", {{"Food Street", 4}, {"Restaurants", 3}});
    trie.insert("adventure", {{"Amusement Parks", 5}, {"Boating", 4}});

    int choice;
    do {
        cout << "\nMenu:\n";
        cout << "1. Search for suggestions by keyword\n";
        cout << "2. Display all places with their ranks\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            string input;
            cout << "Enter a keyword to search for suggestions: ";
            cin >> input;

            vector<pair<string, int>> results = trie.search(input);
            if (!results.empty()) {
                // Sort suggestions using Merge Sort
                mergeSort(results, 0, results.size() - 1);

                cout << "Suggestions for \"" << input << "\" (ranked):\n";
                for (const auto& suggestion : results) {
                    cout << "- " << suggestion.first << " (Rank: " << suggestion.second << ")\n";
                }
            } else {
                cout << "No suggestions found for \"" << input << "\".\n";
            }
        }
        else if (choice == 2) {
            unordered_set<string> uniqueSuggestions;
            unordered_map<string, int> allSuggestionsWithRanks;
            TrieNode* root = trie.getRoot(); // Access the root node
            trie.getAllSuggestions(root, uniqueSuggestions, allSuggestionsWithRanks);  // Collect all unique suggestions and their ranks

            if (!uniqueSuggestions.empty()) {
                vector<pair<string, int>> allSuggestions;

                // Collect the unique suggestions and their respective ranks
                for (const string& place : uniqueSuggestions) {
                    allSuggestions.push_back({place, allSuggestionsWithRanks[place]});
                }

                // Sort all suggestions using Merge Sort based on their rank
                mergeSort(allSuggestions, 0, allSuggestions.size() - 1);

                cout << "All places with their ranks (sorted):\n";
                for (const auto& suggestion : allSuggestions) {
                    cout << "- " << suggestion.first << " (Rank: " << suggestion.second << ")\n";
                }
            } else {
                cout << "No suggestions found.\n";
            }
        }
        else if (choice == 3) {
            cout << "Exiting...\n";
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 3);

    return 0;
}


//Tourist Safety
#include <iostream>
#include <vector>
#include <climits>
#include <unordered_map>
#include <string>
#include <algorithm>

using namespace std;

// Define a structure for an edge
struct Edge {
    int u, v, weight;
};

// Disjoint Set (Union-Find) to help Kruskal's algorithm
struct DisjointSet {
    vector<int> parent, rank;

    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unionSets(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY) {
            if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
            } else if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }
};

// Function for Kruskal's Algorithm to find MST
vector<Edge> kruskal(int numPlaces, vector<Edge>& edges) {
    DisjointSet ds(numPlaces);
    vector<Edge> mst;

    // Sort edges by weight (distance)
    sort(edges.begin(), edges.end(), [](const Edge& e1, const Edge& e2) {
        return e1.weight < e2.weight;
    });

    // Process edges and add to MST
    for (const auto& edge : edges) {
        int u = edge.u, v = edge.v, w = edge.weight;
        if (ds.find(u) != ds.find(v)) {
            mst.push_back(edge);
            ds.unionSets(u, v);
        }
    }

    return mst;
}

// Bellman-Ford algorithm to find the shortest path from the source
vector<int> bellmanFord(int numPlaces, const vector<Edge>& edges, int source) {
    vector<int> dist(numPlaces, INT_MAX);
    dist[source] = 0;

    // Relax all edges |V| - 1 times
    for (int i = 0; i < numPlaces - 1; i++) {
        for (const auto& edge : edges) {
            if (dist[edge.u] != INT_MAX && dist[edge.u] + edge.weight < dist[edge.v]) {
                dist[edge.v] = dist[edge.u] + edge.weight;
            }
        }
    }

    return dist;
}

// Function to assign risk level based on the distance
string getRiskLevel(int distance) {
    if (distance < 50)
        return "Low Risk";
    else if (distance < 100)
        return "Moderate Risk";
    else
        return "High Risk";
}

int main() {
    vector<string> places = {
        "Museums", "Amusement Parks", "National Parks", "Ashrams", "Malls", "Food Street",
        "Boating", "Lalpari Lake", "Temples", "Restaurants", "Farms", "Main Market",
        "Art Gallery", "Jewelry Streets", "Parks"
    };

    unordered_map<string, int> placeIndex;
    for (int i = 0; i < places.size(); i++) {
        placeIndex[places[i]] = i;
    }

    int numPlaces = places.size();
    vector<Edge> edges;

    // Predefined distances (in kilometers) between places
    edges = {
        {0, 1, 20}, {1, 0, 20},  // Museums <-> Amusement Parks
        {0, 2, 50}, {2, 0, 50},  // Museums <-> National Parks
        {0, 3, 10}, {3, 0, 10},  // Museums <-> Ashrams
        {0, 4, 30}, {4, 0, 30},  // Museums <-> Malls
        {1, 5, 60}, {5, 1, 60},  // Amusement Parks <-> Food Street
        {2, 6, 40}, {6, 2, 40},  // National Parks <-> Boating
        {3, 7, 25}, {7, 3, 25},  // Ashrams <-> Lalpari Lake
        {4, 8, 70}, {8, 4, 70},  // Malls <-> Temples
        {5, 9, 90}, {9, 5, 90},  // Food Street <-> Restaurants
        {6, 10, 110}, {10, 6, 110}, // Boating <-> Farms
        {7, 11, 55}, {11, 7, 55}, // Lalpari Lake <-> Main Market
        {8, 12, 45}, {12, 8, 45}, // Temples <-> Art Gallery
        {9, 13, 80}, {13, 9, 80}, // Restaurants <-> Jewelry Streets
        {10, 14, 35}, {14, 10, 35}, // Farms <-> Parks
        // Add more predefined distances as needed
    };

    // Menu-driven program
    int choice;
    while (true) {
        cout << "Menu:\n";
        cout << "1. Calculate Risk Level from Source\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Clear input buffer after reading integer
        cin.ignore();

        if (choice == 1) {
            string sourcePlace;
            cout << "Enter the source place: ";
            getline(cin, sourcePlace);

            // Check if the source place exists
            if (placeIndex.find(sourcePlace) == placeIndex.end()) {
                cout << "Invalid place name. Please enter a valid place from the list.\n";
                continue;
            }

            // Run Bellman-Ford algorithm on the original graph (not MST)
            vector<int> distances = bellmanFord(numPlaces, edges, placeIndex[sourcePlace]);

            // Output the risk levels for all places
            cout << "Risk Levels from " << sourcePlace << ":\n";
            for (int i = 0; i < numPlaces; i++) {
                if (distances[i] == INT_MAX)
                    cout << places[i] << ": Unreachable\n";
                else
                    cout << places[i] << ": " << getRiskLevel(distances[i])
                         << " (Distance: " << distances[i] << " km)\n";
            }
        } else if (choice == 2) {
            cout << "Exiting program.\n";
            break;
        } else {
            cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
