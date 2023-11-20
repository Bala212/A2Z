1) Maximum height of binary tree
//  Count number of levels!!
int maxDepth(TreeNode *root)
{
    if (root == NULL)
        return NULL;
    queue<TreeNode *> q;
    q.push(root);
    int level = 0;
    while (!q.empty())
    {
        int size = q.size();
        while (size--)
        {
            auto node = q.front();
            q.pop();
            if (node->left != NULL)
                q.push(node->left);
            if (node->right != NULL)
                q.push(node->right);
        }
        level++;
    }
    return level;
}

Recursive one
//  1+max(leftHeight, rightHeight) using postOrder traversal!
int maxDepth(TreeNode *root)
{
    if (root == NULL)
        return 0;
    int leftHeight = maxDepth(root->left);
    int rightHeight = maxDepth(root->right);
    return 1 + max(leftHeight, rightHeight);
}

Time Complexity: O(N) 
Space Complexity: O(1) Extra Space + O(H) Recursion Stack space, where “H”  is the height of the binary tree.
--------------------------------------------------------------------------------------------------
2) Check if the Binary Tree is Balanced Binary Tree
// A binary tree is balanced if, for all nodes in the tree, the difference between left and right subtree
//  height is not more than 1.
int f(TreeNode *root)
{
    if (root == NULL)
        return 0;
    // Get the left height
    int leftHeight = f(root->left);
    // If at left part we get unbalanced tree, return -1
    if (leftHeight == -1)
        return -1;

    // Get the right height
    int rightHeight = f(root->right);
    // If at right part we get unbalanced tree, return -1
    if (rightHeight == -1)
        return -1;

    // If the difference between left and right height is greater than 1 return -1
    if (abs(leftHeight - rightHeight) > 1)
        return -1;
    // Else return the height of current node and continue
    return 1 + max(leftHeight, rightHeight);
}

bool isBalanced(TreeNode *root)
{
    return f(root) != -1;
}
Time Complexity: O(N)
Space Complexity: O(1) Extra Space + O(H) Recursion Stack space
                    (Where “H”  is the height of binary tree)

--------------------------------------------------------------------------------------------------
3) Diameter of Binary Tree

int f(TreeNode *root, int &diameter)
{
    // If node is null, height is 0
    if (root == NULL)
        return 0;

    // find the left height
    int leftHeight = f(root->left, diameter);

    // find the right height
    int rightHeight = f(root->right, diameter);

    // Update the diameter everytime as leftHeight + rightHeight
    diameter = max(diameter, leftHeight + rightHeight);

    // return the height of current node to it's previous call
    return 1 + max(leftHeight, rightHeight);
}

int diameterOfBinaryTree(TreeNode *root)
{
    int diameter = 0;
    // Get the maximum diamater
    f(root, diameter);
    // return diameter
    return diameter;
}

Time Complexity: O(N)
Space Complexity: O(1) Extra Space + O(H) Recursion Stack space
--------------------------------------------------------------------------------------------------
4) Maximum path sum Binary Tree

int f(TreeNode *root, int &maxi)
{
    // If node is null, we will return sum as 0
    if (root == NULL)
        return 0;

    // Calculate leftSum and rightSum, and if it comes -ve, dropdown it to 0
    int leftSum = max(0, f(root->left, maxi));
    int rightSum = max(0, f(root->right, maxi));

    // Get the maximum path sum that this node can give
    // sum will be current node's data + leftSum + rightSum
    maxi = max(maxi, root->val + leftSum + rightSum);

    // return the maximum sum, when some path is going through this node
    // maximum sum will be current node's data + max(leftSum + rightSum)
    return root->val + max(leftSum, rightSum);
}

int maxPathSum(TreeNode *root)
{
    int maxi = INT_MIN;
    f(root, maxi);
    return maxi;
}

Time Complexity: O(N).
Reason: We are doing a tree traversal.

