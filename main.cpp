#include <iostream>
#include <fstream>
#include<iomanip>
#include<algorithm>

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
int search_tree(BstNode* root, int data);
BstNode* Delete(BstNode* root, int data);
BstNode* FindMin(BstNode* root);
BstNode* PreOrder(BstNode* root);
BstNode* PostOrder(BstNode* root);
BstNode* tempNode = NULL;
BstNode* InOrder(BstNode* root);
void delete_tree(BstNode* root); 
int height(BstNode* root);
int balance(BstNode* root);
BstNode* RightRight_Rotate(BstNode* root);
BstNode* RightLeft_Rotate(BstNode* root);
BstNode* LeftLeft_Rotate(BstNode* root);
BstNode* LeftRight_Rotate(BstNode* root);

BstNode* balanceTree(BstNode* root);

int main() {
	BstNode* root = NULL;
	char input;
	int search_int = 0;
	int delete_int = 0;
	int traversal_int = 0;
	int insertion_int = 0;



	while (1) {
		cout << "\n------------------------------------------------------------------\n";
		cout << "Choose the number of the option to be performed:\n";
		cout << "\t1 Create Tree\n";
		cout << "\t2 Insert data\n";
		cout << "\t3 Delete data\n";
		cout << "\t4 Search for data\n";
		cout << "\t5 Transversal\n";
		cout << "\t6 Delete Tree\n";
		cout << "\t7 Check Balance\n";
		cout << "------------------------------------------------------------------\n";
		input = getchar();

		switch (input) {
		case '1': {

			/*Open input file*/
			ifstream inFile;
			int x = 0;

			inFile.open("input.txt");

			if (!inFile) {
				cout << "Unable to open input.txt";
			}

			cout << "1\n";
			delete_tree();
			cout << "2";

			cout << "\nCreate Tree: ";

			while (inFile >> x) {
				cout << x;
				cout << " ";
				root = Insert(root, x);
			}

			root = balanceTree(root);

			}
				break;
		case '2': {
			cout << "\nPlease enter the number you would like to add to the tree:\n";
			cin >> insertion_int;
			
			root = Insert(root, insertion_int);
			root = balanceTree(root);
		}
				break;
		case '3': {
			if (root == NULL) {
				cout << "\n\tNode cannot be deleted. Empty Tree!\n";
			}
			else {
				cout << "\nPlease enter the number you want to delete\n";
				cin >> delete_int;

				if (search_tree(root, delete_int) == -1) {
					cout << "\nNode cannot be found. Deletion cannot be performed\n";
				}
				else {
					Delete(root, delete_int);
					cout << "\nNumber Deleted.";
				}
			}
			break;
		case '4': {
			cout << "\nPlease enter a number to search for:\n";
			cin >> search_int;

			int search_tree_int = search_tree(root, search_int);

			if (search_tree_int != -1) {
				cout << "\nThe number is in the tree at height: ";
				cout << search_tree_int;
				cout << "\n";
			}
			else {
				cout << "\n\tThe number is NOT in the tree\n";
			}
		}
		}
				break;
		case '5': {
			if (root == NULL) {
				cout << "\n\tThere is no tree to traverse!\n";
			}
			else {
				cout << "\nPlease enter the corresponding number to select traversal type:\n";
				cout << "1 Pre-Order\n";
				cout << "2 Post-Order\n";
				cout << "3 In-Order\n\n";

				cin >> traversal_int;

				if (traversal_int == 1) {
					cout << "\n\n";
					PreOrder(root);
				}
				else if (traversal_int == 2) {
					cout << "\n\n";
					PostOrder(root);
				}
				else if (traversal_int == 3) {
					cout << "\n\n";
					InOrder(root);
				}
				else {
					cout << "\n\tError, \n\tPlease enter a valid number (1, 2, or 3)\n";
				}
			}
		}
				break;
		case '6': {
			cout << "\nDelete Tree: Tree Deleted\n";
			delete_tree(root);
			root = NULL;
			}
				break;
		case '7': {
			cout << "\n";
			cout << "The balance of the tree is: ";
			cout << balance(root);
			cout << "\n";
			}
				break;
			default:
				cout << "\n\terror\n";
		}
		input = getchar();
	}

	return 0;
}

