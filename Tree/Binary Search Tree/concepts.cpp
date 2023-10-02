Intro:https://takeuforward.org/data-structure/binary-search-tree-bst-introduction/

1) Binary Search Trees: Given a Inorder of BST, tell whether it is a BST or not.

bool isValidBST(vector<int> &order) {
    // Inorder traversal of BST is always in sorted manner
    
    // Iterate through the order vector
    for (int i = 0; i < order.size() - 1; i++) {
        
        // Check if the current element is greater than or equal to the next element
        if (order[i] >= order[i + 1])
            return false; // Not a valid BST
        
    }
    
    return true; // Valid BST
}

Time complexity:O(N)
Space complexity: O(1)

---------------------------------------------------------------------------------------------------------------------------
2) Search in a Binary Search Tree

#Approach1: While loop

TreeNode* searchBST(TreeNode* root, int val) {
    // Perform a search for a given value in a Binary Search Tree (BST)

    // Iterate through the tree while the current node is not NULL and the value is not found
    while (root != NULL && root->val != val) {
        
        // If the given value is less than the value of the current node, move to the left subtree
        if (val < root->val)
            root = root->left;
        
        // If the given value is greater than the value of the current node, move to the right subtree
        else
            root = root->right;
    }
    
    // Return the node containing the value if found, or NULL if the value is not present in the BST
    return root;
}
Time complexity:O(logN) (We won’t traverse in the whole tree )
Space complexity: O(1)

#Approach2: Recursive

TreeNode* searchBST(TreeNode* root, int val) {
    // Search for a given value in a Binary Search Tree (BST) recursively

    // Create a temporary pointer
    TreeNode* temp;

    // Base cases:
    // If the root is NULL or its value matches the target value, return the root
    if (root == NULL || root->val == val)
        return root;

    // Recursive cases:
    // If the target value is less than the value of the current node, search in the left subtree
    else if (val < root->val)
        temp = searchBST(root->left, val);

    // If the target value is greater than the value of the current node, search in the right subtree
    else
        temp = searchBST(root->right, val);

    // Return the result of the recursive search
    return temp;
}
Time complexity:O(logN) (We won’t traverse in the whole tree )
Space Complexity: O(N) (worst space complexity because we are using Recursion)

---------------------------------------------------------------------------------------------------------------------------
3) Minimum value in a Binary Search Tree
int minVal(Node* root) {
    // Find the minimum value in a Binary Search Tree (BST)

    // If the root is NULL, return -1 (indicating an empty tree)
    if (root == NULL)
        return -1;

    // Create a temporary pointer and initialize it with the root
    Node* temp = root;

    // Traverse to the leftmost node (which contains the minimum value)
    while (temp->left != NULL) {
        temp = temp->left;
    }

    // Return the data value of the leftmost node (minimum value)
    return temp->data;
}

Time complexity:O(logN) we are traversing height of BST.
Space complexity: O(1)

---------------------------------------------------------------------------------------------------------------------------
4) Maximum value in a Binary Search Tree

For maximum we will search on right, instead of left!!

***************************************************************************************************************************