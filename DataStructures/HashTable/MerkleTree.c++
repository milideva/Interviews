#include <iostream>
#include <vector>
#include <string>
#include <functional>

class MerkleNode {
public:
    std::size_t hash;
    MerkleNode* left;
    MerkleNode* right;

    MerkleNode(std::size_t hashValue) : hash(hashValue), left(nullptr), right(nullptr) {}
};

class MerkleTree {
public:
    MerkleNode* root;

    MerkleTree(const std::vector<std::string> &dataBlocks) {
        std::vector<MerkleNode*> leaves;
        for (const auto &data : dataBlocks) {
            leaves.push_back(new MerkleNode(std::hash<std::string>{}(data)));
        }
        root = buildTree(leaves);
    }

    ~MerkleTree() {
        deleteTree(root);
    }

private:
    MerkleNode* buildTree(std::vector<MerkleNode*> &nodes) {
        if (nodes.size() == 1) {
            return nodes[0];
        }

        std::vector<MerkleNode*> parentNodes;

        for (size_t i = 0; i < nodes.size(); i += 2) {
            if (i + 1 < nodes.size()) {
                std::size_t combinedHash = std::hash<std::size_t>{}(nodes[i]->hash ^ nodes[i + 1]->hash);
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
    std::vector<std::string> dataBlocks = {
        "block1",
        "block2",
        "block3",
        "block4"
    };

    MerkleTree tree(dataBlocks);
    std::cout << "Merkle Root: " << tree.root->hash << std::endl;

    return 0;
}