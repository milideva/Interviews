#include <iostream>
#include <map>
#include <string>
#include <functional>

// Hash function to map keys to hash values
unsigned int hash(const std::string& key) {
    std::hash<std::string> hasher;
    //std::cout << "hasher: key: "  << key << " hash: " << hasher(key) << std::endl;
    return hasher(key);
}

class ConsistentHashing {
    
private:
    std::map <unsigned int, std::string> hashRing; // sorted by hash of node to node
    const int numKeys;
    const int numNodes;

public:
    ConsistentHashing(int maxNodes, int maxKeys) : numNodes(maxNodes), numKeys(maxKeys) {
        // Add nodes to the hash ring
        for (auto i = 1; i <= maxNodes; i++) {
            std::string node = "Node" + std::to_string(i);
            addNode(node);
        }
    }
    
    // Add node to the hash ring
    void addNode(const std::string& node) {
        unsigned int nodeHash = hash(node);
        hashRing[nodeHash] = node;
    }

    // Remove node from the hash ring
    void removeNode(const std::string& node) {
        unsigned int nodeHash = hash(node);
        hashRing.erase(nodeHash);
    }

    // Get the node responsible for the given key
    std::string getNode(const std::string& key) {
        unsigned int keyHash = hash(key);
        auto it = hashRing.lower_bound(keyHash);

        // The lower_bound function in C++ returns an iterator pointing to the first element in a sorted range that is not less than a specified value. In the context of the consistent hashing implementation provided earlier, it's used to find the first node whose hash value is greater than or equal to the hash value of a given key.

        if (it == hashRing.end()) {
            // Wrap around if key hash is greater than the hash of the last node
            it = hashRing.begin();
        }

        return it->second; // Return the node responsible for the key
    }
    
    int getNumKeys (void) {
        return numKeys;
    }

    int getNodes (void) {
        return numNodes;
    }
};


void test(ConsistentHashing &ch, std::string text) {
    
    for (auto i = 1; i <= ch.getNumKeys(); i++) {
        std::string key = "data" + std::to_string(i);
        std::cout << "Key " << key << " is " << text << " mapped to node: " << ch.getNode(key) << std::endl;
    }
}


int main() {
    int numNodes = 5;
    int numKeys = 100;

    ConsistentHashing ch(numNodes, numKeys);

    // Get the node responsible for a key
    std::string testString = "currently";
    test(ch, testString);
    
    // Remove a node from the hash ring
    ch.removeNode("Node2");

    // Get the node responsible for the same keys again
    testString = "now";
    test(ch, testString);

    return 0;
}