BstNode* Insert(BstNode* root, int data) {
	if (root == NULL) {
		root = GetNewNode(data);
	}
	else if (data < root->data) {
		root->left = Insert(root->left, data); 
	}
	else if (data > root->data) {
		root->right = Insert(root->right, data);
	}
	else {
		cout << "\n\tThe selected number already exists!\n";
	}

	return root;
}

void delete_tree() {

}

int search_tree(BstNode* root, int data) {
	if (root == NULL) {
		return -1;
	}

	else if (root->data == data) {
		return height(root);
	}

	else if (data <= root->data) {
		return search_tree(root->left, data);
	}

	else {
		return search_tree(root->right, data);
	}
}

BstNode* Delete(BstNode* root, int data) {
	if (root == NULL) {
		return NULL;
	}
	
	else if (data < root->data) {
		root->left = Delete(root->left, data);
	}
	else if(data > root->data) {
		root->right = Delete(root->right, data);
	}
	else {	
		if (root->left == NULL && root->right == NULL) {
			delete root;
			root = NULL;
		}
		else if (root->left == NULL) {
			struct BstNode *temp = root;
			root = root->right;
			delete temp;
		}
		else if (root->right == NULL) {
			struct BstNode* temp = root;
			root = root->left;
			delete temp;
		}
		else {
			struct BstNode* temp = FindMin(root->right);
			root->data = temp->data;
			root->right = Delete(root->right, temp->data);
		}
	}

	return root;		//completes tree at previous else-if statement (== NULL)
}

BstNode* FindMin(BstNode* root) {
	if(root->left != NULL) {
		root = FindMin(root->left);
	}
	
	return root;
}

BstNode* PreOrder(BstNode* root) {
	if (root != NULL) {
		cout << root->data;
		cout << "\n";
		PreOrder(root->left);
		PreOrder(root->right);
	}
	return root;
}

BstNode* PostOrder(BstNode* root) {
	if (root != NULL) {
		PostOrder(root->left);
		PostOrder(root->right);
		cout << root->data;
		cout << "\n";
	}
		return root;
}

BstNode* InOrder(BstNode* root) {
	if (root != NULL) {
		InOrder(root->left);
		cout << root->data;
		cout << "\n";
		InOrder(root->right);
	}
	return root;
}

void delete_tree(BstNode* root) {
	if (root) {					
		if (root->left) {
			delete_tree(root->left);		
		}
		if (root->right) {
			delete_tree(root->right);		
		}

		delete root;
	}
}

int balance(BstNode* root) {
	int left_height = height(root->left);
	int right_height = height(root->right);
	int balance_factor = left_height - right_height;
	return balance_factor;
}

int height(BstNode* root) {
	int height_int = 0;
	if (root != NULL) {
		int right_height = height(root->right);
		int left_height = height(root->left);
		int max_height = 0;
		if (left_height > right_height) {
			max_height = left_height;
		}
		else {
			max_height = right_height;
		}
		height_int = max_height + 1;
	}
	return height_int;
}

BstNode* balanceTree(BstNode* root) {
	int bal_factor = balance(root);
	if (bal_factor > 1) {
		if (balance(root->left) > 0)
			root = LeftLeft_Rotate(root);
		else
			root = LeftRight_Rotate(root);
	}
	else if (bal_factor < -1) {
		if (balance(root->right) > 0)
			root = RightLeft_Rotate(root);
		else
			root = RightRight_Rotate(root);
	}
	return root;
}

BstNode* RightRight_Rotate(BstNode* previousNode) {
	BstNode* currentNode;
	currentNode = previousNode->right;
	previousNode->right = currentNode->left;
	currentNode->left = previousNode;
	return currentNode;
}
BstNode* LeftLeft_Rotate(BstNode* previousNode) {
	BstNode* currentNode;
	currentNode = previousNode->left;
	previousNode->left = currentNode->right;
	currentNode->right = previousNode;
	return currentNode;
}
BstNode* LeftRight_Rotate(BstNode* previousNode) {
	BstNode* currentNode;
	currentNode = previousNode->left;
	previousNode->left = RightRight_Rotate(currentNode);
	return LeftLeft_Rotate(previousNode);
}
BstNode* RightLeft_Rotate(BstNode* previousNode) {
	BstNode* currentNode;
	currentNode = previousNode->right;
	previousNode->right = LeftLeft_Rotate(currentNode);
	return RightRight_Rotate(previousNode);
}