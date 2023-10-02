1) Ceil from BST
Ceil mhnje just motha kivva equal interger.
Mhnje closest integrer gretaer than or equal to given number.

int findCeil(BinaryTreeNode<int> *root, int x){
    // Find the smallest element in the Binary Search Tree (BST) that is greater than or equal to x

    // Initialize the answer variable with -1
    int ans = -1;

    // Traverse through the BST until the root becomes NULL
    while(root!=NULL){
        
        // If the current node's data is equal to x, return x as the ceil
        if(root->data == x)
            return x;

        // If the current node's data is less than x, update the answer with the current node's data and move to the left subtree
        // We are storing ans here, bcoz we got some value greater than x, and now we are further
        // reducing it by searching on left of root
        if(root->data > x){
            ans = root->data;
            root=root->left;
        }

        // If x is greater than the current node's data, move to the right subtree
        else{
            root = root->right;
        }
    }

    // Return the answer as the ceil of x in the BST
    return ans;
}

Time Complexity: O(logN) We are traversing reducing half part always
Space Complexity: O(1)

--------------------------------------------------------------------------------------------------------------------------
2) Floor from BST

Floor mhnje just chota kivva equal integer.
Mhnje greatest (largest pan chota given integer pekshya) integer smaller than or 
equal to given number.

int Floor(BinaryTreeNode<int> *root, int x)
{
    // Find the largest element in the Binary Search Tree (BST) that is less than or equal to x

    // Initialize the answer variable with -1
    int ans = -1;

    // Traverse through the BST until the root becomes NULL
    while(root != NULL){
        // If the current node's data is equal to x, return x as the floor
        if(root->data == x)
            return x;

        // If the current node's data is less than x, update the answer with the current node's data and move to the right subtree
        // We are storing ans here, bcoz we got some value less than x, and now we are further
        // increasing it by searching on right of root		
        if(root->data < x){
            ans = root->data;
            root = root->right;
        }
        // If the current node's data is greater than x, move to the left subtree
        else{
            root = root->left;
        }
    }

    // Return the answer as the floor of x in the BST
    return ans;
}

Time Complexity: O(logN) We are traversing reducing half part always
Space Complexity: O(1)

--------------------------------------------------------------------------------------------------------------------------
3) Insert into a Binary Search Tree.

a) The node will attach the given node always to the end of tree.
b) If given value is less than current node, we should look on left:
          a) if the left of current node is NULL
               we create the node with given value and attach it to left of current node.
         b) Else, left is not NULL, we simply move to left, and this left will decide further
             where to attach given value node.
c) If given value is greater than current node, we should look on right:
          a) if the right of current node is NULL
               we create the node with given value and attach it to right of current node.
         b) Else, right is not NULL, we simply move to right, and this right will decide 
              further where to attach given value node.
d) By this, 2 and 3 repeats until e reach the end, and get attached the node.



TreeNode* insertIntoBST(TreeNode* root, int val) {
    // Insert a new node with the given value into a Binary Search Tree (BST)

    // If the root is NULL, create a new node with the given value and assign it as the root
    if (root == NULL) {
        TreeNode* node = new TreeNode(val);
        root = node;
        return root;
    }

    // Create a temporary pointer and initialize it with the root
    TreeNode* temp = root;

    // Traverse the BST to find the appropriate position to insert the new node
    while (1) {
        // If the value is less than the current node's value, move to the left subtree
        if (val < temp->val) {
            // If the left child is NULL, create a new node with the given value and assign it as the left child
            if (temp->left == NULL) {
                temp->left = new TreeNode(val);
                break;
            }
            // If the left child is not NULL, move to the left child
            else {
                temp = temp->left;
            }
        }
        // If the value is greater than or equal to the current node's value, move to the right subtree
        else {
            // If the right child is NULL, create a new node with the given value and assign it as the right child
            if (temp->right == NULL) {
                TreeNode* node = new TreeNode(val);
                temp->right = node;
                break;
            }
            // If the right child is not NULL, move to the right child
            else {
                temp = temp->right;
            }
        }
    }

    // Return the root of the modified BST
    return root;
}

Time Complexity: O(logN) We are traversing reducing half part always
Space Complexity: O(1)

--------------------------------------------------------------------------------------------------------------------------
4) Delete Node in a BST

