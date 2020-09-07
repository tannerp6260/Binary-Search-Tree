#include <iostream>
#include <fstream>
#include<iomanip>

using namespace std;


struct BstNode {
	int data;
	BstNode* left;
	BstNode* right;
};

BstNode* GetNewNode(int data) {
	BstNode* newNode = new BstNode();
	newNode->data = data;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;
}

BstNode* Insert(BstNode* root, int data);

void delete_tree();

bool search_tree(BstNode* root, int data);

BstNode* Delete(BstNode* root, int data);

//FindMin(root->right)
BstNode* FindMin(BstNode* root);

BstNode* tempNode = NULL;

int main() {
	BstNode* root = NULL;
	char input;
	ifstream inFile;
	int x = 0;
	int search_int = 0;
	int delete_int = 0;

	/*Open input file*/
	inFile.open("input.txt");

	if (!inFile) {
		cout << "Unable to open input.txt";
	}

	//while (inFile >> x) {
		//cout << x;
		//cout << "\n";
	//}

	while (1) {
		cout << "Choose the number of the option to be performed:\n";
		cout << "\t1 Create Tree\n";
		cout << "\t2 Insert Value\n";
		cout << "\t3 Delete Value\n";
		cout << "\t4 Search for Value\n";
		cout << "\t5 Transversal\n";
		cout << "\t6 Delete Tree\n";
		cout << "\t7 Check Balance\n";

		input = getchar();

		switch (input) {
		case '1': {
			cout << "Create Tree\n";
			delete_tree();

			root = NULL;

			while (inFile >> x) {
				cout << x;
				root = Insert(root, x);
			}
			}
				break;
		case '2': 
				break;
		case '3': {
			cout << "Please enter the number you want to delete\n";
			cin >> delete_int;
			Delete(root, delete_int);
		}
				break;
			case '4':{
			cout << "Search tree:\nPlease enter a number to search for:\n";
			cin >> search_int;
			
			if (search_tree(root, search_int)) {
				cout << "The number is in the tree";
			}
			else {
				cout << "The number is NOT in the tree";
			}
			}
				break;
			case '5':
				break;
			case '6':
				break;
			case '7':
				break;
			default:
				cout << "error";
		}
		input = getchar();
		//root = Insert(root, 15);
		//root = Insert(root, 10);
		//root = Insert(root, 20);
	}

	return 0;
}

BstNode* Insert(BstNode* root, int data) {
	if (root == NULL) {
		root = GetNewNode(data);
	}
	else if (data <= root->data) {
		root->left = Insert(root->left, data); 
	}
	else {
		root->right = Insert(root->right, data);
	}

	return root;
}

void delete_tree() {

}

bool search_tree(BstNode* root, int data) {
	if (root == NULL) {
		return 0;
	}

	else if (root->data == data) {
		return 1;
	}

	else if (data <= root->data) {
		return search_tree(root->left, data);
	}

	else {
		return search_tree(root->right, data);
	}
}

BstNode* Delete(BstNode* root, int data) {
	//if there is no tree
	if (root == NULL) {
		return NULL;
	}
	
	//if data is less than current node's data move left
	else if (data < root->data) {
		root->left = Delete(root->left, data);
	}
	//if data is greater than current node's data move right
	else if(data > root->data) {
		root->right = Delete(root->right, data);
	}
	//if data is equal to current node's data delete object
	else {	//search is complete, now we need to handle deletion
		//no child node
		if (root->left == NULL && root->right == NULL) {
			cout << "deleting node no child\n";
			cout << root->data;
			delete root;
			root = NULL;
				
		}
		//one child node
		else if (root->left == NULL) {
			//BstNode* tempNode = new BstNode();
			cout << "deleting node one child\n";
			cout << root->data;
			struct BstNode *temp = root;
			root = root->right;
			delete temp;
		}
		else if (root->right == NULL) {
			cout << "deleting node right child\n";
			cout << root->data;
			struct BstNode* temp = root;
			root = root->left;
			delete temp;
		}
		//two children
		else {
			cout << "deleting node left child\n";
			cout << root->data;
			struct BstNode* temp = FindMin(root->right);
			root->data = temp->data;
			root->right = Delete(root->right, temp->data);
		}

	}

	return root;		//completes tree at previous else-if statement (== NULL)
}

//FindMin(root->right)
BstNode* FindMin(BstNode* root) {
	if(root->left != NULL) {
		root = FindMin(root->left);
	}
	
	return root;

}