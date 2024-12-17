#include "priorityQueue.hpp"

//==============================================================
// Default Constructor
//==============================================================
template <class T>
PriorityQueue<T>::PriorityQueue() {}

//==============================================================
// Copy Constructor
//==============================================================
template <class T>
PriorityQueue<T>::PriorityQueue(const PriorityQueue& other) {
    minHeap = other.minHeap;
    position = other.position;
}

//==============================================================
// Destructor
//==============================================================
template <class T>
PriorityQueue<T>::~PriorityQueue() {
    minHeap.clear();
    position.clear();
}

//==============================================================
// Assignment Operator
//==============================================================
template <class T>
PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue<T>& other) {
    if (this != &other) {
        minHeap = other.minHeap;
        position = other.position;
    }
    return *this;
}

//==============================================================
// Insert
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
// Decrease Key 
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