1. If the root is NULL, the tree is empty, so return NULL.
2. Compare the key with the value of the current node to determine the direction of 
    traversal:
   - If the key is less than the current node's value, recursively delete the key from 
      the left subtree.
   - If the key is greater than the current node's value, recursively delete the key from 
      the right subtree.
   - If the key is equal to the current node's value, we have found the node to be 
      deleted.
3. Handle different cases based on the existence of children:
   - Case 1: If the node has no children, return NULL to remove it from the tree.
   - Case 2: If the node has no left child, return the right child to replace the deleted 
      node.
   - Case 3: If the node has no right child, return the left child to replace the deleted 
      node.
   - Case 4: If the node has both left and right children, find the maximum value in 
      the left subtree (predecessor), attach the right subtree to the rightmost node of 
      the modified left subtree, and return the left child as the new root. We are 
      returning the left node as an new root node, by deleting a current root node
      before that we have attached the right subtree of node to be deleted to the
      rightmost extreme of left subtree to maintain the BST property
4. Return the root of the modified BST after deleting the node.

By following these steps, the algorithm ensures the proper deletion of a node while 
maintaining the BST structure.

TreeNode* deleteNode(TreeNode* root, int key) {
    // Delete a node with the given key from a Binary Search Tree (BST)

    // If the root is NULL, return NULL
    if (root == NULL) {
        return NULL;
    }

    // If the key is less than the root's value, recursively delete the key from the left subtree
    // and attach the updated subtree to the left of root.
    if (key < root->val) {
        root->left = deleteNode(root->left, key);
    }

    // If the key is greater than the root's value, recursively delete the key from the right subtree
    // and attach the updated subtree to the right of root.
    else if (key > root->val) {
        root->right = deleteNode(root->right, key);
    }

    // If the key is equal to the root's value
    else {
        // Case 1: If the root has no children, return NULL (LEAF NODE)
        if (root->left == NULL && root->right == NULL) {
            return NULL;
        }

        // Case 2: If the root has no left child, return the right child (HAS ONLY ONE CHILDREN)
        if (root->left == NULL) {
            return root->right;
        }

        // Case 3: If the root has no right child, return the left child (HAS ONLY ONE CHILDREN)
        if (root->right == NULL) {
            return root->left;
        }

        // Case 4: If the root has both left and right children (HAS BOTH THE CHILDS)
        else {
            // Find the maximum value in the left subtree
            TreeNode* temp = root->left;
            while (temp->right != NULL) {
                temp = temp->right;
            }

            // Attach the right subtree of the root to the rightmost node of the left subtree
            temp->right = root->right;

            // Return the left child as the new root
            return root->left;
        }
    }

    // Return the root of the modified BST
    return root;
}


Time Complexity: O(logN) We are traversing reducing half part always
Space Complexity: O(logN) recursion stack space

--------------------------------------------------------------------------------------------------------------------------
5) Kth smallest element in Binary Search Tree


void inorder(TreeNode* root, int &k, int &ans) {
    // Perform an inorder traversal of the Binary Search Tree (BST) to find the kth smallest element

    // If the root is NULL, return
    if (root == NULL) {
        return;
    }

    // Recursively traverse the left subtree
    inorder(root->left, k, ans);

    // Decrement the value of k
    k--;

    // If k becomes 0, the current node is the kth smallest element
    if (k == 0) {
        ans = root->val;
        return;
    }

    // Recursively traverse the right subtree
    inorder(root->right, k, ans);
}

int kthSmallest(TreeNode* root, int k) {
    // Find the kth smallest element in the Binary Search Tree (BST)

    int ans;
    // Perform inorder traversal to find the kth smallest element
    inorder(root, k, ans);

    // Return the kth smallest element
    return ans;
}

Time Complexity: O(min(K,N))

Space Complexity: O(min(K,N))

--------------------------------------------------------------------------------------------------------------------------
6) Kth largest element in Binary Search Tree

**Just do ulta inorder!!**

*When we apply reverse inorder, we will get the traversal in non-increasing
fashion i.e. decreasing elements, first element is the largest among the BST.


