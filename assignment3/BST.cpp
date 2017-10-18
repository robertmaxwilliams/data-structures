/*
* 2. (6 points) Write efficient functions that take only a pointer to the root of a binary tree, T, and compute
* (a) the number of nodes in T
* (b) the number of leaves in T
* (c) the number of full nodes in T
* What is the running time of your routines? (Problem 4.31 from the book)
*/

#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream
 
#include <algorithm>
#include <random>

using namespace std;

struct node 
{
	int value;
	struct node* left = nullptr;
	struct node* right = nullptr;
};


/* A binary tree node has data, pointer to left child 
   and a pointer to right child */
class BinarySearchTree 
{
public:
	// Constructors/Destructors and assignment here.
	void insert(int value);
	node* insert(int value, node *tnode);
	void print();
	void print(node *tnode, int depth);
	void print_inorder();
	void print_inorder(node *tnode);
	int deepest_node_depth(node *tnode);
	int deepest_node_depth();
	int shallowest_node_depth(node *tnode);
	int shallowest_node_depth();
	int countNodes();
	int countNodes(node *tnode);
	int countLeaves(node *tnode);
	int countLeaves();
	int countFullNodes(node *tnode);
	int countFullNodes();
	int findKth(int K, node* tnode);
	int findKth(int K);

    node* root = nullptr;
private:
};

//insert function
node* BinarySearchTree::insert(int val, node *tnode){
    node *temp=tnode;
    if(temp == nullptr){
        temp = new node;
        temp->value = val;
    }
    else if(val < temp->value){
        temp->left = insert(val,temp->left);
    }
    else if(val > temp->value){
        temp->right = insert(val,temp->right);
    }
    return temp;
}
//function to call insert with root
void BinarySearchTree::insert(int value){
	root = insert(value, root);
}

//print everything from tnode on
void BinarySearchTree::print(node*tnode, int depth){
	if (tnode == nullptr)
		return;
	for (int i = 0; i < depth-1; i++)
		cout << "| ";
	if (depth > 0)
		cout << "|>";
	cout << tnode->value << endl;
	print(tnode->left, depth+1);
	print(tnode->right, depth+1);
}

//print the whole tree
void BinarySearchTree::print(){
	print(root, 0);
}

//print inorder
void BinarySearchTree::print_inorder(node *tnode){
	if (tnode == nullptr)
		return;
	print_inorder(tnode->left);
	cout << tnode->value << ' ';
	print_inorder(tnode->right);
}

//print inorder helper
void BinarySearchTree::print_inorder(){
	print_inorder(root);
}

//deepest node depth
int BinarySearchTree::deepest_node_depth(node *tnode){
	if (tnode == nullptr)
		return 0;
	return 1 + std::max(deepest_node_depth(tnode->left), deepest_node_depth(tnode->right));
}
int BinarySearchTree::deepest_node_depth(){
	return deepest_node_depth(root);
}

//shallowest node depth
int BinarySearchTree::shallowest_node_depth(node *tnode){
	if (tnode == nullptr)
		return 0;
	return 1 + std::min(shallowest_node_depth(tnode->left), shallowest_node_depth(tnode->right));
}
int BinarySearchTree::shallowest_node_depth(){
	return shallowest_node_depth(root);
}

//count nodes from tnode
int BinarySearchTree::countNodes(node *tnode){
	if (tnode == nullptr)
		return 0;
	return 1 + countNodes(tnode->left) + countNodes(tnode->right);
}

//count node helper
int BinarySearchTree::countNodes(){
	return countNodes(root);
}

//leaf counting
int BinarySearchTree::countLeaves(node *tnode){
	if (tnode == nullptr)
		return 0;
	if (tnode->left == nullptr && tnode->right == nullptr)
		return 1;
	return countLeaves(tnode->left) + countLeaves(tnode->right);
}

//leaf count helper
int BinarySearchTree::countLeaves(){
	return countLeaves(root);
}

//count full nodes (nodes with two children)
int BinarySearchTree::countFullNodes(node *tnode){
	int count = 0;
	if (tnode == nullptr)
		return 0;
	if (tnode->left != nullptr && tnode->right != nullptr)
		count = 1;
	return count + countFullNodes(tnode->left) + countFullNodes(tnode->right);
}

//full node count helper
int BinarySearchTree::countFullNodes(){
	return countFullNodes(root);
}

