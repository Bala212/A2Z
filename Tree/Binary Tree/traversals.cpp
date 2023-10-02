DFS:
// 1.Inorder
void inorder(TreeNode *root, vector<int> &ans)
{
    if (root == NULL)
    {
        return;
    }
    // LEFT ROOT RIGHT
    inorder(root->left, ans);
    ans.push_back(root->val);
    inorder(root->right, ans);
}
---------------------------------------------------------------------------------------
// 2.Preorder
void preorder(TreeNode *root, vector<int> &ans)
{
    if (root == NULL)
    {
        return;
    }
    // ROOT LEFT RIGHT
    ans.push_back(root->val);
    preorder(root->left, ans);
    preorder(root->right, ans);
}
---------------------------------------------------------------------------------------
//3. void postorder(TreeNode *root, vector<int> &ans)
{
    if (root == NULL)
    {
        return;
    }
    // LEFT RIGHT ROOT
    postorder(root->left, ans);
    postorder(root->right, ans);
    ans.push_back(root->val);
}
Time Complexity: O(N).
Reason: We are traversing N nodes and every node is visited exactly once.

Space Complexity: O(N)
Reason: Space is needed for the recursion stack. In the worst case (skewed tree), space complexity can be O(N).

-x-x-x-x--x--x-x-x--x-x--x---x-x--x-x-x-x-x-x-x--x-x-x--x-x-x-x-x-x-x-x----x-x-x-x--x--x--x-x-x-x--
BFS (Level order)

// print in a single vector
vector<int> levelOrder(TreeNode *root)
{
    vector<int> ans;
    if (root == NULL)
    {
        return ans;
    }

    queue<TreeNode *> q;

    q.push(root);

    while (!q.empty())
    {
        // pop node from queue and insert it's left and right into queue
        TreeNode *temp = q.front();
        q.pop();
        if (temp->left != NULL)
            q.push(temp->left);
        if (temp->right != NULL)
            q.push(temp->right);

        // Push current node in answer
        ans.push_back(temp->val);
    }
    return ans;
}

// print every level, separately
vector<vector<int>> levelOrder(TreeNode *root)
{
    // to store the level order
    vector<vector<int>> ans;
    if (root == NULL)
    {
        return ans;
    }

    queue<TreeNode *> q;
    // Push the root in queue
    q.push(root);

    while (!q.empty())
    {
        int size = q.size();
        vector<int> level;
        // Traverse each level
        while (size--)
        {
            TreeNode *temp = q.front();
            q.pop();
            if (temp->left != NULL)
                q.push(temp->left);
            if (temp->right != NULL)
                q.push(temp->right);
            // Push nodes of a particular level
            level.push_back(temp->val);
        }
        // Push current level into ans
        ans.push_back(level);
    }

    return ans;
}
// Time Complexity: O(N)
// Space Complexity: O(N)
---x--x--x----x--x--x--x--x--x-x-x--x-x-x---x--x--x-x-x-x-x---x-x-x-x-x--x-x-x-x-x--x-x--x--x-x-x--x--x-x--x-x-x-x--x-x-x-x--x-x--xx-x---x---x-x-x-x--x--x--x
ITERATIVE CODES:

1) Iterative preorder

We first push the right child of this popped node and then push the left child, if they are not NULL. 
We do so because stack is a last-in-first-out(LIFO) data structure. We need to access the left child first, so we need to push it at the last.

vector<int> preorderTraversal(TreeNode* root) {
    vector<int> ans; // Vector to store the preorder traversal
    if(root == NULL) return ans; // If the root is null, return an empty vector
    stack<TreeNode*> s; // Stack to perform iterative traversal
    s.push(root); // Push the root node to the stack
    while(!s.empty()){
        TreeNode* node = s.top(); // Get the top node from the stack
        s.pop(); // Pop the node from the stack

        ans.push_back(node->val); // Add the value of the current node to the answer vector (preorder visit)

        if(node->right != NULL) s.push(node->right); // Push the right child to the stack if it exists

        if(node->left != NULL) s.push(node->left); // Push the left child to the stack if it exists
    }
    return ans; // Return the preorder traversal vector
}
// Time Complexity: O(N)
// Space Complexity: O(N)
--------------------------------------------------------------------------------------------------------------------------------------------------------------------
2) Iterative Inorder 


