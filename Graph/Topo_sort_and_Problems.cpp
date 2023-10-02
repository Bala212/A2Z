Topo sort is not valid in graph which are undirected or having edges.

Hence, it is only valid in Directed Acyclic Graph(DAG).

1) Topological sort using DFS

*DFS karat karat depth nmadhe jaa, ani yettana (backtrack) stack madhe push karat chala!!

Intuition:
Since we are inserting the nodes into the stack after the completion of the traversal, we are making sure, 
there will be no one who appears afterward but may come before in the ordering as everyone during the traversal 
would have been inserted into the stack. 

class Solution
{
public:
    // Helper function to perform depth-first search for topological sorting.
    void dfsTopo(int node, int vis[], vector<int> adj[], stack<int> &s)
    {
        vis[node] = 1; // Mark the current node as visited.
        
        // Traverse all adjacent nodes of the current node.
        for (auto &adjNode : adj[node])
        {
            if (!vis[adjNode]) // If the adjacent node is not visited, then visit it.
            {
                dfsTopo(adjNode, vis, adj, s);
            }
        }
        
        s.push(node); // Push the current node into the stack after all its adjacent nodes are processed.
    }

    // Function to return a list containing vertices in topological order. 
    vector<int> topoSort(int V, vector<int> adj[]) 
    {
        int vis[V] = {0}; // Initialize a visited array to keep track of visited nodes.
        
        stack<int> s; // Create a stack to store the vertices in topological order.
        
        // Perform DFS on all unvisited nodes to find the topological order.
        for (int i = 0; i < V; i++)
        {
            if (!vis[i])
                dfsTopo(i, vis, adj, s);
        }
        
        vector<int> ans; // Create a vector to store the final topological order.
        
        // Pop elements from the stack and add them to the result vector to get the topological order.
        while (!s.empty())
        {
            ans.push_back(s.top());
            s.pop();
        }
        
        return ans; // Return the topological order as a vector.
    }
};

Time Complexity: O(V+E)+O(V), where V = no. of nodes and E = no. of edges. There can be at most V components. So, another O(V) time complexity.

Space Complexity: O(2N) + O(N) ~ O(2N): O(2N) for the visited array and the stack carried during DFS calls and O(N) for recursive stack space, 
                  where N = no. of nodes.

---------------------------------------------------------------------------------------------------------------------------
2) Kahns algorithm|Topological sort Algorithm using BFS

a) Find the indegrees of all the nodes.
b) Insert all nodes with indegree 0 into the queue.
c) Take them out of the queue one by one and reduce the indegree of the adjacent nodes(remove the links with adjacent nodes).
d) By reducing the indegree, if it becomes zero then push that adjacent node into the queue means that whichever nodes were
   coming towards this adjacent nodes are all present in the queue/are processed, so you also can go into the queue and be
   the part of the topo sort.

The provided code implements topological sorting using Breadth-First Search (BFS) by calculating the indegree of each 
vertex and using a queue to keep track of vertices with indegree 0. The algorithm starts by finding all vertices with 
indegree 0 and adds them to the queue. It then repeatedly removes a vertex from the queue, adds it to the topological 
order, and updates the indegree of its adjacent nodes. If an adjacent node's indegree becomes 0, it is added to the queue. 
The process continues until all vertices are processed, and the resulting ans vector contains the topological order of the 
vertices in the graph.

Note: Points to remember when a node is popped out, indegrees for all its adjacent 
nodes are decreased by one and if any of them becomes 0, we push that node into 
the queue. Meanwhile, WE INCLUDE THE CURRENT NODE IN THE ANSWER 
IMMEDIATELY AFTER IT IS POPPED OUT OF THE QUEUE.

