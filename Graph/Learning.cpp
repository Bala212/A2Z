1) Number of graphs

Note: If there are n nodes in a graph, then number of possible edges are n*(n-1)/2.

// Function to count the number of graphs that can be formed with 'n' nodes.
// The function takes an integer 'n' as input, representing the number of nodes 
//  in the graph.
int countingGraphs(int n)
{
    // Calculate the maximum number of edges that can be present in the graph 
    // with 'n' nodes. Since each node can be connected to every other node except 
    // itself, there are 'n-1' possible connections for each node.
    // If there is edge between 1 to 2, there is no need of edge from 2 to 1 again
    // so we divide by 2.
    int edges = n * (n - 1) / 2;

    // The number of graphs that can be formed with 'n' nodes is equal to 2^edges.
    // This is because for each edge, we have two choices: include it in the graph or 
    //exclude it. So, the total number of possible combinations is 2^edges.
    return 1 << edges;
}

---------------------------------------------------------------------------------------------------------------------------
2) Graph representation

a) Adjacency matrix

int main()
{
    int n, m;
    cin >> n >> m;
    // adjacency matrix for undirected graph
    // time complexity: O(n)
    int adj[n+1][n+1];
    for(int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u][v] = 1;
        adj[v][u] = 1  // this statement will be removed in case of directed graph
    }
    return 0;
}

b) Adjacency Lists

#Undirected graph
int main()
{
    int n, m;
    cin >> n >> m;
    // adjacency list for undirected graph
    // time complexity: O(2E)
    vector<int> adj[n+1];
    for(int i = 0; i < m; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    return 0;
}
Space complexity = O(2xE)

#Directed graph
int main()
{
    int n, m;
    cin >> n >> m;
    // adjacency list for directed graph
    // time complexity: O(E)
    vector<int> adj[n+1];
    for(int i = 0; i < m; i++)
    {
        int u, v;
        // u —> v
        cin >> u >> v;
        adj[u].push_back(v);
    }
    return 0;
}
Space complexity = O(E)

---------------------------------------------------------------------------------------------------------------------------
3) BFS TRAVERSAL OF GRAPH

a) In BFS, we start with a “starting” node, mark it as visited, and push it into the queue data structure.
b) In every iteration, we pop out the node ‘v’ and put it in the solution vector, as we are traversing this node.
c) All the unvisited adjacent nodes from ‘v’ are visited next and are pushed into the queue. 
   The list of adjacent neighbors of the node can be accessed from the adjacency list.
d) Repeat steps 2 and 3 until the queue becomes empty, and this way you can easily traverse all the nodes in the graph.

The algorithm Breadth-First Search (BFS) to traverse a graph starting from a given node (node 0 in this case) 
and visit all its reachable nodes. The main intuition behind BFS is to explore all the nodes at the current level 
before moving on to the nodes at the next level.

Here's a step-by-step explanation of the intuition behind the algorithm:

1. Initialization:
   - We initialize a boolean array called 'vis' of size 'V' (number of vertices in the graph) to keep track of visited nodes. 
     All elements in 'vis' are initiall set to 0, indicating that no nodes have been visited yet.
   - We create a queue data structure to help us perform the BFS traversal. We start the BFS from node 0 
     (can be any starting node, but here it is chosen as 0) and mark it as visited by setting vis[0] = 1.
   - We initialize an empty vector called 'ans' to store the order of visited nodes during the BFS traversal.

2. BFS Traversal:
   - We enter the main loop of BFS that continues until the queue becomes empty.
   - In each iteration, we dequeue the front node from the queue and process it.
   - We add the current node to the 'ans' vector, which keeps track of the order in which nodes are visited during the BFS.
   - We explore all the adjacent nodes of the current node. These are nodes that can be reached by moving one edge from the current node.
   - If an adjacent node has not been visited (vis[adjNode] == 0), we mark it as visited (vis[adjNode] = 1) and enqueue it into the queue. 
     This ensures that we will visit all nodes at the current level before moving on to the nodes at the next level.

3. Completion:
   - Once the queue becomes empty, we have visited all the reachable nodes from the starting node (node 0).
   - The 'ans' vector now contains the BFS traversal result, which is the order of nodes visited during BFS.

The BFS algorithm ensures that we visit nodes in the order of their distance from the starting node. 
Nodes at the same distance (level) are visited in the order they appear in the adjacency list. 
This makes BFS particularly useful for finding the shortest path in unweighted graphs and exploring all 
connected components in an undirected graph. It guarantees that we explore nodes layer by layer, 
which can be very helpful in various graph-related problems.

// Function to perform Breadth-First Search (BFS) on a graph represented by an adjacency list.
// The function takes the number of vertices 'V' and the adjacency list 'adj[]' as inputs.
vector<int> bfsOfGraph(int V, vector<int> adj[]) {
    // Create an array to keep track of visited nodes.
    int vis[V] = {0};

    // Create a queue to perform BFS traversal.
    queue<int> q;

    // Start BFS from the first node (node 0) and mark it as visited.
    q.push(0);
    vis[0] = 1;

    // Vector to store the order of visited nodes during BFS traversal.
    vector<int> ans;

    // Perform BFS traversal until the queue becomes empty.
    while (!q.empty()) {
        // Get the front node from the queue.
        int node = q.front();
        q.pop();

        // Add the current node to the answer vector since it has been visited.
        ans.push_back(node);

        // Explore the adjacent nodes of the current node.
        for (auto &adjNode : adj[node]) {
            // If the adjacent node is not visited, mark it as visited and enqueue it.
            if (!vis[adjNode]) {
                q.push(adjNode);
                vis[adjNode] = 1;
            }
        }
    }

    // Return the vector containing the BFS traversal result.
    return ans;
}

