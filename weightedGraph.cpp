//=========================================================
// WeightedGraph.cpp
// Andrew McCutchan, Namu Kim
// Implementaiton file for WeightedGraph class
// 12/18/2024
//=========================================================

#include "weightedGraph.hpp"

//==============================================================
// Default Constructor
// Initializes an empty Weighted graph onject
// INPUTS: NONE
// OUTPUTS: NONE
//==============================================================
template <class T>
WeightedGraph<T>::WeightedGraph() {
    listSize = 0;
}

//==============================================================
// Copy Constructor
// Initializes a weighted graph object, copying data from a
// separate weighted graph
// INPUTS: weighted graph object
// OUTPUTS: NONE
//==============================================================
template <class T>
WeightedGraph<T>::WeightedGraph(const WeightedGraph<T> &other) {
    listSize = other.listSize;
    coords = other.coords;
    adjacencyList = other.adjacencyList;
}

//==============================================================
// Destructor
// INPUTS: NONE
// OUTPUTS: NONE
// Frees memory (since vectors and u-maps have their own deallocation, nothing to be done here)
//==============================================================
template <class T>
WeightedGraph<T>::~WeightedGraph() {}

//==============================================================
// Assignment operator
// INPUTS: Weighted graph object
// OUTPUTS: New weighted graph object
//==============================================================
template <class T>
WeightedGraph<T>& WeightedGraph<T>::operator=(const WeightedGraph<T> &other) {
    coords = other.coords;
    adjacencyList = other.adjacencyList;
    listSize = other.listSize;
    return *this;
}

//============================================================== 
// addEdge
// INPUTS: Verteces U and V and weight of their edge.
// OUTPUTS: NONE
// Inserts a new edge into our weighted graph
//==============================================================
template <class T>
void WeightedGraph<T>::addEdge(const T& u, const T& v, double weight) {
    adjacencyList[u][v] = weight;
}

//============================================================== 
// edgeIn
// INPUTS: Verteces U and V
// OUTPUTS: Bool if edge is in graph
//==============================================================
template <class T>
bool WeightedGraph<T>::edgeIn(const T& u, const T& v) {
    return adjacencyList[u].find(v) != adjacencyList[u].end();
}

//==============================================================  
// addVertex
// INPUTS: Node ID, X and Y coordinates
// OUTPUTS: NONE
// Inserts a vertex into the graph with its ID and coordinates
//==============================================================
template <class T>
void WeightedGraph<T>::addVertex(const T& id, double x, double y) {
    coords[id] = make_pair(x, y);
}

//==============================================================
// readFromSTDIN
// INPUTS: NONE
// OUTPUTS: Weighted Graph object
// Reads a graph inputed from STDIN
//==============================================================
template <class T>
WeightedGraph<T> WeightedGraph<T>::readFromSTDIN() {
    int n, m;
    cin >> n >> m;

    WeightedGraph<T> g;
    g.listSize = n;

    for (int i = 0; i < n; i++) {
        T id;
        double x, y;
        cin >> id >> x >> y;
        g.addVertex(id, x, y);
    }

    for (int i = 0; i < m + 1; i++) {
        string line;
        getline(cin, line);
        istringstream street(line);

        T u, v;
        double weight;
        if (street >> u >> v >> weight) {
            g.addEdge(u, v, weight);
        }  
    }
    return g;
}

//==============================================================
// readFromFile
// INPUTS: File
// OUTPUTS: Weighted Graph object
// Reads a file from parameter
//==============================================================
template <class T>
WeightedGraph<T> WeightedGraph<T>::readFromFile(const string& filename) {
    int n, m;
    ifstream file(filename);

    if (!file) {
        throw runtime_error("file not found");
    }

    file >> n >> m;
    WeightedGraph<T> g;
    g.listSize = n;

    for (int i = 0; i < n; i++) {
        T id;
        double x, y;
        file >> id >> x >> y;
        g.coords[id] = make_pair(x, y);
    }

    for (int i = 0; i < m + 1; i++) {
        string line;
        getline(file, line);
        istringstream street(line);

        T u, v;
        double weight;
        if (street >> u >> v >> weight) {
            g.addEdge(u, v, weight);
        }  
    }
    file.close();
    return g;
}

