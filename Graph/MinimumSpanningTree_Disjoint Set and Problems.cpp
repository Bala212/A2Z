1) Minimum spanning tree

A spanning tree is a tree in which we have N nodes(i.e. All the nodes present 
in the original graph) and N-1 edges and all nodes are reachable from each other.

Point to remember is that a graph may have more than one spanning trees.

Among all possible spanning trees of a graph, the minimum spanning tree is 
the one for which the sum of all the edge weights is the minimum.

Note: There may exist multiple minimum spanning trees for a graph like a graph 
            may have multiple spanning trees.

There are a couple of algorithms that help us to find the minimum spanning 
tree of a graph. One is Prim’s algorithm and the other is Kruskal’s algorithm.
---------------------------------------------------------------------------------------------------------------------------
2) Prim’s Algorithm – Minimum Spanning Tree

TO FIND THE SUM  OF EDGES IN MST AND EDGES IN MST

Take the elements out, if it is unvisited consider that edge add it's weight to 
the answer and put the adjacent nodes with the parent as current node into the
priority queue.

Mark node as visited when the are popped from priority queue, because while
pushing we don't know whether that node is visited at the lower weight or not.
It is sure that when we pop out from pq, it will be of minimum weight!!

We are always picking edges with minimum weights from pq. While pushing
it is not sure that, that node is visited with minimum edge weight or not
that's why we don't mark the node as visited while inserting, but mark as visited
when we pop from the pq, as it will be popped with minimum weight as MIN HEAP.
PQ f {wt, {node, parent}}. We are storing parent because we want the edge also
if the question asks us for the edges in MST. The edge will be from parent to node
or node to parent if it is undirected graph.
 
If the question asks us for only the sum of edges, then there is no need to store 
parent with the node just {wt, node}.

We are storing parent because we want the edges in MST as well na!!

Certainly! The code implements Prim's algorithm, which finds the Minimum Spanning Tree (MST) of a weighted undirected 
graph. Here's a neat and concise intuition of how the algorithm works:

**Intuition:**
1. Start with an arbitrary node as the initial node of the MST.
2. Create a priority queue (min-heap) to store edges in ascending order of weights.
3. Initialize the priority queue with an edge of weight 0 from the initial node.
4. Initialize a visited array to keep track of visited nodes (nodes already included in the MST).
5. Initialize the sum of edge weights of the MST to zero.
6. While the priority queue is not empty:
   a. Pop the edge with the minimum weight from the priority queue.
   b. If the popped node of is already visited means it is already the part of MST, skip it.
   c. If not,mark the popped node as visited (added to the MST).
   d. Add the weight of the current edge to the sum.
   e. Explore all adjacent nodes of the current node and add their edges to the priority queue if the adjacent node is 
      not yet visited.
7. Once all nodes are visited or the priority queue is empty, return the sum of weights of all the edges that form 
   the Minimum Spanning Tree.

In summary, Prims algorithm starts with an initial node and keeps adding the edge with the minimum weight that connects 
a node in the MST to a node outside it. It continues this process until all nodes are included in the MST, resulting in 
the minimum sum of edge weights that form a tree connecting all nodes of the given graph.

The final result is the sum of weights of all the edges that form the Minimum Spanning Tree of the given graph.

class Solution
{
public:
    // Function to find the sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[])
    {
        // Create a priority queue to store edges in ascending order of weights.
        // We use a pair of integers: {weight, node} where 'weight' is the weight of the edge,
        // and 'node' is the adjacent node to which the edge leads.
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Create a vector to keep track of visited nodes.
        vector<int> vis(V, 0);

        // Initialize the priority queue with the first node (0) with weight 0.
        pq.push({0, 0});
        int sum = 0; // Initialize the sum of edge weights of the Minimum Spanning Tree.

        // Start the loop until the priority queue becomes empty.
        while (!pq.empty()) {
            auto it = pq.top(); // Fetch the edge with the minimum weight from the priority queue.
            pq.pop(); // Remove the edge from the priority queue.

            int node = it.second; // Extract the node (adjacent to the current MST) from the edge.
            int nodeWt = it.first; // Extract the weight of the edge.

            if (vis[node])
                continue; // If the node is already visited (part of the MST), skip it.

            vis[node] = 1; // Mark the node as visited (added to the MST).

            sum += nodeWt; // Add the weight of the current edge to the sum.

            // Explore all adjacent nodes of the current node.
            for (auto &it : adj[node]) {
                int adjNode = it[0]; // Extract the adjacent node.
                int adjWt = it[1]; // Extract the weight of the edge to the adjacent node.

                if (!vis[adjNode]) {
                    // If the adjacent node is not yet visited, add the edge to the priority queue.
                    pq.push({adjWt, adjNode});
                }
            }
        }

        return sum; // Return the sum of weights of edges in the Minimum Spanning Tree.
    }
};

