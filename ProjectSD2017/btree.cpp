#include<iostream>
#include "bTree.h"

using std::cout;
using std::cin;
using std::endl;

bTreeNode::bTreeNode(int _min) : minDegree(_min) {
	students.reserve(2 * minDegree - 1);
	children.reserve(2 * minDegree);
}

bTree::bTree(int _minD) : minDegree(_minD) {
	root = nullptr;
}

int bTree::amount() {
	return root->students.size();
}
void bTree::splitter(bTreeNode* root, int index, bTreeNode* previousNode) { //make sure thet a node has space for key before the key is inserted 
																			//splits the child from the node
																			// root=new node, index = NULL, previousNode = root
	bTreeNode *newNode = new bTreeNode(previousNode->minDegree); // the new node is initialized as root

	for (int i = 0; i < root->minDegree - 1; i++) { //copy the last (minimum degree - 1) keys of newNode to its child
		newNode->students.push_back(previousNode->students[i + root->minDegree]);
	}

	if (previousNode->children.size() != 0) { //copy the last minimum degree keys of newNode to its child
		for (int i = 0; i < root->minDegree; i++) {
			newNode->children.push_back(previousNode->children[i + root->minDegree]);
		}
	}

	previousNode->students.pop_back(); //reduce the number of keys in newNode
	for (int i = root->students.size(); i >= index + 1; i--) { //create space of new child since the node is going to have one
		root->children.insert(root->children.begin() + (i + 1), root->children[i]);
		root->children.erase(root->children.begin() + (i));
	}

	root->children.insert(root->children.begin() + (index + 1), newNode); //link the new child to this node
	for (int i = root->students.size() - 1; i >= index; i--) {
		root->students.insert(root->students.begin() + (i + 1), root->students[i]);
		root->students.erase(root->students.begin() + (i));
	}

	root->students.insert(root->students.begin() + (index), previousNode->students[root->minDegree - 1]);
	for (int i = previousNode->students.size(); i >= root->minDegree; i--) {
		previousNode->students.pop_back();
	}
}

void bTree::insertInTree(bTreeNode* root, Student &student) {
	int index = root->students.size() - 1; //initialize index as index of rightmost element

	if (root->children.size() == 0) { //if this is a leaf node
		while (index >= 0 && compareStudentsNames(student.getName(), root->students[index].getName()) < 0) {
			//finds the location of new key to be inserted
			//moves all greater keys to one place ahead
			root->students.insert(root->students.begin() + (index + 1), root->students[index]);
			root->students.erase(root->students.begin() + (index));
			index--;
		}
		//insert the new key at found location
		root->students.insert(root->students.begin() + (index + 1), student);
	}
	else {//if this node is not leaf
		while (index >= 0 && compareStudentsNames(student.getName(), root->students[index].getName()) < 0) {
			//find the child which is goint to have the new key
			index--;
		}//checks if the found child is full
		if (root->children[index + 1]->students.size() == (2 * root->minDegree) - 1) {
			//splits the child if it is full
			splitter(root, index + 1, root->children[index + 1]);
			//after the split, the middle key goes up
			//checks which of the two is going to have the new key
			if (compareStudentsNames(student.getName(), root->students[index + 1].getName()) > 0)
				index++;
		}
		insertInTree(root->children[index + 1], student);
	}
}

void bTree::printInFile(bTreeNode* root, ostream& out) {
	unsigned index = 0;
	for (index = 0; index < root->students.size(); index++) {
		if (root->children.size() != 0) {
			printInFile(root->children[index], out);
		}
		out << root->students[index] << endl;
	}

	if (root->children.size() != 0) {
		printInFile(root->children[index], out);
	}

}

Student* bTree::searchFor(bTreeNode* node, const char* name) {
	int index = 0;
	while (index < node->students.size() && compareStudentsNames(name, node->students[index].getName()) > 0) {
		index++;
	}
	if (compareStudentsNames(name, node->students[index].getName()) == 0)
		return &node->students[index];
	if (node->children.size() == 0)
		return &Student();
	return searchFor(node->children[index], name);
}

void bTree::printRecords() {
	if (root != nullptr) {
		printInFile(root, cout);
	}
	else cout << "The database is empty!" << endl;
}

vector<Student> bTree::getRoot() {
	return root->students;
}

void bTree::printBTree() {
	ofstream outputFile("students.txt");
	printInFile(root, outputFile);

}

void bTree::searchForPhoneNumber(const char* name) {
	if (searchFor(root, name) == &Student()) {
		warningMessage();
	}
	if (root != nullptr && !(searchFor(root, name) == &Student())) {
		cout << "The student with name: " << name << " has the following phone number: " << (*searchFor(root, name)).getPhoneNumber() << endl;
	}
	if (root == nullptr) {
		cout << "The database is empty." << endl;
	}
}

void bTree::searchForGrade(const char * name) {
	if (searchFor(root, name) == &Student()) {
		warningMessage();
	}

	if (root != nullptr && !(searchFor(root, name) == &Student())) {
		cout << "The student with name: " << name << " has the following grade: " << (*searchFor(root, name)).getGrade() << endl;
	}
	if (root == nullptr) {
		cout << "The database is empty." << endl;
	}
}
void bTree::updateGrade(const char* name) {
	if (isEmpty())
		warningMessage();
	if (!(searchFor(root, name) == &Student())) {

		cout << name << " 's previous grade is " << (*searchFor(root, name)).getGrade() << endl;
		cout << "Insert new grade for this student: " << endl;

		double newGrade;
		cin >> newGrade;

		(*searchFor(root, name)).setGrade(newGrade);
		cout << "The student's new grade is " << (*searchFor(root, name)).getGrade() << endl;

	}
	else warningMessage();
}
void bTree::updatePhoneNumber(const char * name) {
	if (isEmpty())
		warningMessage();
	if (!(searchFor(root, name) == &Student())) {
		cout << name << " 's previous phone number is " << (*searchFor(root, name)).getPhoneNumber() << endl;
		cout << "Insert new phone number for this student:" << endl;

		unsigned long newPhoneNumber;
		cin >> newPhoneNumber;
		(*searchFor(root, name)).setPhoneNumber(newPhoneNumber);
		cout << "The student's new phone number is " << (*searchFor(root, name)).getPhoneNumber() << endl;
	}
	else warningMessage();
}

bool bTree::isEmpty() {
	return (root == nullptr);
}

void bTree::insertNewRecords(Student student) {
	if (root == nullptr) {
		root = new bTreeNode(minDegree);
		root->students.push_back(student);
	}
	else {
		if (root->students.size() == (2 * minDegree - 1)) {
			bTreeNode *newNode = new bTreeNode(minDegree);
			newNode->children.push_back(root);
			splitter(newNode, 0, root);
			int index = 0;
			if (compareStudentsNames(student.getName(), newNode->students.front().getName()) > 0) {
				index++;
			}
			insertInTree(newNode->children[index], student);
			root = newNode;
		}
		else {
			insertInTree(root, student);
		}

	}
}

