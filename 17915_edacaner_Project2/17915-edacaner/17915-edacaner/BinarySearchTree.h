#ifndef _BINARYSEARCHTREE
#define _BINARYSEARCHTREE

#include <string>
using namespace std;

class treeNode {
public:
   int code;
   string strVal;
   treeNode *left;
   treeNode *right;
};

class BinarySearchTree {
 public:
   BinarySearchTree();
   BinarySearchTree(const BinarySearchTree & tree);
   ~BinarySearchTree();

   int search(string Value);
   void insert(int eda, string Value);

 private:
   void deleteIter(treeNode * Tree);
   int searchIter(string Value, treeNode * Tree);
   bool insertIter(int eda, string Value, treeNode * &Tree);

   treeNode *root;
};
#endif