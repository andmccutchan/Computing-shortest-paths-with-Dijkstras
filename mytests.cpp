#include <iostream> 
#include "weightedGraph.hpp"
#include "priorityQueue.hpp"
using namespace std;


// Test functions declared here
// Weighted Graph test functions
// Priority Que test functions
// Disjkstra's test functions
//============================================================

// CLI function declared here
//============================================================

//=============================================================
// CLI function (change from main to other name)
int main (void) {

    WeightedGraph<long long> graph; //Windows compatible, Window long = 32bits.
    
    while (true) {
        string filename;
        cout << "Enter a file or 'q' to quit: ";
        getline(cin, filename); //using getline and cin together causes issues, unify.

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

        bool run = true; // Boolean to control while loop.
        // CLI interface
        while (true) {
            double x_1, y_1, x_2, y_2;
            long long s, t;
            string coord;

            // Input first coordinates
            cout << "Enter a start coordinate (formatted as 'x y') or 'q' to quit: ";
            getline(cin, coord);
            if (coord == "q") {
                cout << "Exiting program." << endl;
                run == false;
                break;
            }
            //Parse input string into pair of doubles
            stringstream sCoord(coord);
            sCoord >> x_1 >> y_1;
            pair<double, double> start = make_pair(x_1, y_1);
            // Loop until valid coordinates are input or program is quit
            while (graph.idFromCoords(start) == -1) {
                cout << "Cannot find coordinates..." << endl;
                cout << "Re-enter a start coordinate (formatted as 'x y') or 'q' to quit: ";
                getline(cin, coord);
                if (coord == "q") {
                    cout << "Exiting program." << endl;
                    run = false;
                    break;
                }
                stringstream sCoord(coord);
                sCoord >> x_1 >> y_1;
                start = make_pair(x_1, y_1);
            }
            // exit if 'q' was typed while inputing first coordinate.
            if (!run) { 
                break;
            }
            cout << "Start node found!" << endl;

            // Input second coordinates
            cout << "Enter an end coordinate (formatted as 'x y') or 'q' to quit: ";
            getline(cin, coord);
            if (coord == "q") {
                cout << "Exiting program." << endl;
                break;
            }
            stringstream eCoord(coord);
            eCoord >> x_2 >> y_2;
            pair<double, double> end = make_pair(x_2, y_2);
            // Loop until valid coordinates are input or program is quit
            while (graph.idFromCoords(end) == -1) {
                cout << "Cannot find coordinates..." << endl;
                cout << "Re-enter an end coordinate (formatted as 'x y') or 'q' to quit: ";
                getline(cin, coord);
                if (coord == "q") {
                    cout << "Exiting program." << endl;
                    run = false;
                    break;
                }
                stringstream eCoord(coord);
                eCoord >> x_2 >> y_2;
                end = make_pair(x_2, y_2);
            }
            // exit if 'q' was typed while inputing second coordinate.
            if (!run) { 
                break;
            }
            cout << "End node found!" << endl;

            // Find ID of each coordinate, then run Dijkstra's
            s = graph.idFromCoords(start);
            t = graph.idFromCoords(end);

            // //Output with coordinates
            // cout << "\n>> Finding shortest path from: " <<
            // "(" << x_1 << ", " << y_1 << ")" << " to (" <<
            // x_2 << ", " << y_2 << ")..." << endl;

            // //Output with node id
            cout << "\n>> Finding shortest path from node [" <<
            s << "] to node [" << t << "]..." << endl;
            graph.dijkstras(s, t);
            
            break; 
        }
        break; //prevent file prompt loop.
    }
}