Time Complexity: O(E*logE) + O(E*logE)~ O(E*logE), where E = no. of given edges.

The maximum size of the priority queue can be E so after at most E iterations the priority queue will be empty and 
the loop will end. Inside the loop, there is a pop operation that will take logE time. This will result in the 
first O(E*logE) time complexity. Now, inside that loop, for every node, we need to traverse all its adjacent nodes 
where the number of nodes can be at most E. If we find any node unvisited, we will perform a push operation and for 
that, we need a logE time complexity. So this will result in the second O(E*logE). 

Space Complexity: O(E) + O(V), where E = no. of edges and V = no. of vertices. O(E) occurs due to the size of the 
priority queue and O(V) due to the visited array. If we wish to get the mst, we need an extra O(V-1) space to store 
the edges of the most.

---------------------------------------------------------------------------------------------------------------------------
3) Disjoint Set | Union by Rank | Union by Size | Path Compression

Tuze notes ani article bagh!!

Union by rank:
#include <bits/stdc++.h>
using namespace std;
class DisjointSet {
    vector<int> rank, parent;
public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }

    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }
};
int main() {
    DisjointSet ds(7);
    ds.unionByRank(1, 2);
    ds.unionByRank(2, 3);
    ds.unionByRank(4, 5);
    ds.unionByRank(6, 7);
    ds.unionByRank(5, 6);
    // if 3 and 7 same or not
    if (ds.findUPar(3) == ds.findUPar(7)) {
        cout << "Same\n";
    }
    else cout << "Not same\n";

    ds.unionByRank(3, 7);

    if (ds.findUPar(3) == ds.findUPar(7)) {
        cout << "Same\n";
    }
    else cout << "Not same\n";
    return 0;
}

Union by size:
using namespace std;
class DisjointSet {
    vector<int> rank, parent, size;
public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};
int main() {
    DisjointSet ds(7);
    ds.unionBySize(1, 2);
    ds.unionBySize(2, 3);
    ds.unionBySize(4, 5);
    ds.unionBySize(6, 7);
    ds.unionBySize(5, 6);
    // if 3 and 7 same or not
    if (ds.findUPar(3) == ds.findUPar(7)) {
        cout << "Same\n";
    }
    else cout << "Not same\n";

    ds.unionBySize(3, 7);

    if (ds.findUPar(3) == ds.findUPar(7)) {
        cout << "Same\n";
    }
    else cout << "Not same\n";
    return 0;
}

---------------------------------------------------------------------------------------------------------------------------
4) Kruskal’s Algorithm – Minimum Spanning Tree 


FINDING MINIMUM SPANNING TREE and SUM.

1) Create a vector of pair of pair which will store the {wt,{node, adjNode}}
     i.e. store every edge of the graph, and wt should be first, bcoz we need to sort
     according to edge weight.
2) Sort edges according to weights.
3) Go on connecting edges one by one using disjoint set (union by rank/size).
4) Connect nodes only if their ultimate parents are different, that means they belong 
     to different components! Add edge weight to sum and, do union of these two 
     edges.
5) If ultimate parents of two nodes is same, that means they are already connected
     or are in the same component so no need to add edge between them.
6) In this way, we are excluding extra edges in the graph, and sorting according 
     to edge weights makes sure that we always choose minimum edge weights to
     connect them.


