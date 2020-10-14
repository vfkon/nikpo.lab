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
	int GetAmountofChildren() {
		return children.size();
	}
	void DestroyTree(Node* current) {
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
//void generatebranches(Node*root, int nodesleft,int level) {
//	srand(time(0));
//	int amount = rand()%6;
//	for (int i = 0; (i < amount); i++) {
//		root->AddNode(root, 10 * level + i);
//	}
//	for (int i = 0; (i < amount)&&(nodesleft>0); i++) {
//		generatebranches(root->GetChild(i),nodesleft-amount,level+1);
//	}
//}
int generatebranches1(Node* root, int nodes,int level, int neededlevel) {
	if (root->GetAmountofChildren() != 0) {
		for (int i = 0; i < root->GetAmountofChildren(); i++) {
			nodes=generatebranches1(root->GetChild(i),nodes,level+1, neededlevel);
		}
	}
	if (level != neededlevel)return nodes;//возврат если для этого листа в какой-то момент рандом выдал 0, лист тупиковый
	srand(time(0));
	int amount = rand() % 6;
	for (int i = 0; i < amount; i++) {
		root->AddNode(root, 10 * level + i);
	}
	return nodes - amount;
}
void gentree(int nodes) {
	Node* root = new Node(0);
	int neededlevel = 0;
	while (nodes > 0) {
		nodes = generatebranches1(root, nodes, 0, neededlevel);
		neededlevel++;
	}
	delete root;
}
//void generatebranches(Node* root, int nodes) {
//	int amount = 0;
//	
//
//	do {
//		amount = rand() % 6;
//		nodes -= amount;
//
//	} while (nodes > 0);
//}
int main() {
	gentree(5);
	return 0;
}