//find nth smallest elements recursively
//iteratively would be easier but recursion ftw, right?
//note that this is like zero-based indexing an array of inorder elements
int BinarySearchTree::findKth(int K, node* tnode){
		
	int leftChildren = countNodes(tnode->left);
	if (leftChildren == K)
		return tnode->value;
	if (leftChildren > K)
		return findKth(K, tnode->left);
	return findKth(K-leftChildren-1, tnode->right);
}
int BinarySearchTree::findKth(int K){
	return findKth(K, root);
}

//create random binary tree with distinct keys 1-n
BinarySearchTree randomKTree(int k){
	//number contains 1-k in order
	vector<int> numbers;
	for (int i = 1; i <= k; i++){
		numbers.push_back(i);
	}
	//shuffle the vector
	std::default_random_engine engine(std::random_device{}());
	std::shuffle(std::begin(numbers), std::end(numbers), engine);
	
	//insert them all into BST
	BinarySearchTree tree = BinarySearchTree();
	for (int number : numbers){
		tree.insert(number);
	}
	return tree;
}

//combine element by one, like this: [1, 2, 3, 4] , [5, 6, 7, 8, 9] -> [5, 1, 6, 2, 7, 3, 8, 4, 9]
vector<int> leaf(vector<int> a, vector<int> b){
	vector<int> longer;
	vector<int> shorter;
	if (a.size() > b.size()){
		shorter = b; longer = a;
	} else {
		shorter = a; longer = b;
	}
	vector<int> output;
	auto longer_iter = longer.begin();
	auto shorter_iter = shorter.begin();
	while (shorter_iter != shorter.end()){
		output.push_back(*longer_iter);
		output.push_back(*shorter_iter);
		longer_iter++;
		shorter_iter++;
	}
	while (longer_iter != longer.end()){
		output.push_back(*longer_iter);
		longer_iter++;
	}
	return output;
}

//return vector with middle firsts, followed by middles of each side, etc.
vector<int> middle_first(vector<int> ordered_list){
	if (ordered_list.size() <= 1)
		return ordered_list;
	int middle_index = ordered_list.size() / 2;
	vector<int>::const_iterator beginning = ordered_list.begin();
	vector<int>::const_iterator middle = ordered_list.begin() + middle_index;
	vector<int>::const_iterator end = ordered_list.end();
	vector<int> first_half(beginning, middle);
	vector<int> middle_part(middle, middle+1);
	vector<int> last_half(middle+1, end);

	first_half = middle_first(first_half);
	last_half = middle_first(last_half);
	vector<int> leafed_sides = leaf(first_half, last_half);
	middle_part.insert(middle_part.end(), leafed_sides.begin(), leafed_sides.end());

	return middle_part;

}

//create a balanced BST
BinarySearchTree balancedKTree(int k){
	//numbers contains 1-k in order
	vector<int> numbers;
	for (int i = 1; i <= k; i++){
		numbers.push_back(i);
	}
	//re-arrange the array to have middle numbers first, recursively
	numbers = middle_first(numbers);

	//insert the numbers into the tree in this order
	BinarySearchTree tree;
	for (int number : numbers){
		tree.insert(number);
		cout << number << ' ';
	}
	cout << endl;
	
	return tree;
}


//create skewed BST
BinarySearchTree skewedKTree(int k){
	//numbers contains 1-k in order
	vector<int> numbers;
	for (int i = 1; i <= k; i++){
		numbers.push_back(i);
	}

	//insert the numbers into the tree in this order
	BinarySearchTree tree;
	for (int number : numbers){
		cout << number << endl;
		tree.insert(number);
	}
	
	return tree;
}

int main(){
	//BinarySearchTree tree = BinarySearchTree();
	BinarySearchTree tree = randomKTree(9);
	tree.print();
	tree.print_inorder();
	cout << tree.countNodes() << endl;
	cout << tree.countLeaves() << endl;
	cout << tree.countFullNodes() << endl;
	cout << "Balanced tree: " << endl;
	BinarySearchTree tree_balanced = balancedKTree(10);
	tree_balanced.print();

	cout << tree_balanced.deepest_node_depth() << endl;
	cout << tree_balanced.shallowest_node_depth() << endl;

	cout << "Kth smallest: " << endl;
	cout << tree_balanced.findKth(7) << " is the 7th element, zero-based counting" << endl;

	cout << "Skewed Tree: " << endl;
	BinarySearchTree tree_skewed = skewedKTree(10);
	tree_skewed.print();

	cout << tree_skewed.deepest_node_depth() << endl;
	cout << tree_skewed.shallowest_node_depth() << endl;
}