class DisjointSet {
    vector<int> rank, parent, size;
public:
    // Constructor to initialize the Disjoint Set data structure.
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        // Initialize each node as a separate set with its parent being itself.
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    // Function to find the ultimate parent of a node using path compression.
    int findUPar(int node) {
        if (node == parent[node])
            return node;
        // Path compression: Update the parent of the current node to its ultimate parent.
        return parent[node] = findUPar(parent[node]);
    }

    // Function to perform union of two sets based on rank (used in Kruskal's algorithm).
    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        // Merge the smaller ranked set with the larger ranked set.
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        } else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        } else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    // Function to perform union of two sets based on size (used in Prim's algorithm).
    void unionBySize(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        // Merge the smaller sized set with the larger sized set.
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        } else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};

class Solution
{
public:
    // Function to find the sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[])
    {
        // Create a vector to store all the edges in the graph along with their weights.
        vector<pair<int, pair<int, int>>> edges;
        for (int i = 0; i < V; i++) {
            for (auto it : adj[i]) {
                int adjNode = it[0];
                int wt = it[1];
                int node = i;

                // Store the edge and its weight as a pair in the 'edges' vector.
                edges.push_back({wt, {node, adjNode}});
            }
        }

        // Create a Disjoint Set data structure to keep track of connected components in the graph.
        DisjointSet ds(V);

        // Sort the edges in ascending order based on their weights.
        sort(edges.begin(), edges.end());

        int mstWt = 0; // Initialize the sum of weights of the Minimum Spanning Tree.

        // Iterate through the sorted edges and add them to the MST if they don't form a cycle.
        for (auto it : edges) {
            int wt = it.first;
            int u = it.second.first;
            int v = it.second.second;

            // If the nodes 'u' and 'v' are not in the same connected component, add the edge to the MST.
            if (ds.findUPar(u) != ds.findUPar(v)) {
                mstWt += wt; // Add the weight of the current edge to the MST weight.
                ds.unionBySize(u, v); // Perform the union of the sets (merge the connected components).
		        // TO GET THE MST, WE WILL STORE THE NODE U AND V EVERYTIME, THAT WILL BE THE EDGES IN MST.
            }
        }

        return mstWt; // Return the sum of weights of all the edges in the Minimum Spanning Tree.
    }
};


Time Complexity: O(N+E) + O(E logE) + O(E*4α*2)   
                 where N = no. of nodes and E = no. of edges. O(N+E) for extracting edge information from the adjacency list. 
		 O(E logE) for sorting the array consists of the edge tuples. Finally, we are using the disjoint set operations inside a loop. 
		 The loop will continue to E times. Inside that loop, there are two disjoint set operations like findUPar() and 
		 UnionBySize() each taking 4 and so it will result in 4*2. That is why the last term O(E*4*2) is added.

Space Complexity: O(N) + O(N) + O(E) where E = no. of edges and N = no. of nodes. 
		  O(E) space is taken by the array that we are using to store the edge information. And in the disjoint set data structure, 
		  we are using two N-sized arrays i.e. a parent and a size array (as we are using unionBySize() function otherwise, 
		  a rank array of the same size if unionByRank() is used) which result in the first two terms O(N).

---------------------------------------------------------------------------------------------------------------------------
5) Number of provinces using disjoint set

https://takeuforward.org/data-structure/number-of-provinces-disjoint-set-g-48/

Note: The intuition is to count the number of nodes for which the nodes themselves are their ultimate parents.

The graph in this problem is given in the form of an adjacency matrix where matrix[i][j] = 1 means that there is an edge between
node i and node j. 

