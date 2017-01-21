#include "BTree.h"
#include <iostream>

using std::cout;
using std::cin;

BTreeNode::BTreeNode(int _minimum) : minimumDegree(_minimum)
{
	allStudents.reserve(2 * minimumDegree - 1);
	children.reserve(2 * minimumDegree);
}

BTree::BTree(int _minimumDegree) : minimumDegree(_minimumDegree)
{
	root = nullptr;
}

int BTree::capacity()
{
	return root->allStudents.size();
}

void BTree::splitHelper(BTreeNode* root, int index, BTreeNode* oldNode) //root = newNode, index =0 , oldNode=root
{
	BTreeNode *newNode = new BTreeNode(oldNode->minimumDegree);
	for (int i = 0; i < root->minimumDegree - 1; i++)
	{
		newNode->allStudents.push_back(oldNode->allStudents[i + root->minimumDegree]);
	}

	if (oldNode->children.size() != 0)
	{
		for (int i = 0; i < root->minimumDegree; i++)
		{
			newNode->children.push_back(oldNode->children[i + root->minimumDegree]);
		}
	}

	oldNode->allStudents.pop_back();
	for (int i = root->allStudents.size(); i >= index + 1; i--)
	{
		root->children.insert(root->children.begin() + (i + 1), root->children[i]);
		root->children.erase(root->children.begin() + (i));
	}

	root->children.insert(root->children.begin() + (index + 1), newNode);

	for (int i = root->allStudents.size() - 1; i >= index; i--)
	{
		root->allStudents.insert(root->allStudents.begin() + (i + 1), root->allStudents[i]);
		root->allStudents.erase(root->allStudents.begin() + (i));
	}

	root->allStudents.insert(root->allStudents.begin() + (index), oldNode->allStudents[root->minimumDegree - 1]);
	for (int i = oldNode->allStudents.size(); i >= root->minimumDegree; i--)
	{
		oldNode->allStudents.pop_back();

	}

}

void BTree::insertHelper(BTreeNode* root, Student &s)
{
	int index = root->allStudents.size() - 1;

	if (root->children.size() == 0)
	{
		while (index >= 0 && compareNames(s.getName(), root->allStudents[index].getName()) < 0)
		{
			root->allStudents.insert(root->allStudents.begin() + (index + 1), root->allStudents[index]);
			root->allStudents.erase(root->allStudents.begin() + (index));

			index--;

		}
		root->allStudents.insert(root->allStudents.begin() + (index + 1), s);
	}
	else
	{
		while (index >= 0 && compareNames(s.getName(), root->allStudents[index].getName()) < 0)
		{
			index--;
		}

		if (root->children[index + 1]->allStudents.size() == (2 * root->minimumDegree) - 1)
		{
			splitHelper(root, index + 1, root->children[index + 1]);
			if (compareNames(s.getName(), root->allStudents[index + 1].getName()) >0)index++;
		}

		insertHelper(root->children[index + 1], s);

	}
}

void BTree::printHelper(BTreeNode* root, ostream& o)
{
	unsigned index = 0;
	for (index = 0; index < root->allStudents.size(); index++)
	{
		if (root->children.size() != 0)
		{
			printHelper(root->children[index], o);
		}
		o << root->allStudents[index] << '\n';
	}

	if (root->children.size() != 0)
	{
		printHelper(root->children[index], o);
	}
	/*if (root->children.size())
	{
	for (BTreeNode* b : root->children)
	{
	printHelper(b, o);
	cout << '\n';
	}
	}*/
}

Student* BTree::searchHelper(BTreeNode* node, const char* name)
{
	int index = 0;
	while (index < node->allStudents.size() && compareNames(name, node->allStudents[index].getName())>0)
	{
		index++;
	}
	if (compareNames(name, node->allStudents[index].getName()) == 0) return &node->allStudents[index];
	if (node->children.size() == 0) return &Student();
	return searchHelper(node->children[index], name);
}

void BTree::print()
{
	if (root != nullptr)
	{
		printHelper(root, cout);
	}
	else cout << "Empty database!" << '\n';
}

vector<Student> BTree::getRoot()
{
	return root->allStudents;
}

void BTree::printBTreeInFile()
{
	ofstream studentsFile("students.txt");
	printHelper(root, studentsFile);

}

void BTree::findNumber(const char* name)
{
	if (searchHelper(root, name) == &Student())
	{
		errorMessage();
	}
	if (root != nullptr && !(searchHelper(root, name) == &Student()))
	{
		cout << "The student " << name << " has number " << (*searchHelper(root, name)).getNumber() << "." << '\n';;
	}
	if (root == nullptr)
	{
		cout << "Empty database" << '\n';
	}
}

void BTree::findAverage(const char * name)
{
	if (searchHelper(root, name) == &Student())
	{
		errorMessage();
	}

	if (root != nullptr && !(searchHelper(root, name) == &Student()))
	{
		cout << "The student " << name << " has average " << (*searchHelper(root, name)).getAverage() << "." << '\n';
	}
	if (root == nullptr)
	{
		cout << "Empty database" << '\n';
	}
}
void BTree::changeAverage(const char* name)
{
	if (isEmpty()) errorMessage();
	if (!(searchHelper(root, name) == &Student())) {

		cout << name << " 'old average  " << (*searchHelper(root, name)).getAverage() << '\n';
		cout << "Enter new average for this student:" << '\n';
		double newAverage;

		cin >> newAverage;

		(*searchHelper(root, name)).setAverage(newAverage);
		cout << "The new average - " << (*searchHelper(root, name)).getAverage() << '\n';


	}
	else errorMessage();
}
void BTree::changeTelephoneNumber(const char * name)
{
	if (isEmpty()) errorMessage();
	if (!(searchHelper(root, name) == &Student())) {

		cout << name << " 'old telephone number  " << (*searchHelper(root, name)).getNumber() << '\n';
		cout << "Enter new average for this student:" << '\n';
		double newNumber;

		cin >> newNumber;

		(*searchHelper(root, name)).setNumber(newNumber);
		cout << "The new average - " << (*searchHelper(root, name)).getNumber() << '\n';
	}
	else errorMessage();
}

bool BTree::isEmpty()
{
	return (root == nullptr);
}

void BTree::add(Student s)
{
	if (root == nullptr)
	{
		root = new BTreeNode(minimumDegree);
		root->allStudents.push_back(s);
	}
	else
	{
		if (root->allStudents.size() == (2 * minimumDegree - 1))
		{
			BTreeNode *newNode = new BTreeNode(minimumDegree);
			newNode->children.push_back(root);
			splitHelper(newNode, 0, root);
			int index = 0;
			if (compareNames(s.getName(), newNode->allStudents.front().getName()) > 0)
			{
				index++;
			}
			insertHelper(newNode->children[index], s);
			root = newNode;
		}
		else
		{
			insertHelper(root, s);
		}

	}
}