void reverseInorder(Node* root, int &k, int &ans) {
    // Perform a reverse inorder traversal of the Binary Search Tree (BST) to find the kth largest element

    // If the root is NULL, return
    if (root == NULL) {
        return;
    }

    // Recursively traverse the right subtree
    reverseInorder(root->right, k, ans);

    // Decrement the value of k
    k--;

    // If k becomes 0, the current node is the kth largest element
    if (k == 0) {
        ans = root->data;
        return;
    }

    // Recursively traverse the left subtree
    reverseInorder(root->left, k, ans);
}

int kthLargest(Node* root, int k) {
    // Find the kth largest element in the Binary Search Tree (BST)

    int ans;
    // Perform reverse inorder traversal to find the kth largest element
    reverseInorder(root, k, ans);

    // Return the kth largest element
    return ans;
}

Time Complexity: O(min(K,N))

Space Complexity: O(min(K,N))

--------------------------------------------------------------------------------------------------------------------------
7) Check if a tree is a BST or BT

a) Before visiting every node(we are traversing in preorder fashion), a range is assigned to it. The lower bound and upper 
bound of the range is passed as parameters to the function. 
b) While visiting the node observe if the node’s key lies between the upper and 
lower bound.
c) If not, return a false without any further traversal.
d) If yes, make recursion calls once for the left subtree and right subtree of the node.
by passing appropriate range:

The left subtree should have a maximum value of the current node's value 
(as all values in the left subtree must be smaller), while the right subtree should 
have a minimum value of the current node's value (as all values in the right subtree 
must be larger).
Once we reach null, return true.

bool check(TreeNode* root, long long minVal, long long maxVal) {
    // Helper function to check if a binary tree is a valid binary search tree (BST)

    // If the root is NULL, it is considered a valid BST
    if (root == NULL) {
        return true;
    }

    int nodeValue = root->val;

    // Check if the value of the current node violates the BST property
    if (nodeValue <= minVal || nodeValue >= maxVal) {
        return false;
    }

    // Recursively check the left and right subtrees with updated min and max values

    // The left subtree should have a maximum value of the current node's value 
    // (as all values in the left subtree must be smaller), 
    bool left = check(root->left, minVal, nodeValue);

    // the right subtree should have a minimum value of the current node's value 
    // (as all values in the right subtree must be larger).
    bool right = check(root->right, nodeValue, maxVal);

    // Return true if both the left and right subtrees are valid BSTs
    return left && right;
}

bool isValidBST(TreeNode* root) {
    // Check if a binary tree is a valid binary search tree (BST)

    // Call the check function with the initial minimum and maximum values
    return check(root, LONG_MIN, LONG_MAX);
}

Time Complexity: O(N) for traversing N nodes.
Space Complexity: O(1) if we ignore the auxiliary stack space.

--------------------------------------------------------------------------------------------------------------------------
8) Lowest Common Ancestor of a Binary Search Tree

1)The first node which lies in between the two numbers p and q is the LCA of nodes.

2) Traverse the BST, if node's value is greater than both p and q then our LCA lies
in the left side of the node, if it is smaller than both p and q, then LCA lies on the
right side. Otherwise, the root is the LCA i.e. p and q lies on either side of root.
i.e. p will be on left and q will be on right. So root will be the LCA

A) While loop (Iterative)

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // Find the lowest common ancestor (LCA) of two nodes in a binary tree

    while (root != NULL) {
        int nodeValue = root->val;

        // If both nodes are less than the current node's value,
        // the LCA must be in the left subtree
        if (p->val < nodeValue && q->val < nodeValue) {
            root = root->left;
        }

        // If both nodes are greater than the current node's value,
        // the LCA must be in the right subtree
        else if (p->val > nodeValue && q->val > nodeValue) {
            root = root->right;
        }

        // If the nodes are on different sides of the current node's value,
        // or one of the nodes matches the current node,
        // the current node is the lowest common ancestor
        else {
            return root;
        }
    }

    // If the loop ends without finding the LCA, return NULL
    return NULL;
}

Time Complexity: O(logN) for traversing N nodes.
Space Complexity: O(1)

