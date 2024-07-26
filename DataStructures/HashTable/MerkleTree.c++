#include <iostream>
#include <vector>
#include <string>
#include <functional>

using namespace std;

class MerkleNode {
public:
    size_t hash;
    MerkleNode* left;
    MerkleNode* right;

    MerkleNode(size_t hashValue) : hash(hashValue), left(nullptr), right(nullptr) {}
};

class MerkleTree {
public:
    MerkleNode* root;

    MerkleTree(const vector<string> &dataBlocks) {
        vector <MerkleNode *> leaves;
        for (const auto &data : dataBlocks) {
            MerkleNode *leafNode = new MerkleNode(hash<string>{}(data));
            leaves.push_back(leafNode);
        }
        root = buildTree(leaves);
    }

    ~MerkleTree() {
        deleteTree(root);
    }

private:
    MerkleNode* buildTree (vector <MerkleNode *> &nodes) {
        if (nodes.size() == 1) {
            return nodes[0];
        }

        vector <MerkleNode *> parentNodes;

        for (size_t i = 0; i < nodes.size(); i += 2) {
            if (i + 1 < nodes.size()) {
                size_t combinedHash = hash<size_t>{}(nodes[i]->hash ^ nodes[i + 1]->hash);
                MerkleNode* parentNode = new MerkleNode(combinedHash);
                parentNode->left = nodes[i];
                parentNode->right = nodes[i + 1];
                parentNodes.push_back(parentNode);
            } else {
                // In case of an odd number of nodes, duplicate the last node
                parentNodes.push_back(nodes[i]);
            }
        }

        return buildTree(parentNodes);
    }

    void deleteTree(MerkleNode* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }
};

int main() {
    vector<string> dataBlocks = {
        "block1",
        "block2",
        "block3",
        "block4"
    };

    MerkleTree tree(dataBlocks);
    cout << "Merkle Root: " << tree.root->hash << endl;

    return 0;
}