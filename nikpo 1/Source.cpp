#include <vector>
#include <cstdlib>
#include <time.h>
class Node {
private:
	Node*parent;
	std::vector<Node*> children;
	int value;
	bool IsDegenerate;
public:
	Node* GetParent() {
		return parent;
	}
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
int generatebranches1(Node* root, int nodes,int level, int neededlevel,int totalnodes) {
	int oldnodes = nodes;
	int amount = 0;
	if (level == neededlevel) {//мы на правильном уровне
		srand(time(0));
		amount = rand() % 6;
		for (int i = 0; i < amount; i++) {
			root->AddNode(root, 10 * level + i);//сгенерировать ветви
		}
		//if ((oldnodes = nodes) && (!root->GetParent())) {
		//	return -1;
		//}
		//if (level != neededlevel) {
		//	if (root->GetParent())return nodes;//возврат если для этого листа в какой-то момент рандом выдал 0, лист тупиковый
		//	else return
		//}
		
	}
	else { //мы на неправильном уровне
		if (root->GetAmountofChildren() != 0) {//но дальше есть еще ветви
			for (int i = 0; i < root->GetAmountofChildren(); i++) {
				nodes = generatebranches1(root->GetChild(i), nodes, level + 1, neededlevel); //идти дальше по дереву
			}
		}
		else {//дальше ветвей нет
			if(totalnodes-nodes<10)
		}
	}
	return nodes - amount;
}
void gentree(int nodes) {
	Node* root = new Node(0);
	int neededlevel = 0;
	int totalnodes = nodes;
	while (nodes > 0) {
		nodes = generatebranches1(root, nodes, 0, neededlevel,totalnodes);
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