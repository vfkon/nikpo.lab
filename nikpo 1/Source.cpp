#include <vector>
#include <cstdlib>
#include <time.h>
class Node {
private:
	Node*parent;
	std::vector<Node*> children;
	int value;
	//bool IsDegenerate;
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
private:
	void DestroyTree(Node* current) {
		std::vector<Node*> ptr;
		for (int i = 0; i < GetAmountofChildren(); i++) {
			delete current->GetChild(i);
			//current->GetChild(i);
		}
		current->children.erase(children.begin(), children.end());
	}
public:
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
int generatebranches1(Node* root, int nodes, int level, int neededlevel, int totalnodes) {
	int oldnodes = nodes;
	int amount = 0;
	if (level == neededlevel) {//мы на правильном уровне
		//srand(time(0));
		amount = rand() % 6;
		for (int i = 0; i < amount; i++) {
			nodes--;
			root->AddNode(root, totalnodes-nodes);//сгенерировать ветви
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
				nodes = generatebranches1(root->GetChild(i), nodes, level + 1, neededlevel, totalnodes); //идти дальше по дереву
			}
		}
		if ((!root->GetParent()) && (nodes == oldnodes)) {
			if (totalnodes - nodes < 10) {
				return nodes + totalnodes; //флаг для уничтожения дерева(см gentree)
			}
			else {
				return -1; // дерево "успешно" сгенерировалось
			}
		}
	}
	return nodes;
}

Node* gentree(int nodes) {
	Node* root = new Node(0);
	int neededlevel = 0;
	int totalnodes = nodes;
	while (nodes > 0) {
		nodes = generatebranches1(root, nodes, 0, neededlevel,totalnodes);
		if (nodes >= totalnodes)goto bad_tree;
		neededlevel++;
	}
	bad_tree:
	return root;
}
int find_leaves(Node* root) {
	int leaves = 0;
	if (root->GetAmountofChildren()) {
		for (int i = 0; i < root->GetAmountofChildren(); i++) {
			leaves += find_leaves(root->GetChild(i));
		}
		return leaves;
	}
	else {
		return 1;
	}
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
	Node* root=nullptr;
	int leaves=0;
	root=gentree(20);
	leaves=find_leaves(root);
	return 0;
}