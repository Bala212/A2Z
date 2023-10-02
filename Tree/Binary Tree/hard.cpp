1) Print Root to Node Path in a Binary Tree
bool getPath(node *root, vector<int> &arr, int x)
{
    // if root is NULL
    // there is no path
    if (!root)
        return false;

    // push the node's value in 'arr'
    arr.push_back(root->data);

    // if it is the required node
    // return true
    if (root->data == x)
        return true;

    // else check whether the required node lies
    // in the left subtree or right subtree of
    // the current node
    bool left = getPath(root->left, arr, x);

    bool right = getPath(root->right, arr, x);

    // Either of them got the node, go on returning true.
    if (left || right)
        return true;

    // required node does not lie either in the
    // left or right subtree of the current node
    // Thus, remove current node's value from
    // 'arr'and then return false
    arr.pop_back();
    return false;
}

vector<int> solve(TreeNode *A, int B)
{
    vector<int> ans;
    if (A == NULL)
        return ans;
    getPath(A, ans, B);
    return ans;
}
Time Complexity: O(N)
Reason: We are doing a simple tree traversal

Space Complexity: O(N)
Reason: In the worst case (skewed tree), space complexity can be O(N).
------------------------------------------------------------------------------------------------------------------------------------------------------------------
2) Lowest Common Ancestor for two given Nodes

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // Base case: If the root is NULL or one of the nodes is the root itself, return the root as it is the LCA.
    if (root == NULL || root == p || root == q) {
        return root;
    }
    
    // Recursively find the lowest common ancestor in the left and right subtrees.
    TreeNode* left = lowestCommonAncestor(root->left, p, q);
    TreeNode* right = lowestCommonAncestor(root->right, p, q);
    
    // Result cases:
    // If the left subtree returns NULL, both p and q are in the right subtree, so return the result from the right subtree.
    if (left == NULL) {
        return right;
    }
    // If the right subtree returns NULL, both p and q are in the left subtree, so return the result from the left subtree.
    if (right == NULL) {
        return left;
    }
    
    // If both left and right are not NULL, we found our result, so return the current root as the LCA.
    return root;6
}

If we get left as NULL that means we didnt found
x or y in left subtree, it may happen that it can be present in right subtree and that
right call will have that x or y, if right found it. Then in this case we will return right
right may be NULL or X or Y. If it is NULL it means that we didnt get x or y in current 
subtree.

Same case is for right call.

This code finds the lowest common ancestor (LCA) of two given nodes `p` and `q` in a binary tree. Here are the comments explaining each part:

1. Base case: If the root is NULL or one of the nodes `p` or `q` is the root itself, return the root as it is the LCA.
2. Recursively find the lowest common ancestor in the left and right subtrees by calling the `lowestCommonAncestor` function.
3. Result cases:
   - If the left subtree returns NULL, both `p` and `q` are in the right subtree, so return the result from the right subtree.
   - If the right subtree returns NULL, both `p` and `q` are in the left subtree, so return the result from the left subtree.
   - If both left and right are not NULL, we found our result, so return the current root as the LCA.

Time complexity: O(N) where n is the number of nodes.
Space complexity: O(N), auxiliary space.

------------------------------------------------------------------------------------------------------------------------------------------------------------------
3) Maximum width of a Binary Tree
Assigning indexes to each node, and calculating width of each level with this indexes
and maximize it always!!
See my notes!!

int widthOfBinaryTree(TreeNode* root) {
    // If the root is NULL, the tree has no width, so return 0.
    if (root == NULL) {
        return 0;
    }

    int ans = 0;
    // Create a queue to perform level order traversal. Each element in the queue is a pair containing the node and its position.
    queue<pair<TreeNode*, int>> q;
    q.push({root, 0});

    while (!q.empty()) {
        // Get the number of nodes at the current level.
        int size = q.size();
        // Get the position of the leftmost node at the current level.
        int mini = q.front().second;
        int first, last;

        // Traverse all nodes at the current level.
        for (int i = 0; i < size; i++) {
            int curr_id = q.front().second;
            TreeNode* node = q.front().first;
            q.pop();

            // If it's the first node at the current level, record its position as 'first'.
            if (i == 0) {
                first = curr_id;
            }
            // If it's the last node at the current level, record its position as 'last'.
            if (i == size - 1) {
                last = curr_id;
            }

            // Push the left child into the queue with the updated position.
            if (node->left != NULL) {
                q.push({node->left, (long long)curr_id * 2 + 1});
            }
            // Push the right child into the queue with the updated position.
            if (node->right != NULL) {
                q.push({node->right, (long long)curr_id * 2 + 2});
            }
        }

        // Calculate the width of the current level and update the maximum width 'ans' if necessary.
        ans = max(ans, last - first + 1);
    }

    // Return the maximum width of the binary tree.
    return ans;
}

