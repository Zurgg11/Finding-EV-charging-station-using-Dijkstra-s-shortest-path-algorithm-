//
//  EVChargingApp.cpp
//
//
//  Created by Shreya Wagley 
//
/*
I hereby certify that no other part of this submission has been copied from any other sources, including the Internet, books, or other student’s work, or generated from generative AI tools, such as ChatGPT except the ones I have listed below:
 
 // - Used the code in this website for printing the path in Dijkstra’s Shortest Path Algorithm.
 //   https://www.geeksforgeeks.org/printing-paths-dijkstras-shortest-path-algorithm/
 
 // - This website shows how to implement Dijkstra’s Shortest Path Algorithm using a set, i have used this as inspiration
 //   in implementing my Dijkstra’s Shortest Path Algorithm using a stack.
 //   https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-set-in-stl/
 
 // - This website help me understand the time complexity of Dijkstra's shortest path algorithm in my shortestPath() function.
 //   https://stackoverflow.com/questions/61890100/why-is-the-time-complexity-of-dijkstra-ov-e-logv
 
 
 
 
I hold a copy of this assignment that I can produce if the original is lost or damaged.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <queue>
#include <map>

using namespace std;

#include "Location.h"
#include "WeightedGraph.h"
#include "EVCharging.h"

int main() {
    // Create an instance of the EVCharging class
    EVCharging charging;

    // Variable to store user's menu choice
    int choice = 0;

    // Display the main menu for the program
    cout << "================================ Electric Vehicle Charging ================================" << endl << endl;

    // Continue displaying the menu until the user chooses to quit (option 10)
    while (choice != 10) {
        // Display the available tasks to the user
        cout << "Choose a task to run: " << endl;
        cout << "1. Print location information" << endl;
        cout << "2. Print adjacency matrix" << endl;
        cout << "3. List all charging stations in ascending order of charging price " << endl;
        cout << "4. List adjacent charging stations " << endl;
        cout << "5. Find cheapest adjacent charging stations " << endl;
        cout << "6. Find the nearest charging station " << endl;
        cout << "7. Find the other cheapest charging station (including return travel cost) " << endl;
        cout << "8. Find the cheapest charging station between origin and destination " << endl;
        cout << "9. Find the best charging path (multiple charging) " << endl;
        cout << "10. Quit" << endl;

        // Get the user's choice
        cin >> choice;

        // Perform the selected task based on user input
        switch (choice) {
            // Task 1: Print location information
            case 1: {
                charging.printLocations();
                break;
            }
            // Task 2: Print adjacency matrix
            case 2: {
                charging.printAdjacencyMatrix();
                break;
            }
            // Task 3: List all charging stations in ascending order of charging price
            case 3: {
                charging.chargingStationPriceAsc();
                break;
            }
            // Task 4: List adjacent charging stations
            case 4: {
                charging.adjacentCharginStations();
                break;
            }
            // Task 5: Find cheapest adjacent charging stations
            case 5: {
                charging.cheapestAdjacentStation();
                break;
            }
            // Task 6: Find the nearest charging station
            case 6: {
                charging.closestChargingStation();
                break;
            }
            // Task 7: Find the other cheapest charging station (including return travel cost)
            case 7: {
                charging.cheapestStationOther();
                break;
            }
            // Task 8: Find the cheapest charging station between origin and destination
            case 8: {
                charging.cheapestChargingPath();
                break;
            }
            // Task 9: Find the best charging path (multiple charging)
            case 9: {
                charging.bestChargingPath();
                break;
            }
            // Task 10: Quit the program
            case 10: {
                cout << "BYE BYE!" << endl;
                break;
            }
            // Default case: Display an error message for invalid choices
            default:
                cout << "Invalid choice. Please choose again." << endl << endl;
        }
    }

    // End of the program
    return 0;
}
