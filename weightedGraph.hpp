//=========================================================
// WeightedGraph.hpp
// Andrew McCutchan, Namu Kim
// Header file containing all function delcarations for
// WeightedGraph class.
// 12/18/2024
//=========================================================
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include "priorityQueue.hpp"
using namespace std;


#ifndef WEIGHTED_GRAPH_HPP
#define WEIGHTED_GRAPH_HPP
template <typename T>
class WeightedGraph {
    private:
        unordered_map<T, pair<double, double> > coords;
        unordered_map<T, unordered_map<T, double > > adjacencyList;
		int listSize;
    public:
                                                WeightedGraph();
                                                WeightedGraph(const WeightedGraph<T> &other);
                                                ~WeightedGraph();
                WeightedGraph<T>&               operator=(const WeightedGraph<T> &other);
                void                            addEdge(const T& u, const T& v, double weight);
		        void                            printAdjacencyList() const;
                bool                            edgeIn(const T& u, const T& v);
                T                               idFromCoords(pair<double, double> node);
                void                            addVertex(const T& id, double x, double y);
                vector<pair <double, double> >  dijkstras(pair<double, double> startCoord, pair<double, double> endCoord);
        static  WeightedGraph<T>                readFromSTDIN();
        static  WeightedGraph<T>                readFromFile(const string& filename);
                pair<double, double>            findNode(pair<double, double> start, pair<double, double> end);

        // getter functions
        const   auto&                           getCoords() const { return coords; }
        unordered_map<T, unordered_map<T, double > > getAdjacencyList() const { return adjacencyList; }
                int                             getSize() const { return listSize; }
};

#endif