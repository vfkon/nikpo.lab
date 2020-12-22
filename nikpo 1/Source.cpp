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
	int GetParentValue() {
		if (parent)return parent->GetValue();
		else return 0;
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


int generatebranches1(Node* root, int nodes, std::vector<int>* m_array, int level, int neededlevel, int totalnodes, bool fixed_m = 0, int m = 0, bool print_stats = 0) {
	int oldnodes = nodes;
	int amount = 0;
	if (level == neededlevel) {
		if (fixed_m) {
			amount = m;
		}
		else {
			amount = rand() % 5;
			m_array->push_back(amount);
			if (print_stats)std::cout << amount << "\n";
		}
		for (int i = 0; i < amount; i++) {
			nodes--;
			root->AddNode(root, totalnodes-nodes);
		}
	}
	else { 
		if (root->GetAmountofChildren() != 0) {
			for (int i = 0; i < root->GetAmountofChildren(); i++) {
				nodes = generatebranches1(root->GetChild(i), nodes,m_array, level + 1, neededlevel, totalnodes,fixed_m,m,print_stats); 
			}
		}
		if ((!root->GetParent()) && (nodes == oldnodes)) {
			if (totalnodes - nodes < 10) {
				return nodes + totalnodes; 
			}
			else {
				return -1; 
			}
		}
	}
	return nodes;
}

Node* gentree(int nodes,bool fixed_m=0,int m=0,bool print_stats = 0) {
	if (print_stats)std::cout << "–езультаты генератора случайных чисел:" << std::endl;
	Node* root = new Node(1);
	int neededlevel = 0;
	int totalnodes = nodes;
	std::vector<int> m_array;
	float mexp = 0;
	nodes--;
	while (nodes > 0) {
		nodes = generatebranches1(root, nodes, &m_array, 0, neededlevel,totalnodes,fixed_m,m,print_stats);
		if (nodes >= totalnodes)return nullptr;
		neededlevel++;
	}
	if (print_stats)std::cout << std::endl << std::endl;
	for (int i = 0; i < m_array.size(); i++) {
		mexp += m_array[i];
	}
	mexp /= m_array.size();
	if (mexp < 1.75f || mexp>2.25f) {
		delete root;
		return nullptr;
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

int display_tree_level(Node* root, int needed_level, int current_level, bool print = 0, bool print_leaves=0) {
	int printed = 0;
	if (needed_level != current_level) {
		if (root->GetAmountofChildren()) {
			for (int i = 0; i < root->GetAmountofChildren(); i++) {
				printed+=display_tree_level(root->GetChild(i), needed_level, current_level + 1,print,print_leaves);
			}
			return printed;
		}
		else {
			if (print_leaves)std::cout << root->GetValue() << "-" << root->GetParentValue ()  << "\t";
			return 0;
		}
	}
	else {
		if ((!root->GetAmountofChildren()) && (print_leaves))std::cout << root->GetValue() << "-" << root->GetParentValue() << "\t";
		if(print)std::cout << root->GetValue() << "-" << root->GetParentValue() << "\t";
		return 1;
	}
}
int determine_height(Node* root, int current_height) {
	int height = 0;
	int old_height = 0;
	if (root->GetAmountofChildren()) {
		for (int i = 0; i < root->GetAmountofChildren(); i++) {
			height = determine_height(root->GetChild(i), current_height + 1);
			if (height > old_height)old_height = height;
		}
		return old_height;
	}
	else return current_height;
}


int display_tree(Node* root,bool print=0,bool print_leaves=0) {
	bool tree = true;
	int needed_level=0;
	int printed = 0;
	int old_printed = 0;
	if (print_leaves)std::cout << "¬ис€чие вершины" << ":";
	while (tree) {
		if(print)std::cout << "”–ќ¬≈Ќ№" <<needed_level<<":";
		printed+=display_tree_level(root, needed_level,0,print,print_leaves);
		if (printed == old_printed)tree = false;
		old_printed = printed;
		needed_level++;
		if(print||print_leaves)std::cout << std::endl; 
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
				root = gentree(200,0,0,0);
				if (root == nullptr)i--;
				else {
					leaves.push_back(find_leaves(root));
					totalnodes.push_back(display_tree(root));
					alpha.push_back((float)totalnodes[i] / (float)leaves[i]);
					height.push_back(determine_height(root,0));
					delete root;
					root = nullptr;
				}
			}
			print_res_to_file(tree_amount, alpha, totalnodes, leaves, height);
			system("cls");
			break;
		}
		case 50:
		{
			Node* root = nullptr;
			float alpha;
			int totalnodes;
			int leaves;
			int height;
			srand(time(0));
			root = gentree(200, 1, 4, 0);
			leaves = find_leaves(root);
			totalnodes = display_tree(root, 1);
			display_tree(root, 0, 1);
			alpha = (float)totalnodes / (float)leaves;
			height = determine_height(root, 0);
			delete root;
			getchar();
			system("cls");
			break;
		}
		case 51:
		{
			Node* root = nullptr;
			float alpha;
			int totalnodes;
			int leaves;
			int height;
			srand(time(0));
			root = gentree(200, 0, 0, 1);
			leaves = find_leaves(root);
			totalnodes = display_tree(root, 1);
			display_tree(root, 0,1);
			alpha = (float)totalnodes / (float)leaves;
			height = determine_height(root, 0);
			delete root;
			getchar();
			system("cls");
			break;
		}
		}
	}
}
int main() {
	setlocale(LC_ALL, "");
	menu();
	return 0;
}