//1. overcrowding of tourist places of attraction
//quick sort                                                                                                                                                                                                                                                                 #include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Attraction {
public:
    std::string name;
    std::string type;
    int visitorCount;

    Attraction(std::string n, std::string t, int v) : name(n), type(t), visitorCount(v) {}
};

class TouristSystem {
private:
    std::vector<Attraction> attractions;

    void quickSort(int low, int high) {
        if (low < high) {
            int pivotIndex = partition(low, high);
            quickSort(low, pivotIndex - 1);
            quickSort(pivotIndex + 1, high);
        }
    }

    int partition(int low, int high) {
        int pivot = attractions[high].visitorCount;
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (attractions[j].visitorCount < pivot) {
                ++i;
                std::swap(attractions[i], attractions[j]);
            }
        }
        std::swap(attractions[i + 1], attractions[high]);
        return i + 1;
    }

public:
    void addAttraction(std::string name, std::string type, int visitorCount) {
        attractions.push_back(Attraction(name, type, visitorCount));
    }

    void displayAllAttractions() {
        quickSort(0, attractions.size() - 1);

        std::cout << "All attractions and their visitor counts:\n";
        for (const auto& attraction : attractions) {
            std::cout << attraction.name << " (" << attraction.type << ") - Visitor Count: " << attraction.visitorCount << "\n";
        }
    }
};

int main() {
    TouristSystem system;

    // Adding some attractions (name, type, visitor count)
    system.addAttraction("Main Market", "Market", 900);
    system.addAttraction("Hidden Lake", "Lake", 1100);
    system.addAttraction("Famous Museum", "Museum", 800);
    system.addAttraction("National Park", "Park", 900);
    system.addAttraction("Art Gallery", "Museum", 750);
    system.addAttraction("Local History Museum", "Museum", 800);
    system.addAttraction("Mahatma Gandhi Ashram", "Historical", 1000);
    system.addAttraction("Metro", "Transportation", 2500);

    system.displayAllAttractions();

    return 0;
}

//BST

#include <iostream>
#include <string>

struct Attraction {
    std::string name;
    std::string type;
    int visitorCount;

    Attraction(std::string n, std::string t, int v) : name(n), type(t), visitorCount(v) {}
};

struct TreeNode {
    Attraction* attraction;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Attraction* a) : attraction(a), left(nullptr), right(nullptr) {}
};

class BST {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, Attraction* attraction) {
        if (node == nullptr) {
            return new TreeNode(attraction);
        }
        if (attraction->visitorCount < node->attraction->visitorCount) {
            node->left = insert(node->left, attraction);
        } else {
            node->right = insert(node->right, attraction);
        }
        return node;
    }

    void inOrder(TreeNode* node) {
        if (node != nullptr) {
            inOrder(node->left);
            std::cout << node->attraction->name << " (" << node->attraction->type << ") - Visitor Count: " << node->attraction->visitorCount << "\n";
            inOrder(node->right);
        }
    }

    Attraction* search(TreeNode* node, int visitorCount) {
        if (node == nullptr || node->attraction->visitorCount == visitorCount) {
            return node != nullptr ? node->attraction : nullptr;
        }
        if (visitorCount < node->attraction->visitorCount) {
            return search(node->left, visitorCount);
        } else {
            return search(node->right, visitorCount);
        }
    }

public:
    BST() : root(nullptr) {}

    void addAttraction(std::string name, std::string type, int visitorCount) {
        Attraction* attraction = new Attraction(name, type, visitorCount);
        root = insert(root, attraction);
    }

    void displayAllAttractions() {
        inOrder(root);
    }

    Attraction* findAttractionByVisitorCount(int visitorCount) {
        return search(root, visitorCount);
    }
};

int main() {
    BST system;
    system.addAttraction("Main Market", "Market", 900);
    system.addAttraction("Hidden Lake", "Lake", 1100);
    system.addAttraction("Famous Museum", "Museum", 800);
    system.addAttraction("National Park", "Park", 900);
    system.addAttraction("Art Gallery", "Museum", 750);
    system.addAttraction("Local History Museum", "Museum", 800);
    system.addAttraction("Mahatma Gandhi Ashram", "Historical", 1000);
    system.addAttraction("Metro", "Transportation", 2500);

    std::cout << "All attractions sorted by visitor count:\n";
    system.displayAllAttractions();

    return 0;
}
//AVL