class Solution
{
public:
    // Function to return a list containing vertices in Topological order. 
    vector<int> topoSort(int V, vector<int> adj[]) 
    {
        vector<int> indegree(V, 0); // Create an array to store the indegree of each vertex, initialized to 0.
        
        // Calculate the indegree of each vertex by traversing the adjacency list.
        for (int i = 0; i < V; i++)
        {
            for (auto adjNode : adj[i])
            {
                indegree[adjNode]++; // Increment the indegree of the adjacent node.
            }
        }
        
        queue<int> q; // Create a queue to perform BFS.
        
        // Find all vertices with indegree 0 (no incoming edges) and add them to the queue.
        for (int i = 0; i < V; i++)
        {
            if (indegree[i] == 0)
            {
                q.push(i);
            }
        }
        
        vector<int> ans; // Create a vector to store the topological order.
        
        // Perform BFS starting from vertices with indegree 0.
        while (!q.empty())
        {
            int node = q.front(); // Get the front element from the queue.
            q.pop(); // Remove the front element.
            
            ans.push_back(node); // Add the current node to the topological order.
            
            // Traverse all adjacent nodes of the current node.
            for (auto &adjNode : adj[node])
            {
                indegree[adjNode]--; // Decrement the indegree of the adjacent node.
                if (indegree[adjNode] == 0) // If the indegree becomes 0, add the adjacent node to the queue.
                {
                    q.push(adjNode);
                }
            }
        }
        
        return ans; // Return the topological order as a vector.
    }
};

Time Complexity: O(V+E), where V = no. of nodes and E = no. of edges. This is a simple BFS algorithm.

Space Complexity: O(N) + O(N) ~ O(2N), O(N) for the indegree array, and O(N) for the queue data structure used in BFS(where N = no.of nodes).

---------------------------------------------------------------------------------------------------------------------------
3) Cycle Detection in Directed Graph using BFS.

1) Topo sort generate kaadh/ kivva topo madhe kiti elements yetil te count kar.
2) Jar topo sort array chi size total/kivva count number of nodes evdhi nasel tr 
cycle ahe!! Karan, topo sort haa Directed Acyclic Graph sathi nighto, baki sathi nahi.

Topo sort nahi ala mhnje Cyclic dependancy ahe graph madhe !!

class Solution {
public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(int V, vector<int> adj[]) {
        vector<int> indegree(V, 0); // Create an array to store the indegree of each vertex, initialized to 0.

        // Calculate the indegree of each vertex by traversing the adjacency list.
        for (int i = 0; i < V; i++) {
            for (auto adjNode : adj[i]) {
                indegree[adjNode]++; // Increment the indegree of the adjacent node.
            }
        }

        queue<int> q; // Create a queue to perform BFS.

        // Find all vertices with indegree 0 (no incoming edges) and add them to the queue.
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        int elementsInTopoSort = 0; // Initialize a variable to count the number of elements in the topological order.

        // Perform BFS starting from vertices with indegree 0.
        while (!q.empty()) {
            int node = q.front(); // Get the front element from the queue.
            q.pop(); // Remove the front element.

            elementsInTopoSort++; // Increment the count of elements in the topological order.

            // Traverse all adjacent nodes of the current node.
            for (auto &adjNode : adj[node]) {
                indegree[adjNode]--; // Decrement the indegree of the adjacent node.
                if (indegree[adjNode] == 0) { // If the indegree becomes 0, add the adjacent node to the queue.
                    q.push(adjNode);
                }
            }
        }

        // If the number of elements in the topological order is less than the total number of vertices (V),
        // then there must be a cycle in the directed graph, so return true. Otherwise, return false.
        return elementsInTopoSort != V;
    }
};

Time Complexity: O(V+E), where V = no. of nodes and E = no. of edges. This is a simple BFS algorithm.

Space Complexity: O(N) + O(N) ~ O(2N), O(N) for the indegree array, and O(N) for the queue data structure used in BFS(where N = no.of nodes).

---------------------------------------------------------------------------------------------------------------------------
4) Course Schedule I(leetcode) | Pre-requisite Tasks(GFG) | Topological Sort (Topo sort is used!):

Question says- SOMETHING BEFORE SOMETHING! Try TOPO SORT NAA

1) Convert the given array of pairs into adjacency list arthat graph create kara!!
2) Ani ata jar ya graph (directed) madhe cycle detect zali tar, apan courses nahi
     karu shakat.