B) Recursive:

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // Find the lowest common ancestor (LCA) of two nodes in a binary tree

    // If the root is NULL, return NULL
    if (root == NULL) {
        return NULL;
    }

    int nodeValue = root->val;

    // If both nodes are less than the current node's value,
    // the LCA must be in the left subtree
    // We are directly returning from here, because we don't want to call right subtree
    if (p->val < nodeValue && q->val < nodeValue) {
        return lowestCommonAncestor(root->left, p, q);
    }

    // If both nodes are greater than the current node's value,
    // the LCA must be in the right subtree
    // We are directly returning from here, because we don't want to go down
    if (p->val > nodeValue && q->val > nodeValue) {
        return lowestCommonAncestor(root->right, p, q);
    }

    // If the nodes are on different sides of the current node's value,
    // the current node is the lowest common ancestor
    return root;
}

Time Complexity: O(logN) for traversing N nodes.
Space Complexity: O(1) if we ignore the auxiliary stack space.

--------------------------------------------------------------------------------------------------------------------------
9) Construct Binary Search Tree from Preorder Traversal

We use only upper bound here!
While going left, send the upper bound as node's value
While going to right, transfer the upper bound as it is.


TreeNode* construct(int &i, int maxVal, vector<int> &preorder) {
    // Helper function to construct a binary search tree (BST) from a preorder traversal

    // If all elements of the preorder traversal have been processed
    // or the current element is greater than the maximum allowed value,
    // return NULL (no node to be constructed)
    if (i == preorder.size() || preorder[i] > maxVal) {
        return NULL;
    }

    // Create a new node with the current element in the preorder traversal
    TreeNode* node = new TreeNode(preorder[i++]);

    // Recursively construct the left subtree
    // we update the maxVal parameter as node->val. This is because in a binary search tree (BST), all nodes in 
    // the left subtree of a particular node must have values smaller than that node's value. By setting maxVal 
    // to node->val, we ensure that the left subtree's nodes are constrained by this condition.
    node->left = construct(i, node->val, preorder);

    // Recursively construct the right subtree
    // when constructing the right subtree, we pass the original maxVal parameter without any modifications. 
    // This is because all nodes in the right subtree of a particular node must have values greater than that 
    // node's value. By keeping maxVal unchanged, we maintain the constraint for the right subtree.
    node->right = construct(i, maxVal, preorder);

    // Return the constructed node
    return node;
}

TreeNode* bstFromPreorder(vector<int>& preorder) {
    // Construct a binary search tree (BST) from a given preorder traversal

    int i = 0; // Index to track the current element in the preorder traversal

    // Call the construct function to recursively build the BST
    // with an initial maximum value of INT_MAX
    return construct(i, INT_MAX, preorder);
}

Time Complexity: O(N) for traversing N nodes.
Space Complexity: O(1) if we ignore the auxiliary stack space.
--------------------------------------------------------------------------------------------------------------------------
10) Predecessor And Successor In BST

pair<int, int> predecessorSuccessor(BinaryTreeNode<int>* root, int key) {
    // Find the predecessor and successor of a given key in a binary search tree (BST)

    int p = -1; // Predecessor initialized to -1
    int s = -1; // Successor initialized to -1
    BinaryTreeNode<int>* temp = root; // Temporary node pointer initialized to the root

    // Finding the predecessor
    while (temp != NULL) {
        // If nodes value is less than key, store it and move to right to get larger value.
        if (temp->data < key) {
            p = temp->data; // Update the predecessor as we move to the right subtree
            temp = temp->right; // Move to the right child
        }
        else {
            // p = temp->data;
            temp = temp->left; // Move to the left child
        }
    }

    temp = root; // Reset the temporary node pointer to the root

    // Finding the successor
    while (temp != NULL) {
        // If nodes value is greater than key, store it and move to left to get smaller value.
        if (temp->data > key) {
            s = temp->data; // Update the successor as we move to the left subtree
            temp = temp->left; // Move to the left child
        }
        else {
            temp = temp->right; // Move to the right child
        }
    }
    return { p, s }; // Return the pair of predecessor and successor
}
Time Complexity: O(logN)
Space Complexity: O(1)
--------------------------------------------------------------------------------------------------------------------------
11) Binary Search Tree Iterator

The given code implements an iterator for a binary search tree (BST) that allows for efficient traversal 
of the tree in an inorder fashion. Here's the intuition behind the code:

The `BSTIterator` class uses a stack to maintain the order of visiting nodes during the inorder traversal. 
The constructor `BSTIterator(TreeNode* root)` initializes the iterator by pushing all the leftmost nodes 
of the BST onto the stack. This ensures that the smallest element in the BST is at the top of the stack initially.