vector<int> getInOrderTraversal(TreeNode *root)
{
    stack<TreeNode*> s; // Stack to perform iterative traversal
    vector<int> ans; // Vector to store the inorder traversal

    while(1){
        if(root != NULL){
            s.push(root); // Push the current node to the stack
            root = root->left; // Move to the left child
        }
        else{
            if(s.empty()) break; // If the stack is empty, we have finished traversing the tree, so we break the loop
            root = s.top(); // Get the top node from the stack, and assign it to root as we
                            // want to move to the right of top node/root node now!
            s.pop(); // Pop the top node from the stack
            ans.push_back(root->data); // Add the value of the current node/root node to the answer vector (inorder visit)
            // We traverse, left nodes root nodes, now move to right.
            root = root->right; // Move to the right child
        }
    }
    return ans; // Return the inorder traversal vector
}

// Time Complexity: O(N)
// Space Complexity: O(N)

--------------------------------------------------------------------------------------------------------------------------------------------------------------------
3) Iterative Postorder

Using 2 stacks:
a) Declare two stacks, s1 and s2.

b) Using s1 we will traverse the tree, as push the root into it, then set while loop
till s1 becomes empty everytime pop node from s1 then WHATEVER WE ARE
POPPING FROM S1, WE WILL PUSH THAT IN S2. And then push left and right nodes
if not NULL into s1.

c) At last s2 will store our post order traversal, pop one by one and push into ans 
vector.

// OR we can insert directly into ans vector instead of pushing in s2, and at end just reverse the ans vector

vector<int> postorderTraversal(TreeNode* root)
{
    vector<int> ans; // Create an empty vector to store the result
    if(root == NULL) return ans; // If the root is NULL, return the empty vector
    
    stack<TreeNode*> s1, s2; // Create two stacks: s1 for processing nodes and s2 for storing the postorder traversal
    
    s1.push(root); // Push the root node into s1 to start the traversal
    
    while(!s1.empty()){
        root = s1.top(); // Get the top node from s1
        s1.pop(); // Remove the top node from s1
        
        s2.push(root); // Push the node into s2 to store it for postorder traversal
        
        // First LEFT then RIGHT
        if(root->left != NULL) s1.push(root->left); // Push the left child of the current node into s1
        
        if(root->right != NULL) s1.push(root->right); // Push the right child of the current node into s1
    }
    
    while(!s2.empty()){
        ans.push_back(s2.top()->val); // Push the value of each node in s2 (postorder traversal) into the result vector
        s2.pop(); // Remove the node from s2
    }
    
    return ans; // Return the postorder traversal stored in the result vector
}


// Time Complexity: O(N)
// Space Complexity: O(2*N)
Pushing directly into ans and reversing in
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> ans; // Create an empty vector to store the result
        if(root == NULL) return ans; // If the root is NULL, return the empty vector
        
        stack<TreeNode*> s1, s2; // Create two stacks: s1 for processing nodes and s2 for storing the postorder traversal
        
        s1.push(root); // Push the root node into s1 to start the traversal
        
        while(!s1.empty()){
            root = s1.top(); // Get the top node from s1
            s1.pop(); // Remove the top node from s1

            // INSERT Directly into ans vector!!
            ans.push_back(root->val);
            
            // First LEFT then RIGHT
            if(root->left != NULL) s1.push(root->left); // Push the left child of the current node into s1
            
            if(root->right != NULL) s1.push(root->right); // Push the right child of the current node into s1
        }
        
        // while(!s2.empty()){
        //     ans.push_back(s2.top()->val); // Push the value of each node in s2 (postorder traversal) into the result vector
        //     s2.pop(); // Remove the node from s2
        // }

        // Reverse ans, instead of popping from s2 and pushing, both works the same
        reverse(ans.begin(), ans.end());
        
        return ans; // Return the postorder traversal stored in the result vector
    }
};

