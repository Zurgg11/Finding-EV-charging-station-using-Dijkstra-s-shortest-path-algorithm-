//
//  EVCharging.h
//  20591029
//
//  Created by Shreya Wagley 
//

#ifndef EVCharging_h
#define EVCharging_h
#include <stack>

// Include necessary headers for the class
#include "Location.h"
#include "WeightedGraph.h"

// Class definition for EVCharging, representing an electric vehicle charging system
class EVCharging {
private:
    // Private members for storing location information and weighted graph
    map<int, Location> locations;  // It can also be unordered_map
    int numberOfLocations;
    WeightedGraphType* weightedGraph;

    // Private helper function to get the index of a location based on its name
    int getIndex(string locationName) {
        for (const auto& el : locations) {
            if (el.second.locationName == locationName) {
                return el.first;
            }
        }
        return -1;
    }

    // Private helper function to get user input for location
    int getLocationInput() {
        cout << "Input a location: ";
        string locationName;
        getline(cin, locationName);
        if (locationName.size() == 0) {
            getline(cin, locationName);
        }
        int index = getIndex(locationName);

        if (index == -1) {
            cout << "There is no location: " << locationName << endl;
        }
        return index;
    }

    // Private helper function to find the cheapest charging station given specific conditions
    int cheapestChargingStation(int origin, int destination, int avoid, int chargingAmount, double& travelCost, double& chargingCost);

public:
    // Constructor and Destructor
    EVCharging();
    ~EVCharging();

    // Public member functions for various tasks
    void inputLocations();
    void printLocations();
    void printAdjacencyMatrix();
    void chargingStationPriceAsc();
    void adjacentCharginStations();
    void cheapestAdjacentStation();
    void closestChargingStation();
    void cheapestStationOther();
    void cheapestChargingPath();
    void bestChargingPath();
};

// Implementation of the EVCharging class

// Constructor
EVCharging::EVCharging() {
    inputLocations();
    weightedGraph = new WeightedGraphType(numberOfLocations);
}

// Destructor
EVCharging::~EVCharging() {
    delete weightedGraph;
}

// Function to read charging location information from a file
void EVCharging::inputLocations() {
    // Implementation details for reading location information from a file
    // (Assuming the file format includes locationName, chargerInstalled, chargingPrice)
    ifstream infile;
    char fileName[50] = "Locations.txt";

//    cout << "Enter charging location file name: ";
//    cin >> fileName;
//    cout << endl;

    infile.open(fileName);

    if (!infile) {
        cout << "Cannot open input file." << endl;
        return;
    }

    int locationIndex = 0;

    while (!infile.eof()) {
        Location s;
        string charger;
        string price;
        while (!infile.eof()) {
            getline(infile, s.locationName, ',');
            getline(infile, charger, ',');
            getline(infile, price);
            s.chargerInstalled = (stoi(charger) == 1) ? true : false;
            s.chargingPrice = stod(price);
            s.index = locationIndex;
            locations[locationIndex] = s;
            locationIndex++;
        }
    }

    numberOfLocations = locationIndex;
}

// Function to print information about all charging locations
void EVCharging::printLocations() {
    // Implementation details for printing location information
    cout << "List of locations and charging information " << endl;
    cout << setw (8) << "Index" << setw (20) << "Location name" << setw (20) <<"Charging station" << setw(20) << "Charging price" << endl;

    map<int, Location>::iterator it = locations.begin();

    for (; it != locations.end(); it++) {
        it->second.printLocation();
    }

    cout << endl;
}

void EVCharging::printAdjacencyMatrix() {
    // Display a header indicating the purpose of the adjacency matrix
    cout << "Adjacency matrix (0 means no direct connection, non-zero value represents the distance of adjacent locations)\n" << endl;

    // Display the header row with location names
    cout << setw(13) << " ";
    for (int i = 0; i < numberOfLocations; i++) {
        cout << setw(13) << locations[i].locationName;
    }
    cout << endl;

    // Iterate over each location to print the adjacency matrix
    for (int i = 0; i < numberOfLocations; i++) {
        // Display the location name in the leftmost column
        cout << setw(13) << locations[i].locationName;

        // Iterate over each location again to fill in the distances
        for (int j = 0; j < numberOfLocations; j++) {
            // Get the distance between locations i and j from the weighted graph
            double distance = weightedGraph->getWeight(i, j);

            // Display 0 if there is no direct connection, otherwise display the distance
            cout << setw(13) << (distance == DBL_MAX ? 0.0 : distance);
        }

        // Move to the next line for the next location
        cout << endl;
    }
}

