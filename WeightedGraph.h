//
//  WeightedGraph.h
//  20591029
//
//  Created by Shreya Wagley 
//

#ifndef WeightedGraph_h
#define WeightedGraph_h

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cfloat>
#include <stack>
#include <list>
#include <vector>

using namespace std;

class WeightedGraphType {
protected:
    int gSize;      //number of vertices
    list<int> *graph; // Store adjacency list
    double **weights; // Store weights of edges
public:
    // Constructor: Initializes the weighted graph with the given size (default is 0)
    WeightedGraphType(int size = 0);
    // Destructor: Deallocates memory used by the weighted graph
    ~WeightedGraphType();

    // Get the adjacency list for a given vertex index
    list<int> getAdjancencyList(int index) {
        return graph[index];
    }
    // Get the weight of the edge between vertices i and j
    double getWeight(int i, int j) {
        return weights[i][j];
    }
    // Print the adjacency list of the graph
    void printAdjacencyList();
    // Print the adjacency matrix of the graph
    void printAdjacencyMatrix();
    // Find the shortest path from the specified index to all other vertices
    vector<double> shortestPath(int index);
    // Find the shortest path from origin to destination using a stack
    stack<int> shortestPath(int origin, int destination);
    
};



// Constructor for WeightedGraphType class
// Initializes the weighted graph with the given size and reads the adjacency matrix from a file
WeightedGraphType::WeightedGraphType(int size) {
    gSize = 0; // Initialize the number of vertices to zero
    ifstream infile; // Input file stream for reading from a file
    char fileName[50] = "Weights.txt"; // Default file name for the adjacency matrix
    
    //uncomment if u want to use a file with different name
    //    cout << "Enter graph adjacency matrix file name: ";
    //    cin >> fileName;
    //    cout << endl;

    // Open the file with the adjacency matrix
    infile.open(fileName);

    // Check if the file is successfully opened
    if (!infile) {
        cout << "Cannot open input file." << endl;
        return;
    }

    // Set the graph size to the given size
    gSize = size;

    // Allocate memory for the adjacency list and weights matrix
    graph = new list<int>[gSize];
    weights = new double *[gSize];

    // Allocate memory for each row of the weights matrix
    for (int i = 0; i < gSize; i++)
        weights[i] = new double[gSize];

    // Read the values from the file and populate the weights matrix and adjacency list
    for (int i = 0; i < gSize; i++) {
        for (int j = 0; j < gSize; j++) {
            double value;
            infile >> value;

            // If the value is zero, set the weight to DBL_MAX (maximum value of double)
            // Otherwise, set the weight to the read value and add the vertex to the adjacency list
            if (value == 0)
                weights[i][j] = DBL_MAX; // System constant representing the maximum value of double
            else {
                weights[i][j] = value;
                graph[i].push_back(j);
            }
        }
    }

    // Close the file after reading
    infile.close();
}


// Destructor for WeightedGraphType class
// Deallocates the memory used for the weights matrix and adjacency list
WeightedGraphType::~WeightedGraphType() {
    // Deallocate memory for each row of the weights matrix
    for (int i = 0; i < gSize; i++)
        delete[] weights[i];

    // Deallocate memory for the weights matrix
    delete[] weights;

    // Clear the adjacency list for each vertex
    for (int index = 0; index < gSize; index++)
        graph[index].clear();

    // Deallocate memory for the adjacency list
    delete[] graph;
}


// Function to print the adjacency matrix of the weighted graph
// Used for debugging purposes
void WeightedGraphType::printAdjacencyMatrix() {
    cout << "\nAdjacency Matrix" << endl;
    
    // Iterate over rows and columns of the matrix
    for (int i = 0; i < gSize; i++) {
        for (int j = 0; j < gSize; j++) {
            // Display the weight value or 0 if the weight is DBL_MAX (no direct connection)
            cout << setw(8) << (weights[i][j] == DBL_MAX ? 0.0 : weights[i][j]);
        }
        cout << endl;
    }
}