The `next` function is used to retrieve the next element in the inorder traversal. It pops the top node 
from the stack and returns its value. After popping a node, it checks if there are any nodes in the right 
subtree of the popped node. If there are, it pushes all the leftmost nodes of the right subtree onto the stack. 
This ensures that the next element retrieved by `next` will be the next node in the inorder sequence.

The `hasNext` function checks if there are any remaining elements to be traversed in the BST. It simply checks 
if the stack is empty or not. If the stack is not empty, it means there are more nodes to be visited, so it 
returns `true`. Otherwise, it returns `false`.

Overall, this iterator implementation allows for efficiently traversing a BST in an inorder fashion without 
explicitly constructing the entire inorder traversal upfront. It utilizes the stack to keep track of the nodes 
and ensures that each node is visited in the correct order according to the inorder traversal.

class BSTIterator {
public:
    stack<TreeNode*> s;  // Stack to store the nodes during inorder traversal

    void pushLeft(TreeNode* root, stack<TreeNode*>& s) {
        // Helper function to push the leftmost nodes to the stack
        while (root != NULL) {
            s.push(root);
            root = root->left;
        }
    }

    BSTIterator(TreeNode* root) {
        // Constructor to initialize the BSTIterator with the root node
        pushLeft(root, s);  // Push the leftmost nodes to the stack
    }

    int next() {
        // Function to get the next element in the inorder traversal
        TreeNode* topNode = s.top();  // Get the topmost node from the stack
        s.pop();  // Pop the node from the stack
        pushLeft(topNode->right, s);  // Push the leftmost nodes of the right subtree to the stack
        return topNode->val;  // Return the value of the topmost node
    }

    bool hasNext() {
        // Function to check if there is any remaining element in the inorder traversal
        return !s.empty();  // Return true if the stack is not empty, indicating there are more elements
    }
};

Time Complexity: O(1) Overall, for each of the operation we take O(1) time
Space Complexity: O(1)

--------------------------------------------------------------------------------------------------------------------------
12) Find a pair with given target in BST

Approach1:
Get  the inorder traversal and apply two sum logic on inorder array.
T.C -> O(N)
S.C-> O(N) to store inorder.

Approach 2: Space of O(H)
Using BST Iterator!!

1) We will use the logic of two pointers only.

2) For left/start/i we will use BST Iterator. (Noraml BST iterator)

3) For right/end/j we will use Reverse BST iterator, to traverse inorder array 
in reverse fashion. Here we will apply reverse inorder to get inorder in decreasing 
fashion. First element in BST Iterator will be maximum one and so on goes on 
decreasing. At one time, stack will be storing at max elements equal to height of 
BST. (Reverse BST Iterator).

4) We will create two objects, one for Normal BST iterator and another for reverse 
BST iterator. Normal will give us the pointer to traverse from smaller element to
larger element and reverse iterator will give us pointer to traverse from larger
element to smaller element.

5) next() function will be use to increment both pointers.

The given code aims to find whether a pair of nodes exists in a binary search tree (BST) 
that sums up to a given value, `k`. Here's the intuition behind the code:

1. The `bstIterator` class is used to traverse the BST in either normal or reverse order. 
It maintains a stack to store the nodes during traversal.

2. The constructor of `bstIterator` initializes the iterator by pushing all the nodes of the 
BST onto the stack in the specified order (normal or reverse).

3. The `next` function retrieves the next element in the traversal. It pops the top node from 
the stack and pushes the corresponding nodes from the subtree onto the stack, ensuring the next 
element will be the correct one in the specified order.

4. The `Solution` class utilizes two instances of `bstIterator` to find a pair of nodes with a
sum of `k` in the BST.

5. It initializes one iterator for normal traversal and another for reverse traversal.

6. The `isPairPresent` function retrieves the next elements from both iterators and checks if 
their sum equals `k`. If the sum is less than `k`, it moves to the next element from the normal iterator. 
If the sum is greater than `k`, it moves to the next element from the reverse iterator.

7. If a pair of nodes with the sum `k` is found, it returns `true`. Otherwise, it returns `false`.