The BFS algorithm remains the same for both types of graphs, but while constructing the adjacency list, 
you need to make sure that you represent the edges correctly based on the graph type. Once you have the 
correct adjacency list representation, you can use the same BFS code to traverse both undirected and 
directed graphs and get the BFS traversal result.

Time Complexity: O(N) + O(2E), Where N = Nodes, 2E is for total degrees as we traverse all adjacent nodes.
                 Inner for loop will run for 2E times overall (2E is the degree of undirected graph, for directed graph it is E)

Space Complexity: O(3N) ~ O(N), Space for queue data structure visited array and an adjacency list

---------------------------------------------------------------------------------------------------------------------------
4) DFS TRAVERSAL OF GRAPH

a) In DFS, we start with a node ‘v’, mark it as visited and store it in the solution vector. It is unexplored as its adjacent nodes are not visited.

b) We run through all the adjacent nodes, and call the recursive dfs function to explore the node ‘v’ which has not been visited previously. 
  This leads to the exploration of another node ‘u’ which is its adjacent node and is not visited. 

c) The adjacency list stores the list of neighbours for any node. Pick the neighbour list of node ‘v’ and run a for loop on the list of neighbours 
  (say nodes ‘u’ and ‘w’ are in the list). We go in-depth with each node. When node ‘u’ is explored completely then it backtracks and explores node ‘w’.

d) This traversal terminates when all the nodes are completely explored. 

The algorithm uses Depth-First Search (DFS) to traverse a graph starting from a given node and visit all its reachable nodes. 
The main intuition behind DFS is to explore as far as possible along each branch before backtracking.

Here's a step-by-step explanation of the intuition behind the algorithm:

1. Initialization:
   - We initialize a boolean array called 'vis' of size 'V' (number of vertices in the graph) to keep track of visited nodes. 
     All elements in 'vis' are initially set to 0, indicating that no nodes have been visited yet.
   - We create an empty vector called 'ans' to store the order of visited nodes during the DFS traversal.

2. DFS Traversal:
   - We choose a starting node (here, node 0 is chosen, but any valid starting node can be selected) and mark it as 
    visited by setting vis[startNode] = 1.
   - We call the recursive 'dfs' function to perform the DFS traversal from the starting node.

3. Recursive DFS Function:
   - The 'dfs' function takes the current 'node' being visited, the adjacency list 'adj[]', the 'vis[]' array, 
     and the 'ans' vector as parameters.
   - We mark the current node as visited by setting vis[node] = 1.
   - We add the current node to the 'ans' vector since it has been visited.
   - We iterate through all the adjacent nodes of the current node.
   - For each adjacent node, if it has not been visited (vis[adjNode] == 0), we recursively call the 'dfs' 
     function on that node. This ensures that we explore the adjacent nodes depth-first, visiting nodes along each branch before backtracking.
   - After exploring all the adjacent nodes, the function returns, and we continue with the next iteration in the main DFS traversal.

4. Completion:
   - Once the DFS traversal from the starting node is complete, we have visited all the reachable nodes in the graph.
   - The 'ans' vector now contains the DFS traversal result, which is the order of nodes visited during DFS.

// Recursive Depth-First Search (DFS) function to traverse a graph starting from the given node.
// The function takes the 'node' to start the DFS, the adjacency list 'adj[]', the 'vis[]' array to track visited nodes,
// and a reference to the 'ans' vector that stores the DFS traversal order.
void dfs(int node, vector<int> adj[], int vis[], vector<int> &ans) {
    // Mark the current node as visited.
    vis[node] = 1;

    // Add the current node to the answer vector as it is visited during DFS traversal.
    ans.push_back(node);

    // Explore all adjacent nodes of the current node.
    for (auto &adjNode : adj[node]) {
        // If the adjacent node is not visited, recursively call the DFS function on that node.
        if (!vis[adjNode]) {
            dfs(adjNode, adj, vis, ans);
        }
    }
}

// Function to return a list containing the DFS traversal of the graph.
// The function takes the number of vertices 'V' and the adjacency list 'adj[]' as inputs.
vector<int> dfsOfGraph(int V, vector<int> adj[]) {
    // Create an array to keep track of visited nodes.
    int vis[V] = {0};

    // Vector to store the DFS traversal order.
    vector<int> ans;

    // Choose a starting node for DFS (here, node 0 is chosen), mark it as visited.
    int startNode = 0;
    vis[startNode] = 1;

    // Perform DFS traversal from the starting node.
    dfs(startNode, adj, vis, ans);

    // Return the vector containing the DFS traversal result.
    return ans;
}


Yes, the same code will run for both undirected and directed graphs without any modifications. 
The reason is that the Depth-First Search (DFS) algorithm itself remains the same for both types of graphs. 
The code's logic does not depend on the type of graph, and it correctly traverses the graph, visiting all reachable nodes.

The DFS algorithm explores nodes deeply before backtracking and continuing to explore other branches. 
This approach works well for both undirected and directed graphs. The main difference between the two types 
of graphs lies in how the adjacency list is constructed, but the DFS traversal remains the same regardless.

The DFS algorithm explores nodes deeply before visiting neighbors, which makes it suitable for tasks like finding connected components, 
detecting cycles, and searching for paths in a graph. It can also be used to topologically sort a directed acyclic graph. 
The order in which nodes are visited during DFS depends on the order of edges in the adjacency list.

Time Complexity: For an undirected graph, O(N) + O(2E), For a directed graph, O(N) + O(E), 
                 Because for every node we are calling the recursive function once, the time taken is O(N) and 2E is for total   
                 degrees as we traverse for all adjacent nodes.

Space Complexity: O(3N) ~ O(N), Space for dfs stack space, visited array and an adjacency list.

**********************************************************************************************************************************************************************