Time Complexity: O(N)
Reason: We are doing a simple level order traversal. The inner loop simply traverses the nodes level-wise and doesn’t add to the complexity.

Space Complexity: O(N)
------------------------------------------------------------------------------------------------------------------------------------------------------------------
4) Check for Children Sum Property in a Binary Tree
Go down by increasing values, and while coming (backtracking) update the root values

void changeTree(BinaryTreeNode<int>* root) {
    // If the current node is NULL, return to the caller (base case)
    if (root == NULL) {
        return;
    }

    // Initialize a variable 'childSum' to hold the sum of values of the left and right child nodes
    int childSum = 0;

    // Calculate the sum of values of the left child (if it exists) and add it to 'childSum'
    if (root->left != NULL) {
        childSum += root->left->data;
    }

    // Calculate the sum of values of the right child (if it exists) and add it to 'childSum'
    if (root->right != NULL) {
        childSum += root->right->data;
    }

    // If the sum 'childSum' is greater than the value of the current node, update the current node's value to 'childSum'
    if (childSum > root->data) {
        root->data = childSum;
    }
    else {
        // Otherwise, if the left child exists, update its value to be the same as the parent's value
        if (root->left != NULL) {
            root->left->data = root->data;
        }
        // if the right child exists, update its value to be the same as the parent's value
        if (root->right != NULL) {
            root->right->data = root->data;
        }
    }

    // Recursively call the changeTree function on the left and right child nodes
    changeTree(root->left);
    changeTree(root->right);

    // Initialize a variable 'rootToBe' to hold the sum of values of the left and right child nodes
    int rootToBe = 0;

    // Calculate the sum of values of the left child (if it exists) and add it to 'rootToBe'
    if (root->left != NULL) {
        rootToBe += root->left->data;
    }

    // Calculate the sum of values of the right child (if it exists) and add it to 'rootToBe'
    if (root->right != NULL) {
        rootToBe += root->right->data;
    }

    // If at least one child exists, update the current node's value to be the sum 'rootToBe'
    // If both left and right are null, then we will end up with assigning 0 to root.
    if (root->left || root->right) {
        root->data = rootToBe;
    }
}

Time Complexity: O(N)
Reason: We are doing a simple tree traversal.

Space Complexity: O(N)
Reason: In the worst case( skewed tree), space complexity can be O(N).
------------------------------------------------------------------------------------------------------------------------------------------------------------------
5) Print all the Nodes at Distance K in Binary Tree

1) Mark parent of each node using level order traversal.
2) Keep on moving by 1 distance everytime (upward, left and right) using BFS
travrersal.
3) When we move k distance, we stop and return the elements inside the queue
as we are pushing the upward, leftward and rightward nodes into the queue in 
each iteration.

void markParents(TreeNode* root, unordered_map<TreeNode*, TreeNode*>& parent) {
    // Create a queue to perform a level order traversal
    queue<TreeNode*> q;
    q.push(root);

    // Perform level order traversal to mark parent nodes
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        
        // If the left child exists, mark its parent as 'node' and push it into the queue
        if (node->left != NULL) {
            parent[node->left] = node;
            q.push(node->left);
        }
        
        // If the right child exists, mark its parent as 'node' and push it into the queue
        if (node->right != NULL) {
            parent[node->right] = node;
            q.push(node->right);
        }
    }
}

vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
    // Create an unordered map to store the parent nodes of each node
    unordered_map<TreeNode*, TreeNode*> parent;
    
    // Mark the parent nodes using the markParents function
    markParents(root, parent);

    // Create a queue to perform a level order traversal
    queue<TreeNode*> q;
    q.push(target);
    
    // Create an unordered map to track visited nodes
    unordered_map<TreeNode*, bool> vis;
    vis[target] = true;
    
    int count = 0;
    
    // Perform a level order traversal until the desired distance 'k' is reached
    while (!q.empty()) {
        int size = q.size();
        
        // If the desired distance 'k' is reached, exit the loop
        if (count == k) {
            break;
        }
        
        // Process all nodes at the current level
        for (int i = 0; i < size; i++) {
            TreeNode* node = q.front();
            q.pop();
            
            // If the left child exists and has not been visited, add it to the queue and mark it as visited
            if (node->left != NULL && !vis[node->left]) {
                q.push(node->left);
                vis[node->left] = true;
            }
            
            // If the right child exists and has not been visited, add it to the queue and mark it as visited
            if (node->right != NULL && !vis[node->right]) {
                q.push(node->right);
                vis[node->right] = true;
            }
            
            // If the parent node exists and has not been visited, add it to the queue and mark it as visited
            if (parent[node] != NULL && !vis[parent[node]]) {
                q.push(parent[node]);
                vis[parent[node]] = true;
            }
        }
        
        count++;
    }

    // Extract the values of nodes at the desired distance 'k' and store them in the answer vector
    vector<int> ans;
    while (!q.empty()) {
        ans.push_back(q.front()->val);
        q.pop();
    }
    
    return ans;
}

Time Complexity: O(N)
Reason: We are doing a simple tree traversal.

Space Complexity: O(N)
Reason: Queue, map!!
------------------------------------------------------------------------------------------------------------------------------------------------------------------
6) Time To Burn Tree
https://www.codingninjas.com/studio/problems/time-to-burn-tree_630563

1) Similar to previous question.
2) map parents.
3) Whenever we push node into queue, we actually burned it.
4) Increase time only when we burn any node.

BinaryTreeNode<int>* mapParent(BinaryTreeNode<int>* root, unordered_map<BinaryTreeNode<int>*, BinaryTreeNode<int>*>& parent, int start) {
    // Create a queue to perform a level order traversal
    queue<BinaryTreeNode<int>*> q;
    q.push(root);
    
    // Create a variable to store the starting node
    BinaryTreeNode<int>* startingNode;
    
    // Perform level order traversal to mark parent nodes and find the starting node
    while (!q.empty()) {
        BinaryTreeNode<int>* node = q.front();
        q.pop();
        
        // If the node's data matches the 'start' value, assign it as the starting node
        if (node->data == start) {
            startingNode = node;
        }
        
        // If the left child exists, mark its parent as 'node' and push it into the queue
        if (node->left != NULL) {
            parent[node->left] = node;
            q.push(node->left);
        }
        
        // If the right child exists, mark its parent as 'node' and push it into the queue
        if (node->right != NULL) {
            parent[node->right] = node;
            q.push(node->right);
        }
    }
    
    return startingNode;
}

int timeToBurnTree(BinaryTreeNode<int>* root, int start) {
    // Create an unordered map to store the parent nodes of each node
    unordered_map<BinaryTreeNode<int>*, BinaryTreeNode<int>*> parent;
    
    // Find the starting node and map the parent nodes using the mapParent function
    BinaryTreeNode<int>* startingNode = mapParent(root, parent, start);
    
    // Create a queue to perform a level order traversal
    queue<BinaryTreeNode<int>*> q;
    q.push(startingNode);
    
    // Create an unordered map to track burned nodes
    unordered_map<BinaryTreeNode<int>*, bool> burned;
    burned[startingNode] = true;
    
    int time = 0;
    
    // Perform a level order traversal until all reachable nodes are burned
    while (!q.empty()) {
        int size = q.size();
        bool burnAny = false;
        
        // Process all nodes at the current level
        for (int i = 0; i < size; i++) {
            BinaryTreeNode<int>* node = q.front();
            q.pop();
            
            // If the left child exists and has not been burned, mark it as burned and add it to the queue
            if (node->left != NULL && !burned[node->left]) {
                burnAny = true;
                burned[node->left] = true;
                q.push(node->left);
            }
            
            // If the right child exists and has not been burned, mark it as burned and add it to the queue
            if (node->right != NULL && !burned[node->right]) {
                burnAny = true;
                burned[node->right] = true;
                q.push(node->right);
            }
            
            // If the parent node exists and has not been burned, mark it as burned and add it to the queue
            if (parent[node] != NULL && !burned[parent[node]]) {
                burnAny = true;
                burned[parent[node]] = true;
                q.push(parent[node]);
            }
        }
        
        // If any node was burned at the current level, increment the time
        if (burnAny) {
            time++;
        }
    }
    
    return time;
}Time Complexity: O(N)
Reason: We are doing a simple tree traversal.

