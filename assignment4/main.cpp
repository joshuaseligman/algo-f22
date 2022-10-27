#include <iostream>
#include <string>

#include "fileUtil.h"
#include "util.h"
#include "binarySearchTree.h"
#include "binaryTreeNode.h"

int main() {
    StringArr* magicItems = readFile("magicitems.txt");

    BinarySearchTree bst;

    for (int i = 0; i < magicItems->length; i++) {
       BinaryTreeNode<std::string>* newNode = new BinaryTreeNode<std::string>(magicItems->arr[i]);
       bst.insert(newNode);
    }

    delete [] magicItems->arr;
    delete magicItems;

    return 0;
}