#include <iostream>
#include <string>
#include <algorithm>

struct Attraction {
    std::string name;
    std::string type;
    int visitorCount;

    Attraction(std::string n, std::string t, int v) : name(n), type(t), visitorCount(v) {}
};

struct TreeNode {
    Attraction* attraction;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode(Attraction* a) : attraction(a), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    TreeNode* root;

    int height(TreeNode* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(TreeNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    TreeNode* rightRotate(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;

        return x;
    }

    TreeNode* leftRotate(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = std::max(height(x->left), height(x->right)) + 1;
        y->height = std::max(height(y->left), height(y->right)) + 1;

        return y;
    }

    TreeNode* insert(TreeNode* node, Attraction* attraction) {
        if (node == nullptr) {
            return new TreeNode(attraction);
        }

        if (attraction->visitorCount < node->attraction->visitorCount) {
            node->left = insert(node->left, attraction);
        } else {
            node->right = insert(node->right, attraction);
        }

        node->height = 1 + std::max(height(node->left), height(node->right));

        int bf = balanceFactor(node);

        if (bf > 1 && attraction->visitorCount < node->left->attraction->visitorCount) {
            return rightRotate(node);
        }

        if (bf < -1 && attraction->visitorCount > node->right->attraction->visitorCount) {
            return leftRotate(node);
        }

        if (bf > 1 && attraction->visitorCount > node->left->attraction->visitorCount) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (bf < -1 && attraction->visitorCount < node->right->attraction->visitorCount) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inOrder(TreeNode* node) {
        if (node != nullptr) {
            inOrder(node->left);
            std::cout << node->attraction->name << " (" << node->attraction->type << ") - Visitor Count: " << node->attraction->visitorCount << "\n";
            inOrder(node->right);
        }
    }

public:
    AVLTree() : root(nullptr) {}

    void addAttraction(std::string name, std::string type, int visitorCount) {
        Attraction* attraction = new Attraction(name, type, visitorCount);
        root = insert(root, attraction);
    }

    void displayAllAttractions() {
        inOrder(root);
    }
};

int main() {
    AVLTree system;
    system.addAttraction("Main Market", "Market", 900);
    system.addAttraction("Hidden Lake", "Lake", 1100);
    system.addAttraction("Famous Museum", "Museum", 800);
    system.addAttraction("National Park", "Park", 900);
    system.addAttraction("Art Gallery", "Museum", 750);
    system.addAttraction("Local History Museum", "Museum", 800);
    system.addAttraction("Mahatma Gandhi Ashram", "Historical", 1000);
    system.addAttraction("Metro", "Transportation", 2500);

    std::cout << "All attractions sorted by visitor count:\n";
    system.displayAllAttractions();

    return 0;
}


//2. Inefficient Travel and Accommodation Bookings
//DIJIKSTRA                                                                                                                                                                                                                                                         #include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Accommodation {
public:
    std::string name;
    std::string location;
    double distanceToDestination; // in kilometers
    double costPerNight; // in currency units

    Accommodation(std::string n, std::string l, double d, double c)
        : name(n), location(l), distanceToDestination(d), costPerNight(c) {}
};

class TravelPlan {
public:
    std::string origin;
    std::string destination;
    double travelCost;
    double travelTime; // in hours

    TravelPlan(std::string o, std::string d, double c, double t)
        : origin(o), destination(d), travelCost(c), travelTime(t) {}
};

class TouristSystem {
private:
    std::vector<Accommodation> accommodations;
    std::vector<TravelPlan> travelPlans;

public:
    void addAccommodation(std::string name, std::string location, double distance, double cost) {
        accommodations.push_back(Accommodation(name, location, distance, cost));
    }

    void addTravelPlan(std::string origin, std::string destination, double cost, double time) {
        travelPlans.push_back(TravelPlan(origin, destination, cost, time));
    }

    void displayAllAccommodations() {
        std::cout << "All accommodations and their details within the city:\n";
        for (const auto& accommodation : accommodations) {
            std::cout << accommodation.name << " in " << accommodation.location
                      << " - Distance: " << accommodation.distanceToDestination << " km, Cost per night: "
                      << accommodation.costPerNight << "\n";
        }
    }

    void displayAllTravelPlans() {
        std::cout << "All travel plans and their details within the city:\n";
        for (const auto& travelPlan : travelPlans) {
            std::cout << "From " << travelPlan.origin << " to " << travelPlan.destination
                      << " - Cost: " << travelPlan.travelCost << ", Travel time: "
                      << travelPlan.travelTime << " hours\n";
        }
    }
};

int main() {
    TouristSystem system;

    // Adding some accommodations (name, location, distance to destination, cost per night)
    system.addAccommodation("Main Market", "Market Area", 9.0, 150.0);
    system.addAccommodation("Hidden Lake", "Lakeside", 3.0, 80.0);
    system.addAccommodation("Famous Museum", "Downtown", 8.0, 100.0);
    system.addAccommodation("National Park", "Parkside", 2.0, 90.0);
    system.addAccommodation("Art Gallery", "Downtown", 3.0, 70.0);
    system.addAccommodation("Local History Museum", "Historic District", 4.0, 60.0);
    system.addAccommodation("Mahatma Gandhi Ashram", "Historical Site", 1.0, 40.0);
    system.addAccommodation("Metro", "Transportation Hub", 2.0, 20.0);

    // Adding some travel plans (origin, destination, cost, travel time)
    system.addTravelPlan("Market Area", "Lakeside", 10.0, 0.5);
    system.addTravelPlan("Downtown", "Parkside", 20.0, 1.0);
    system.addTravelPlan("Transportation Hub", "Historical Site", 15.0, 0.75);
    system.addTravelPlan("Historic District", "Downtown", 5.0, 0.25);

    // Displaying all accommodations and travel plans within the city
    system.displayAllAccommodations();
    printf("\n");
    system.displayAllTravelPlans();

    return 0;
}
//5.difficulty in itinerary planning
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip> // For formatted output

// Structure to represent a destination
struct Destination {
    std::string name;
    double proximity; // Distance from the starting point
    int importance;   // Importance level (higher is better)
};

// Comparator function to sort destinations
bool compareDestinations(const Destination& a, const Destination& b) {
    // Prioritize higher importance, then closer proximity
    if (a.importance != b.importance)
        return a.importance > b.importance;
    return a.proximity < b.proximity;
}

int main() {
    int n;
    std::cout << "Enter the number of destinations: ";
    std::cin >> n;

    std::vector<Destination> destinations(n);

    // Input destinations
    for (int i = 0; i < n; ++i) {
        std::cout << "Enter name, proximity (km), and importance (1-10) for destination " << i + 1 << ": ";
        std::cin >> destinations[i].name >> destinations[i].proximity >> destinations[i].importance;
    }

    // Sort destinations based on importance and proximity
    std::sort(destinations.begin(), destinations.end(), compareDestinations);

    // Display sorted destinations
    std::cout << "\nRecommended order of visit:\n";
    std::cout << std::left << std::setw(15) << "Destination" 
              << std::setw(15) << "Proximity (km)" 
              << std::setw(15) << "Importance" << "\n";
    std::cout << std::string(45, '-') << "\n";

    for (const auto& dest : destinations) {
        std::cout << std::left << std::setw(15) << dest.name 
                  << std::setw(15) << dest.proximity 
                  << std::setw(15) << dest.importance << "\n";
    }

    return 0;
}
//HEAP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

struct Accommodation {
    std::string name;
    std::string location;
    double proximity;
    double cost;

    Accommodation(std::string n, std::string l, double p, double c) : name(n), location(l), proximity(p), cost(c) {}
};

struct TravelPlan {
    std::string origin;
    std::string destination;
    double cost;
    double travelTime;

    TravelPlan(std::string o, std::string d, double c, double t) : origin(o), destination(d), cost(c), travelTime(t) {}
};

struct Attraction {
    std::string name;
    std::string type;
    int visitorCount;

    Attraction(std::string n, std::string t, int v) : name(n), type(t), visitorCount(v) {}
};

// Comparator for the max heap
struct CompareAttraction {
    bool operator()(Attraction* a1, Attraction* a2) {
        return a1->visitorCount < a2->visitorCount;
    }
};

class TouristSystem {
private:
    std::priority_queue<Attraction*, std::vector<Attraction*>, CompareAttraction> attractionHeap;
    std::vector<Accommodation> accommodations;
    std::vector<TravelPlan> travelPlans;

public:
    void addAccommodation(std::string name, std::string location, double proximity, double cost) {
        accommodations.push_back(Accommodation(name, location, proximity, cost));
    }

    void addTravelPlan(std::string origin, std::string destination, double cost, double travelTime) {
        travelPlans.push_back(TravelPlan(origin, destination, cost, travelTime));
    }

    void addAttraction(std::string name, std::string type, int visitorCount) {
        Attraction* attraction = new Attraction(name, type, visitorCount);
        attractionHeap.push(attraction);
    }

    void displayAllAttractions() {
        std::priority_queue<Attraction*, std::vector<Attraction*>, CompareAttraction> tempHeap = attractionHeap;
        std::cout << "All attractions sorted by visitor count:\n";
        while (!tempHeap.empty()) {
            Attraction* attraction = tempHeap.top();
            tempHeap.pop();
            std::cout << attraction->name << " (" << attraction->type << ") - Visitor Count: " << attraction->visitorCount << "\n";
        }
    }

    void displayAllAccommodations() {
        std::cout << "All accommodations:\n";
        for (const auto& accommodation : accommodations) {
            std::cout << accommodation.name << " (" << accommodation.location << ") - Proximity: " << accommodation.proximity << ", Cost: " << accommodation.cost << "\n";
        }
    }

    void displayAllTravelPlans() {
        std::cout << "All travel plans:\n";
        for (const auto& travelPlan : travelPlans) {
            std::cout << travelPlan.origin << " -> " << travelPlan.destination << " - Cost: " << travelPlan.cost << ", Travel Time: " << travelPlan.travelTime << "\n";
        }
    }
};

int main() {
    TouristSystem system;

    // Adding accommodations
    system.addAccommodation("Main Market", "Market Area", 9.0, 150.0);
    system.addAccommodation("Hidden Lake", "Lakeside", 3.0, 80.0);
    system.addAccommodation("Famous Museum", "Downtown", 8.0, 100.0);
    system.addAccommodation("National Park", "Parkside", 2.0, 90.0);
    system.addAccommodation("Art Gallery", "Downtown", 3.0, 70.0);
    system.addAccommodation("Local History Museum", "Historic District", 4.0, 60.0);
    system.addAccommodation("Mahatma Gandhi Ashram", "Historical Site", 1.0, 40.0);
    system.addAccommodation("Metro", "Transportation Hub", 2.0, 20.0);

    // Adding travel plans
    system.addTravelPlan("Market Area", "Lakeside", 10.0, 0.5);
    system.addTravelPlan("Downtown", "Parkside", 20.0, 1.0);
    system.addTravelPlan("Transportation Hub", "Historical Site", 15.0, 0.75);
    system.addTravelPlan("Historic District", "Downtown", 5.0, 0.25);

    // Adding attractions
    system.addAttraction("Main Market", "Market", 900);
    system.addAttraction("Hidden Lake", "Lake", 1100);
    system.addAttraction("Famous Museum", "Museum", 800);
    system.addAttraction("National Park", "Park", 900);
    system.addAttraction("Art Gallery", "Museum", 750);
    system.addAttraction("Local History Museum", "Museum", 800);
    system.addAttraction("Mahatma Gandhi Ashram", "Historical", 1000);
    system.addAttraction("Metro", "Transportation", 2500);

    // Displaying data
    system.displayAllAccommodations();
    std::cout << "\n";
    system.displayAllTravelPlans();
    std::cout << "\n";
    system.displayAllAttractions();

    return 0;
}
//FENWICK TreeNode
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

struct Accommodation {
    std::string name;
    std::string location;
    double proximity;
    double cost;

    Accommodation(std::string n, std::string l, double p, double c) : name(n), location(l), proximity(p), cost(c) {}
};

struct TravelPlan {
    std::string origin;
    std::string destination;
    double cost;
    double travelTime;

    TravelPlan(std::string o, std::string d, double c, double t) : origin(o), destination(d), cost(c), travelTime(t) {}
};

struct Attraction {
    std::string name;
    std::string type;
    int visitorCount;

    Attraction(std::string n, std::string t, int v) : name(n), type(t), visitorCount(v) {}
};

class FenwickTree {
private:
    std::vector<int> tree;
    int maxSize;

public:
    FenwickTree(int size) : maxSize(size) {
        tree.resize(size + 1, 0);
    }

    void update(int index, int value) {
        while (index <= maxSize) {
            tree[index] += value;
            index += index & -index;
        }
    }

    int query(int index) {
        int sum = 0;
        while (index > 0) {
            sum += tree[index];
            index -= index & -index;
        }
        return sum;
    }

    int rangeQuery(int left, int right) {
        return query(right) - query(left - 1);
    }
};

class TouristSystem {
private:
    std::unordered_map<int, Attraction*> attractionsMap;
    FenwickTree visitorCountTree;
    std::vector<Accommodation> accommodations;
    std::vector<TravelPlan> travelPlans;

public:
    TouristSystem(int size) : visitorCountTree(size) {}

    void addAccommodation(std::string name, std::string location, double proximity, double cost) {
        accommodations.push_back(Accommodation(name, location, proximity, cost));
    }

    void addTravelPlan(std::string origin, std::string destination, double cost, double travelTime) {
        travelPlans.push_back(TravelPlan(origin, destination, cost, travelTime));
    }

    void addAttraction(std::string name, std::string type, int visitorCount) {
        Attraction* attraction = new Attraction(name, type, visitorCount);
        int index = visitorCount;
        attractionsMap[index] = attraction;
        visitorCountTree.update(index, 1);
    }

    void displayAllAttractions() {
        std::cout << "All attractions sorted by visitor count:\n";
        for (const auto& entry : attractionsMap) {
            std::cout << entry.second->name << " (" << entry.second->type << ") - Visitor Count: " << entry.second->visitorCount << "\n";
        }
    }

    void displayAllAccommodations() {
        std::cout << "All accommodations:\n";
        for (const auto& accommodation : accommodations) {
            std::cout << accommodation.name << " (" << accommodation.location << ") - Proximity: " << accommodation.proximity << ", Cost: " << accommodation.cost << "\n";
        }
    }

    void displayAllTravelPlans() {
        std::cout << "All travel plans:\n";
        for (const auto& travelPlan : travelPlans) {
            std::cout << travelPlan.origin << " -> " << travelPlan.destination << " - Cost: " << travelPlan.cost << ", Travel Time: " << travelPlan.travelTime << "\n";
        }
    }

    int getVisitorCountRange(int left, int right) {
        return visitorCountTree.rangeQuery(left, right);
    }
};

int main() {
    TouristSystem system(3000);

    // Adding accommodations
    system.addAccommodation("Main Market", "Market Area", 9.0, 150.0);
    system.addAccommodation("Hidden Lake", "Lakeside", 3.0, 80.0);
    system.addAccommodation("Famous Museum", "Downtown", 8.0, 100.0);
    system.addAccommodation("National Park", "Parkside", 2.0, 90.0);
    system.addAccommodation("Art Gallery", "Downtown", 3.0, 70.0);
    system.addAccommodation("Local History Museum", "Historic District", 4.0, 60.0);
    system.addAccommodation("Mahatma Gandhi Ashram", "Historical Site", 1.0, 40.0);
    system.addAccommodation("Metro", "Transportation Hub", 2.0, 20.0);

    // Adding travel plans
    system.addTravelPlan("Market Area", "Lakeside", 10.0, 0.5);
    system.addTravelPlan("Downtown", "Parkside", 20.0, 1.0);
    system.addTravelPlan("Transportation Hub", "Historical Site", 15.0, 0.75);
    system.addTravelPlan("Historic District", "Downtown", 5.0, 0.25);

    // Adding attractions
    system.addAttraction("Main Market", "Market", 900);
    system.addAttraction("Hidden Lake", "Lake", 1100);
    system.addAttraction("Famous Museum", "Museum", 800);
    system.addAttraction("National Park", "Park", 900);
    system.addAttraction("Art Gallery", "Museum", 750);
    system.addAttraction("Local History Museum", "Museum", 800);
    system.addAttraction("Mahatma Gandhi Ashram", "Historical", 1000);
    system.addAttraction("Metro", "Transportation", 2500);

    // Displaying data
    system.displayAllAccommodations();
    std::cout << "\n";
    system.displayAllTravelPlans();
    std::cout << "\n";
    system.displayAllAttractions();

    // Example of range query
    int countInRange = system.getVisitorCountRange(800, 1100);
    std::cout << "\nNumber of attractions with visitor count in range 800 to 1100: " << countInRange << "\n";

    return 0;
}