Space Complexity: O(N)
Reason: Space is needed for the recursion stack. In the worst case (skewed tree), space complexity can be O(N).
// --------------------------------------------------------------------------------------------------
5) Check if two trees are identical
bool isSameTree(TreeNode *p, TreeNode *q)
{
    if (p == NULL || q == NULL)
    {
        // Both should be NULL
        return p == q;
    }

    // Traverse in preorder fashion, first check root, and the left and right subtrees
    return (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

Time Complexity: O(N).
Reason: We are doing a tree traversal.

Space Complexity: O(N)
Reason: Space is needed for the recursion stack. In the worst case (skewed tree), space complexity can be O(N).
// --------------------------------------------------------------------------------------------------
6) Zig Zag Traversal Of Binary Tree

// Depending on flag variable insert a level into answer, by level order traversal
vector<vector<int>> zigzagLevelOrder(TreeNode *root)
{
    // To know in which manner we have to push the level into answer
    bool leftToRight = 1;
    // Do a simple level order traversal, and depending upon the leftToright value
    // insert a level in ans
    queue<TreeNode *> q;
    q.push(root);
    vector<vector<int>> ans;
    // If empty tree, return empty vector
    if (root == NULL)
        return ans;
    while (!q.empty())
    {
        // size of a queue, i.e size of current level
        int size = q.size();
        // vector to store a level
        vector<int> temp;
        // Traverse whole level
        while (size--)
        {
            auto node = q.front();
            q.pop();
            if (node->left != NULL)
                q.push(node->left);
            if (node->right != NULL)
                q.push(node->right);
            temp.push_back(node->val);
        }
        // depending upon leftToRight value, reverse the level or don't
        if (!leftToRight)
        {
            reverse(temp.begin(), temp.end());
        }
        // toggle the leftToRIght for next level
        leftToRight = !leftToRight;
        // push the current level into answer
        ans.push_back(temp);
    }
    return ans;
}
// Time Complexity: O(N)
// Space Complexity: O(N)
// --------------------------------------------------------------------------------------------------
8) Boundary Traversal of a Binary Tree

bool isLeaf(Node *root)
{
    // If left and right are null, it is a leaf node
    return root->left == NULL && root->right == NULL;
}

void addLeftBoundary(Node *root, vector<int> &ans)
{
    // Traverse till root not becomes null, i.e does not reach end
    while (root != NULL)
    {
        // Push current value in ans, if it not a leaf node
        if (!isLeaf(root))
            ans.push_back(root->data);
        // If there exists a left node go there, else go right
        if (root->left != NULL)
            root = root->left;
        else
            root = root->right;
    }
}

void addRightBoundary(Node *root, vector<int> &ans)
{
    // WE WANT RIGHT BOUNDARY IN REVERSE FASHION
    vector<int> temp;
    // Traverse till root not becomes null, i.e does not reach end
    while (root != NULL)
    {
        // Push current value in ans, if it not a leaf node
        if (!isLeaf(root))
            temp.push_back(root->data);
        // If there exists a right node go there, else go left
        if (root->right != NULL)
            root = root->right;
        else
            root = root->left;
    }
    // Push reverse in ans
    for (int i = temp.size() - 1; i >= 0; i--)
    {
        ans.push_back(temp[i]);
    }
}

void addLeafNodes(Node *root, vector<int> &ans)
{
    // THIS IS INORDER TRAVERSAL
    // When we encounter a leaf node, add it to answer and return to previous call
    if (isLeaf(root))
    {
        ans.push_back(root->data);
        return;
    }
    // Go left and then right
    if (root->left != NULL)
        addLeafNodes(root->left, ans);
    if (root->right != NULL)
        addLeafNodes(root->right, ans);
}

vector<int> boundary(Node *root)
{
    vector<int> ans;
    if (root == NULL)
        return ans;
    // If root is not a leaf node, push it into answer
    if (!isLeaf(root))
        ans.push_back(root->data);
    // Add left boundary
    addLeftBoundary(root->left, ans);
    // Add leaf nodes
    addLeafNodes(root, ans);
    // Add right boundary
    addRightBoundary(root->right, ans);
    // return the ans
    return ans;
}

