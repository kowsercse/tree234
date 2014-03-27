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
	Node* parent;
	Node* children[MAX_SIZE + 1];
	Entry* entries[MAX_SIZE];
	int size;

//	bool exists(Entry* entry) {
//		for (int i = 0; i < size; i++) {
//			if (entries[i]->compareTo(entry) == 0) {
//				return true;
//			}
//		}
//		return false;
//	}
	bool contains(Entry* entry) {
		for (int i = 0; i < 4; i++) {
			if (entries[4]->equals(entry)) {
				return true;
			}
		}
		return false;
	}

	int findInsertPosition(Entry* entry) {
		int i = 0;
		while (i < size && entries[i]->getKey() < entry->getKey()) {
			i++;
		}
		return i;
	}

	void pushLeftFromPosition(int i) {
		for (int j = i; j < size; j++) {
			entries[j + 1] = entries[j];
		}
	}

public:
	Node() {
		size = 0;
		parent = NULL;
	}
	Node(Node* parent, Entry* entry) {
		this->parent = parent;
		entries[0] = entry;
		size = 1;
	}
	void split() {
		Node* left = new Node(this, entries[0]);
		Node* right = new Node(this, entries[2]);
		if (!isLeaf()) {
			left->children[0] = children[0];
			left->children[1] = children[1];
			right->children[0] = children[2];
			right->children[1] = children[1];

			for (int i = 0; i <= size; i++) {
				children[i] = NULL;
			}
		}
		this->children[0] = left;
		this->children[1] = right;
		Entry* middle = this->entries[1];
		for (int i = 0; i < size; i++) {
			this->entries[i] = NULL;
		}
		this->entries[0] = middle;
		this->size = 1;
	}
	void insert(Entry* entry) {
		if (this->isFull()) {
			split();
			Node* current = this;
			while (!current->isLeaf()) {
				current = current->descend(entry);
			}
			current->insert(entry);
		} else {
			int insertPosition = findInsertPosition(entry);
			pushLeftFromPosition(insertPosition);
			entries[insertPosition] = entry;
			size++;
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
	Node* getParent() {
		return parent;
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
	}
	void print() {
		root->printInorder();
	}
};

int main() {
	int values[] = { 3, 7, 4, 9, 10, 0, 5, 6, 8, 2, 1, -3, -8, -5 };
	Tree* tree = new Tree();
	for (int i = 0; i < 14; i++) {
		int key = values[i];
		Entry* entry = new Entry(key, key);
		cout << entry->getKey() << ends;
		tree->insert(entry);
		tree->print();
		cout << endl;
	}

	return 0;
}