//-----------------------------------------------------Task 3-------------------------------------------
void EVCharging::chargingStationPriceAsc() {
    // Vector to store charging locations with installed chargers
    vector<Location> locationPrice;

    // Iterate over all locations to filter those with installed chargers
    for (map<int, Location>::iterator it = locations.begin(); it != locations.end(); it++) {
        if (it->second.chargerInstalled)
            locationPrice.push_back(it->second);
    }

    // Sort the vector in ascending order based on charging prices
    sort(locationPrice.begin(), locationPrice.end());

    // Print information about each charging location in sorted order
    for (int i = 0; i < locationPrice.size(); i++) {
        locationPrice[i].printLocation();
    }
}

//-----------------------------------------------------Task 4-------------------------------------------
void EVCharging::adjacentCharginStations() {
    // Get user input for the location
    int index = getLocationInput();

    // Check if the input location is valid
    if (index == -1) {
        return;
    }

    // Flag to track whether any charging stations were found
    bool found = false;

    // Iterate over the adjacency list of the input location
    for (int i : weightedGraph->getAdjancencyList(index)) {
        // Check if the adjacent location has a charging station
        if (locations[i].chargerInstalled) {
            // Print the name of the adjacent charging station
            cout << endl << locations[i].locationName << endl;
            found = true;
        }
    }

    // Display a message if no charging stations are adjacent to the input location
    cout << endl;
    if (!found) {
        cout << "No charging station adjacent to " << locations[index].locationName << endl;
    }
}

//-----------------------------------------------------Task 5-------------------------------------------
void EVCharging::cheapestAdjacentStation() {
    // Get user input for the location
    int index = getLocationInput();

    // Check if the input location is valid
    if (index == -1) {
        return;
    }

    // Randomly generate a charging amount between 10 and 50 kWh
    int chargingAmount = rand() % 41 + 10;
    cout << "Charging amount: " << chargingAmount << " kWh" << endl;

    // Variables to track the lowest cost and the corresponding charging station ID
    double lowestCost = DBL_MAX;
    int lowestID = -1;

    // Iterate over the adjacency list of the input location
    for (int i : weightedGraph->getAdjancencyList(index)) {
        // Calculate the cost of charging at the current adjacent charging station
        double cost = weightedGraph->getWeight(index, i) * 2 * 0.1 + chargingAmount * locations[i].chargingPrice;

        // Check if the charging station is installed, cost is lower, and charging amount is valid
        if (locations[i].chargerInstalled && cost < lowestCost) {
            if (locations[i].chargingPrice > 0 || chargingAmount <= 25) {
                // Update the lowest cost and corresponding charging station ID
                lowestCost = cost;
                lowestID = i;
            }
        }
    }

    // Display the result based on whether a cheapest charging station was found
    if (lowestID != -1) {
        cout << "The cheapest charging station near you is: " << locations[lowestID].locationName << endl;
        cout << "Charging will cost: $" << static_cast<double>(lowestCost) << endl;
    } else {
        cout << "No charging station adjacent to " << locations[index].locationName << endl;
    }
}

//-----------------------------------------------------Task 6-------------------------------------------
void EVCharging::closestChargingStation() {
    // Get user input for the location
    int index = getLocationInput();

    // Check if the input location is valid
    if (index == -1) {
        return;
    }

    // Compute the shortest path distances from the input location to all other locations
    vector<double> shortestPath = weightedGraph->shortestPath(index);

    // Variables to track the nearest charging station and the corresponding distance
    double nearest = DBL_MAX;
    int nearestStation = 0;

    // Iterate through the shortest path distances to find the nearest charging station
    for (int i = 0; i < shortestPath.size(); i++) {
        // Check if the location is not the input location, has a charging station, and has a shorter path
        if (i != index && locations[i].chargerInstalled && shortestPath[i] < nearest) {
            // Update the nearest charging station and corresponding distance
            nearest = shortestPath[i];
            nearestStation = i;
        }
    }

    // Display the result based on whether a nearest charging station was found
    cout << locations[nearestStation].locationName << " is the nearest charging station to you, with a distance of " << nearest << " km" << endl;
}
//-----------------------------------------------------Task 7-------------------------------------------
void EVCharging::cheapestStationOther() {
    // Get user input for the location
    int index = getLocationInput();

    // Check if the input location is valid
    if (index == -1) {
        return;
    }

    // Randomly generate a charging amount between 10 and 50 kWh
    int chargingAmount = rand() % 41 + 10;
    cout << "Charging amount: " << chargingAmount << " kWh" << endl;

    // Variables to store charging and travel costs
    double chargingCost, travelCost;

    // Find the other cheapest charging station and retrieve associated costs
    int lowestID = cheapestChargingStation(index, index, index, chargingAmount, travelCost, chargingCost);

    // Display the results based on whether another cheapest charging station was found
    if (lowestID != -1) {
        cout << "The other cheapest charging station is " << locations[lowestID].locationName << endl;
        cout << "Charging cost: $" << chargingCost << endl;
        cout << "Travel cost: $" << travelCost << endl;
        cout << "Total cost: $" << chargingCost + travelCost << endl;
    } else {
        cout << "No results found!" << endl;
    }
}

