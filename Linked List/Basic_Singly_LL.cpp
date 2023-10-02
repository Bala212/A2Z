// 1.Construct a linked list from array!!
Node *constructLL(vector<int> &arr)
{
    // code here
    if (arr.size() == 0)
        return NULL;
    Node *temp = new Node(arr[0]);
    Node *head = temp;
    for (int i = 1; i < arr.size(); i++)
    {
        Node *node = new Node(arr[i]);
        temp->next = node;
        temp = node;
    }
    return head;
}
//! T.C -> O(N)
//! S.C -> O(N)
// --------------------------------------------------------------------------------------------------

// 2. Insertions in linked list
// Function to insert a node at the beginning of the linked list.
Node *insertAtBegining(Node *head, int x)
{
    // Create a node with data x
    Node *node = new Node(x);

    // If there is no linked list, return node created
    if (head == NULL)
        return node;

    // Point next of created node to head
    node->next = head;

    // Point head to created node
    head = node;

    // return the linked list
    return head;
}
// T.C -> O(1)
// S.C -> O(1)

// Function to insert a node at the end of the linked list.
Node *insertAtEnd(Node *head, int x)
{
    // Create a node with data x
    Node *node = new Node(x);

    // If there is no linked list, return node created
    if (head == NULL)
        return node;

    // Go to end of linked list
    Node *tail = head;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }

    // Tail's nect should point to created node
    tail->next = node;

    // Return the linked list
    return head;
}
//! T.C -> O(N)
//! S.C -> O(1)
// --------------------------------------------------------------------------------------------------
// 3. Delete in linked list
// At position
Node *deleteNode(Node *head, int x)
{
    // Your code here
    Node *temp = head;
    // deleta at 1st position
    if (x == 1)
    {
        // Point head to next of head
        head = temp->next;
        temp->next = NULL;
        delete temp;
    }
    // Delete at Middle or End
    else
    {
        // We have to move 1 step before position and currently we are at head
        for (int i = 0; i < x - 2; i++)
        {
            temp = temp->next;
        }

        // Delete logic
        Node *nodeToDelete = temp->next;
        temp->next = nodeToDelete->next;
        nodeToDelete->next = NULL;
        delete nodeToDelete;
    }
    return head;
}
// T.C -> O(x)
// S.C -> O(1)
// Just a node is given and all elements are unique, No access to head!!
void deleteNode(ListNode *node)
{
    // Copy the value of next node in node to be deleted
    node->val = node->next->val;
    // Delete the next node of given node
    node->next = node->next->next;
}
//! T.C -> O(1)
//! S.C -> O(1)
// --------------------------------------------------------------------------------------------------
// 4.Count nodes of linked list
int getCount(struct Node *head)
{
    // Code here
    int cnt = 0;
    while (head != NULL)
    {
        head = head->next;
        cnt++;
    }
    return cnt;
}
// T.C -> O(N)
// S.C -> O(1)
// --------------------------------------------------------------------------------------------------
// 5.Search an element in the Linked List
bool searchKey(int n, struct Node *head, int key)
{
    // Code here
    while (head != NULL)
    {
        if (head->data == key)
            return 1;
        head = head->next;
    }
    return 0;
}
// T.C -> O(N)
// S.C -> O(1)