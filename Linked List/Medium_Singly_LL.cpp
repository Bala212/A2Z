// 1. Print linked list from END
// Tail recursion!
void printReverse(Node *root)
{
    if (root == NULL)
        return;
    printReverse(root->next);
    cout << root->data;
}
// T.C -> O(N) -> N states of recursion
// S.C -> O(N) -> Recursion stack
// ----------------------------------------------------------------------------
// 2.Middle of the Linked List
ListNode *middleNode(ListNode *head)
{
    int l = 0;
    ListNode *temp = head;
    while (temp != NULL)
    {
        l++;
        temp = temp->next;
    }

    temp = head;
    int t = l / 2;
    while (t--)
    {
        temp = temp->next;
    }
    return temp;
}
// T.C -> O(N+N/2)
// S.C -> O(1)
ListNode *middleNode(ListNode *head)
{
    ListNode *fast = head;
    ListNode *slow = head;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
// T.C -> O(N/2)
// S.C -> O(1)
// --------------------------------------------------------------------------------------------------

// 3. Reverse linked list [Iterative]
ListNode *reverseList(ListNode *head)
{
    // A LL with no node or single node
    if (head == NULL || head->next == NULL)
        return head;
    // Declare two pointers prev and curr
    ListNode *prev = NULL;
    ListNode *curr = head;
    // Change links until curr is not NULL
    while (curr != NULL)
    {
        // Store the node next to curr, as we are going to change link of curr pointer
        // And we need the access of further linked list.
        ListNode *forward = curr->next;
        // Set next of current to prev( we are revesring the linkages)
        curr->next = prev;
        // Move forward i.e shift the pointers ahead ( order matters)
        prev = curr;
        curr = forward;
    }
    // prev will act as a new head now, it will point to the end of LL with reverse links
    return prev;
}
// T.C -> O(N)
// S.C -> O(1)
// --------------------------------------------------------------------------------------------------
// 4. Reverse linked list [Recursive]
ListNode *reverseList(ListNode *head)
{
    // When we reach end node, return!
    if (head == NULL || head->next == NULL)
    {
        return head;
    }
    // Reverse the further list and store inside node
    ListNode *node = reverseList(head->next);
    // Once we reach end, change the links to make the LL reverse
    head->next->next = head;
    head->next = NULL;
    // Return new head of reversed LL
    return node;
}
//! T.C -> O(N)
//! S.C -> O(N) -> Recurive stack
// --------------------------------------------------------------------------------------------------
// 5. Detect a loop in linked list
// Using map/set
bool cycleDetect(node *head)
{
    // Declare a set
    unordered_set<node *> hashTable;
    while (head != NULL)
    {
        // If this node is previously visited, then there is a cycle
        if (hashTable.find(head) != hashTable.end())
            return true;
        // If it's a node we visit first time, insert it into set
        hashTable.insert(head);
        // Move to next node
        head = head->next;
    }
    // Head has reached NULL, no cycle
    return false;
}
// T.C -> O(N) or (N*logN) -> depending upon map/set
// S.C -> O(N) -> set

// Using two pointers
bool hasCycle(ListNode *head)
{
    // If empty or a single node
    if (head == NULL)
        return false;

    // Declare slow and fast
    ListNode *slow = head;
    ListNode *fast = head;

    // Traverse until fast reaches null or slow == fast
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
        // There is a cycle
        if (slow == fast)
            return true;
    }
    // No cycle detected!
    return false;
}
// T.C -> O(N)
// S.C -> O(1)
// --------------------------------------------------------------------------------------------------
// 6.Starting point of loop in a Linked List
// Using map/set
ListNode *detectCycle(node *head)
{
    unordered_set<ListNode *> st;
    while (head != NULL)
    {
        if (st.find(head) != st.end())
        {
            // We got the staring node of loop
            return head;
        }
        st.insert(head);
        head = head->next;
    }
    return NULL;
}
// T.C -> O(N) or (N*logN) -> depending upon map/set
// S.C -> O(N) -> set
// Using fast and slow pointers
ListNode *detectCycle(ListNode *head)
{
    if (head == NULL)
        return NULL;
    // Initialize two pointers, slow and fast, to the head of the linked list.
    ListNode *slow = head;
    ListNode *fast = head;

    // Move the slow pointer one step and the fast pointer two steps at a time through the linked list,
    // until they either meet or the fast pointer reaches the end of the list.
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
        // If the pointers meet, there is a cycle in the linked list.
        // Reset the slow pointer to the head of the linked list, and move both pointers one step at a time
        // until they meet again. The node where they meet is the starting point of the cycle.
        if (slow == fast)
        {
            slow = head;
            while (slow != fast)
            {
                slow = slow->next;
                fast = fast->next;
            }
            // slow/fast is the starting node!
            return slow;
        }
    }
    // If the fast pointer reaches the end of the list without meeting the slow pointer,
    // there is no cycle in the linked list. Return null.
    return NULL;
}
// T.C -> O(N)
// S.C -> O(1)
// --------------------------------------------------------------------------------------------------
// 7.Length of loop in the Linked List
int countNodesinLoop(struct Node *head)
{
    if (head == NULL)
        return 0;
    Node *slow = head;
    Node *fast = head;
    // We have to return 0 if there is no cycle
    int cnt = 0;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
        // We got the loop!!
        if (slow == fast)
        {
            // We will again run slow pointer till fast pointer is ahead of slow
            // i.e we will get the length of loop, but as we do not traverse till they meet
            // We increase the cnt by 1 before only, so to get the complete length of loop
            cnt++;
            while (slow->next != fast)
            {
                slow = slow->next;
                cnt++;
            }
            break;
        }
    }
    // If we get the loop it returns the length of loop, else 0
    return cnt;
}
// T.C -> O(N)
// S.C -> O(1)
// --------------------------------------------------------------------------------------------------
// 8.Check if LL is palindrome or not
ListNode *reverse(ListNode *head)
{
    if (head == NULL)
        return NULL;
    ListNode *prev = NULL;
    ListNode *curr = head;
    while (curr != NULL)
    {
        ListNode *forward = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forward;
    }
    return prev;
}

