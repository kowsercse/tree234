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
	Entry() {
		key = 0;
		value = 0;
	}
	Entry(int key, int value) {
		this->key = key;
		this->value = value;
	}
	int compareTo(Entry* entry) {
		return key - entry->key;
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

	Node() {
		parent = NULL;
		size = 0;
	}
	bool exists(Entry* entry) {
		for (int i = 0; i < size; i++) {
			if (entries[i]->compareTo(entry) == 0) {
				return true;
			}
		}
		return false;
	}
	void putSecond(Entry* entry) {
		if (entries[0]->compareTo(entry) > 0) {
			entries[1] = entries[0];
			entries[0] = entry;
		} else {
			entries[1] = entry;
		}
		size = 2;
	}
	void putThird(Entry* entry) {
		if (entries[0]->compareTo(entry) > 0) {
			entries[2] = entries[1];
			entries[1] = entries[0];
		} else if (entries[1]->compareTo(entry) < 0) {
			entries[2] = entry;
		} else {
			entries[2] = entries[1];
			entries[1] = entry;
		}
		size = 3;
	}

public:
	Node(Entry* entry) {
		parent = NULL;
		size = 0;

		entries[0] = entry;
		size = 1;
	}
	bool contains(Entry* entry) {
		for (int i = 0; i < 4; i++) {
			if (entries[4]->equals(entry)) {
				return true;
			}
		}
		return false;
	}
	void printInorder() {
		cout << "[";
		for (int i = 0; i < size; i++) {
			cout << entries[i]->getKey();
		}
		cout << "]" << endl;
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
		for (int i = 0; i <= size; i++) {
		}
		return NULL;
	}
	void split() {
	}

	void insert(Entry* entry) {
		if (exists(entry)) {
			return;
		}

		if (size == 1) {
			putSecond(entry);
		} else if (size == 2) {
			putThird(entry);
		} else if (size == 3) {
			split();
		}
	}

	/**
	 * done
	 */
	bool isFull() {
		return this->size == 3;
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
			root = new Node(entry);
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
	for (int i = 0; i < 3; i++) {
		int key = values[i];
		Entry* entry = new Entry(key, key);
		cout << entry->getKey() << ends;
		tree->insert(entry);
		tree->print();
	}

	return 0;
}