The intuition behind this approach is that by using two iterators, one traversing the BST in normal 
order and the other in reverse order, we can efficiently find the pair of nodes with the desired sum `k`. 
By comparing the sums of the current elements from both iterators, we can determine whether to move to 
the next element from the normal iterator or the reverse iterator, narrowing down the search space until 
a pair with the sum `k` is found or all possibilities are exhausted.


class bstIterator {
    stack<Node*> st;  // Stack to store nodes during traversal
    int reverse = 1;  // Indicates the direction of traversal: 1 for reverse, 0 for normal

private:
    void pushAll(Node* root) {
        // Helper function to push nodes to the stack in the specified direction
        while (root) {
            st.push(root);
            if (reverse)
                root = root->right;  // Traverse right subtree if reverse is true
            else
                root = root->left;  // Traverse left subtree if reverse is false
        }
    }

public:
    bstIterator(Node* root, int isReverse) {
        // Constructor to initialize the iterator with the root node and direction
        reverse = isReverse;
        pushAll(root);  // Push nodes to the stack based on the specified direction
    }

    int next() {
        // Function to retrieve the next element in the traversal
        Node* node = st.top();  // Get the top node from the stack
        st.pop();  // Pop the node from the stack

        if (!reverse)
            pushAll(node->right);  // Push nodes from the right subtree if reverse is false
        else
            pushAll(node->left);  // Push nodes from the left subtree if reverse is true

        return node->data;  // Return the data of the popped node
    }
};

class Solution {
public:
    int isPairPresent(struct Node* root, int k) {
        if (!root)
            return false;

        bstIterator next(root, false);  // Create an iterator for normal traversal
        bstIterator before(root, true);  // Create an iterator for reverse traversal

        int i = next.next();  // Get the next element from the normal iterator
        int j = before.next();  // Get the next element from the reverse iterator

        while (i < j) {
            if (i + j == k)
                return true;  // Found a pair with the sum k
            if (i + j < k)
                i = next.next();  // Move to the next element from the normal iterator
            else
                j = before.next();  // Move to the next element from the reverse iterator
        }

        return false;  // No pair found with the sum k
    }
};


Time Complexity: O(N) 
Space Complexity: O(2*H) Two BST Iterators.

--------------------------------------------------------------------------------------------------------------------------
13) Recover Binary Search Tree (Two values are swapped)

Tuze notes vaach, kalel!!

The given code is used to recover a binary search tree (BST) that has two nodes swapped mistakenly. Here's the intuition behind the code:

a) The `inorder` function performs an inorder traversal of the BST, which visits the nodes in ascending order.

b) During the inorder traversal, we keep track of the previously visited node (`prev`) and compare its value with the current node's value.

c) If the value of `prev` is greater than the current node's value, it indicates that we have found a misplaced node.

d) The first misplaced node encountered is assigned to `first`, and the subsequent node is assigned to `middle`. 
If another misplaced node is found, it is assigned to `last`.

e) After the inorder traversal, we have identified the misplaced nodes, namely `first`, `middle`, and `last`.

f) The `recoverTree` function swaps the values of the misplaced nodes to restore the correct ordering of the BST.

g) If both `first` and `last` are non-null, it means that the misplaced nodes are not adjacent. 
In this case, we swap the values of `first` and `last` to correct the BST.

h) If only `first` and `middle` are non-null, it means that the misplaced nodes are adjacent. 
In this case, we swap the values of `first` and `middle` to correct the BST.

By identifying the misplaced nodes and performing the necessary swaps, the code ensures that the BST is 
recovered and satisfies the BST property, where the left subtree values are smaller and the right subtree values are larger than the node values.

class Solution {
public:
    // Pointer to the first misplaced node
    TreeNode* first; 

    // Pointer to the middle misplaced node (in case of two adjacent misplaced nodes)  
    TreeNode* middle; 

    // Pointer to the last misplaced node 
    TreeNode* last;
    
    // Pointer to the previously visited node during inorder traversal    
    TreeNode* prev;    

    void inorder(TreeNode* root) {
        if (root == NULL)
            return;

        // Traverse the left subtree
        inorder(root->left);  

        // Check if the current node is misplaced (not in increasing order)
        if (prev != NULL && prev->val > root->val) {
            // Found the first misplaced node
            if (first == NULL) {
                // Update first to prev node
                first = prev; 
                // Mod will store current node, in case swapped nodes are adjacent one!! Middle and first will
                // be those nodes!! 
                middle = root;
            } 
            // If there was previous misplaced, so update the last misplaced node
            else { 
                last = root;  // Found the last misplaced node
            }
        }

        prev = root;  // Update the previously visited node

        inorder(root->right);  // Traverse the right subtree
    }