//-----------------------------------------------------Task 8-------------------------------------------
void EVCharging::cheapestChargingPath() {
    // Get user input for the origin location
    int origin = getLocationInput();
    if (origin == -1) {
        return;
    }

    // Get user input for the destination location
    int destination = getLocationInput();
    if (destination == -1) {
        return;
    }

    // Randomly generate a charging amount between 10 and 50 kWh
    int chargingAmount = rand() % 41 + 10;
    cout << "Charging amount: " << chargingAmount << " kWh" << endl;

    // Variables to store charging and travel costs
    double chargingCost, travelCost;

    // Find the cheapest charging station and retrieve associated costs
    int lowestId = cheapestChargingStation(origin, destination, -1, chargingAmount, travelCost, chargingCost);

    // Display the results based on whether the cheapest charging station was found
    if (lowestId != -1) {
        cout << "The other cheapest charging station is " << locations[lowestId].locationName << endl;
        cout << "Charging cost: $" << chargingCost << endl;
        cout << "Travel cost: $" << travelCost << endl;
        cout << "Total cost: $" << chargingCost + travelCost << endl;
    } else {
        cout << "No results found!" << endl;
    }

    // Display the travel path
    cout << "Travel path: ";

    // Display the travel path from origin to the other cheapest charging station
    if (lowestId != origin) {
        stack<int> path1 = weightedGraph->shortestPath(origin, lowestId);

        while (path1.size() > 1) {
            cout << locations[path1.top()].locationName << ", ";
            path1.pop();
        }
    }

    // Display the travel path from the other cheapest charging station to the destination
    stack<int> path2 = weightedGraph->shortestPath(lowestId, destination);
    while (!path2.empty()) {
        cout << locations[path2.top()].locationName << ", ";
        path2.pop();
    }

    cout << endl << endl;
}

//-----------------------------------------------------Task 9-------------------------------------------

/*This function uses the `cheapestChargingStation` method to find the cheapest charging station for two scenarios:
 * charging 25 kWh and charging a random amount between 10 and 50 kWh. It then compares the costs and recommends the
 * best charging strategy, considering the availability of free charging for 25 kWh. The function displays the associated
 * costs and the travel path for the recommended charging scenario.
 */