Space Complexity: O(N)
Reason: Queue, map!!
------------------------------------------------------------------------------------------------------------------------------------------------------------------
7) Count Complete Tree Nodes

Given tree is CBT.

Approach 1: O(N) using any traversal, here preorder.
void getCount(TreeNode* root, int& count) {
    // Base case: If the current node is NULL, return to the caller
    if (root == NULL) {
        return;
    }

    // Increment the count for each visited node
    count++;

    // Recursively traverse the left and right subtrees
    getCount(root->left, count);
    getCount(root->right, count);
}

int countNodes(TreeNode* root) {
    // Base case: If the root is NULL, the tree is empty, so return 0
    if (root == NULL) {
        return 0;
    }

    int ans = 0;
    
    // Call the getCount function to count the number of nodes in the tree
    getCount(root, ans);

    // Return the count of nodes
    return ans;
}

Approach2: Using property of CBT
1) If H is the height of CBT and last level has all the nodes, then the total number 
of nodes in that CBT are 2^H - 1.

2) If leftHeight == rightHeight, then tree is CBT and no. of nodes are 2^H-1

3) Else, last level is not completely filled, so recursively call the same function
to calculate the nodes in left subtree and right subtree and return
1 + leftNodes + rightNodes.

int leftHeight(TreeNode *root)
{
    int h = 0;
    // Traverse the left subtree and increment the height until reaching the leftmost leaf node
    while (root != NULL)
    {
        h++;
        root = root->left;
    }
    return h;
}

int rightHeight(TreeNode *root)
{
    int h = 0;
    // Traverse the right subtree and increment the height until reaching the rightmost leaf node
    while (root != NULL)
    {
        h++;
        root = root->right;
    }
    return h;
}

int countNodes(TreeNode *root)
{
    // Base case: If the root is NULL, the tree is empty, so return 0
    if (root == NULL)
    {
        return 0;
    }

    // Get the height of the left and right subtrees
    int lh = leftHeight(root);
    int rh = rightHeight(root);

    // If the left and right heights are equal, the tree is a perfect binary tree, so return the count directly using the formula (2^h) - 1
    if (lh == rh)
    {
        return (1 << lh) - 1;
    }

    // If the left and right heights are not equal, recursively count the nodes in the left and right subtrees
    // Find number of nodes in left subtree and right subtree using the same function.
    int leftNodes = countNodes(root->left);
    int rightNodes = countNodes(root->right);

    // Return the total count of nodes, which is the sum of the root node and the counts from the left and right subtrees
    return 1 + leftNodes + rightNodes;
}
Time Complexity: O(log^2 N).
Reason: To find the leftHeight and right Height we need only logN time and in the worst case we will encounter the 
second case(leftHeight!=rightHeight) for at max logN times, so total time complexity will be O(log N * logN)

Space Complexity: O(logN)
Reason: Space is needed for the recursion stack when calculating height. As it is a complete tree, the height will always be logN.
------------------------------------------------------------------------------------------------------------------------------------------------------------------
8) Requirements needed to construct a binary tree

a) If we are given preorder and postorder, we cannot generate a unique binary tree.
We can generate treees, but not a unique one!!

b) We can produce unique binary trees from inorder and preorder or postorder!!

c) There should be a inorder given to produce a unique binary tree.
------------------------------------------------------------------------------------------------------------------------------------------------------------------
9) Construct A Binary Tree from Inorder and Preorder Traversal

a) Hash indexes of inorder to access root index anytime.
b) Create a node with root( start index of preorder)
c) calculate number of left subtree nodes
d) Call the next recursive functions with their proper indexes, for left and right subtree.
See my notes for better understanding!!