Time Complexity: O(N).
Reason: The time complexity will be O(H) + O(H) + O(N) which is ≈ O(N)

Space Complexity: O(N)
Reason: Space is needed for the recursion stack while adding leaves. In the worst case (skewed tree), space complexity can be O(N).
--------------------------------------------------------------------------------------------------
8) Vertical Order Traversal Of Binary Tree

vector<vector<int>> verticalTraversal(TreeNode *root)
{
    // We are using map because we want verticals like ...-2, -1, 0, 1, 2...
    // Multiset because we have to store duplicate nodes as well and in sorted order
    // {vertical, {level,{nodes...} } }
    map<int, map<int, multiset<int>>> m;

    // A queue to do level order traversal and assign vertical and level to each node
    // {node, {vertical, level} }
    queue<pair<TreeNode *, pair<int, int>>> q;

    // push root node
    q.push({root, {0, 0}});

    // do level order traversal and assign node with their level and vertical, and at same time
    // store nodes at a partcular level in map
    while (!q.empty())
    {
        // get the top front node from queue
        auto top = q.front();
        q.pop();
        // a node itself
        TreeNode *node = top.first;
        // node's vertical
        int vertical = top.second.first;
        // node's level
        int level = top.second.second;

        // go left (decrease vertical) and right( increase vertical) and increase level by 1 for both
        if (node->left != NULL)
            q.push({node->left, {vertical - 1, level + 1}});
        if (node->right != NULL)
            q.push({node->right, {vertical + 1, level + 1}});

        // Store the vetical and level into the map
        m[vertical][level].insert(node->val);
    }
    // Extract nodes vertical wise from map
    vector<vector<int>> ans;
    for (auto &ele : m)
    {
        // to store a current vertical!
        vector<int> col;
        // nodes are present in second second of map which are stored in multiset
        for (auto &eleSec : ele.second)
        {
            for (auto &nodes : eleSec.second)
            {
                col.push_back(nodes);
            }
        }
        // Push back a current vertical!
        ans.push_back(col);
    }

    // return the vector of verticals
    return ans;
}

Time Complexity: O(N*logN)
Space Complexity: O(N)+O(N)
--------------------------------------------------------------------------------------------------
9) Top view of Binary Tree
vector<int> topView(Node *root)
{
    // {line, node}, and we want line in sorted order ...-2, -1, 0, 1, 2...
    map<int, int> m;

    // queue to do level order traversal
    // {node, line}
    queue<pair<Node *, int>> q;

    // root is on line 0
    q.push({root, 0});

    while (!q.empty())
    {
        auto top = q.front();
        q.pop();

        Node *node = top.first;
        int line = top.second;

        // If there doesn't exist this line in map i.e we are visting this line
        // first time so store it inside map, if its first time means this node
        // is fist on this line
        if (m.find(line) == m.end())
            m[line] = node->data;

        // Push left and right childs of current node

        // left-> line-1
        if (node->left != NULL)
            q.push({node->left, line - 1});

        // right -> line+1
        if (node->right != NULL)
            q.push({node->right, line + 1});
    }

    vector<int> ans;

    // Extract node assigned with each line
    // map stores line in sorted fashion as required ...-2, -1, 0, 1, 2...
    for (auto &val : m)
    {
        ans.push_back(val.second);
    }

    // return top view stored in ans
    return ans;
}
// Time Complexity: O(N)
// Space Complexity: O(N)
--------------------------------------------------------------------------------------------------
10) Bottom view of Binary Tree

