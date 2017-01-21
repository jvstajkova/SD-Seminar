#pragma once
#ifndef BTREE_H_
#define BTREE_H_

#include<iostream>
#include<vector>
#include<fstream>
#include "student.h"

using std::ofstream;
using std::vector;

struct bTreeNode {
	vector<Student> students;
	int minDegree; //minimum degree = minimum number of keys
	vector<bTreeNode*> children;
	bTreeNode(int);
};

class bTree {
private:
	bTreeNode *root;
	int minDegree;
	void splitter(bTreeNode*, int, bTreeNode*);//splits the given child node at the child node's given index
	void insertInTree(bTreeNode*, Student&);
	//void remove(bTreeNode*, Student&);
	void printInFile(bTreeNode*, ostream&);
	Student* searchFor(bTreeNode*, const char*); //search by name
public:
	int amount();
	bTree(int);
	vector<Student> getRoot();
	void insertNewRecords(Student);//inserts new records into the node
	bool isEmpty();
	void printRecords();
	void printBTree(); //prints the bTree into file
	void searchForPhoneNumber(const char* name);//finds student's phone number by student's name
	void searchForGrade(const char* name); // finds student's grade by his name
	void updateGrade(const char* name);//updates student's grade
	void updatePhoneNumber(const char* name); //updates student's phone number

};

#endif BTREE_H
