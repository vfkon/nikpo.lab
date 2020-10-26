#include <vector>
#include <cstdlib>
#include <time.h>
#include<iostream>
#include <locale.h>
#include <fstream>
#include <conio.h>
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
	int GetValue() {
		return value;
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
		value = 1;
	};
	Node(int initval,Node*prnt=nullptr) {
		value = initval;
		parent = prnt;
	};
	~Node() {
		DestroyTree(this);
	};
	
};

//subfunction of gentree, called for each new level. 
//Returns amount of nodes left to generate, or, in case of degenerate tree, a number bigger than the initial number.
int generatebranches1(Node* root, int nodes, int level, int neededlevel, int totalnodes,bool fixed_m=0,int m=0) {
	int oldnodes = nodes;
	int amount = 0;
	if (level == neededlevel) {//correct level
		if (fixed_m) {
			amount = m;
		}
		else {
			amount = rand() % 6;
		}
		for (int i = 0; i < amount; i++) {
			nodes--;
			root->AddNode(root, totalnodes-nodes);//generate nodes
		}
	}
	else { //wrong level
		if (root->GetAmountofChildren() != 0) {//but there are more branches
			for (int i = 0; i < root->GetAmountofChildren(); i++) {
				nodes = generatebranches1(root->GetChild(i), nodes, level + 1, neededlevel, totalnodes); //go to the next branch
			}
		}
		if ((!root->GetParent()) && (nodes == oldnodes)) {
			if (totalnodes - nodes < 10) {
				return nodes + totalnodes; //tree is degenerate
			}
			else {
				return -1; // tree failed to generate 'totalnodes' but is okay for the task
			}
		}
	}
	return nodes;
}
//generates a new random tree. Takes the minimal amount of nodes needed
Node* gentree(int nodes,bool fixed_m=0,int m=0) {
	Node* root = new Node(0);
	int neededlevel = 0;
	int totalnodes = nodes;
	nodes--;
	while (nodes > 0) {
		nodes = generatebranches1(root, nodes, 0, neededlevel,totalnodes,fixed_m,m);
		if (nodes >= totalnodes)return nullptr;
		neededlevel++;
	}
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
//recursive part of display tree function, called for every level in the tree. 
//Returns the amount of printed nodes, which can be used to stop the algorithm.
int display_tree_level(Node* root, int needed_level,int current_level) {
	int printed = 0;
	if (needed_level != current_level) {
		if (root->GetAmountofChildren()) {
			for (int i = 0; i < root->GetAmountofChildren(); i++) {
				printed+=display_tree_level(root->GetChild(i), needed_level, current_level + 1);
			}
			return printed;
		}
		else {
			return 0;
		}
	}
	else {
		//std::cout << root->GetValue() << "-" << current_level << "\t";
		return 1;
	}
}

//prints out the tree level by level, returns the amount of nodes printed
int display_tree(Node* root) {
	bool tree = true;
	int needed_level=0;
	int printed = 0;
	int old_printed = 0;
	while (tree) {
		//std::cout << "”–ќ¬≈Ќ№" <<needed_level<<":";
		printed+=display_tree_level(root, needed_level,0);
		if (printed == old_printed)tree = false;
		old_printed = printed;
		needed_level++;
		//std::cout << std::endl; 
	}
	return printed;
}
void print_res_to_file(size_t size,std::vector<float>&alpha, std::vector<int>&totalnodes,std::vector<int>&leaves,std::vector<int>&treeheights) {
	std::ofstream fout;
	fout.open("table");
	fout << "alpha\ttotal\tleaves\theight" << std::endl;
	for (size_t i = 0; i < size; i++) {
		fout<< alpha[i]<<"\t"<< totalnodes[i] << "\t" << leaves[i] << "\t" << treeheights[i] << std::endl;

	}
	fout.close();
}
float calc_MX(std::vector<float> alpha) {

	return 0;
}
void printmenu() {
	std::cout << "NUM1-сгенерировать случайные деревь€ и записать в файл результаты" << std::endl;
	std::cout << "NUM2 - сгенерировать детерминированное дерево, вывести на печать характеристики и записать в файл" << std::endl;
	std::cout << "NUM3 - сгенерировать одно случайное дерево, вывести на печать" << std::endl;
	std::cout << "ESC - выйти" << std::endl;
}
void menu() {
	int key = 0;
	bool cycle = 1;
	while (cycle) {
		printmenu();
		key = _getch();
		if (key == 224)key = _getch();
		switch (key) {
		case 27:
			cycle = 0;
			break;
		case 49:
		{
			int tree_amount;
			std::cout << "¬ведите количество деревьев:";
			std::cin >> tree_amount;
			Node* root = nullptr;
			std::vector<float> alpha;
			std::vector<int> totalnodes;
			std::vector<int> leaves;
			std::vector<int> height;
			srand(time(0));
			for (int i = 0; i < tree_amount; i++) {
				root = gentree(400);
				if (root == nullptr)i--;
				else {
					leaves.push_back(find_leaves(root));
					totalnodes.push_back(display_tree(root));
					alpha.push_back((float)totalnodes[i] / (float)leaves[i]);
					height.push_back(0);
					delete root;
					root = nullptr;
				}
			}
			print_res_to_file(tree_amount, alpha, totalnodes, leaves, height);
			system("cls");
			break;
		}
		case 46:

			break;
		}
	}
}
int main() {
	setlocale(LC_ALL, "");
	menu();
	//float MX=calc_MX(alpha);
	return 0;
}