TreeNode* constructTree(vector<int>& inorder, int inStart, int inEnd, vector<int>& preorder, int preStart, int preEnd, map<int,int>& indexOf) {
    // Base case: If the start index is greater than the end index for either the inorder or preorder arrays, return NULL
    if (inStart > inEnd || preStart > preEnd) {
        return NULL;
    }

    // Create a new TreeNode with the value from the current position in the preorder array as the root
    TreeNode* root = new TreeNode(preorder[preStart]);

    // Find the index of the root value in the inorder array
    int rootIndex = indexOf[preorder[preStart]];

    // Calculate the number of elements in the left subtree
    int leftTreeElements = rootIndex - inStart;

    // Recursively construct the left subtree by passing the appropriate indices for the inorder and preorder arrays
    root->left = constructTree(inorder, inStart, rootIndex - 1, preorder, preStart + 1, preStart + leftTreeElements, indexOf);

    // Recursively construct the right subtree by passing the appropriate indices for the inorder and preorder arrays
    root->right = constructTree(inorder, rootIndex + 1, inEnd, preorder, preStart + leftTreeElements + 1, preEnd, indexOf);

    // Return the constructed root node
    return root;
}

TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    // Initialize the start and end indices for the inorder and preorder arrays
    int inStart = 0, preStart = 0;
    int inEnd = inorder.size() - 1;
    int preEnd = preorder.size() - 1;

    // Create a map to store the indices of values in the inorder array
    unordered_map<int, int> indexOf;

    // Populate the map with the indices of values in the inorder array
    for (int i = inStart; i <= inEnd; i++) {
        indexOf[inorder[i]] = i;
    }

    // Construct and return the tree using the constructTree function
    return constructTree(inorder, inStart, inEnd, preorder, preStart, preEnd, indexOf);
}
Time Complexity: O(N)
Assumption: Hashmap returns the answer in constant time.

Space Complexity: O(N)
Reason: We are using an external hashmap of size ‘N’.
------------------------------------------------------------------------------------------------------------------------------------------------------------------
10) Construct A Binary Tree from Inorder and Postorder Traversal
The whole approach is same as preorder, just the pointers will change.
See my notes for the same, the only change is in post order pointers.

Once we get number of left elements, we can find other indexes easily!!!!


TreeNode* construct(vector<int>& inorder, int inStart, int inEnd, vector<int>& postorder, int postStart, int postEnd, unordered_map<int, int>& m) {
    // Base case: If the start index is greater than the end index for either the inorder or postorder arrays, return NULL
    if (inStart > inEnd || postStart > postEnd) {
        return NULL;
    }

    // Create a new TreeNode with the value from the current position in the postorder array as the root
    TreeNode* root = new TreeNode(postorder[postEnd]);

    // Find the index of the root value in the inorder array
    int rootIndex = m[postorder[postEnd]];

    // Calculate the number of elements in the left subtree
    int leftTreeElements = rootIndex - inStart;

    // Recursively construct the left subtree by passing the appropriate indices for the inorder and postorder arrays
    root->left = construct(inorder, inStart, rootIndex - 1, postorder, postStart, postStart + leftTreeElements - 1, m);

    // Recursively construct the right subtree by passing the appropriate indices for the inorder and postorder arrays
    root->right = construct(inorder, rootIndex + 1, inEnd, postorder, postStart + leftTreeElements, postEnd - 1, m);

    // Return the constructed root node
    return root;
}

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    // Initialize the start and end indices for the inorder and postorder arrays
    int inStart = 0, inEnd = inorder.size() - 1;
    int postStart = 0, postEnd = postorder.size() - 1;

    // Create an unordered map to store the indices of values in the inorder array
    unordered_map<int, int> m;

    // Populate the map with the indices of values in the inorder array
    for (int i = 0; i <= inEnd; i++) {
        m[inorder[i]] = i;
    }

    // Construct and return the tree using the construct function
    return construct(inorder, inStart, inEnd, postorder, postStart, postEnd, m);
}
Time Complexity: O(N)
Assumption: Hashmap returns the answer in constant time.

Space Complexity: O(N)
Reason: We are using an external hashmap of size ‘N’.
------------------------------------------------------------------------------------------------------------------------------------------------------------------
11) Serialize And Deserialize a Binary Tree
See notes!!