void EVCharging::bestChargingPath() {
    // Get user input for the origin location
    int origin = getLocationInput();
    if (origin == -1) {
        return;
    }
    
    // Get user input for the destination location
    int destination = getLocationInput();
    if (destination == -1) {
        return;
    }
    
    // Randomly generate a charging amount between 10 and 50 kWh
    int chargingAmount = rand() % 41 + 10;
    cout << "Charging amount: " << chargingAmount << " kWh" << endl;
    
    // Variables to store charging and travel costs for two scenarios
    double chargingCost, travelCost;
    int freeCharging = cheapestChargingStation(origin, destination, -1, 25, travelCost, chargingCost);
    int lowestId = cheapestChargingStation(origin, destination, -1, chargingAmount, travelCost, chargingCost);
    
    // Display the results based on the recommended charging scenario
    if (chargingAmount <= 25 && locations[freeCharging].chargingPrice > 0) {
        // Display the recommended scenario for charging 25 kWh
        if (lowestId != -1) {
            cout << "The best way of charging is to charge at " << locations[lowestId].locationName << endl;
            cout << "Charging cost: $" << chargingCost << endl;
            cout << "Travel cost: $" << travelCost << endl;
            cout << "Total cost: $" << chargingCost + travelCost << endl;
        } else {
            cout << "No results found!" << endl;
        }
        
        // Display the travel path for the recommended scenario
        cout << "Travel path: ";
        
        // Display the travel path from origin to the recommended charging station
        if (lowestId != origin) {
            stack<int> path1 = weightedGraph->shortestPath(origin, lowestId);
            
            while (path1.size() > 1) {
                cout << locations[path1.top()].locationName << ", ";
                path1.pop();
            }
        }
        
        // Display the travel path from the recommended charging station to the destination
        stack<int> path2 = weightedGraph->shortestPath(lowestId, destination);
        while (!path2.empty()) {
            cout << locations[path2.top()].locationName << ", ";
            path2.pop();
        }
    } else {
        // Variables to store charging and travel costs for two charging scenarios
        double travelCost1, chargingCost1, travelCost2, chargingCost2;
        int lowestIdL = origin, lowestIdR = destination;
        
        // Find the cheapest charging station for charging 25 kWh
        if (freeCharging != origin) {
            lowestIdL = cheapestChargingStation(origin, freeCharging, freeCharging, chargingAmount - 25, travelCost1, chargingCost1);
        } else {
            travelCost1 = 0;
            chargingCost1 = DBL_MAX;
        }
        
        // Calculate the travel cost from the free charging station to the destination
        vector<double> shortestPath = weightedGraph->shortestPath(freeCharging);
        travelCost1 = travelCost1 + shortestPath[destination] * 0.1;
        
        // Find the cheapest charging station for charging the remaining kWh
        if (freeCharging != destination) {
            lowestIdR = cheapestChargingStation(freeCharging, destination, freeCharging, chargingAmount - 25, travelCost2, chargingCost2);
        } else {
            travelCost2 = 0;
            chargingCost2 = DBL_MAX;
        }
        
        // Calculate the travel cost from the origin to the free charging station
        shortestPath = weightedGraph->shortestPath(origin);
        travelCost2 = travelCost2 + shortestPath[freeCharging] * 0.1;
        
        // Display the results based on the recommended charging scenario
        cout << "The best way of charging is " << endl;
        if (travelCost1 + chargingCost1 <= travelCost2 + chargingCost2) {
            // Display the recommended scenario for charging at two different locations
            cout << "Charging " << chargingAmount - 25 << " kWh at " << locations[lowestIdL].locationName << endl;
            cout << "Charging 25 kWh at " << locations[freeCharging].locationName << endl;
            cout << "Charging cost: $" << chargingCost1 << endl;
            cout << "Travel cost: $" << travelCost1 << endl;
            cout << "Total cost: $" << chargingCost1 + travelCost1 << endl;
            
            // Display the travel path for the recommended scenario
            cout << "Travel path: ";
            
            // Display the travel path from origin to the recommended charging station
            if (lowestIdL != origin) {
                stack<int> path1 = weightedGraph->shortestPath(origin, lowestIdL);
                
                while (path1.size() > 1) {
                    cout << locations[path1.top()].locationName << ", ";
                    path1.pop();
                }
            } else {
                cout << locations[origin].locationName << ", ";
            }
            
            // Display the travel path from the recommended charging station to the free charging station
            stack<int> path2 = weightedGraph->shortestPath(lowestIdL, freeCharging);
            while (!path2.empty()) {
                cout << locations[path2.top()].locationName << ", ";
                path2.pop();
            }
            
            // Display the travel path from the free charging station to the destination
            if (freeCharging != destination) {
                stack<int> path3 = weightedGraph->shortestPath(freeCharging, destination);
                while (!path3.empty()) {
                    cout << locations[path3.top()].locationName << ", ";
                    path3.pop();
                }
            }
        } else {
            // Display the recommended scenario for charging at two different locations
            cout << "Charging 25 kWh at " << locations[freeCharging].locationName << endl;
            cout << "Charging " << chargingAmount - 25 << " kWh at " << locations[lowestIdR].locationName << endl;
            cout << "Charging cost: $" << chargingCost2 << endl;
            cout << "Travel cost: $" << travelCost2 << endl;
            cout << "Total cost: $" << chargingCost2 + travelCost2 << endl;
            
            // Display the travel path for the recommended scenario
            cout << "Travel path: " << endl;
            
            // Display the travel path from origin to the free charging station
            if (freeCharging != origin) {
                stack<int> path1 = weightedGraph->shortestPath(origin, freeCharging);
                
                while (path1.size() > 1) {
                    cout << locations[path1.top()].locationName << ", ";
                    path1.pop();
                }
            }
            
            // Display the travel path from the free charging station to the recommended charging station
            stack<int> path2 = weightedGraph->shortestPath(freeCharging, lowestIdR);
            while (!path2.empty()) {
                cout << locations[path2.top()].locationName << ", ";
                path2.pop();
            }
            
            // Display the travel path from the recommended charging station to the destination
            if (lowestIdR != destination) {
                stack<int> path3 = weightedGraph->shortestPath(lowestIdR, destination);
                while (!path3.empty()) {
                    cout << locations[path3.top()].locationName << ", ";
                    path3.pop();
                }
            }
        }
    }
    cout << endl << endl;
}
#endif /* EVCharging_h */
