// 1.Reverse LL in group of given size K
int length(ListNode *head)
{
    int len = 0;
    while (head != NULL)
    {
        head = head->next;
        len++;
    }
    return len;
}

ListNode *reverseKGroup(ListNode *head, int k)
{
    if (head == NULL)
        return NULL;

    // if length of current LL to be reversed is less than k, return head as it is
    if (length(head) < k)
        return head;

    // Reverse k nodes
    ListNode *prev = NULL;
    ListNode *curr = head;
    // We declare next here bcoz we want it further outside while loop
    ListNode *next = NULL;

    int cnt = 0;
    while (curr != NULL && cnt < k)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        cnt++;
    }

    // If there is any list further, Reverse it and attach to next of head( head will be pointing to
    // end of reversed list)
    if (next != NULL)
    {
        head->next = reverseKGroup(next, k);
    }

    // Prev will be pointing to the reversed LL's head
    return prev;
}
// Time complexity -> O(N)
// Space complexity -> O(N)
// --------------------------------------------------------------------------------------------------
// 2. Rotate LL to right by k places
ListNode *rotateRight(ListNode *head, int k)
{
    // If LL is empty
    if (head == NULL)
        return NULL;

    // Link last node to first node, and calculate length too
    int len = 1;
    ListNode *temp = head;
    while (temp->next != NULL)
    {
        temp = temp->next;
        len++;
    }
    // Pont last node to head/first node
    temp->next = head;

    // if k>len drop it to actual rotation needed
    k = k % len;

    // Get the ( len-k)th node, we have to point it to NULL, before that set
    // next of this node to head because, that will be the head of rotated linked list
    ListNode *ptr = head;
    for (int i = 1; i < len - k; i++)
    {
        ptr = ptr->next;
    }

    // Make head as next node of ptr
    head = ptr->next;

    // point ptr to NULL
    ptr->next = NULL;

    // return updated head
    return head;
}
// Time Complexity: O(length of list) + O(length of list – (length of list%k))
// Space Complexity: O(1)
// --------------------------------------------------------------------------------------------------
// 3.Flattening a Linked List
Node *merge(Node *l1, Node *l2)
{
    // THIS IS FUNCTION OF 'MERGE TWO SORTED LINKED LIST'
    if (l1 == NULL)
        return l2;
    if (l2 == NULL)
        return l1;

    if (l1->data > l2->data)
    {
        swap(l1, l2);
    }

    Node *ans = l1;

    // Merge using bottom pointers
    while (l1 != NULL && l2 != NULL)
    {
        Node *temp = NULL;
        while (l1 != NULL && l1->data <= l2->data)
        {
            temp = l1;
            l1 = l1->bottom;
        }
        temp->bottom = l2;
        swap(l1, l2);
    }
    return ans;
}

Node *flatten(Node *root)
{
    // If root is null or root reaches at end or there in single node return it
    if (root == NULL || root->next == NULL)
        return root;

    // Go for list on right
    root->next = flatten(root->next);

    // Now return merged list to previous call
    return merge(root, root->next);

    // Just dry run it!!
}
// Time Complexity: O(N), where N is the total number of nodes present
// Reason: We are visiting all the nodes present in the given list.
// Space Complexity: O(1)
// --------------------------------------------------------------------------------------------------
// 4.Clone Linked List with Random and Next Pointer
// USING MAP
Node *copyRandomList(Node *head)
{

    // A map to create copy of nodes
    unordered_map<Node *, Node *> m;

    Node *temp = head;

    // Create a exact copy of original LL, with linking next and random pointers
    while (temp != NULL)
    {
        Node *newNode = new Node(temp->val);
        m[temp] = newNode;
        temp = temp->next;
    }

    temp = head;

    // Link next and random pointers!
    while (temp != NULL)
    {

        // get clonedNode of original node
        Node *clonedNode = m[temp];
        // link next and random pointers, check for null as well

        // link next of clonedNode to copy of next of original node which is in cloned LL
        if (temp->next != NULL)
            clonedNode->next = m[temp->next];
        else
            clonedNode->next = NULL;

        // link random of clonedNode to copy of random of original node which is in cloned LL
        if (temp->random != NULL)
            clonedNode->random = m[temp->random];
        else
            clonedNode->random = NULL;

        // move ahead
        temp = temp->next;
    }

    // return copy of head
    return m[head];
}
// Time Complexity: O(N)+O(N)
// Space Complexity: O(N) ->Map

// Using Just pointers No extra space
Node *copyRandomList(Node *head)
{

    // Declare two pointers, one to create a copy and another to keep track further LL
    Node *iter = head;
    Node *front = head;

    // STEP 1 -> INSERT COPY NODES

    // Create copy nodes and inster them alternatively
    while (iter != NULL)
    {
        // Store next node of current node for further execution
        front = iter->next;

        // create a new copy of node ro insert it between current node and next node
        Node *copyNode = new Node(iter->val);

        // Insert krdo!
        iter->next = copyNode;
        copyNode->next = front;

        // move further
        iter = front;
    }

    // STEP 2 -> LINK RANDOM POINTERS OF COPY NODES
    iter = head;
    // Iterate till iter becomes NULL
    while (iter != NULL)
    {
        // If current node's random is nor NULL, link random pointers of copy node
        // which is just next to current node with next of random pointer of current node
        if (iter->random != NULL)
        {
            iter->next->random = iter->random->next;
        }
        // move current pointer by two steps (skipping copy nodes)
        iter = iter->next->next;
    }

    // STEP 3 -> LINK NEXT POINTERS OF COPY NODES AND ORIGINAL NODES

    // Create a dummy node, to return the ans LL at last
    Node *ans = new Node(0);
    Node *copy = ans;
    iter = head;
    while (iter != NULL)
    {

        // Store next original node in front
        front = iter->next->next;

        // Connect the next pointer of copy node, which is iter's (original LL's) next
        copy->next = iter->next;

        // Connext next pointers of original LL
        iter->next = front;

        // Move copyt pointer ahed
        copy = copy->next;

        // Move iter (original LL's ptr) ahead
        iter = front;
    }

    // Return the head of copy node
    return ans->next;
}
// Time Complexity: O(N)+O(N)+O(N)
// Space Complexity: O(1)