// Encodes a tree to a single string.
string serialize(TreeNode* root) {
    // Base case: If the root is NULL, return an empty string
    if (root == NULL) {
        return "";
    }

    string ans = "";

    // Create a queue to perform a level order traversal
    queue<TreeNode*> q;
    q.push(root);

    // Perform level order traversal to serialize the tree
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        // If the current node is NULL, append "#" to the string
        if (node == NULL) {
            ans.append("#,");
        }
        // Otherwise, append the value of the current node to the string
        else {
            ans.append(to_string(node->val) + ',');
        }

        // If the current node is not NULL, enqueue its left and right children
        // As we have to process NULL value too, we are not checking for left and right as NULL
        if (node != NULL) {
            q.push(node->left);
            q.push(node->right);
        }
    }

    return ans;
}

// Decodes your encoded data to tree.
TreeNode* deserialize(string data) {
    // Base case: If the input string is empty, return NULL
    if (data.size() == 0) {
        return NULL;
    }

    // Create a stringstream to parse the input string
    stringstream s(data);
    string str;
    // getline is a function that reads a line of input from a specified input stream and stores it into a string
    // variable. It is part of the <string> library.
    getline(s, str, ',');

    // Create the root node using the first value in the string
    TreeNode* root = new TreeNode(stoi(str));

    // Create a queue to reconstruct the tree from the serialized string
    queue<TreeNode*> q;
    q.push(root);

    // Reconstruct the tree using the serialized string
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        // Attach the next character in the string as the left child
        getline(s, str, ',');
        if (str == "#") {
            // # means left child is NULL
            node->left = NULL;
        }
        else {
            // create a node, and attach to left
            TreeNode* leftNode = new TreeNode(stoi(str));
            node->left = leftNode;
            // Push the created node into queue to attach left and right of this node further
            q.push(leftNode);
        }

        // Attach the next character in the string as the right child
        getline(s, str, ',');
        if (str == "#") {
            node->right = NULL;
        }
        else {
            // create a node, and attach to right
            TreeNode* rightNode = new TreeNode(stoi(str));
            node->right = rightNode;
            // Push the created node into queue to attach left and right of this node further
            q.push(rightNode);
        }
    }

    return root;
}

Time Complexity: O(N)
Space Complexity: O(N)
------------------------------------------------------------------------------------------------------------------------------------------------------------------
12) Morris Inorder Traversal of a Binary Tree

The Morris Inorder Traversal algorithm is an efficient way to traverse a binary tree without using 
recursion or an explicit stack. It allows us to visit each node in the tree in the order of an inorder traversal.

The intuition behind the Morris Inorder Traversal can be summarized as follows:

1. Start at the root of the tree.
2. Initialize a pointer called `current` to the root.
3. While `current` is not NULL:
   a) If `current` does not have a left child:
     - Push the current node, as it does not have left child, so it will be printed and then move to right
     - Move to the right child (`current = current->right`).
   b) If `current` has a left child:
     - Before moving to left node, make connection of current node and the node where the left inorder will end, so that we can come to current node again
       to print the root/current node
     - Find the rightmost node in the left subtree of `current`. This node is the rightmost node in the 
       left subtree or the rightmost node of the right subtree of the left child of `current`, at which the inorder of left tree will end!!
     b1) If the rightmost node's right child is NULL: ( Mark the thread)
       - Means there is no previous link between right most node and current node, so create it and then move to left!!
       - Set the right child of the rightmost node to `current`.
       - Move to the left child (`current = current->left`).
     b2) If the rightmost node's right child is `current`: (Remove the thread)
       - Means there were link already there, so remove it
       - Restore the tree structure by setting the right child of the rightmost node to NULL.
       - Push the current node, as we come to the end of inorder traversal of left subtree, bcoz we are at the rightmost node where te inorder of left ended.
       - and we noe have to go the root, which we will be getting by current node through link. Once we push the current node, move to right.
       - Move to the right child (`current = current->right`).

By using this algorithm, we can traverse the tree in an inorder manner without using a separate stack
or recursive calls. The algorithm utilizes the right child pointers in the tree to navigate and then restore the original structure of the tree.

In simple terms, the Morris Inorder Traversal algorithm allows us to traverse a binary tree without extra 
memory and without changing the structure of the tree. It takes advantage of the unused right child pointers
to create temporary connections that enable us to move through the tree in the desired order.