3) We will use BFS (kahns algo ) here to detect a cycle, bcoz next question ask 
     us to print those processes. Though we can use DFS also no issues.

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        int V = numCourses; // Number of courses (vertices) in the graph.
        vector<int> adj[V]; // Create an array of vectors to represent the adjacency list.

        // Build the adjacency list using the prerequisites vector.
        for (auto &val : prerequisites) {
            adj[val[1]].push_back(val[0]); // Add the edge (val[1] -> val[0]) to the adjacency list.
        }

        // Create an array to store the indegree of each vertex, initialized to 0.
        vector<int> indegree(V, 0);

        // Calculate the indegree of each vertex by traversing the adjacency list.
        for (int i = 0; i < V; i++) {
            for (auto &val : adj[i]) {
                indegree[val]++;
            }
        }

        queue<int> q; // Create a queue to perform BFS.

        // Find all vertices with indegree 0 (no incoming edges) and add them to the queue.
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> topo; // Create a vector to store the topological order.

        // Perform BFS starting from vertices with indegree 0.
        while (!q.empty()) {
            int node = q.front(); // Get the front element from the queue.
            q.pop(); // Remove the front element.

            topo.push_back(node); // Add the current node to the topological order.

            // Traverse all adjacent nodes of the current node.
            for (auto &val : adj[node]) {
                indegree[val]--; // Decrement the indegree of the adjacent node.
                if (indegree[val] == 0) { // If the indegree becomes 0, add the adjacent node to the queue.
                    q.push(val);
                }
            }
        }

        // If the number of elements in the topological order is less than the total number of courses (V),
        // it means that there is a cycle in the graph, and it is impossible to finish all courses.
        if (topo.size() != V) {
            return false;
        }
        
        // Otherwise, the graph is acyclic, and all courses can be finished.
        return true;
    }
};

Finally, if the number of elements in the topological order is not equal to the total number of courses (V), 
it indicates that there is a cycle in the graph, and the function returns false. Otherwise, if the graph is 
acyclic, it returns true, indicating that all courses can be finished without any circular dependencies.

Time Complexity: O(V+E), where V = no. of nodes and E = no. of edges. This is a simple BFS algorithm.

Space Complexity: O(N) + O(N) ~ O(2N), O(N) for the indegree array, and O(N) for the queue data structure used in BFS(where N = no.of nodes).
                  Extra O(N) for storing the topological sorting. Total ~ O(3N).

---------------------------------------------------------------------------------------------------------------------------
5) Course Schedule II | Topological Sort (using BFS to store tha topo sort, though we can use DFS also):

If we are able to complete all tasks successfully then print the order in which tasks
are to be done ( i.e. print the topo sort) otherwise return false;

If cycle is not present, means all tasks can be performed then return the topo sort
of the graph otherwise return empty vector.

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        int V = numCourses; // Number of courses (vertices) in the graph.
        vector<int> adj[V]; // Create an array of vectors to represent the adjacency list.

        // Build the adjacency list using the prerequisites vector.
        for (auto &val : prerequisites) {
            adj[val[1]].push_back(val[0]); // Add the edge (val[1] -> val[0]) to the adjacency list.
        }

        // Create an array to store the indegree of each vertex, initialized to 0.
        vector<int> indegree(V, 0);

        // Calculate the indegree of each vertex by traversing the adjacency list.
        for (int i = 0; i < V; i++) {
            for (auto &val : adj[i]) {
                indegree[val]++;
            }
        }

        queue<int> q; // Create a queue to perform BFS.

        // Find all vertices with indegree 0 (no incoming edges) and add them to the queue.
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        vector<int> topo; // Create a vector to store the topological order.

        // Perform BFS starting from vertices with indegree 0.
        while (!q.empty()) {
            int node = q.front(); // Get the front element from the queue.
            q.pop(); // Remove the front element.

            topo.push_back(node); // Add the current node to the topological order.

            // Traverse all adjacent nodes of the current node.
            for (auto &val : adj[node]) {
                indegree[val]--; // Decrement the indegree of the adjacent node.
                if (indegree[val] == 0) { // If the indegree becomes 0, add the adjacent node to the queue.
                    q.push(val);
                }
            }
        }

        // If the number of elements in the topological order is not equal to the total number of courses (V),
        // it means that there is a cycle in the graph, and it is impossible to finish all courses.
        if (topo.size() != V) {
            vector<int> empty; // Create an empty vector to return in case of a cycle.
            return empty;
        }
        
        // Otherwise, the graph is acyclic, and all courses can be finished.
        return topo; // Return the topological order vector.
    }
};

