#include <atomic>
#include <memory>
#include <iostream>

template <typename T>
class LocklessQueue {
private:
    struct Node {
        std::shared_ptr<T> data;
        std::atomic<Node*> next;
        std::atomic<Node*> prev;
        
        Node() : next(nullptr), prev(nullptr) {}
        
        explicit Node(const T& value) : data(std::make_shared<T>(value)), next(nullptr), prev(nullptr) {}
    };
    
    // Head and tail are dummy nodes that never change
    Node* head;
    Node* tail;

public:
    LocklessQueue() {
        // Create dummy nodes
        head = new Node();
        tail = new Node();
        
        // Connect them
        head->next.store(tail);
        tail->prev.store(head);
    }
    
    ~LocklessQueue() {
        // Clean up all nodes between head and tail
        Node* current = head->next.load();
        while (current != tail) {
            Node* next = current->next.load();
            delete current;
            current = next;
        }
        
        // Delete the dummy nodes
        delete head;
        delete tail;
    }
    
    void enqueue(const T& value) {
        // Create new node
        Node* new_node = new Node(value);
        
        while (true) {
            // Tail->prev is the last real node (or head if queue is empty)
            Node* last = tail->prev.load();
            
            // Set new node's next to tail
            new_node->next.store(tail);
            
            // Set new node's prev to the current last node
            new_node->prev.store(last);
            
            // Try to update last->next to point to our new node
            if (last->next.compare_exchange_strong(tail, new_node)) {
                // Successfully linked new_node after last
                
                // Now update tail->prev to point to new_node
                // This might fail if another enqueue happens simultaneously,
                // but that's okay as the queue will still be in a valid state
                tail->prev.compare_exchange_strong(last, new_node);
                
                return;
            }
            
            // If we get here, another thread modified the structure before we could
            // We'll retry the whole operation
        }
    }
    
    std::shared_ptr<T> dequeue() {
        while (true) {
            // Head->next points to the first real node (or tail if queue is empty)
            Node* first = head->next.load();
            
            // If first is tail, the queue is empty
            if (first == tail) {
                return nullptr;
            }
            
            // Get the node after first
            Node* next = first->next.load();
            
            // Try to update head->next to skip over first
            if (head->next.compare_exchange_strong(first, next)) {
                // Successfully removed first from the queue
                
                // Update next->prev to point to head
                // This might fail if another dequeue happens simultaneously,
                // but that's okay as the queue will still be in a valid state
                if (next) {
                    next->prev.compare_exchange_strong(first, head);
                }
                
                // Get the data before deleting the node
                std::shared_ptr<T> result = first->data;
                
                // Free the removed node
                delete first;
                
                return result;
            }
            
            // If we get here, another thread modified the structure before we could
            // We'll retry the whole operation
        }
    }
    
    bool isEmpty() {
        return head->next.load() == tail;
    }
};

// Example usage
int main() {
    LocklessQueue<int> q;
    
    // Enqueue some values
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    
    // Dequeue and print values
    std::shared_ptr<int> value;
    while ((value = q.dequeue()) != nullptr) {
        std::cout << "Dequeued: " << *value << std::endl;
    }
    std::cout << "Manish is great \n";
    
    return 0;
}