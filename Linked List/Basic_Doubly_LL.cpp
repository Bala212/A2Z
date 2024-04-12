// 1.Introduction to Doubly Linked List
Node *constructDLL(vector<int> &arr)
{
    // Create first node with value as first element of array
    Node *ans = new Node(arr[0]);

    // a pointer to link another nodes
    Node *temp = ans;

    // traverse, create and link nodes
    for (int i = 1; i < arr.size(); i++)
    {
        // create a node
        Node *node = new Node(arr[i]);

        // link next pointer of last node with newly created node
        temp->next = node;

        // link prev pointer of newly created node with last node of list
        node->prev = temp;

        // move forward, last node becomes the newly created node
        temp = node;
    }

    // Return the DLL created
    return ans;
}
// Time Complexity: O(N)
// Space Complexity: O(1)
------------------------------------------------------------------------------------------------
2.Doubly linked list Insertion at given position

void addNode(Node *head, int pos, int data)
{
    // Go till pos-1 node
    Node *temp = head;
    for (int i = 0; i < pos; i++)
    {
        temp = temp->next;
    }

    // Node at 'pos' will be next node of data after insertion
    Node *nextOfPos = temp->next;

    // Create a node with given data
    Node *node = new Node(data);

    // Join prev and next links, take pen and paper
    temp->next = node;
    node->prev = temp;
    node->next = nextOfPos;
    if (nextOfPos != NULL)
        nextOfPos->prev = node;
}
// Time Complexity: O(pos)
// Space Complexity: O(1)
------------------------------------------------------------------------------------------------
4. Reverse a DLL

Node *reverseDLL(Node *head)
{
    // Declare two pointers, one at 1st another at 2nd node
    Node *ptr1 = head;
    Node *ptr2 = head->next;

    // change pointers of 1st node (mandotary)
    ptr1->next = NULL;
    ptr1->prev = ptr2;

    // change pointers of rest of the nodes
    while (ptr2 != NULL)
    {

        // change pointers of current node
        // prev will point to next node of current node
        ptr2->prev = ptr2->next; // order matters!!
        // next will point to previos node, which is ptr1
        ptr2->next = ptr1;

        // move forward
        ptr1 = ptr2;
        // address of node next to ptr2 is stored in ptr2's prev
        ptr2 = ptr2->prev;
    }

    // ptr1 will be head of reversed DLL i.e last node!
    return ptr1;
}
// Time Complexity: O(N)
// Space Complexity: O(1)