vector<int> bottomView(Node *root)
{
    // {line, node}, and we want line in sorted order ...-2, -1, 0, 1, 2...
    map<int, int> m;

    // queue to do level order traversal
    // {node, line}
    queue<pair<Node *, int>> q;

    // root is on line 0
    q.push({root, 0});

    while (!q.empty())
    {
        auto top = q.front();
        q.pop();

        Node *node = top.first;
        int line = top.second;

        // Here we don’t need to check whether the node is previously present on the
        // map or node before entering it. We have to replace the node of each line
        // if that was previously present on the map and by this we will get the last
        // node of each line.
        m[line] = node->data;

        // Push left and right childs of current node

        // left-> line-1
        if (node->left != NULL)
            q.push({node->left, line - 1});

        // right -> line+1
        if (node->right != NULL)
            q.push({node->right, line + 1});
    }

    vector<int> ans;

    // Extract node assigned with each line
    // map stores line in sorted fashion as required ...-2, -1, 0, 1, 2...
    for (auto &val : m)
    {
        ans.push_back(val.second);
    }

    // return bottom view stored in ans
    return ans;
}

Time Complexity: O(N)
Space Complexity: O(N)

--------------------------------------------------------------------------------------------------
11) Left View of binary tree
First node in every level!!

same as above top/bottom view, but here we are storing level in map and in top/bottom we stores verticals/line

vector<int> leftView(Node *root)
{
   // Create an empty vector to store the left view elements
   vector<int> ans;
   
   // If the root is NULL, return the empty vector
   if(root == NULL){
       return ans;
   }
   
   // Create a map to store the leftmost element at each level
   // {level, node}
   map<int, int> m;
   
   // Create a queue to perform level order traversal
   queue<pair<Node*, int>> q;
   // {node, level}
   q.push({root, 0});
   
   while(!q.empty()){
       // Get the front node and its level from the queue
       auto it = q.front();
       q.pop();
       
       Node *node = it.first;
       int level = it.second;
       
       // Update the map with the leftmost element at each level
       // Only update if the level is not already present in the map
       if(m.find(level) == m.end()){
           m[level] = node->data;
       }
       
       // Push the left child to the queue if it exists
       if(node->left != NULL){
           q.push({node->left, level + 1});
       }
       
       // Push the right child to the queue if it exists
       if(node->right != NULL){
           q.push({node->right, level + 1});
       }
   }
   
   // Traverse the map and store the leftmost elements in the result vector
   for(auto &val : m){
       ans.push_back(val.second);
   }
   
   // Return the left view elements
   return ans;
}

Approach2: Preorder
void f(TreeNode *root, int level, vector<int> &ans)
{
    if (root == NULL)
        return;

    // When we reach a level equal to size of ans vector, push that node into ans
    if (level == ans.size())
        ans.push_back(root->val);

    // Preorder
    f(root->left, level + 1, ans);
    f(root->right, level + 1, ans);
}

vector<int> leftSideView(TreeNode *root)
{
    vector<int> ans;

    // Initially level is 0
    int level = 0;

    // Go and fill out the vector
    f(root, level, ans);

    // return the ans vector
    return ans;
}
// Time Complexity: O(N)
// Space Complexity: O(H)
--------------------------------------------------------------------------------------------------
12) Right View of Binary Tree

Approach1: Last node in every level

Same logic of bottom view!!! We are not checking while inserting level into map, this will
endure that last node is inserted in map of a particular level

    vector<int> rightSideView(TreeNode* root) {
        // Create an empty vector to store the right view elements
        vector<int> ans;

        // If the root is NULL, return the empty vector
        if (root == NULL) {
            return ans;
        }

        // Create a map to store the rightmost element at each level
        // {level, node}
        map<int, int> m;
        
        // Create a queue to perform level order traversal
        queue<pair<Node*, int>> q;

        // {node, level}
        q.push({root, 0});

        while (!q.empty()) {
            // Get the front node and its level from the queue
            auto it = q.front();
            q.pop();
            
            TreeNode *node = it.first;
            int level = it.second;
            
            // just a simple MODIFICATION HERE!!
            // Update the map with the rightmost element at each level
            // if (m.find(level) == m.end()) {
                m[level] = node->val;
            // }
            
            // 
            // Push the right child to the queue if it exists
            if (node->left != NULL) {
                q.push({node->left, level + 1});
            }
            
            // Push the left child to the queue if it exists
            if (node->right != NULL) {
                q.push({node->right, level + 1});
            }
        }

        // Traverse the map and store the rightmost elements in the result vector
        for (auto &val : m) {
            ans.push_back(val.second);
        }

        // Return the right view elements
        return ans;
    }

