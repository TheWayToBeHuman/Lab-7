#include <iostream>
#include <string>
#include <thread> // For this_thread::sleep_for
#include <chrono> // For chrono::seconds
using namespace std;

struct Node
{
    string data;
    Node* next;
};

// PROVIDED: Linked queue operations
void enqueue(Node*& front, Node*& rear, string name)
{
    Node* newNode = new Node{name, nullptr};
    if (rear == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

string dequeue(Node*& front, Node*& rear) {
    if (front == nullptr) return "";
    Node* oldFront = front;
    string name = oldFront->data;
    front = front->next;
    if (front == nullptr) rear = nullptr;
    delete oldFront;
    return name;
}

void displayQueue(Node* front) {
    if (front == nullptr) {
        cout << "Queue is empty.\n";
        return;
    }

    cout << "Waiting customers: ";
    for (Node* current = front; current != nullptr; current = current->next)
        cout << current->data << " ";
    cout << endl;
}

int main() {
    Node* front = nullptr;
    Node* rear = nullptr;

    // TODO 1: Enqueue five customers
    enqueue(front, rear, "Ali");
    enqueue(front, rear, "John");
    enqueue(front, rear, "Sara");
    enqueue(front, rear, "David");
    enqueue(front, rear, "Emma");

    // TODO 2: Display the initial waiting queue.
    displayQueue(front);

    // TODO 3: Write a loop that continues until the queue is empty.
    while (front != nullptr) {
        // a. Display the name of the front customer being served.
        cout << "Now serving: " << front->data << endl;

        // b. Simulate 10 seconds of service.
        this_thread::sleep_for(chrono::seconds(10));

        // c. Dequeue the served customer.
        string served = dequeue(front, rear);

        // d. Print completion message.
        cout << "Service completed: " << served << " (10 seconds)" << endl;
    }

    // TODO 4: Announce that all customers have been served.
    cout << "All customers have been served." << endl;

    // TODO 5: Display the final queue to confirm it is empty.
    displayQueue(front);

    // PROVIDED: Safety cleanup if any nodes remain.
    while (front != nullptr) dequeue(front, rear);

    return 0;
}