--------------------------------------------------------------------------------------------------------------------------------------------------------------------
4) All three traversals in one traversal!

#Stack of pair<Node*, int>

*if num == 1 (Preorder) [1 mhnje root ek number la, mhnje preorder]
   - Push the node into preorder array
   - increase the num and again push the updated num with same node into queue  
   - Push the left child of node if exists (with num as 1) Left because: Preorder madhe root nantr left yeto!! Root nantr je yeta te push kara thodkyat!!

*if num == 2 (Inorder) [2 mhnje root don number la, mhnje inorder]
   - Push the node into inorder array
   - increase the num and again push the updated num with same node into queue
   - Push the right child of node if exists (with num as 1) Right because: Inorder madhe root nantr right yeto!! Root nantr je yeta te push kara thodkyat!!

*if num == 3 (Inorder) [3 mhnje root shevti na, mhnje postorder]
   - Push the node into postorder array
   - No push, nothing; as there is nothing after root in postorder.

In preorder traversal, we print a node at the first visit itself. Whereas, in inorder traversal 
at the first visit to a node, we simply traverse to the left child. It is only when we return from 
the left child and visit that node the second time, that we print it. Similarly, in postorder traversal, 
we print a node in its third visit after visiting both its children.

Striver cha article vaach!!


void fill(BinaryTreeNode<int> *root, vector<int> &inorder, vector<int> &preorder, vector<int> &postorder){
    stack<pair<BinaryTreeNode<int> *, int>> s;
    s.push({root, 1}); // Push the root node with state 1 into the stack

    while(!s.empty()){
        auto it = s.top(); // Get the top element of the stack
        s.pop(); // Remove the top element from the stack

        if(it.second == 1){ // If the state is 1 (preorder processing)
            preorder.push_back(it.first->data); // Push the current node's data into the preorder vector
            it.second++; // Update the state to 2
            s.push(it); // Push the updated element back into the stack
            if(it.first->left != NULL){ // If the left child exists
                s.push({it.first->left, 1}); // Push the left child with state 1 into the stack
                // state 1 because this pushed node in a new node we are traversing, so need to be start with 1 na
            }
        }
        else if(it.second == 2){ // If the state is 2 (inorder processing)
            inorder.push_back(it.first->data); // Push the current node's data into the inorder vector
            it.second++; // Update the state to 3
            s.push(it); // Push the updated element back into the stack
            if(it.first->right != NULL){ // If the right child exists
                s.push({it.first->right, 1}); // Push the right child with state 1 into the stack
            }
        }
        else{ // If the state is 3 (postorder processing)
            postorder.push_back(it.first->data); // Push the current node's data into the postorder vector
        }
    }
}

vector<vector<int>> getTreeTraversal(BinaryTreeNode<int> *root){
    vector<vector<int>> ans; // Create a 2D vector to store the traversal results
    if(root == NULL) return ans; // If the root is NULL, return the empty 2D vector
    
    vector<int> inorder, preorder, postorder; // Create vectors to store the inorder, preorder, and postorder traversals
    
    fill(root, inorder, preorder, postorder); // Fill the traversal vectors using the fill() function

    ans.push_back(inorder); // Push the inorder traversal vector into the result 2D vector
    ans.push_back(preorder); // Push the preorder traversal vector into the result 2D vector
    ans.push_back(postorder); // Push the postorder traversal vector into the result 2D vector

    return ans; // Return the result 2D vector containing all the traversal vectors
}

// Time Complexity: O(3*N)
// Space Complexity: O(4*N)
***********************************************************************************************************************************************************************




