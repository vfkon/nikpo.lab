#include <vector>
#include <cstdlib>
#include <time.h>
class Node {
private:
	Node*parent;
	std::vector<Node*> children;
	int value;
public:
	Node* GetChild(int index) {
		return children[index];
	}
	void DestroyTree(Node* current) {
		while (parent != nullptr)current = current->parent;
		for (int i = 0; i < children.size(); i++) {
			DestroyTree(children[i]);
			delete children[i];
		}
		children.clear();
	}
	void AddNode(Node*root,int initval) {
		Node *leaf = new Node(initval,root);
		children.push_back(leaf);
	}
	Node() {
		parent = nullptr;
		value = 0;
	};
	Node(int initval,Node*prnt=nullptr) {
		value = initval;
		parent = prnt;
	};
	~Node() {
		DestroyTree(this);
	};
	
};
void generatebranches(Node*root, int nodesleft,int level) {
	srand(time(0));
	int amount = rand()%6;
	for (int i = 0; i < amount; i++) {
		root->AddNode(root, 10 * level + i);
	}
	for (int i = 0; i < amount; i++) {
		generatebranches(root->GetChild(i),nodesleft-amount,level+1);
	}
	delete root;
}
int main() {
	Node* root = new Node(0);
	delete root;
	return 0;
}