Approach2: First node in every level From right!! ( See my notes)

Level order traversal madhe right nodes pahile push kara!!

vector<int> rightView(Node *root)
{
    // Create an empty vector to store the right view elements
    vector<int> ans;

    // If the root is NULL, return the empty vector
    if (root == NULL) {
        return ans;
    }

    // Create a map to store the rightmost element at each level
    map<int, int> m;

    // Create a queue to perform level order traversal
    queue<pair<Node*, int>> q;
    q.push({root, 0});

    while (!q.empty()) {
        // Get the front node and its level from the queue
        auto it = q.front();
        q.pop();
        
        Node *node = it.first;
        int level = it.second;
        
        // Update the map with the rightmost element at each level
        // BECAUSE WE ARE PUSHING RIGHT NODES FIRST IN
        // Only update if the level is not present in the map
        if (m.find(level) == m.end()) {
            m[level] = node->data;
        }
        
        // 
        // Push the right child to the queue if it exists
        if (node->right != NULL) {
            q.push({node->right, level + 1});
        }
        
        // Push the left child to the queue if it exists
        if (node->left != NULL) {
            q.push({node->left, level + 1});
        }
    }

    // Traverse the map and store the rightmost elements in the result vector
    for (auto &val : m) {
        ans.push_back(val.second);
    }

    // Return the right view elements
    return ans;
}


Approach3: Reverse preorder
void f(TreeNode *root, int level, vector<int> &ans)
{
    if (root == NULL)
        return;

    // When we reach a level equal to size of ans vector, push that node into ans
    if (level == ans.size())
        ans.push_back(root->val);

    // Reverse pre order
    f(root->right, level + 1, ans);
    f(root->left, level + 1, ans);
}

vector<int> rightSideView(TreeNode *root)
{
    vector<int> ans;

    // Initially level is 0
    int level = 0;

    // Go and fill out the vector
    f(root, level, ans);

    // return the ans vector
    return ans;
}
// Time Complexity: O(N)
// Space Complexity: O(H)
--------------------------------------------------------------------------------------------------
Left View of Binary Tree

Approach1: First node in every level( From left)!! ( See my notes)
Level order traversal madhe left nodes pahile push kara!!

vector<int> leftView(Node *root)
{
   // Create an empty vector to store the left view elements
   vector<int> ans;
   
   // If the root is NULL, return the empty vector
   if(root == NULL){
       return ans;
   }
   
   // Create a map to store the leftmost element at each level
   map<int, int> m;
   
   // Create a queue to perform level order traversal
   queue<pair<Node*, int>> q;
   q.push({root, 0});
   
   while(!q.empty()){
       // Get the front node and its level from the queue
       auto it = q.front();
       q.pop();
       
       Node *node = it.first;
       int level = it.second;
       
       // Update the map with the leftmost element at each level
       // Only update if the level is not already present in the map
       if(m.find(level) == m.end()){
           m[level] = node->data;
       }
       
       // Push the left child to the queue if it exists
       if(node->left != NULL){
           q.push({node->left, level + 1});
       }
       
       // Push the right child to the queue if it exists
       if(node->right != NULL){
           q.push({node->right, level + 1});
       }
   }
   
   // Traverse the map and store the leftmost elements in the result vector
   for(auto &val : m){
       ans.push_back(val.second);
   }
   
   // Return the left view elements
   return ans;
}
--------------------------------------------------------------------------------------------------
13) Leftmost and rightmost nodes of binary tree
https://practice.geeksforgeeks.org/problems/leftmost-and-rightmost-nodes-of-binary-tree/1

Do the level order traversal and take the left most and right elements in each level . 

