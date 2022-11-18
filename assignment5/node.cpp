#include <string>

#include "node.h"
#include "spice.h"
#include "vertex.h"

template <typename T>
Node<T>::Node(T initialData) {
    // Initialize the node with the data and without a next node in the linked list
    Node::data = initialData;
    Node::next = nullptr;
}

// Define acceptable data types that the Node can accept for the template
template class Node<std::string>;
template class Node<int>;
template class Node<Spice*>;
template class Node<Vertex*>;