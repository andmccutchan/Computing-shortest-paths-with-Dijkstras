//=========================================================
// PriorityQueue.cpp
// Andrew McCutchan, Namu Kim
// Implementaiton file for PriorityQueue class
// 12/18/2024
//=========================================================

#include "priorityQueue.hpp"

//==============================================================
// Default Constructor
// INPUTS: NONE
// OUTPUTS: NONE
// Createa empty prioirty queue object
//==============================================================
template <class T>
PriorityQueue<T>::PriorityQueue() {}

//==============================================================
// Copy Constructor
// INPUTS: Other PQ object
// OUTPUTS: NONE
// Copies data from existing priority queue object
//==============================================================
template <class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue& other) {
    minHeap = other.minHeap;
    position = other.position;
}

//==============================================================
// Destructor
// INPUTS: NONE
// OUTPUTS: NONE
// Frees up memory
//==============================================================
template <class T>
PriorityQueue<T>::~PriorityQueue() {
    minHeap.clear();
    position.clear();
}

//==============================================================
// Assignment Operator
// INPUTS: Other PQ object
// OUTPUTS: New PQ object contained data from existing PQ
//==============================================================
template <class T>
PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue<T>& other) {
    if (this != &other) {
        minHeap = other.minHeap;
        position = other.position;
    }
    return *this;
}

template <class T>
pair<T, double> PriorityQueue<T>::operator[](const T& index) const {
    if (index < 0 || index >= static_cast<int>(minHeap.size())) {
        throw std::out_of_range("Index out of range");
    }
    return minHeap[index]; 
}

//==============================================================
// Insert
// INPUTS: NodeID and its weight
// OUTPUTS: NONE
// Inserts a node with its weight from the start ID
//==============================================================
template <class T>
void PriorityQueue<T>::insert(const T& nodeId, double priority) {
    if (position.count(nodeId) > 0) {
        throw runtime_error("Node already exists in priority queue");
    }

    minHeap.push_back(make_pair(nodeId, priority));
    position[nodeId] = minHeap.size() - 1;
    
    heapifyUp(minHeap.size() - 1);
}

//==============================================================
// Extract Min
// INPUTS: NONE
// OUTPUTS: Pair with node and weight
// Takes the min value out of the priority queue and returns it 
//==============================================================
template <class T>
pair<T, double> PriorityQueue<T>::extractMin() {
    if (isEmpty()) {
        throw runtime_error("Priority queue is empty");
    }

    pair<T, double> minElement = minHeap[0];

    T lastNodeId = minHeap.back().first;
    minHeap[0] = minHeap.back();
    
    minHeap.pop_back();
    
    position.erase(minElement.first);
    
    if (!isEmpty()) {
        position[minHeap[0].first] = 0;
        heapifyDown(0);
    }

    return minElement;
}

//==============================================================
// Decrease Key 
// INPUTS: Node ID to change, its new priority
// OUTPUTS: NONE
// Enters an existing node and a new values to make its priority
//==============================================================
template <class T>
void PriorityQueue<T>::decreaseKey(const T& nodeId, double newPriority) {
    if (position.count(nodeId) == 0) {
        throw runtime_error("Node not found in priority queue");
    }

    int index = position[nodeId];

    if (newPriority >= minHeap[index].second) {
        return;
    }

    minHeap[index].second = newPriority;
    
    heapifyUp(index);
}

//==============================================================
// PrintMinHeap 
// INPUTS: NONE
// OUTPUTS: NONE
// Prints out the min PQ
//==============================================================
template <class T>
void PriorityQueue<T>::printMinHeap() {
    cout << "Priority Queue (Min-Heap):" << endl;
    cout << "-----------------------------------" << endl;

    for (size_t i = 0; i < minHeap.size(); ++i) {
        cout << i << ": "
             << minHeap[i].first << ", "
             << minHeap[i].second << endl;
    }
}

template class PriorityQueue<long>;
template class PriorityQueue<long long>;
template class PriorityQueue<int>;