//==============================================================
// Dijkstra's
// INPUTS: Start coordinate pair and end coordinate pair
// OUTPUTS: Vector of shortest path coordinates
// Computes the shortest path between two nodes. This function takes
// coordinates inputted by the user and gets their associated nodes,
// then computes the shortest path between the two.
//==============================================================
template <class T>
vector<pair<double, double> > WeightedGraph<T>::dijkstras(pair<double, double> start, pair<double, double> end) {
    pair<double, double> startAndEndNodes = findNode(start, end);

    PriorityQueue<T> pq;
    unordered_map<T, pair<T, double> > S;

    for (const auto& [node, _] : adjacencyList) { 
        // S[node].first = parent
        // S[node].second = shortest path estimate from source (node.d)
        S[node].first = -1;
        S[node].second = numeric_limits<double>::infinity();
        pq.insert(node, S[node].second);
    }

    S[startAndEndNodes.first].second = 0;// s.d = 0
    pq.decreaseKey(startAndEndNodes.first, 0);  

    while (!pq.isEmpty()) {
        auto [current, currentDist] = pq.extractMin();

        if (current == startAndEndNodes.second) {
            break;
        }

        for (const auto& [neighbor, weight] : adjacencyList[current]) {
            double newDist = currentDist + weight;

            if (S[neighbor].second > newDist) {
                S[neighbor].second = newDist;
                S[neighbor].first = current;

                pq.decreaseKey(neighbor, newDist);
            }
        }
    }

    vector<pair<double, double>> path;
    for (T i = startAndEndNodes.second; i != -1; i = S[i].first) {
        path.push_back(coords[i]);
    }
    reverse(path.begin(), path.end());

    return path;    
}

//==============================================================
// printAdjacencyList
// INPUTS: NONE
// OUTPUTS: NONE
// Prints out weighted graph in adjacency list representation
//==============================================================
template <class T>
void WeightedGraph<T>::printAdjacencyList() const {
    for (const auto& [node, neighbors] : adjacencyList) {
        cout << node << ": ";
        for (const auto& [neighbor, weight] : neighbors) {
            cout << " -> (" << neighbor << ", " << weight << ") ";
        }
        cout << endl;
    }
}   

//============================================================== 
// idFromCoords
// INPUTS: Coord pair
// OUTPUTS: Node ID
// finds and returns id of node by searching coodrs for coordinate pair
//==============================================================
template <class T>
T WeightedGraph<T>::idFromCoords(pair<double, double> node) {
    T nodeId = -1; // -1 does not exist as id in coords
    for (const auto& [id, coord] : coords) {                          
        if (node.first == coord.first && node.second == coord.second) {
            nodeId = id;
        }
    }
    return nodeId;
}

//==============================================================
// findNode
// INPUTS: start and end coordinates
// OUTPUTS: Pair (start node ID, end node ID);
// Takes coordinates and finds the associated node ID
//==============================================================
template <class T>
pair<double, double> WeightedGraph<T>::findNode(pair<double, double> start, pair<double, double> end) {
    T startNode = -1, endNode = - 1;
    for (const auto& [id, coord] : coords) {                          
        if (start.first == coord.first && start.second == coord.second) {
            startNode = id;
        }

        if (end.first == coord.first && end.second == coord.second) {
            endNode = id;
        }
    }

    if (startNode == -1 || endNode == -1) {
        throw invalid_argument("Start or end coord not found");
    }

    return make_pair(startNode, endNode);
}

// class instantiations
template class WeightedGraph<long>;
template class WeightedGraph<long long>;
template class WeightedGraph<int>;