class Solution {
public:
    int numProvinces(vector<vector<int>> adj, int V) {
        // Create a Disjoint Set data structure with V nodes.
        DisjointSet ds(V);

        // Iterate through the adjacency matrix to process the connections between cities.
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (adj[i][j] == 1) {
                    // If there is a direct connection between cities i and j (adj[i][j] == 1),
                    // union the sets containing cities i and j in the Disjoint Set data structure.
                    ds.unionBySize(i, j);
                }
            }
        }

        int cnt = 0; // Initialize a counter to keep track of the number of provinces.

        // Count the number of unique provinces using the Disjoint Set data structure.
        // A unique province has its representative parent node as itself (ds.parent[i] == i).
	// We can also use ultimate parent here!! For using parent we need to declare them public!
        for (int i = 0; i < V; i++) {
            if (ds.parent[i] == i)
                cnt++;
        }

        return cnt; // Return the total number of provinces.
    }
};

Time Complexity: O(N2)+O(N* 4α) ~ O(N2)+O(N) where N = no. of nodes. O(N2) for visiting the adjacency matrix 
		 and O(N) for the counting of ultimate parents. 4α is so small that this term can be ignored.

Space Complexity: O(2N), where N = no. of nodes. O(2N) for the two arrays parent and size(or rank) of size N.

---------------------------------------------------------------------------------------------------------------------------
6) Number of Operations to Make Network Connected – DSU

Article vaach!!

1) Minimum no. of edges required: no. of components - 1
2) So, if extraEdges in graph >= nC -1 then return nC - 1, else return -1
3) Extra edges can be calculated as, how many time we encounter the condition
     that while doing union using disjoint set, their ultimate parents are same.
4) Ultimate parents are same means they are already connected there is no need
     of extra edge.
5) No. of components can be calculated by condition that how many nodes are
     there whose ultimate parent is that node itself!!


## GENERATE THE DISJOINT SET DATA STRUCTURE OF GIVEN GRAPH FIRST!!

class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        // Create a Disjoint Set data structure with 'n' nodes, representing the 'n' computers in the network.
        DisjointSet ds(n);

        int extraEdges = 0; // Initialize a counter for extra edges (redundant connections).

        // Iterate through the connections to process each connection.
	// GENERATE THE DISJOINT SET DATA STRUCTURE OF GIVEN GRAPH FIRST!!
        for (int i = 0; i < connections.size(); i++) {
            // Check if the nodes of the current connection are not in the same connected component.
            if (ds.findUParent(connections[i][0]) != ds.findUParent(connections[i][1]))
                ds.unionBySize(connections[i][0], connections[i][1]); // Merge the connected components.

            else
                extraEdges++; // If the nodes are already in the same connected component, it is an extra edge.
        }

        int cc = 0; // Initialize a counter for connected components (networks).

        // Count the number of unique connected components (networks) in the Disjoint Set data structure.
        for (int i = 0; i < n; i++) {
            if (ds.parent[i] == i)
                cc++; // A unique connected component has its ultimate  parent node as itself.
        }

        int ans = cc - 1; // The number of extra edges required to connect all networks is (number of networks - 1).

        // If there are enough extra edges to connect all networks, return the number of extra edges required.
        if (extraEdges >= ans) {
            return ans;
        }

        return -1; // If there are not enough extra edges to connect all networks, return -1.
    }
};

Time Complexity: O(E*4α)+O(N*4α) where E = no. of edges and N = no. of nodes. 
		 The first term is to calculate the number of extra edges and the second term is to 
		 count the number of components. 4α is for the disjoint set operation we have used and this term 
		 is so small that it can be considered constant.

Space Complexity: O(2N) where N = no. of nodes. 2N for the two arrays(parent and size) of size N we have used inside the disjoint set.

---------------------------------------------------------------------------------------------------------------------------
7) Accounts Merge

1) First, we will try to iterate over every single email and add them with their 
     respective indices(i.e. Index of the accounts the email belongs to)  in a map data 
     structure. If we found that mail already exists, just merge those two account
     index using union by size/rank indicating that they are the same account. This
     will update the ultimate parents of the merged account!

2) Now, it’s time to merge the emails. So, we will iterate over each email and will 
    add them to the ultimate parent of the current account’s index.

3) Finally, we will sort the emails for each account individually to get our answers 
     in the format specified in the question. Also add name of that account at the
     beginning.
 
NOTE:
a) Here we will perform the disjoint set operations on the indices of the accounts 
     considering them as the nodes.