vector<int> inorderTraversal(TreeNode* root) {
    // Create an empty vector to store the inorder traversal result
    vector<int> ans;

    // Start with the root node
    TreeNode* curr = root;

    // Traverse the tree using the Morris Inorder Traversal algorithm
    while (curr != NULL) {
        // If the current node does not have a left child:
        if (curr->left == NULL) {
            // Visit the node (add its value to the result vector)
            ans.push_back(curr->val);
            // Move to the right child
            curr = curr->right;
        }
        // If the current node has a left child:
        else {
            // Find the rightmost node in the left subtree
            TreeNode* temp = curr->left;
            // Loop till temps's next is NULL or curr/root node  
            while (temp->right != NULL && temp->right != curr) {
                temp = temp->right;
            }

            // If the rightmost node's right child is NULL:
            if (temp->right == NULL) {
                // Create a temporary connection by setting the right child of the rightmost node to the current node
                temp->right = curr;
                // Move to the left child
                curr = curr->left;
            }
            // If the rightmost node's right child is the current node (the temporary connection already exists):
            else { //temp->right == curr, means we reach the end of left inorder ( left call of current node)
                // Remove the temporary connection by setting the right child of the rightmost node to NULL
                temp->right = NULL;
                //Push the current node as we have reach the end of inorder of left subtree
                ans.push_back(curr->val);
                // Move to the right child
                curr = curr->right;
            }
        }
    }

    // Return the inorder traversal result
    return ans;
}

Time Complexity: O(N).

Space Complexity: O(1)

------------------------------------------------------------------------------------------------------------------------------------------------------------------
13) Morris Preorder Traversal of a Binary Tree

The Morris Preorder Traversal is a smart algorithm for visiting all the nodes of a binary tree 
in a specific order called preorder. What makes it special is that it doesn't require recursion 
or additional space, like a stack, to accomplish this traversal.

Here's how it works in a simple way:
1. Start with the root node of the binary tree.
2. While there are still nodes to visit:
   a. If the current node has no left child, push the node as it will be root node na!! and move to its right child.
   b. If the current node has a left child, find the rightmost node in its left subtree. ( We will push the current node/root node into ans while forming the chain)
      - If the rightmost node doesnt have a right child means there is no previous chain i.e. left part is not visited yet so first visit root/current node
        and then move to left i.e. make a temporary link from it to the current node. Visit the current node and move to its left child.
      - If the rightmost node already has a right child (linked back to the current node) i.e. we have finished the left traversal no move towards right
        i.e break the link and move to the right child of the current node.
3. Repeat steps 2a and 2b until all nodes have been visited.

By establishing and breaking these temporary links, the algorithm ensures that each node is visited exactly once, 
following the preorder order: current node, left child, right child.

The Morris Preorder Traversal is a clever technique because it allows us to traverse a binary tree in the 
desired order without using recursion or additional space. This can be helpful in situations where memory usage 
is a concern or when recursion or stacks are not preferred.

vector<int> preorderTraversal(TreeNode *root)
{
    // Create an empty vector to store the preorder traversal result
    vector<int> ans;

    // Set the current node as the root of the tree
    TreeNode *curr = root;

    // Traverse the tree using Morris Preorder Traversal
    while (curr != NULL)
    {
        // If the current node has no left child:
        if (curr->left == NULL)
        {
            // Push the current node  and move to its right child
            ans.push_back(curr->val);
            curr = curr->right;
        }
        // If the current node has a left child:
        else
        {
            // Find the rightmost node in the left subtree
            TreeNode *temp = curr->left;
            while (temp->right != NULL && temp->right != curr)
            {
                temp = temp->right;
            }

            // If the rightmost node doesn't have a right child:
            if (temp->right == NULL)
            {
                // Establish a temporary link from it to the current node
                temp->right = curr;
                // Push the current node, as it will be the first time we ae visiting the root!!
                // We push the root node when we are creating the chain!!
                ans.push_back(curr->val);
                // Move to the left child
                curr = curr->left;
            }
            // If the rightmost node already has a right child: We have done with left preorder so let's move to right
            // as we have push the root node before only, while creating the linkage
            else
            {
                // Break the link and move to the right child of the current node
                temp->right = NULL;
                curr = curr->right;
            }
        }
    }
    // Return the preorder traversal result
    return ans;
}

Time Complexity: O(N)
Space Complexity: O(1)

------------------------------------------------------------------------------------------------------------------------------------------------------------------
14)