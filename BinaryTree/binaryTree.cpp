#include<iostream>

using namespace std;

struct Node {
	int data;

	Node* left;
	Node* right;

	Node(int data, Node* left = nullptr, Node* right = nullptr) : left(left), right(right) {}
};

class BinaryTree {
	Node* root;
	BinaryTree(Node* node) {
		root = copyNode(node);
	}

	Node* copyNode(Node* node) {
		if (node == nullptr)
			return node;
		return new Node(node->data, copyNode(node->left), copyNode(node->right));
	}

	void eraseNode(Node* node) {
		if (node != nullptr) {
			eraseNode(node->left);
			eraseNode(node->right);
			delete node;
		}
	}

	void assignFrom(Node*& to, Node*& from) {
		Node* toDel = to;
		to = from;
		from = nullptr;
		eraseNode(to);
	}

public:
	BinaryTree() : root(nullptr) {}

	BinaryTree(int rootData, BinaryTree&& left = BinaryTree(), BinaryTree&& right = BinaryTree()) {  //&& priema ei takiva vremenni danni
		root = new Node(rootData);
		assignFrom(root->left, left.root);
		assignFrom(root->right, right.root);
	}

	BinaryTree(const BinaryTree& other) {
		root = copyNode(other.root);
	}

	BinaryTree& operator=(const BinaryTree& other) {
		if (this != &other) {
			eraseNode(root);
			root = copyNode(other.root);
		}
	}

	~BinaryTree() {
		eraseNode(root);
	}

	bool empty() const { return root == nullptr; }

	BinaryTree leftTree() const {
		return BinaryTree(root->left);
	}

	BinaryTree rightTree() const {
		return BinaryTree(root->right);
	}
	int getRoot () const {
		return root->data;
	}
	friend ostream& operator<<(ostream& os, const BinaryTree& bt) {
		//da izvede purvo korena, posle lqvoto, posle dqsnoto poddurvo

		if (bt.empty())
			return os << '.';
		return os << bt.getRoot() << ' ' << bt.leftTree() << ' ' << bt.rightTree() << ' ';

	}
};

int main() {
	BinaryTree bt(3);
	BinaryTree bt2(3, 4, 5);
	BinaryTree bt3(3, 4, BinaryTree(5, 6, 7));

	cout << bt3 << endl;

	system("pause");
	return 0;
}