b) As in each account, the first element is the name, we will start iterating from the 
    second element in each account to visit only the emails sequentially.

Read article for approach!!

class Solution {
public:
    vector<vector<string>> accountsMerge(vector<vector<string>> &details) {
        int n = details.size();
        // Create a Disjoint Set data structure with 'n' nodes, representing the 'n' accounts in the input.
        DisjointSet ds(n);

        // Sort the 'details' vector to group accounts with the same owner together.
        sort(details.begin(), details.end());

        // Create a map to associate each email with its corresponding node (account) in the Disjoint Set.
        unordered_map<string, int> mapMailNode;

        // Process each account to build connections between accounts based on their shared emails.
        for (int i = 0; i < n; i++) {
            for (int j = 1; j < details[i].size(); j++) {
                string mail = details[i][j];
                // If the email is not in the map, associate it with the current node (account) 'i'.
                if (mapMailNode.find(mail) == mapMailNode.end()) {
                    mapMailNode[mail] = i;
                }
                else {
                    // If the email is already in the map, merge the corresponding nodes (accounts) using the Disjoint
                    // Set. This will update the ultimate parents too!!
                    ds.unionBySize(i, mapMailNode[mail]);
                }
            }
        }

        // Create an array 'mergedMail' to store the merged emails of each account.
        vector<string> mergedMail[n];
        for (auto it : mapMailNode) {
            string mail = it.first;
            int node = ds.findUParent(it.second);
            mergedMail[node].push_back(mail); // Add the email to the merged list of its ultimate parent/node (account)
        }

        vector<vector<string>> ans; // Create a vector to store the final merged accounts.

        // Iterate through the accounts and construct the final merged accounts vector.
        for (int i = 0; i < n; i++) {
            if (mergedMail[i].size() == 0) continue; // Skip accounts with no merged emails.
            sort(mergedMail[i].begin(), mergedMail[i].end()); // Sort the emails of the current account.
            vector<string> temp;
            temp.push_back(details[i][0]); // Add the account owner's name as the first element of 'temp'.
            for (auto it : mergedMail[i]) {
                temp.push_back(it); // Add the merged email	s of the account.
            }
            ans.push_back(temp); // Add the merged account to the final result vector.
        }

        sort(ans.begin(), ans.end()); // Sort the final merged accounts vector.

        return ans; // Return the final merged accounts vector.
    }
};

Time Complexity: O(N+E) + O(E*4ɑ) + O(N*(ElogE + E)) where N = no. of indices or nodes and E = no. of emails. 
		 The first term is for visiting all the emails. The second term is for merging the accounts. And the third term is for sorting the emails and storing them in the answer array.

Space Complexity: O(N)+ O(N) +O(2N) ~ O(N) where N = no. of nodes/indices. The first and second space is for the ‘mergedMail’ 
		  and the ‘ans’ array. The last term is for the parent and size array used inside the Disjoint set data structure.

---------------------------------------------------------------------------------------------------------------------------
8) Making a Large Island – DSU

1) Join the given groups/components by union by size.
2) Try replacing all zeroes.
3) Edge case, is matrix does not contain zero,  we will just run a loop from 
    node number 0 to n*n and for each node number, we will find the ultimate 
    parent. After that, we will find the sizes of those ultimate parents and will 
    take the size of the largest one.

