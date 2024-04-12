// 1.Delete all occurrences of a given key in a doubly linked list
void deleteAllOccurOfX(struct Node **head, int x)
{
    // HANDLE FIRST AND LAST NODE SEPARATELY
    Node *temp = *head;
    while (temp != NULL)
    {
        if (temp->data == x)
        {
            // first node
            if (temp->prev == NULL)
            {
                // make head point to next 2nd node
                *head = temp->next;
            }

            // second node
            else if (temp->next == NULL)
            {
                // point second last node to NULL
                temp->prev->next = NULL;
            }

            // any middle node
            else
            {
                // previos will point to next of deleted node
                temp->prev->next = temp->next;
                // prev(pointer) of deleted node's next node will point to deleted node's previous node
                temp->next->prev = temp->prev;
            }
        }

        // move forward
        temp = temp->next;
    }
}
// Time Complexity -> O(N)
// Space Complexity -> O(1)
// ------------------------------------------------------------------------------------------------
// 2.Find pairs with given sum in doubly linked list
vector<pair<int, int>> findPairsWithGivenSum(Node *head, int target)
{
    // A simple two pointers approach, like array
    Node *start = head;
    Node *end = head;

    // one pointer pointing to end of DLL
    while (end->next != NULL)
    {
        end = end->next;
    }

    vector<pair<int, int>> ans;

    // As DLL is sorted, we will iterate till start's data is less that end's data
    while (start->data < end->data)
    {
        // value at start
        int num1 = start->data;

        // value at end
        int num2 = end->data;

        // sum
        int sum = num1 + num2;

        // if sum == target, we got one of the answer
        if (sum == target)
        {
            ans.push_back({num1, num2});
            // move pointers
            start = start->next;
            end = end->prev;
        }
        // according to sum, move pointers
        else if (sum < target)
            start = start->next;
        else
            end = end->prev;
    }
    return ans;
}
// Time Complexity -> O(N)
// Space Complexity -> O(2*Pairs)
// --------------------------------------------------------------------------------------------------
// 3.Remove duplicates from sorted DLL
{
    // declare two pointers left and right
    Node *right = head;
    Node *left = head;

    // iterate till right becomes NULL
    while (right != NULL)
    {
        // If we get some pair(left and right) which is not equal, means between
        // them there might be duplicates equal to left's data so join left and right
        if (left->data != right->data)
        {
            left->next = right;
            right->prev = left;
            left = right;
        }

        // move forward till left and right are equal
        right = right->next;
    }

    // If the duplicates are at the end of DLL, we need to manually set
    // the left's next to NULL as left will be the last node after deletion of duplicate nodes
    // (dry run on 1 2 3 3 3 4 4)
    left->next = NULL;

    return head;
}
// Time Complexity -> O(N)
// Space Complexity -> O(1)