// Function to print the adjacency list of the weighted graph
// Used for debugging purposes
void WeightedGraphType::printAdjacencyList() {
    cout << "\nAdjacency List" << endl;
    
    // Iterate over vertices in the graph
    for (int index = 0; index < gSize; index++) {
        cout << index << ": ";
        
        // Display the adjacent vertices for the current vertex
        for (int e : graph[index])
            cout << e << " ";
        
        cout << endl;
    }

    cout << endl;
}


// Function to find the shortest path from a given vertex to all other vertices
// Returns a vector containing the smallest weights from the source vertex
vector<double> WeightedGraphType::shortestPath(int index) {
    // Vector to store the smallest weights from the source vertex
    vector<double> smallestWeight(gSize);
    
    // Initialize the vector with the weights from the source vertex to all other vertices
    for (int j = 0; j < gSize; j++)
        smallestWeight[j] = weights[index][j];

    // Array to keep track of whether the minimum weight to a vertex is found
    bool *weightFound;
    weightFound = new bool[gSize];

    // Initialize the array to false, indicating that no weights are found yet
    for (int j = 0; j < gSize; j++)
        weightFound[j] = false;

    // Set the source vertex as found with a weight of 0
    weightFound[index] = true;
    smallestWeight[index] = 0;

    // Loop to find the smallest weights to all vertices
    for (int i = 0; i < gSize - 1; i++) {
        double minWeight = DBL_MAX;
        int v = 0;

        // Find the vertex with the minimum weight that is not yet found
        for (int j = 0; j < gSize; j++)
            if (!weightFound[j])
                if (smallestWeight[j] < minWeight) {
                    v = j;
                    minWeight = smallestWeight[v];
                }

        // Mark the vertex as found
        weightFound[v] = true;

        // Update the smallest weights to other vertices through the newly found vertex
        for (int j = 0; j < gSize; j++)
            if (!weightFound[j])
                if (minWeight + weights[v][j] < smallestWeight[j])
                    smallestWeight[j] = minWeight + weights[v][j];
    } //end for
    
    return smallestWeight;
} //end shortestPath



// Function to find the shortest path from a given origin to a destination
// Returns a stack containing the vertices in the shortest path
stack<int> WeightedGraphType::shortestPath(int origin, int destination) {
    // Vector to store the smallest weights from the origin to all other vertices
    vector<double> smallestWeight(gSize);
    
    // Initialize the vector with the weights from the origin to all other vertices
    for (int j = 0; j < gSize; j++)
        smallestWeight[j] = weights[origin][j];

    // Array to keep track of whether the minimum weight to a vertex is found
    bool *weightFound;
    weightFound = new bool[gSize];

    // Initialize the array to false, indicating that no weights are found yet
    for (int j = 0; j < gSize; j++)
        weightFound[j] = false;

    // Set the origin vertex as found with a weight of 0
    weightFound[origin] = true;
    smallestWeight[origin] = 0;

    // Loop to find the smallest weights to all vertices
    for (int i = 0; i < gSize - 1; i++) {
        double minWeight = DBL_MAX;
        int v = 0;

        // Find the vertex with the minimum weight that is not yet found
        for (int j = 0; j < gSize; j++)
            if (!weightFound[j])
                if (smallestWeight[j] < minWeight) {
                    v = j;
                    minWeight = smallestWeight[v];
                }

        // Mark the vertex as found
        weightFound[v] = true;

        // Update the smallest weights to other vertices through the newly found vertex
        for (int j = 0; j < gSize; j++)
            if (!weightFound[j])
                if (minWeight + weights[v][j] < smallestWeight[j])
                    smallestWeight[j] = minWeight + weights[v][j];
    } //end for
    
    // Create a stack to store the path
    stack<int> pathStack;

    // Build the path by backtracking from the destination index
    int current = destination;
    pathStack.push(current);

    while (current != origin) {
        bool pathFound = false;
        for (int j = 0; j < gSize; j++) {
            if (weights[j][current] < DBL_MAX && smallestWeight[current] == smallestWeight[j] + weights[j][current]) {
                current = j;
                pathStack.push(current);
                pathFound = true;
                break;
            }
        }
        
        if (!pathFound) {
            break;
        }
    }

    // Return the stack containing the shortest path
    return pathStack;
} //end shortestPath


#endif /* WeightedGraph_h */
