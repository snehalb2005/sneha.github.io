#include <iostream>
#include <vector>
#include <iomanip> // For formatted output

// Structure to represent a destination
struct Destination {
    std::string name;
    double proximity; // Distance from the starting point
    int importance;   // Importance level (higher is better)
};

// Comparator function to compare destinations
bool compareDestinations(const Destination& a, const Destination& b) {
    // Prioritize higher importance, then closer proximity
    if (a.importance != b.importance)
        return a.importance > b.importance;
    return a.proximity < b.proximity;
}

// Merge function
void merge(std::vector<Destination>& destinations, int left, int mid, int right) {
    int n1 = mid - left + 1; // Size of left subarray
    int n2 = right - mid;    // Size of right subarray

    std::vector<Destination> leftArray(n1);
    std::vector<Destination> rightArray(n2);

    // Copy data to temporary arrays
    for (int i = 0; i < n1; ++i)
        leftArray[i] = destinations[left + i];
    for (int i = 0; i < n2; ++i)
        rightArray[i] = destinations[mid + 1 + i];

    int i = 0, j = 0, k = left;

    // Merge the temporary arrays back into the original array
    while (i < n1 && j < n2) {
        if (compareDestinations(leftArray[i], rightArray[j])) {
            destinations[k] = leftArray[i];
            ++i;
        } else {
            destinations[k] = rightArray[j];
            ++j;
        }
        ++k;
    }

    // Copy the remaining elements, if any
    while (i < n1) {
        destinations[k] = leftArray[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        destinations[k] = rightArray[j];
        ++j;
        ++k;
    }
}

// Merge sort function
void mergeSort(std::vector<Destination>& destinations, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        // Sort the left and right halves
        mergeSort(destinations, left, mid);
        mergeSort(destinations, mid + 1, right);

        // Merge the sorted halves
        merge(destinations, left, mid, right);
    }
}

int main() {
    // Predefined destinations
    std::vector<Destination> destinations = {
        {"Museum", 2.5, 8},
        {"Park", 5.0, 6},
        {"Market", 3.0, 7},
        {"Lake", 4.5, 7},
        {"Metro", 1.0, 5},
        {"National Park", 6.0, 9},
        {"Historical Monument", 4.0, 10}
    };

    // Sort destinations using merge sort
    mergeSort(destinations, 0, destinations.size() - 1);

    // Display sorted destinations
    std::cout << "\nRecommended order of visit:\n";
    std::cout << std::left << std::setw(20) << "Destination"
              << std::setw(15) << "Proximity (km)"
              << std::setw(10) << "Importance" << "\n";
    std::cout << std::string(45, '-') << "\n";

    for (const auto& dest : destinations) {
        std::cout << std::left << std::setw(20) << dest.name
                  << std::setw(15) << dest.proximity
                  << std::setw(10) << dest.importance << "\n";
    }

    return 0;
}
#include <iostream>
#include <vector>
#include <unordered_map>
#include <climits>

struct Edge {
    int source;
    int destination;
    int weight; // Weight represents risk level or travel time
};

void bellmanFord(int vertices, int edges, int start, const std::vector<Edge>& graph, const std::unordered_map<int, std::string>& location_names) {
    std::vector<int> distance(vertices, INT_MAX);
    distance[start] = 0;

    // Relax all edges (vertices - 1) times
    for (int i = 0; i < vertices - 1; ++i) {
        for (const auto& edge : graph) {
            if (distance[edge.source] != INT_MAX && distance[edge.source] + edge.weight < distance[edge.destination]) {
                distance[edge.destination] = distance[edge.source] + edge.weight;
            }
        }
    }

    // Check for negative weight cycles
    for (const auto& edge : graph) {
        if (distance[edge.source] != INT_MAX && distance[edge.source] + edge.weight < distance[edge.destination]) {
            std::cout << "Graph contains a negative weight cycle.\n";
            return;
        }
    }

    // Display results
    std::cout << "\nSafest travel distances from location " << location_names.at(start) << ":\n";
    for (int i = 0; i < vertices; ++i) {
        if (distance[i] == INT_MAX) {
            std::cout << location_names.at(i) << ": Unreachable\n";
        } else {
            std::cout << location_names.at(i) << ": " << distance[i] << " risk level\n";
        }
    }
}

int main() {
    const int vertices = 5;
    const int edges = 6;

    std::vector<Edge> graph = {
        {0, 1, 2},
        {0, 2, 4},
        {1, 3, 1},
        {1, 4, 7},
        {2, 3, 3},
        {3, 4, 1}
    };

    std::unordered_map<int, std::string> location_names = {
        {0, "Park"},
        {1, "Museum"},
        {2, "Hotel"},
        {3, "Beach"},
        {4, "Market"}
    };

    // Add bidirectional edges to the graph
    for (int i = 0; i < edges; ++i) {
        graph.push_back({graph[i].destination, graph[i].source, graph[i].weight});
    }

    int start = 0; // Starting location is Park
    bellmanFord(vertices, edges, start, graph, location_names);

    return 0;
}