void printCorner(Node *root)
{
    queue<Node*> q;
    q.push(root);
    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; ++i) {
            Node* temp = q.front();
            if ( i == 0 || i == n - 1)
                cout << temp->data << " ";

            if (temp->left != nullptr)
                q.push(temp->left);
            if (temp->right != nullptr)
                q.push(temp->right);

            q.pop();
        }
    }

}
--------------------------------------------------------------------------------------------------
14) Symmetric Binary Tree
*Root's left subtree should be equal to root's right subtree.

bool check(TreeNode *root1, TreeNode *root2)
{
    // Both has to be NULL at same time!!
    if (root1 == NULL || root2 == NULL)
    {
        return root1 == root2;
    }

    // If anywhere, node's value is different return false
    if (root1->val != root2->val)
    {
        return false;
    }

    // left's--> left and right's->right
    bool leftRight = check(root1->left, root2->right);

    // left's--> right and right's->left
    bool rightLeft = check(root1->right, root2->left);

    // if both are symmetric return true
    return leftRight && rightLeft;
}

bool isSymmetric(TreeNode *root)
{
    // If tree is empty
    if (root == NULL)
    {
        return true;
    }

    // check left and right subtree of root, whether they are identical or not
    return check(root->left, root->right);
}


// OR simpple, like qustion check if two tree are identical code!!

class Solution {
public:
    bool check(TreeNode* root1,TreeNode* root2){
        // Both has to be NULL at same time!!
        if(root1==NULL || root2==NULL){
            return root1 == root2;
        }

        //left's--> left and right's->right
        bool leftRight = check(root1->left,root2->right);

        //left's--> right and right's->left
        bool rightLeft = check(root1->right,root2->left);

        // their values are same and left subtree and right subtree are symmetric then return true
        return root1->val == root2->val &&  leftRight && rightLeft;
    }

    bool isSymmetric(TreeNode* root) {
        // If tree is empty
        if(root==NULL){
            return true;
        }
        // check left and right subtree of root, whether they are identical or not
        return check(root->left,root->right);
    }
};

Time Complexity: O(N)
Reason: We are doing simple tree traversal and changing both root1 and root2 simultaneously.

Space Complexity: O(N)
Reason: In the worst case (skewed tree), space complexity can be O(N).

--------------------------------------------------------------------------------------------------
15) Check if Tree is Isomorphic

https://practice.geeksforgeeks.org/problems/check-if-tree-is-isomorphic/1
class Solution{
  public:
    // Return True if the given trees are isomotphic. Else return False.
    bool isIsomorphic(Node *root1,Node *root2)
    {
        if(root1 == NULL || root2 == NULL){
            return root1 == root2;
        }
        
        bool values = root1->data == root2->data;
        
        bool sameTraverse = isIsomorphic(root1->left, root2->left) && isIsomorphic(root1->right, root2->right);
        
        bool crossTraverse = isIsomorphic(root1->left, root2->right) && isIsomorphic(root1->right, root2->left);
        
        return values && (sameTraverse || crossTraverse);
    }
};

--------------------------------------------------------------------------------------------------
16) Leaf under budget

https://practice.geeksforgeeks.org/problems/leaf-under-budget/1


class Solution {
public:
    // Function to count the number of leaf nodes at level 'k' in a binary tree
    int getCount(Node* root, int k) {
        // Create a queue to perform level-order traversal
        queue<pair<Node*, int>> q;
        // Initialize the queue with the root node and its level (which is 1 in this case)
        q.push({root, 1});

        // Initialize a counter to keep track of leaf nodes found at level 'k'
        int cnt = 0;

        // Start the level-order traversal
        while (!q.empty()) {
            Node* node = q.front().first; // Get the current node
            int level = q.front().second; // Get the level of the current node
            q.pop(); // Remove the current node from the queue

            // Check if the current node is a leaf node and at the desired level 'k'
            if (node->left == NULL && node->right == NULL && k >= level) {
                cnt++; // Increment the counter if it's a leaf node at level 'k'
                k = k - level; // Decrease 'k' to track remaining leaf nodes at the same level
            }

            // Enqueue the left child if it exists, along with its level
            if (node->left != NULL) {
                q.push({node->left, level + 1});
            }

            // Enqueue the right child if it exists, along with its level
            if (node->right != NULL) {
                q.push({node->right, level + 1});
            }
        }

        // Return the count of leaf nodes found at level 'k'
        return cnt;
    }
};

