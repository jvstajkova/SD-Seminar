#pragma once
#ifndef B_TREE
#define B_TREE

#include <vector>
#include "student.h"
#include <fstream>
using std::vector;
using std::ofstream;
struct BTreeNode
{
	vector<Student> allStudents;
	int minimumDegree;
	vector<BTreeNode*> children;
	BTreeNode(int);



};

class BTree
{
	BTreeNode *root;
	int minimumDegree;
	void splitHelper(BTreeNode*, int, BTreeNode*);
	void insertHelper(BTreeNode*, Student&);
	void printHelper(BTreeNode*, ostream&);
	Student* searchHelper(BTreeNode*, const char*);
public:
	int capacity();
	BTree(int);
	void add(Student);
	bool isEmpty();
	void print();
	vector<Student> getRoot();
	void printBTreeInFile();
	void findNumber(const char* name);
	void findAverage(const char* name);
	void changeAverage(const char* name);
	void changeTelephoneNumber(const char* name);
};
#endif B_TREE