Finally, if the number of elements in the topological order is not equal to the total number of courses (V), 
it indicates that there is a cycle in the graph, and the function returns an empty vector. Otherwise, if the 
graph is acyclic, it returns the topological order vector, representing the order in which courses can be taken.

Time Complexity: O(V+E), where V = no. of nodes and E = no. of edges. This is a simple BFS algorithm.

Space Complexity: O(N) + O(N) ~ O(2N), O(N) for the indegree array, and O(N) for the queue data structure used in BFS(where N = no.of nodes). 
                  Extra O(N) for storing the topological sorting. Total ~ O(3N).

---------------------------------------------------------------------------------------------------------------------------
6) Find Eventual Safe States – BFS – Topological Sort:

Using BFS (Topo Sort | Kahns Algorithm)

Note: Points to remember that any node which is a part of a cycle or leads to the 
cycle through an incoming edge towards the cycle, cannot be a safe node. Apart 
from these types of nodes, every node is a safe node.

a) Terminal nodes chi outdegree zero ahe, te terminal nodes ahe barobar, mg samja
apan terminal node pasun suruvat keli baghayla ki baba kon kon terminal nodes 
kade yeu shakta te safe nodes astil barobar.

b) Mhnje aaplyala terminal node pasun start karaych ahe ani baghat jaych kon kon
mazya paryant yeu shakto.

c) Ata te apan kasa karnar hai na, apan kay karu apan ulta karu apan terminal nodes
pasun suruwat karu ani nodes la mokla karat chalu.

d) Mokla kasa krnar, tr Topo sort algo use karun(Indegree vala | BFS), pn ithe tar
terminal nodes chi outdegree zero ahe, aani aaplyala topo sort sathi indegee jyanchi
zero ae te nodes pahije start karayla, mg tyasathi apan GRAPH CHE EDGES 
REVERSE KARU, mhnje jya nodes chi outdegree 0 ahe, tyanchi indegree zero hoel 
ani outdegree non zero hoel.

e) Ata, jya nodes chi indegree zero ahe te terminal nodes ahet mg tithun apan start
karu traversal (topo sort) ani aju baju chya nodes la mokla karat chalu (indegree 
reduce karun adjacent nodes chi) jya nodes chi indegree zero hoel tee safe nodes 
astil, karan tyanchi terminal nodes ne ch tyanci indegree zero keli ahe, mhnje te 
terminal node kade jau shakta hai na, mhnjech kay ki te safe ahet !!

f) Mg je tuzya topo sort madhe elements astil, te tuze safe nodes astil, karan tu 
topo sort madhe tech nodes push karto jyanchi indegree zero ahe, karan te queue
madhun yetat ani apan queue madhe tech nodes push karto jyanchi indegree zero
ahe!!

class Solution {
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int V = graph.size(); // Get the total number of nodes in the graph
        vector<int> indegree(V, 0); // Create an array to store the in-degrees of each node
        vector<int> revAdj[V]; // Create an array of vectors to represent the reverse adjacency list

        // Create the reverse adjacency list by traversing the given adjacency list
        for (int i = 0; i < V; i++) {
            for (auto &val : graph[i]) {
                revAdj[val].push_back(i); // Add the reverse edge to the corresponding node
            }
        }

        // Calculate the in-degrees of each node by traversing the reverse adjacency list
        for (int i = 0; i < V; i++) {
            for (auto &adjNode : revAdj[i]) {
                indegree[adjNode]++; // Increment the in-degree of the adjacent node
            }
        }

        queue<int> q; // Create a queue to perform BFS traversal
        vector<int> safeNodes; // Create a vector to store the eventual safe nodes

        // Add all nodes with in-degree 0 to the queue initially
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        // Perform BFS to find the eventual safe nodes
        while (!q.empty()) {
            int node = q.front(); // Get the front node from the queue
            q.pop();

            safeNodes.push_back(node); // Add the node to the list of safe nodes

            // Reduce the in-degree of the adjacent nodes and add them to the queue if in-degree becomes 0
            for (auto &adjNode : revAdj[node]) {
                indegree[adjNode]--;
                if (indegree[adjNode] == 0) {
                    q.push(adjNode);
                }
            }
        }

        sort(safeNodes.begin(), safeNodes.end()); // Sort the safe nodes in ascending order

        return safeNodes; // Return the eventual safe nodes in topological order
    }
};

