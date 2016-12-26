#pragma once
#include <stdio.h>

int max(int a, int b) {
	return (a > b) ? a : b;
}

class TreeAVL {
public:
	struct AVLNode {
		int key;
		AVLNode* left;
		AVLNode* right;
		int height;
	};

private:
	int height(AVLNode* node) {
		if (node == nullptr)
			return 0;
		return node->height;
	}

	int getBalance(AVLNode* node) {
		if (node == nullptr)
			return 0;
		return height(node->left) - height(node->right);
	}

	AVLNode* rightRotate(AVLNode* y) {
		AVLNode* x = y->left;
		AVLNode* T2 = x->right;

		// Perform the rotation
		x->right = y;
		y->left = T2;

		// Update the heights
		y->height = max(height(y->left), height(y->right)) + 1;
		x->height = max(height(x->left), height(x->right)) + 1;

		// Return the new root
		return x;
	}

	AVLNode* leftRotate(AVLNode* x) {
		AVLNode* y = x->right;
		AVLNode* T2 = y->left;

		// Perform the rotation
		y->left = x;
		x->right = T2;

		// Update the heights
		x->height = max(height(x->left), height(x->right)) + 1;
		y->height = max(height(y->left), height(y->right)) + 1;

		// Return the new root
		return y;
	}

private:
	AVLNode* root;

public:
	TreeAVL() : root(nullptr) {}

	AVLNode* getRoot() {
		return root;
	}

	void preOrder(AVLNode* root) {
		if (root != nullptr) {
			printf("%d ", root->key);
			preOrder(root->left);
			preOrder(root->right);
		}
	}

	void inOrder(AVLNode* root) {
		if (root != nullptr) {
			inOrder(root->left);
			printf("%d ", root->key);
			inOrder(root->right);
		}
	}
	
	void postOrder(AVLNode* root) {
		if (root != nullptr) {
			postOrder(root->left);
			postOrder(root->right);
			printf("%d ", root->key);
		}
	}

	AVLNode* treeMinimum(AVLNode* node) {
		AVLNode* current = node;
		while (current->left != nullptr)
			current = current->left;
		return current;
	}

	AVLNode* treeMaximum(AVLNode* node) {
		AVLNode* current = node;
		while (current->right != nullptr)
			current = current->right;
		return current;
	}

	void insert(int key) {
		root = _insert(root, key);
	}

	void remove(int key) {
		root = _remove(root, key);
	}

private:
	AVLNode* _insert(AVLNode* node, int key) {
		// 1. Check if node is null
		if (node == nullptr) {
			AVLNode* N = new AVLNode;
			N->key = key;
			N->left = nullptr;
			N->right = nullptr;
			N->height = 1;
			return N;
		}

		// 2. Perform normal BST insertion
		if (key < node->key)
			node->left = _insert(node->left, key);
		else
			node->right = _insert(node->right, key);

		// 3. Update the height of the ancestor node
		node->height = max(height(node->left), height(node->right)) + 1;

		// 4. Balance
		int balance = getBalance(node);

		// L-L case
		if (balance > 1 && key < node->left->key)
			return rightRotate(node);

		// R-R case
		if (balance < -1 && key > node->right->key)
			return leftRotate(node);

		// L-R case
		if (balance > 1 && key > node->left->key) {
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}

		// R-L case
		if (balance < -1 && key < node->right->key) {
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}

		// already balanced case
		return node;
	}

	AVLNode* _remove(AVLNode* node, int key) {
		// 1. Perform normal BST removal
		if (node == nullptr)
			return node;

		if (key < node->key)
			node->left = _remove(node->left, key);
		else if (key > node->key)
			node->right = _remove(node->right, key);
		else { // if key == node->key => delete this
			// Case 1. No children
			if (node->left == nullptr && node->right == nullptr) {
				delete node;
				node = nullptr;
			}
			// Case 2. One child
			else if ((node->left != nullptr) != (node->right != nullptr)) {
				// select the child
				AVLNode* temp = node->left ? node->left : node->right;
				*node = *temp;
				delete temp;
			}
			// Case 3. Two children
			else {
				// Get the inorder successor
				// (smallest in the right subtree)
				AVLNode* temp = treeMinimum(node->right);
				// Copy its data to this node
				node->key = temp->key;
				// Delete the inorder successor
				node->right = _remove(node->right, temp->key);
			}
		}

		// Did we remove the only node?
		if (node == nullptr)
			return node;

		// 2. Update the height
		node->height = max(height(node->left), height(node->right)) + 1;

		// 3. Balance
		int balance = getBalance(node);

		// L-L case
		if (balance > 1 && getBalance(node->left) >= 0)
			return rightRotate(node);

		// R-R case
		if (balance < -1 && getBalance(node->right) <= 0)
			return leftRotate(node);

		// L-R case
		if (balance > 1 && getBalance(node->left) < 0) {
			node->left = leftRotate(node->left);
			return rightRotate(node);
		}

		// R-L case
		if (balance < -1 && getBalance(node->right) > 0) {
			node->right = rightRotate(node->right);
			return leftRotate(node);
		}

		// already balanced case
		return node;
	}
};