Node number = row*m + col

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        // Create a Disjoint Set data structure with 'n*n' nodes to represent each cell in the 'grid'.
        DisjointSet ds(n * n);

        // Process each cell in the 'grid' and build connections between neighboring cells that have the value 1.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    int dx[] = {-1, 0, 1, 0}; // Offsets for neighboring cells (up, right, down, left).
                    int dy[] = {0, 1, 0, -1};
                    for (int ind = 0; ind < 4; ind++) {
                        int nR = i + dx[ind];
                        int nC = j + dy[ind];
                        if (nR >= 0 && nR < n && nC >= 0 && nC < n) {
                            if (grid[nR][nC]) {
                                int node = i * n + j; // Convert cell coordinates (i, j) to a node index.
                                int adjNode = nR * n + nC; // Convert neighboring cell coordinates to an adjacent
                                // nodeindex.
                                // Merge the connected components of the current cell and its neighbor.
                                ds.unionBySize(node, adjNode); 
                            }
                        }
                    }
                }
            }
        }   

        int mx = -1e9; // Initialize the maximum island size.

        // Iterate through each cell in the 'grid' to find and calculate the size of the largest island.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) { // If the current cell is water (0), check its neighboring cells.
                    int dx[] = {-1, 0, 1, 0};
                    int dy[] = {0, 1, 0, -1};
                    // Use a set to store unique representative nodes (components) of neighboring
                    // islands.
                    set<int> components; 
                    for (int ind = 0; ind < 4; ind++) {
                        int nR = i + dx[ind];
                        int nC = j + dy[ind];
                        if (nR >= 0 && nR < n && nC >= 0 && nC < n) {
                            if (grid[nR][nC] == 1) {
                                // Add the ultimate parents/node of
                                // the neighboring island to the set.
                                components.insert(ds.findUParent(nR * n + nC)); 
                            }
                        }
                    }
                    int size = 1; // Start with size 1 (the current cell is part of the island).
                    for (auto it : components) {
                        size += ds.size[it]; // Add the size of each neighboring island to the total size.
                    }
                    mx = max(mx, size); // Update the maximum island size found so far.
                }
            }
        }    

        // After processing all cells, find the largest size among all individual islands and return it.
        for (int i = 0; i < n * n; i++) {
            mx = max(mx, ds.size[i]); // Compare each island's size with the current maximum.
        }
        return mx; // Return the size of the largest island.
    }
};

Time Complexity: O(N2)+O(N2) ~ O(N2) where N = total number of rows of the grid. Inside those nested loops, 
		 all the operations are taking apparently constant time. So, O(N2) for the nested loop only, is the time complexity.

Space Complexity: O(2*N2) where N = the total number of rows of the grid. This is for the two arrays i.e. parent array 
		  and size array of size N2 inside the Disjoint set.
---------------------------------------------------------------------------------------------------------------------------
9) Most Stones Removed with Same Row or Column – DSU
---------------------------------------------------------------------------------------------------------------------------
10) Number of Islands – II – Online Queries – DSU
****************************************************************************************************************************************************
11) Minimum cost to connect all points

#Just return the MST SUM

https://leetcode.com/problems/min-cost-to-connect-all-points/?envType=daily-question&envId=2023-09-15

class Ds{
    vector<int> par, sizeOf;
    public:

    Ds(int size){
        // this.size = size;
        par.resize(size+1);
        for(int i=0;i<=size;i++){
            par[i] = i;
        }

        sizeOf.resize(size+1, 1);
    }

    int ultPar(int node){
        if(par[node] == node) return node;

        return par[node] = ultPar(par[node]);
    }

    void unionBySize(int u, int v){
        int uPar = ultPar(u);
        int vPar = ultPar(v);

        if(uPar == vPar) return;

        int uSize = sizeOf[u];
        int vSize = sizeOf[v];

        if(uSize >= vSize ){
            uSize += vSize;
            par[vPar] = par[uPar];
        }
        else{
            vSize += uSize;
            par[uPar] = par[vPar];
        }
    }
};

class Solution {
public:
    int minCostConnectPoints(vector<vector<int>>& p) {
        int n = p.size();
        Ds ds(n);

        vector<pair<int, pair<int, int>>  > edges;

        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                int xF = p[i][0];
                int yF = p[i][1];
                int xS = p[j][0];
                int yS = p[j][1];

                int dis = abs(xF-xS) + abs(yF-yS);

                edges.push_back({dis, {i,j} });
                edges.push_back({dis, {j,i} });
            }
        }

        sort(edges.begin(), edges.end());
        int ans = 0;
        for(auto &val : edges){
            int wt = val.first;
            int u = val.second.first;
            int v = val.second.second;

            if(ds.ultPar(u) != ds.ultPar(v)){
                ds.unionBySize(u, v);
                ans += wt;
            }
        }

        return ans;
    }
};

