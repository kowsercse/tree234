//============================================================================
// Name        : Tree234.cpp
// Author      : Kowser
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

using namespace std;

const int MAX_SIZE = 3;

class Entry {
	int key;
	int value;

public:
	Entry(int key, int value) {
		this->key = key;
		this->value = value;
	}
	bool equals(Entry* other) {
		if (other == NULL) {
			return false;
		}
		return key == other->key;
	}
	int getKey() {
		return key;
	}
};

class Node {
	Node* children[MAX_SIZE + 1];
	Entry* entries[MAX_SIZE];
	int size;

	bool exists(Entry* entry) {
		for (int i = 0; i < size; i++) {
			if (entries[i]->getKey() == entry->getKey()) {
				return true;
			}
		}
		return false;
	}
	void init(Node* parent, Entry* entry) {
		this->parent = parent;
		if (entry != NULL) {
			entries[0] = entry;
			size = 1;
		}
	}
	int findInsertPosition(Entry* entry) {
		int i = 0;
		while (i < size && entries[i]->getKey() < entry->getKey()) {
			i++;
		}
		return i;
	}
	void promote(Entry* middle, Node* left, Node* right) {
		if (this->isFull()) {
			Entry* middleTree = this->entries[1];
			Node* leftTree = new Node(entries[0]);
			Node* rightTree = new Node(entries[2]);

			leftTree->children[0] = children[0];
			leftTree->children[1] = children[1];
			rightTree->children[0] = children[2];
			rightTree->children[1] = children[3];

			Node* node = middleTree->getKey() > middle->getKey() ? leftTree : rightTree;
			node->promote(middle, left, right);

			if (this->parent == NULL) {
				this->parent = new Node();
			}
			this->parent->promote(middleTree, leftTree, rightTree);
		} else {
			int insertPosition = findInsertPosition(middle);
			left->parent = this;
			right->parent = this;
			for (int j = size; j> insertPosition; j--) {
				children[j + 1] = children[j];
			}
			this->children[insertPosition] = left;
			this->children[insertPosition + 1] = right;

			put(insertPosition, middle);
		}
	}

	void put(int insertPosition, Entry* entry) {
		for (int j = size; j > insertPosition; j--) {
			entries[j] = entries[j - 1];
		}
		entries[insertPosition] = entry;
		size++;
	}

public:
	Node* parent;
	Node() {
		init(NULL, NULL);
	}
	Node(Entry* entry) {
		init(NULL, entry);
	}
	Node(Node* parent, Entry* entry) {
		init(parent, entry);
	}
	void insert(Entry* entry) {
		if (this->isFull()) {
			Entry* middle = this->entries[1];
			Node* left = new Node(entries[0]);
			Node* right = new Node(entries[2]);

			left->children[0] = children[0];
			left->children[1] = children[1];
			right->children[0] = children[2];
			right->children[1] = children[3];

			Node* node = middle->getKey() > entry->getKey() ? left : right;
			node->insert(entry);

			if (this->parent == NULL) {
				this->parent = new Node();
			}
			this->parent->promote(middle, left, right);
		} else {
			int insertPosition = findInsertPosition(entry);
			put(insertPosition, entry);
		}
	}

	/**
	 * done
	 */
	bool isFull() {
		return this->size == 3;
	}
	bool isLeaf() {
		return children[0] == NULL;
	}
	Node* descend(Entry* entry) {
		if (isLeaf()) {
			return NULL;
		}
		for (int i = 0; i < size; i++) {
			if (entries[i]->getKey() > entry->getKey()) {
				return children[i];
			}
		}
		return children[size];
	}
	void printInorder() {
		cout << "[";
		for (int i = 0; i < size; i++) {
			if (!isLeaf()) {
				this->children[i]->printInorder();
			}
			cout << "." << entries[i]->getKey() << ".";
		}
		if (!isLeaf()) {
			this->children[size]->printInorder();
		}
		cout << "]";
	}
};

class Tree {
	Node* root;

public:
	Tree() {
		root = NULL;
	}
	void insert(Entry* entry) {
		if (root == NULL) {
			root = new Node();
		}

		Node* current = root;
		while (!current->isLeaf()) {
			current = current->descend(entry);
		}

		current->insert(entry);
		if (root->parent != NULL) {
			root = root->parent;
		}
	}
	void print() {
		root->printInorder();
		cout << endl;
	}
};

int main() {
	int values[] = { 3, 7, 4, 9, 10, 0, 5, 6, 8, 2, 1, -3, -8, -5 };
	Tree* tree = new Tree();
	for (int i = 0; i < 14; i++) {
		int key = values[i];
		Entry* entry = new Entry(key, key);
		cout << entry->getKey() << endl;
		tree->insert(entry);
		tree->print();
	}
	tree->print();

	return 0;
}