bool isPalindrome(ListNode *head)
{

    // If empty or single node
    if (head == NULL || head->next == NULL)
        return 1;

    // FIND THE MIDDLE NODE OF LL
    ListNode *slow = head;
    ListNode *fast = head;

    // We have to find left middle if length is even, bcoz we are going to reverse
    // next part of left node!
    while (fast->next != NULL && fast->next->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Slow is the middle node
    ListNode *mid = slow;

    // Reverse the LL ahead of mid and link it with next of mid
    mid->next = reverse(mid->next);

    // Take two pointers, one at head and another at next to mid
    // And check for equality
    ListNode *ptr1 = head;
    ListNode *ptr2 = mid->next;
    
    // Traverse till ptr2 is not null
    while (ptr2 != NULL)
    {
        // If data at ptr1 and ptr2 are not same, LL is not a palindrome
        if (ptr1->val != ptr2->val)
            return 0;
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    // If we reach here, means LL is a palindrome
    return 1;
}
// T.C->O(N/2)+O(N/2)+O(N/2)
// S.C-> O(1)
// --------------------------------------------------------------------------------------------------
//Q. Segrregate odd and even nodes in LL


// Pen paper ghe!!
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if(!head)   return NULL;
        if(!head->next) return head;

        ListNode *odd = head , *even = head->next;
        ListNode *q = head->next;

        while(odd->next != NULL && even->next != NULL)
        {
            odd->next = even->next;
            odd = odd->next;
            even->next = odd->next;
            even = even->next;
        }
        odd->next = q;
        return head;
        
    }
};
// O(n) time
// -------------------------------------------------------
// 10.Remove N-th node from the end of a Linked List
ListNode *removeNthFromEnd(ListNode *head, int n)
{

    int l = 0;

    ListNode *temp = head;
    while (temp != NULL)
    {
        l++;
        temp = temp->next;
    }
    // first element to be deleted
    if (l == n)
    {
        return head->next;
    }

    int d = l - n - 1;
    temp = head;

    while (d--)
    {
        temp = temp->next;
    }

    ListNode *tbd = temp->next;
    if (temp->next != NULL)
        temp->next = temp->next->next;

    delete tbd;
    return head;
}
// T.C->O(2*N)
// S.C-> O(1)
// Optimal ( fast and slow)
ListNode *removeNthFromEnd(ListNode *head, int n)
{
    // we are using this extra dummy node is that there is an edge case. If the node is equal to the length
    // of the LinkedList, then this slow will point to slow’s next→ next. And we can say our dummy start node will
    //  be broken and will be connected to the slow next→ next.
    ListNode *dummy = new ListNode();
    // Store it to return at last
    dummy->next = head;
    if (head == NULL)
        return NULL;
    // Declare two pointers initioalized with dummy node
    ListNode *slow = dummy;
    ListNode *fast = dummy;
    // bring fast pointer to nth node
    while (n--)
    {
        fast = fast->next;
    }
    // increase slow pointer till fast comes to last node
    while (fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next;
    }

    // The node to be deleted will be node after slow pointer
    // So delete it by rearranging links
    slow->next = slow->next->next;

    // return head which is stored in dummy's next
    return dummy->next;
}
// T.C->O(N)
// S.C-> O(1)
// --------------------------------------------------------------------------------------------------
// 11.Delete the middle node of LL
ListNode *deleteMiddle(ListNode *head)
{

    // If empty or a single node
    if (head == NULL || head->next == NULL)
        return NULL;
    // Declare three pointers
    ListNode *slow = head;
    ListNode *fast = head;

    // We have to delete a node which will be pointed by slow after iterations
    // So we need node previous of slow to delete slow, so we store it in another pointer
    ListNode *prevOfSlow = NULL;
    while (fast != NULL && fast->next != NULL)
    {
        prevOfSlow = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    // Delete node pointed by slow node, using pointer just before slow
    prevOfSlow->next = prevOfSlow->next->next;

    // return the LL
    return head;
}
// T.C -> O(N)
// S.C -> O(1)
// --------------------------------------------------------------------------------------------------
// 12) 	Sort LL

class Solution {
public:

    // Function to find the middle node of the linked list
    ListNode* getMid(ListNode* head){
        ListNode* slow = head;
        ListNode* fast = head;

        // Move the fast pointer by two steps and the slow pointer by one step
        while(fast ->next != NULL && fast -> next -> next != NULL){
            slow = slow -> next;
            fast = fast -> next -> next;
        }

        return slow; // Return the slow pointer (middle node)
    }

    // Function to merge two sorted linked lists
    ListNode* merge(ListNode* head1, ListNode *head2){
        // Base cases: if either of the heads is NULL, return the other head
        if(head1 == NULL) return head2;
        if(head2 == NULL) return head1;

        ListNode* l1 = head1;
        ListNode* l2 = head2;

        // Determine the head of the merged list based on the values of the heads of input lists
        if(l2->val < l1->val) swap(l1, l2);

        ListNode* ans = l1; // Store the head of the merged list

        // Iterate through the lists, rearrange pointers to merge them in sorted order
        while(l1 != NULL && l2 != NULL){
            ListNode* temp = NULL;
            while(l1 != NULL && l1->val <= l2-> val){
                temp = l1;
                l1 = l1->next;
            }
            temp->next = l2;
            swap(l1, l2);
        }

        return ans; // Return the head of the merged list
    }

    // Function to perform merge sort on the linked list
    ListNode* sortList(ListNode* head) {
        // Base cases: if the list is empty or has only one node, return the head
        if(head == NULL || head->next  == NULL) return head;

        ListNode* mid = getMid(head); // Find the middle node of the list

        ListNode* left = head;
        ListNode* right = mid->next;
        mid->next = NULL;

        left = sortList(left); // Recursively sort the left half of the list
        right = sortList(right); // Recursively sort the right half of the list

        ListNode* ans = merge(left, right); // Merge the sorted left and right halves

        return ans; // Return the sorted list
    }
    
};
// T.C -> O(N*logN)
// S.C -> O(1)
// --------------------------------------------------------------------------------------------------
// 13) Sort linked list of 0s 1s 2s without changing links
Node* sortList(Node *head){  
    // Create three dummy nodes for the heads of three lists
    Node* zeroHead = new Node(0);
    Node* oneHead = new Node(0);
    Node* twoHead = new Node(0);

    // Create tail pointers for each list, initially pointing to the dummy heads
    Node* zeroTail = zeroHead;
    Node* oneTail = oneHead;
    Node* twoTail = twoHead;
    
    // Traverse the original list and append nodes to respective lists based on their data value
    while(head != NULL){
        if (head->data == 0) {
            zeroTail->next = head;
            zeroTail = zeroTail->next;
        } 
        else if (head->data == 1) {
            oneTail->next = head;
            oneTail = oneTail->next;
        }
        else {
            twoTail->next = head;
            twoTail = twoTail->next;
        }
        head = head->next;
    }

    // Connect the lists in the order 0s -> 1s -> 2s

    // If one's are not present, connext zero and two
    if (oneHead->next == NULL) {
        zeroTail->next = twoHead->next; 
    }
    // connect zero, one and two
    else {
        zeroTail->next = oneHead->next;
        oneTail->next = twoHead->next;
    }
    
    twoTail->next = NULL;

    // Return the head of the sorted list
    return zeroHead->next;
}
// T.C -> O(N)
// S.C -> O(1)
// --------------------------------------------------------------------------------------------------
// 14. Find the intersection point of Y LL
// Approach -> Difference in length
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
{
    ListNode *tempA = headA;
    ListNode *tempB = headB;
    int l1 = 0, l2 = 0;
    while (tempA != NULL)
    {
        l1++;
        tempA = tempA->next;
    }
    while (tempB != NULL)
    {
        l2++;
        tempB = tempB->next;
    }
    tempA = headA;
    tempB = headB;
    if (l2 > l1)
    {
        int temp = l2 - l1;
        while (temp--)
        {
            tempB = tempB->next;
        }
    }
    else
    {
        int temp = l1 - l2;
        while (temp--)
        {
            tempA = tempA->next;
        }
    }

    while (tempA != tempB)
    {
        tempA = tempA->next;
        tempB = tempB->next;
    }
    return tempA;
}
// T.C-> O(2max(length of list1,length of list2))+O(abs(length of list1-length of list2))+O(min(length of list1,length of list2))
// S.C -> O(1)

// Optimal 2 ->
// 1) Take two dummy nodes for each list. Point each to the head of the lists.
// 2) Iterate over them. If anyone becomes null, point them to the head of the
//    opposite lists and continue iterating until they collide.
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
{
    // If anyone of them in empty return NULL
    if (headA == NULL || headB == NULL)
        return NULL;

    // Declare two pointers to iterate lists
    ListNode *a = headA;
    ListNode *b = headB;

    // Iterate till both pointers become equal
    // If there exists a joint, it will return that node
    // else both of them will become NULL, end the loop and returns NULL
    while (a != b)
    {
        // If a becomes NULL point it to head of other list, else move ahead
        if (a == NULL)
            a = headB;
        else
            a = a->next;
        // If b becomes NULL point it to head of other list, else move ahead
        if (b == NULL)
            b = headA;
        else
            b = b->next;
    }
    // return either joint node or NULL
    return a;
}
// T.C->O(N+M)
// S.C-> O(1)
// --------------------------------------------------------------------------------------------------
// Q.15 Add two number represented by LL
ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
{

    // Create a node to which our new LL will be attached
    ListNode *ans = new ListNode(0);

    // to iterate and link new nodes
    ListNode *temp = ans;

    // initialise carry with 0
    int carry = 0;

    // Loop will break when, l1==NULL && l2==NULL && carry==0
    // at last when carry becomes zero, that case is also handled here
    while (l1 != NULL || l2 != NULL || carry != 0)
    {

        // everytime we have to calculate new sum
        int sum = 0;

        // if pointers are not NULL add their value to sum
        if (l1 != NULL)
        {
            sum += l1->val;
            l1 = l1->next;
        }
        if (l2 != NULL)
        {
            sum += l2->val;
            l2 = l2->next;
        }

        // add previos carry into sum
        sum += carry;

        // calculate current carry, that should be added to the next sum
        carry = sum / 10;

        // create a node with value sum%10 and link it with ans LL
        ListNode *node = new ListNode(sum % 10);

        // link the node with ans
        temp->next = node;

        // move ahead of pointer of answer LL
        temp = temp->next;
    }

    // Our LL will be start from next of ans node( dummy node initialised with 0)
    return ans->next;
}
// Time Complexity: O(max(m,n))
// Space Complexity: O(max(m,n)). The length of the new list is at most max(m,n)+1.}
// --------------------------------------------------------------------------------------------------
// 17.Merge two sorted linked lists
ListNode *mergeTwoLists(ListNode *list1, ListNode *list2)
{
    // If one list is empty return the another one!!
    if (list1 == NULL)
        return list2;
    if (list2 == NULL)
        return list1;

    // Declare two pointers, l1 and l2
    ListNode *l1 = list1;
    ListNode *l2 = list2;

    // l1 will always point to node with smaller value
    if (l1->val > l2->val)
        swap(l1, l2);

    // l1 will be our final LL
    ListNode *ans = l1;

    while (l1 != NULL && l2 != NULL)
    {
        ListNode *temp = NULL;
        while (l1 != NULL && l1->val <= l2->val)
        {
            // temp will store, the previous smaller value of l1 which has to be linked
            // with l2 once we break out of this loop i.e l1->val > l2->val
            temp = l1;

            // Move l1 ahead
            l1 = l1->next;
        }
        // Once we encounter l1->val > l2->val, link previous smaller of l1 with l2 which is stored
        // in temp
        temp->next = l2;

        // as l1 will be containing a larger value, which contradicts our algorithm so swap l1 and l2
        swap(l1, l2);
    }

    // Return the l1 list which is stored in ans
    return ans;
}
// Time Complexity : O(N+M)
// Space Complexity :O(1)
// --------------------------------------------------------------------------------------------------
// 18.Swap nodes in pairs

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if(head == NULL) return NULL;
        ListNode* p1 = head;

        while( p1!=NULL &&  p1->next != NULL){
            swap(p1->val,p1->next->val);
            p1 = p1->next->next;
        }
        return head;
    }
};

ListNode* swapPairs(ListNode* head) {
    // Swap pairs of adjacent nodes in a linked list

    // If the head is NULL or the head's next node is NULL, return the head
    if (head == NULL || head->next == NULL)
        return head;

    // Create pointers for the current node, next node, and a temporary node
    ListNode* curr = head;
    ListNode* next = head->next;
    ListNode* temp = next->next;

    // Adjust the pointers to swap the pairs of nodes
    curr->next = temp;
    next->next = curr;

    // Recursively swap the remaining nodes in the linked list
    curr->next = swapPairs(temp);

    // Return the new head after swapping pairs
    return next;
}