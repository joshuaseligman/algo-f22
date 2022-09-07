#include <iostream>
#include <string>

#include "node.h"
#include "stack.h"
#include "queue.h"
#include "fileUtil.h"
#include "util.h"

// Function to test the Node class
void testNode() {
    // Create the nodes on the stack, so we do not have to delete later
    Node<std::string> n1("node 1");
    Node<std::string> n2("node 2");
    Node<std::string> n3("node 3");

    // Set up the links
    n1.next = &n2;
    n2.next = &n3;

    // Print out the data of each node in the linked list
    Node<std::string>* cur = &n1;
    while (cur != nullptr) {
        std::cout << cur->data << std::endl;
        cur = cur->next;
    }
}

// Function to test the Stack class
void testStack() {
    // Create a stack and add some data to it
    Stack<char> stack;
    stack.push('h');
    stack.push('s');
    stack.push('o');
    stack.push('J');

    // Print out the letters as we remove them from the stack
    while (!stack.isEmpty()) {
        std::cout << stack.pop();
    }
    std::cout << std::endl;

    try {
        // This should throw an error
        stack.pop();
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

// Function to test the Queue class
void testQueue() {
    // Create a queue and add some data to it
    Queue<char> queue;
    queue.enqueue('J');
    queue.enqueue('o');
    queue.enqueue('s');
    queue.enqueue('h');

    // Print out the letters as we remove them from the queue
    while (!queue.isEmpty()) {
        std::cout << queue.dequeue();
    }
    std::cout << std::endl;

    try {
        // This should throw an error
        queue.dequeue();
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
    }
}

bool isPalindrome(std::string word) {
    // Initialize an empty stack and queue for the checks
    Stack<char> wordStack;
    Queue<char> wordQueue;

    // Iterate through each character in the word to populate the stack and queue
    for (int i = 0; i < word.length(); i++) {
        char character = word[i];
        if (character == ' ') {
            // Go to next character because we are ignoring whitespace
            continue;
        } else if (character >= 'a' && character <= 'z') {
            // Adjust the character to make it uppercase by taking the difference between
            // the start of the lowercase letters and the start of the uppercase letters
            character -= 'a' - 'A';
        }
        // Add the character to both the stack and the queue
        wordStack.push(character);
        wordQueue.enqueue(character);
    }

    while (!wordStack.isEmpty() && !wordQueue.isEmpty()) {
        // Get the character from the top of the stack and queue
        char charFromStack = wordStack.pop();
        char charFromQueue = wordQueue.dequeue();

        if (charFromStack != charFromQueue) {
            // We can return false because we already know that the string is not a palindrome
            return false;
        }
    }

    // The string is a palindrome
    return true;
}

int main() {
    std::cout << "----- Testing Node class -----" << std::endl;
    testNode();
    std::cout << std::endl;

    std::cout << "----- Testing Stack class -----" << std::endl;
    testStack();
    std::cout << std::endl;

    std::cout << "----- Testing Queue class -----" << std::endl;
    testQueue();
    std::cout << std::endl;

    std::cout << "----- Testing isPalindrome -----" << std::endl;
    std::cout << isPalindrome("racecar") << std::endl; // 1
    std::cout << isPalindrome("RaCecAr") << std::endl; // 1
    std::cout << isPalindrome("ra   c e   car") << std::endl; // 1
    std::cout << isPalindrome("4") << std::endl; // 1
    std::cout << isPalindrome("") << std::endl; // 1
    std::cout << isPalindrome("ABC") << std::endl; // 0
    std::cout << std::endl;

    // try {
    //     // Read the file and store it in an array
    //     StringArr* data = readFile("magicitems.txt");

    //     // Print out each row
    //     for (int i = 0; i < data->length; i++) {
    //         std::cout << data->arr[i] << std::endl;
    //     }

    //     // Clean up memory
    //     delete data;
    // } catch (const std::invalid_argument& e) {
    //     std::cerr << e.what() << std::endl;
    // }

    return 0;
}