    void recoverTree(TreeNode* root) {
        first = NULL;
        middle = NULL;
        last = NULL;
        prev = NULL;

        inorder(root);  // Perform inorder traversal to find misplaced nodes

        // Swapped nodes are not adjacent!!
        if (first != NULL && last != NULL) {
            swap(first->val, last->val);  // Swap the values of the first and last misplaced nodes
        } 
        // Swapped nodes are adjacent, last will be null, as we will find only one pair with distortion!!
        // and first time last and middle will get set to that nodes and last will remain NULL na!!
        else if (first != NULL && middle != NULL) {
            swap(first->val, middle->val);  // Swap the values of the first and middle misplaced nodes
        }
    }

Time Complexity: O(N) 
Space Complexity: O(1) Ignoring recursion stack!!

--------------------------------------------------------------------------------------------------------------------------
14) Largest BST in Binary Tree

Video bagh saral

The above code aims to find the largest Binary Search Tree (BST) in a given binary tree. Here's the intuition behind the code:

a) We define a class called `NodeValue` to store information about a subtree. This includes the minimum value (`minNode`), 
maximum value (`maxNode`), and the size of the largest BST (`maxSize`) found in that subtree.

b) The `largestBSTSolve` function is a recursive helper function. It takes a `TreeNode<int>*` as input and 
returns a `NodeValue` object.

c) The base case of the recursion is when the current node is null (`!root`). In this case, we return a `NodeValue` 
object with minimum and maximum values set to `INT_MAX` and `INT_MIN` respectively (representing an empty subtree) and a size of 0.

d) When the current node is not null, we recursively call `largestBSTSolve` on the left and right subtrees to 
find the largest BST in each subtree.

e) We then check if the current node and its children form a valid BST. This is done by comparing the value of 
the current node (`root->data`) with the maximum value in the left subtree (`left.maxNode`) and the minimum value 
in the right subtree (`right.minNode`).

f) If the current node and its children form a valid BST, we create a new `NodeValue` object. The minimum value 
of the new object is set to the minimum of the left subtree's minimum value and the current node's value. 
We are comparing with root because, for leafnode minimum will be INT_MAX and root value will be less than INT_MAX
so to pass root's value, we are taking minimum of both values, same in case of maximum value
The maximum value is set to the maximum of the right subtree's maximum value and the current node's value. 
The size is calculated as 1 plus the sizes of the left and right subtrees.

g) If the current node and its children do not form a valid BST, we create a new `NodeValue` object with the 
minimum value set to `INT_MIN`, the maximum value set to `INT_MAX`, and the size set to the maximum of the 
sizes of the left and right subtrees.

h) Finally, the `largestBST` function serves as an interface to the algorithm. It calls `largestBSTSolve` on 
the root of the binary tree and returns the size of the largest BST found.

The intuition behind the code is to recursively traverse the binary tree, checking at each node if it forms a 
valid BST with its children. By combining the information from the left and right subtrees, the algorithm 
identifies the largest BST in the entire binary tree.

The goal is to find the largest Binary Search Tree (BST) within a given binary tree. 

To find the largest BST, we need to consider each node and its subtrees. The key 
observation is that a valid BST must satisfy the property that the value of each 
node is greater than the maximum value in its left subtree and less than the 
minimum value in its right subtree.

Starting from the root of the binary tree, the code uses a recursive approach to 
traverse each node and its subtrees. It calculates the largest BST in the left subtree 
and the largest BST in the right subtree.

The `NodeValue` class is used to store the information about a subtree. It keeps 
track of the minimum value (`minNode`), maximum value (`maxNode`), and the 
size of the largest BST (`maxSize`) found in that subtree.

At each node, the code checks if the current node and its subtrees form a valid BST 
by comparing the root value with the maximum value in the left subtree and the 
minimum value in the right subtree. If the condition is satisfied, it means that the 
current node can be included in a valid BST. In this case, the code updates the 
`NodeValue` object with the appropriate minimum and maximum values and 
increments the size of the largest BST by adding the sizes of the left and right 
subtrees.

