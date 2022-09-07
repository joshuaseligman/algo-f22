#pragma once

// Node represents an item within a singly linked list and can store strings (for now)
class Node {
    public:
        // Nodes need data of some kind and a pointer to the next node in the list
        std::string data;
        Node* next;
        
        Node(std::string initialData);
};

// // Node represents an item within a singly linked list and can store data of a given type
// template <typename T>
// class Node {
//     public:
//         // A node has the data it is storing (of a type defined by the user) and a pointer to the next node
//         T data;

//         // The pointer uses the template to make sure all elements of the linked list store the same data type
//         Node<T>* next;

//         // Nodes will be instantiated with some data and not have a next node
//         Node(T initialData) {
//             data = initialData;
//             next = nullptr;
//         };
// };

// Super helpful resources on templates for c++
// https://isocpp.org/wiki/faq/templates#templates-defn-vs-decl
// https://isocpp.org/wiki/faq/templates#separate-template-fn-defn-from-decl