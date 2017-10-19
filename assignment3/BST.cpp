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

#include <iterator>     // std::iterator, std::input_iterator_tag

using namespace std;

struct node 
{
	int value;
	struct node* left = nullptr;
	struct node* right = nullptr;
	struct node* parent = nullptr;
};


/* A binary tree node has data, pointer to left child 
   and a pointer to right child */
class BinarySearchTree 
{
public:
	// Constructors/Destructors and assignment here.
	void insert(int value);
	node* insert(int value, node *tnode, node *parent);
	node* max_node(node *tnode);
	node* min_node(node *tnode);
	node* primary_node(node *tnode, bool primary_is_right);
	node* secondary_node(node *tnode, bool primary_is_right);
	void delete_node_choose(node *tnode, bool use_largest, bool is_random);
	void delete_root_largest();
	void delete_root_smallest();
	void delete_root_random();
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
node* BinarySearchTree::insert(int val, node *tnode, node *parent){
    node *temp=tnode;
    if(temp == nullptr){
        temp = new node;
        temp->value = val;
		temp->parent = parent;
    }
    else if(val < temp->value){
        temp->left = insert(val,temp->left, tnode);
    }
    else if(val > temp->value){
        temp->right = insert(val,temp->right, tnode);
    }
    return temp;
}
//function to call insert with root
void BinarySearchTree::insert(int value){
	root = insert(value, root, nullptr);
}

//find node with largest value
node* BinarySearchTree::max_node(node *tnode){
	if (tnode->right == nullptr)
		return tnode;
	return max_node(tnode->right);
}

//find node with smallest value
node* BinarySearchTree::min_node(node *tnode){
	if (tnode->left == nullptr)
		return tnode;
	return max_node(tnode->left);
}

node* BinarySearchTree::primary_node(node *tnode, bool primary_is_right){
	if (primary_is_right)
		return tnode->right;
	return tnode->left;
}

node* BinarySearchTree::secondary_node(node *tnode, bool primary_is_right){
	if (primary_is_right)
		return tnode->left;
	return tnode->right;
}

//delete node by recursvily filling in with primary, or fall back to secondary 
void BinarySearchTree::delete_node_choose(node *tnode, bool use_largest, bool is_random){
	if (is_random)
		use_largest = rand()%2;
	if (tnode == nullptr)
		return;
	if (primary_node(tnode, use_largest) == nullptr){
		if (secondary_node(tnode, use_largest) == nullptr){
			//if both children are nullptr, delete yourself (unless parent is null!)
			if (tnode->parent == nullptr)
				return;
			if (tnode->parent->left == tnode)
				tnode->parent->left = nullptr;
			else 
				tnode->parent->right = nullptr;
			delete(tnode);
		//if primary is null and secondary is not, pull up and recurse
		} else {
			tnode->value = secondary_node(tnode, use_largest)->value;
			delete_node_choose(secondary_node(tnode, use_largest), use_largest, is_random);
			return;
		}
	} else {
		//if neither is null, use primary, pull its value and recurse
		tnode->value = primary_node(tnode, use_largest)->value;
		delete_node_choose(primary_node(tnode, use_largest), use_largest, is_random);
	}
}

//delete node and fill in with largest, recursively
void BinarySearchTree::delete_root_largest(){
	delete_node_choose(root, true, false);
}

//delete node and fill in with smallest, recursively
void BinarySearchTree::delete_root_smallest(){
	delete_node_choose(root, false, false);
}

//delete node and fill in at random, recursively
void BinarySearchTree::delete_root_random(){
	delete_node_choose(root, false, true);
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
	print(tnode->right, depth+1);
	print(tnode->left, depth+1);
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
	}
	
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
		tree.insert(number);
	}
	
	return tree;
}

/*
 *==============================
 * Iterator implementation
 *=============================
 */

vector<int> toVector(node *tnode){
	if (tnode == nullptr){
		vector<int> empty;
		return empty;
	}
	vector<int> temp, left_child, right_child;
	left_child = ::toVector(tnode->left);
	right_child = ::toVector(tnode->right);
	temp = left_child;
	temp.insert(temp.end(), right_child.begin(), right_child.end());
	return temp;
}
	
