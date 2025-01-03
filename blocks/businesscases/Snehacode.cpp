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