The algorithms intuition is to identify the eventual safe nodes in a directed graph. It does this by using a BFS 
approach to gradually eliminate nodes with in-degree 0, starting from the nodes that have no incoming edges. 
As nodes are eliminated, their adjacent nodes may become candidates for eventual safe nodes if they have no other incoming edges. 
The algorithm continues this process until all reachable nodes are considered and adds them to the list of eventual safe nodes. 
The final result is a sorted list of nodes representing the ones that will not be part of any cycles and are considered eventually safe in the graph.

Time Complexity: O(V+E)+O(N*logN), where V = no. of nodes and E = no. of edges. This is a simple BFS algorithm. 
		 Extra O(N*logN) for sorting the safeNodes array, where N is the number of safe nodes.

Space Complexity: O(N) + O(N) + O(N) ~ O(3N), O(N) for the indegree array, O(N) for the queue data structure used 
                  in BFS(where N = no.of nodes), and extra O(N) for the adjacency list to store the graph in a reversed order.

---------------------------------------------------------------------------------------------------------------------------
7) Alien Dictionary – Topological Sort: 

Again the question says SOMETHING BEFORE SOMETHING !!

1) From each consecutive pair of words, figure out who is appearing before whom
     by considering first non equal alphabets in two words and create a corresponding 
     graph (The graph will be directed)

2) Return the topo sort of the created graph using BFS/DFS, that will be the 
     sequence of alphabets in Alien dictionary.

Note: The intuition is to check every consecutive pair of words and find out the differentiating factor. 
      With these factors, we will form a directed graph, and the whole problem balls down to a topological sort of problem.

// User function Template for C++
class Solution {
public:
    string findOrder(string dict[], int n, int K) {
        // Create an adjacency list to represent the character dependencies
        vector<int> adj[K];
        // Create an array to store the in-degrees of each character node
        int indegree[K] = {0};

        // Build the adjacency list and calculate in-degrees based on the given dictionary
        for (int i = 0; i < n - 1; i++) {
            string s1 = dict[i];
            string s2 = dict[i + 1];
            int len = min(s1.size(), s2.size());
            for (int j = 0; j < len; j++) {
                if (s1[j] != s2[j]) {
                    // Add an edge from character s1[j] to character s2[j]
		            // a - 0, b - 1, c - 2... and so on
                    adj[s1[j] - 'a'].push_back(s2[j] - 'a');
                    // Increment the in-degree of character s2[j]
                    indegree[s2[j] - 'a']++;
                    break;
                }
            }
        }

        // Perform a topological sort using BFS
        queue<int> q;
        // Initialize the queue with nodes having in-degree 0
        for (int i = 0; i < K; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        string ans = "";
        // Process the nodes in the queue and update in-degrees of adjacent nodes
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            // Add the character representation of the node to the answer string
	    // get back the character from int: 0 - a, 1 - b, 2 - c... and so on
            ans.push_back(node + 'a');
            // Reduce the in-degree of adjacent nodes and add them to the queue if in-degree becomes 0
            for (auto &val : adj[node]) {
                indegree[val]--;
                if (indegree[val] == 0) {
                    q.push(val);
                }
            }
        }

        // Return the topological order as the answer
        return ans;
    }
};

The follow-up question for the interview:

When is the ordering not possible?
There are two such cases when ordering is not possible:
a) If every character matches and the largest word appears before the shortest word: For example, if “abcd” appears before “abc”, 
   we can say the ordering is not possible.
b) If there exists a cyclic dependency between the characters: For example, in the dictionary: dict: {“abc”, “bat”, “ade”} 
   there exists a cyclic dependency between ‘a’ and ‘b’ because the dictionary states ‘a’ < ‘b’ < ‘a’, which is not possible.


Time Complexity: O(N*len)+O(K+E), where N is the number of words in the dictionary, ‘len’ is the length up to the index where the first inequality occurs, 
                 K = no. of nodes, and E = no. of edges.

Space Complexity: O(K) + O(K)+O(K)+O(K) ~ O(4K), O(K) for the indegree array, and O(K) for the queue data structure used in BFS
                  (where K = no.of nodes), O(K) for the answer array and O(K) for the adjacency list used in the algorithm.
*************************************************************************************************************************************************************************
