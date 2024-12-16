#include <iostream> 
#include "weightedGraph.hpp"
#include "priorityQueue.hpp"
#include "weightedGraph.cpp"
#include "priorityQueue.cpp"
using namespace std;


// Test functions declared here
// Weighted Graph test functions
// Priority Que test functions
// Disjkstra's test functions
//============================================================

// CLI function declared here
//============================================================

int main (void) {
// Testing or CLI prompt here

// CLI function (move out of main later)
//=============================================================
    WeightedGraph<long long> graph; //Windows compatible, Window long = 32bits.
    
    while (true) {
        string filename;
        cout << "Enter a file or 'q' to quit: ";
        getline(cin, filename); //using getline and cin together causes issues, unifit.

        if (filename == "q") {
            cout << "Exiting program." << endl;
            break;
        }

        try {
            graph = WeightedGraph<long long>::readFromFile(filename);
            cout << "Graph loaded successfully from " << filename << endl;
        } catch (const runtime_error& e) {
            cout << "Error: " << e.what() << ". Try running again with correct graph." << endl;
            break; 
        }

        while (true) {
            double x_1, y_1, x_2, y_2;
            string coord;

            cout << "Enter a start coordinate (formatted as 'x y') or 'q' to quit: ";
            getline(cin, coord);

            if (coord == "q") {
                cout << "Exiting program." << endl;
                break;
            }
            else { 
                stringstream StoD(coord);
                StoD >> x_1 >> y_1;
                // add test case for edge in adjList
            }

            cout << "Enter an end coordinate (formatted as 'x y') or 'q' to quit: ";
            getline(cin, coord);

            if (coord == "q") {
                cout << "Exiting program." << endl;
                break;
            }
            else {
                stringstream StoD(coord);
                StoD >> x_2 >> y_2;
                // add test case for edge in adjList
            }

            //Start Dijkstra's and find shortest path
            cout << "\n >>Finding shortest path from: " <<
            "(" << x_1 << ", " << y_1 << ")" << " to (" <<
            x_2 << ", " << y_2 << ")..." << endl;

    
            pair<double, double> start = make_pair(x_1, y_1);
            pair<double, double> end = make_pair(x_2, y_2);
            //call dijkstra's with pairs


            
            break; 
        }
        break; //prevent file prompt loop.
    }
}