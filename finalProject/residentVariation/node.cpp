#include "node.h"
#include "hospital.h"
#include "resident.h"
#include "stableMatching.h"

#include <iostream>

template <typename T>
Node<T>::Node(T initialData) {
    // Initialize the node with the data and without a next node in the linked list
    Node::data = initialData;
    Node::next = nullptr;
}

// Define acceptable data types that the Node can accept for the template
template class Node<Resident*>;
template class Node<Hospital*>;
template class Node<AlgoOutput*>;