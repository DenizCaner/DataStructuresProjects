#include "BinarySearchTree.h"
#include <iostream>
#include <string>

using namespace std;

BinarySearchTree::BinarySearchTree() {
	root = nullptr;
}

void BinarySearchTree::deleteIter(treeNode* node) {
	if (node != nullptr) {
		deleteIter(node->left);
		deleteIter(node->right);
		delete node;
	}
}

BinarySearchTree::~BinarySearchTree() {
	deleteIter(root);
}

int BinarySearchTree::searchIter(string val, treeNode* node) {
	if (node == nullptr)
		return false;
	else if (node->strVal == val)
		return node->code;
	else if (node->strVal > val)
		return (searchIter(val, node->left));
	else if (node->strVal < val)
		return (searchIter(val, node->right));
	else
		return false;
}

int BinarySearchTree::search(string val) {
	return (searchIter(val, root));
}

bool BinarySearchTree::insertIter(int intVal, string val, treeNode * &node) {
	if (node == nullptr) {
		node = new treeNode;
		node->strVal = val;
		node->code = intVal;
		node->left = nullptr;
		node->right = nullptr;
		return true;
	} else if (node->strVal > val) {
		return (insertIter(intVal, val, node->left));
	} else  if (node->strVal < val) {
		return (insertIter(intVal, val, node->right));
	} else  if (node->strVal == val) {
		return false;
	}
}

void BinarySearchTree::insert(int intVal, string val) {
	insertIter(intVal, val, root);
}
