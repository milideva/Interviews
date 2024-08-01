#include <iostream>
#include <vector>
#include <random>

struct Node {
    int val;
    Node *next;
    Node *random;
    Node (int v) : val(v), next(nullptr), random(nullptr) {}
};

class SinglyLinkedList {
    Node *head;
    public:
    SinglyLinkedList (): head(nullptr) {}
    ~SinglyLinkedList () {
        Node *curr = head;
        
        while (curr) {
            Node *next = curr->next;
            delete curr;
            curr = next;
        }
    }
    
    void insertAtBeginning (int val) {
        Node *newNode = new Node(val);
        newNode->next = head;
        head = newNode;
        return;
    }
    
    void insertSorted (int val) {
        Node *prev, *curr = head;
        Node *newNode = new Node(val);
        if (newNode == nullptr) 
            return;
        if (head == nullptr) {
            head = newNode;
            return;
        }
        prev = nullptr;
        while (curr and curr->val < val) {
            prev = curr;
            curr = curr->next;
        }
        if (prev) {
            prev->next = newNode;
        }
        if (curr == head) {
            head = newNode;
        }
        newNode->next = curr;
    }
    
    // What should be the middle node if #nodes is even?
    Node *middleOfLinkedList (void) {
        Node *slow, *fast;
        
        slow = fast = head;
        
        while (fast and fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }
    
    void reverseLinkedList (void) {
        Node *curr = head;
        Node *prev = nullptr;
        while (curr) {
            Node *next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        if (prev) 
            head = prev;
    }
    
    void display (void) const {
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->val;
            if (temp->random) {
                std::cout << " R{" << temp->random->val << "}";   
            }
            std::cout << " -> ";
            temp = temp->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    void setRandom (void) {
        if (!head) return;
    
        // Collect all nodes in a vector
        std::vector<Node*> nodes;
        Node* curr = head;
        while (curr) {
            nodes.push_back(curr);
            curr = curr->next;
        }
    
        // Create a random device and use it to seed the random number generator
        std::random_device rd;
        std::mt19937 g(rd());
    
        // Shuffle the vector to randomize node positions
        std::shuffle(nodes.begin(), nodes.end(), g);
    
        // Set random pointers using the shuffled nodes
        curr = head;
        for (Node* randomNode : nodes) {
            curr->random = randomNode;
            curr = curr->next;
        }
    }
};


void test (void) {
    SinglyLinkedList list;
    list.insertSorted(1);
    list.insertSorted(2);
    list.insertSorted(3);
    list.insertSorted(4);
    list.insertSorted(5);

    list.display();

    Node* middleNode = list.middleOfLinkedList();
    if (middleNode != nullptr) {
        std::cout << "Middle node: " << middleNode->val << std::endl;
    } else {
        std::cout << "The list is empty." << std::endl;
    }
    
    list.reverseLinkedList();
    list.display();
    
    list.setRandom(); // Call to set random pointers
    list.display();

}

int main(void) {
    test();
    return 0;
}
