#ifndef TREAP_H
#define TREAP_H

#include <cstdlib>
#include <ctime>

struct TreapNode {
    int key, priority;
    TreapNode* left;
    TreapNode* right;

    TreapNode(int key) : key(key), priority(rand() % 50000 + 1), left(nullptr), right(nullptr) {}
};

class Treap {
public:
    TreapNode* root;

    Treap() : root(nullptr) {
        srand(time(nullptr));
    }

    TreapNode* rotateRight(TreapNode* y) {
        TreapNode* x = y->left;
        y->left = x->right;
        x->right = y;
        return x;
    }

    TreapNode* rotateLeft(TreapNode* x) {
        TreapNode* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    TreapNode* insert(TreapNode* root, int key) {
        if (!root)
            return new TreapNode(key);

        if (key == root->key) {
            return root;
        }

        if (key < root->key) {
            root->left = insert(root->left, key);
            if (root->left->priority > root->priority)
                root = rotateRight(root);
        } else {
            root->right = insert(root->right, key);
            if (root->right->priority > root->priority)
                root = rotateLeft(root);
        }

        return root;
    }


    TreapNode* deleteNode(TreapNode* root, int key, bool& found) {
        if (!root) {
            found = false;
            return root;
        }

        if (key < root->key)
            root->left = deleteNode(root->left, key, found);
        else if (key > root->key)
            root->right = deleteNode(root->right, key, found);
        else {
            found = true;
            if (!root->left)
                return root->right;
            else if (!root->right)
                return root->left;

            if (root->left->priority < root->right->priority) {
                root = rotateLeft(root);
                root->left = deleteNode(root->left, key, found);
            } else {
                root = rotateRight(root);
                root->right = deleteNode(root->right, key, found);
            }
        }
        return root;
    }

    bool search(TreapNode* root, int key) {
        if (!root) return false;
        if (root->key == key) return true;
        if (key < root->key)
            return search(root->left, key);
        return search(root->right, key);
    }

    void insert(int key) {
        if (!search(root, key)) root = insert(root, key);
    }

    bool deleteNode(int key) {
        bool found = false;
        root = deleteNode(root, key, found);
        return found;
    }

    bool search(int key) {
        return search(root, key);
    }
};

#endif // TREAP_H