--------------------------------------------------------------------------------------------------
17) K Sum Paths
https://leetcode.com/problems/path-sum-iii/

1) Brute: Same as N^2 in array (gives TLE)

class Solution {
public:

    // Variable to store the count of paths with the target sum
    int ans = 0;

    // Recursive function to find paths with the target sum starting from a given node
    void findSum(TreeNode* root, int k, int currSum){
        // Base case: If the node is null, return
        if(!root) return;

        // Update the current sum by adding the value of the current node
        currSum += root->val;

        // If the current sum is equal to the target sum, increment the answer count
        if(currSum == k) ans++;

        // Recursively explore paths in the left and right subtrees
        findSum(root->left, k, currSum);
        findSum(root->right, k, currSum);
    }

    // Function to find paths with the target sum in the entire tree
    int pathSum(TreeNode* root, int targetSum) {
        // Base case: If the root is null, there are no paths
        if(!root) return 0;

        // Call the helper function to find paths starting from the current node
        findSum(root, targetSum, 0);

        // Recursively explore paths in the left and right subtrees
        pathSum(root->left, targetSum);
        pathSum(root->right, targetSum);

        // Return the total count of paths with the target sum
        return ans;
    }
};

// T.C-> N^2


2) Map vala approach, same as array like looking for sum - k before!

class Solution {
public:

    // Variable to store the count of paths with the target sum
    int ans = 0;

    // Recursive function to find paths with the target sum starting from a given node
    void findSum(TreeNode* root, int k, long long currSum, unordered_map<long long, int> &m){
        // Base case: If the node is null, return
        if(!root) return;

        // Update the current sum by adding the value of the current node
        currSum += root->val;

        // If there is a subarray sum (currSum - k) encountered before, increment the answer count
        ans += m[currSum - k];

        // Update the frequency of the current cumulative sum in the map
        m[currSum]++;

        // Recursively explore paths in the left and right subtrees
        findSum(root->left, k, currSum, m);
        findSum(root->right, k, currSum, m);

        // Backtrack: Decrement the frequency of the current cumulative sum and update the current sum
        // right kade jaych ahe na parat yeun (left kadun) tyamule je add kela ahe te kadhava lagel na
        m[currSum]--;
        currSum -= root->val;
    }

    // Function to find paths with the target sum in the entire tree
    int pathSum(TreeNode* root, int k) {
        // Base case: If the root is null, there are no paths
        if(!root) return 0;

        // Initialize an unordered map to store cumulative sums and their frequencies
        unordered_map<long long, int> m;
        // Initialize the map with a dummy entry to account for paths starting from the root
        m[0]++;

        // Initialize the current cumulative sum
        long long currSum = 0;

        // Call the helper function to find paths starting from the current node
        findSum(root, k, currSum, m);

        // Return the total count of paths with the target sum
        return ans;
    }
};

T.C-> N or NlogN (depends on map!, uk)

// OR (not keeping global 'ans' variable, returning count from function itself)
class Solution {
public:
    int findSum(TreeNode* root, int k, long long currSum, unordered_map<long long, int> &m){
        if(!root) return 0;

        currSum += root->val;

        int cnt = m[currSum - k];
        
        m[currSum]++;

        int left = findSum(root->left, k, currSum, m);
        int right = findSum(root->right, k, currSum, m);

        m[currSum]--;

        currSum -= root->val;

        return cnt + left + right;
    }

    int pathSum(TreeNode* root, int k) {

        if(!root) return 0;

        unordered_map<long long, int> m;

        m[0]++;

        long long currSum = 0;

        return findSum(root, k, currSum, m);

    }
};