#include <iostream> 
#include "weightedGraph.hpp"
#include "priorityQueue.hpp"
using namespace std;

int main (void) {



    


    //=============================================================
    WeightedGraph<long> graph;
    
    while (true) {
        string filename;
        cout << "Enter a file or 'q' to quit: ";
        getline(cin, filename); //using getline and cin together causes issues, unifit.

        if (filename == "q") {
            cout << "Exiting program." << endl;
            break;
        }

        try {
            graph = WeightedGraph<long>::readFromFile(filename);
            cout << "Graph loaded successfully from " << filename << endl;
        } catch (const runtime_error& e) {
            cout << "Error: " << e.what() << ". Try running again with correct graph." << endl;
            break; 
        }
        // bool valid;
        while (true) {
            double x_1, y_1, x_2, y_2;
            string coord;
            cout << "Enter a start coordinate (formatted as 'x y') or 'q' to quit: ";
            //cin >> x_1 >> y_1;

            getline(cin, coord);
            cout << "input: " << coord << endl;
            if (coord == "q") {
                cout << "Exiting program." << endl;
                break;
            }
            else {
                stringstream StoD(coord);
                StoD >> x_1 >> y_1;
                // cout << "First number: " << x_1 << endl;
                // cout << "Second number: " << y_1 << endl;
                //cout << typeid(x_1).name() << endl;
            }

            cout << "Enter an end coordinate (formatted as 'x y') or 'q' to quit: ";
            // cin >> x_2 >> y_2;
            getline(cin, coord);
            if (coord == "q") {
                cout << "Exiting program." << endl;
                break;
            }
            else {
                stringstream StoD(coord);
                StoD >> x_2 >> y_2;
                // cout << "First number: " << x_1 << endl;
                // cout << "Second number: " << y_1 << endl;
                //cout << typeid(x_1).name() << endl;
            }

            cout << "start coordinates are: " << x_1 << ", " << y_1 << endl;
            cout << "end coordinates are: " << x_2 << ", " << y_2 << endl;
        

            pair<double, double> start = make_pair(x_1, y_1);
            pair<double, double> end = make_pair(x_2, y_2);
            //call dijkstra's


            
            break; 
        }
    }
}