If the current node and its subtrees do not form a valid BST, the code returns a 
`NodeValue` object with minimum and maximum values set to INT_MIN and 
INT_MAX, respectively. This indicates that there is no valid BST at that node.

By recursively applying this process to each node and its subtrees, the code 
eventually finds the largest BST in the given binary tree.

In summary, the code traverses the binary tree in a recursive manner, checks if each 
node and its subtrees form a valid BST, and keeps track of the largest BST found so 
far. By comparing the values at each node, it ensures that the BST property is 
maintained. The approach effectively divides the problem into smaller subproblems, 
allowing the code to find the largest BST efficiently.



#include <bits/stdc++.h>

class NodeValue
{
public:
    int minNode, maxNode, maxSize;

    NodeValue(int min, int max, int size)
    {
        minNode = min;
        maxNode = max;
        maxSize = size;
    }
};

NodeValue largestBSTSolve(TreeNode<int> *root)
{ // Base case: if root is null, return NodeValue with minimum and maximum values as INT_MAX and INT_MIN respectively, and size as 0.
    if (!root)
        return NodeValue(INT_MAX, INT_MIN, 0);

    // Recursively calculate the largest BST in the left subtree.
    auto left = largestBSTSolve(root->left);

    // Recursively calculate the largest BST in the right subtree.
    auto right = largestBSTSolve(root->right);

    // Check if the current node and its children form a valid BST.
    // If yes, return a NodeValue with the minimum value as the minimum of the left subtree's minimum value and the current node's value,
    // We are comparing with root because, for leafnode minimum will be INT_MAX and root value will be less than INT_MAX
    // So to pass root's value, we are taking minimum of both values, same in case of maximum value
    // the maximum value as the maximum of the right subtree's maximum value and the current node's value,
    // and the size as 1 plus the sizes of the left and right subtrees.
    if (root->data > left.maxNode && root->data < right.minNode)
        return NodeValue(left.minNode, right.maxNode, 1 + left.maxSize + right.maxSize);

    // If the current node and its children do not form a valid BST,
    // return a NodeValue with minimum value as INT_MIN, maximum value as INT_MAX,
    // so that this node cannot be considder as a valid BST while bactracking!!
    // and the size as the maximum of the sizes of the left and right subtrees.
    // because this function will carry the maximim BST size ion this side of tree
    return NodeValue(INT_MIN, INT_MAX, max(left.maxSize, right.maxSize));
}

int largestBST(TreeNode<int> *root)
{
    // Call the largestBSTSolve function and return the size of the largest BST in the given binary tree.
    return largestBSTSolve(root).maxSize;
}

Time Complexity: O(N) 
Space Complexity: O(1) Ignoring recursion stack!!

**************************************************************************************************************************
15) Binary Tree to BST

https://practice.geeksforgeeks.org/problems/binary-tree-to-bst/1

class Solution {
public:
    // Helper function to perform an inorder traversal of the binary tree
    void inorder(Node* root, vector<int>& in) {
        if (root == NULL) {
            return;
        }
        // Recursively traverse the left subtree
        inorder(root->left, in);
        // Add the current node's data to the 'in' vector
        in.push_back(root->data);
        // Recursively traverse the right subtree
        inorder(root->right, in);
    }

    // Helper function to convert the binary tree to a BST using the sorted 'in' vector
    void convertToBst(Node* root, vector<int>& in, int& index) {
        if (root == NULL) {
            return;
        }
        // Recursively update the nodes with values from the sorted 'in' vector
        convertToBst(root->left, in, index);
        root->data = in[index++];
        convertToBst(root->right, in, index);
    }

    // The given root is the root of the Binary Tree
    // Return the root of the generated BST
    Node* binaryTreeToBST(Node* root) {
        if (root == NULL) {
            return NULL;
        }
        // Store the inorder traversal of the given binary tree in the 'in' vector
        vector<int> in;
        inorder(root, in);
        // Sort the 'in' vector to get the values in ascending order
        sort(in.begin(), in.end());
        int index = 0;
        // Convert the binary tree to a BST by updating node values with sorted values
        convertToBst(root, in, index);
        // Return the root of the generated BST
        return root;
    }
};