//borrowed from here: https://gist.github.com/jeetsukumaran/307264
class TreeIterator
{
	public:
		typedef TreeIterator self_type;
		typedef std::vector<int>::iterator iterator;  
		typedef int  value_type;
		typedef int& reference;
		typedef int* pointer;
		typedef std::forward_iterator_tag iterator_category;
		typedef int difference_type;
		TreeIterator(node* ptr) { 
			int_vector = toVector(ptr);
			iter = int_vector.begin();	
			}
		iterator begin() { return int_vector.begin(); }
		iterator end() {return int_vector.end(); }
		self_type operator++() { self_type i = *this; iter++; return i; }
		self_type operator++(int junk) {iter++; return *this; }
		reference operator*() { return *iter; }
		std::vector<int>::iterator operator->() { return iter; }
		bool operator==(const self_type& rhs) { return *iter == *(rhs.iter); }
		bool operator!=(const self_type& rhs) { return *iter != *(rhs.iter); }
	private:
		pointer _ptr;
		vector<int> int_vector;
		std::vector<int>::iterator iter;
};


	
int main(){
	srand(time(NULL));

	/*
	 * ====================================
	 * QUESTION ANSWERING CODE
     *====================================
	 */
	cout << endl;
	cout << "Problem 1: \na)show the result of inserting 3, 1, 4, 6, 9, 2, 5, 7 into an initially empty binary tree" << endl;
	cout << "Note the format the tree is diplayed in, with right child the left child under its parent." << endl;
	BinarySearchTree myTree = BinarySearchTree();
	vector<int> numbers = {3, 1, 4, 6, 9, 2, 5, 7};
	for (int number : numbers)
		myTree.insert(number);
	myTree.print();	
	cout << "b) Now we will delete the root and see what it looks like" << endl;
	myTree.delete_root_largest();
	myTree.print();

	cout << endl;
	cout << "Problem 2: find running time of my effecient algorythms for:" << endl;
	cout << "a) number of nodes. This visits every node once, so it runs on O(n)" << endl;
	cout << "nodes in myTree: " << myTree.countNodes() << endl << endl;
	cout << "b) number of leaves. This also has to visit each node once, so it runs on O(n)" << endl;
	cout << "leaves in myTree: " << myTree.countLeaves() << endl << endl;
	cout << "c) number of full nodes. Any node can have this, so we have to traverse the entire tree, so again O(n)" << endl;
	cout << "full nodes in myTree: " << myTree.countFullNodes() << endl << endl;

	cout << endl;
	cout << "problem 3: algorithm to findKth smallest node. My algorithm, with an unmodified tree, involves checking number of children under each node, and going left to go smaller and right to find a larger elements. Each call takes O(n) and it takes on average O(log(N)) to get to the right element, so it runs on O(N*log(N))." << endl;
	cout << "To find it in O(log(N)), each node needs to keep track of its number of children. Inserting only needs to increment this value for each node it visits, so insertion remains O(log(n)). With this algorythm, we can find Kth element in logarithmic time." << endl;
	cout << "Kth smallest: " << endl;
	cout << myTree.findKth(4) << " is the 4th element, zero-based counting." << endl;
	
	cout << endl;

	cout << "problem 4: iterator implementation";
	TreeIterator myIter = TreeIterator(myTree.root);
	for (int tnode : myIter){
		cout << tnode << ' ';
	}
	cout << endl;
	
	cout << "problem 5" << endl;
	cout << "a) generate n node random binary tree. Runs in O(nlog(n)) time because of individual insertions." << endl;
	BinarySearchTree random_tree = randomKTree(9);
	random_tree.print();
	
	cout << endl;
	cout << "b) generate N-node balanced and skewed tree. Balanced runs on O(nlog(n)) and skewed in O(n)" << endl;
	BinarySearchTree balanced = balancedKTree(9);
	cout << "balanced: " << endl;
	balanced.print();
	cout << "skewed: " << endl;
	BinarySearchTree skewed = skewedKTree(9);
	skewed.print();

	cout << "c) delete and replace by largest, smallest and random. compare results. Random is slightly slower but usually maintains balance." << endl;
	BinarySearchTree a = balancedKTree(100); 
	BinarySearchTree b = balancedKTree(100); 
	BinarySearchTree c = balancedKTree(100); 
	for (int i = 0; i < 90; i++){
		a.delete_root_largest();
		b.delete_root_smallest();
		c.delete_root_random();
	}
	cout << endl << "removed largest:" << endl;
	a.print();
	cout << endl << "removed smallest:" << endl;
	b.print();
	cout << endl << "removed random:" << endl;
	c.print();

	
	
}
