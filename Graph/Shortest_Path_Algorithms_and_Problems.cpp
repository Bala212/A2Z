1) Shortest Path in Directed Acyclic Graph | Topological Sort

Topo sort kadhun, topo sort nusar adjacent nodes relax kar!!

1) Do a topo sort of given DAG( use DFS/BFS), if we use DFS, let it come into the 
     stack. Do topo for each component of graph.

2) Take nodes out of the stack one by one, and relax the adjacent nodes(relaxing 
     means update the distance), this adjacent nodes will be the nodes ahead of the 
     current popped node, as it is a topo sort na, YES uk! 

3) Declare and Initialize a distance array with infinity which will store the distance of
     node 'i' from the source.

Mhnje apan kay krtoy basically, apan start karat ahot source pasna (jyachyakade koni
yet nhiye) ani apan tya node chya pudche nodes(adjacent nodes pudche) la visit 
karat ahot ani distacne update karat ahot jar pudchya node cha current distance 
motha ahe current node + tyanchyatla weight ya pekshya tr apan te update krto, ata 
te pudche nodes kashe kadhayche? tar te kadhayche topo sort ne, tula mahiti ae 
topo sort kay krta te asa sort krta ki ek node chya pudche nodes tyachya nantr yeun 
basta. Asa pudhe jaat jaat apan pratyek node cha distance update krto! Topo sort 
hee sure krta ki, current chya pudche sagle nodes tyachya pudhe ahe topo sort 
madhe, mhanun aaplyala soppa jata traverse karayla graph ani distance update 
karayla!! Topo sort chya first node pasun chalu krto apan ani obviously toch source
node asnar, karan topo mhnje kay mahiti ae tula!



Here's the intuition behind the algorithm:

1. Topological Sorting:
   - The first step of the algorithm is to perform a Depth First Search (DFS) to obtain the topological order of the nodes in the graph. 
     Topological Sorting is only possible in Directed Acyclic Graphs (DAGs).
   - The DFS starts from the source node (node 0) and recursively explores its adjacent nodes in a depth-first manner.
   - Once all the adjacent nodes are visited and marked as visited, the current node is pushed onto a stack. 
     This stack will contain nodes in the order of their finishing times, with the node at the top of the stack being the last to finish.

2. Shortest Path Calculation:
   - After obtaining the topological order of nodes, the algorithm initializes an array `dist` to store the shortest distances from the 
     source node (node 0) to all other nodes in the graph.
   - The distance from the source node to itself is set to 0 since the distance from a node to itself is always 0.
   - The algorithm then processes nodes in the topological order from the stack.
   - For each node `node` popped from the stack, the algorithm examines its adjacent nodes (neighbors).
   - For each adjacent node `adjNode`, the algorithm tries to update its shortest distance from the source node by considering the weight 
     of the edge from `node` to `adjNode`. If the path through `node` to `adjNode` is shorter than the current shortest distance to `adjNode`,
     the distance is updated.
   - By traversing the nodes in topological order, the algorithm guarantees that for each node, all the incoming edges 
     (edges from nodes that come before it in the topological order) have already been processed. Thus, the shortest distance to each node is correctly calculated.

3. Handling Unreachable Nodes:
   - If a node is unreachable from the source node, its distance remains set to a large value (1e9 in this case). To represent these unreachable nodes, 
     the algorithm converts all nodes with a distance of 1e9 to -1 before returning the final shortest distance array.

Intuition Summary:
The algorithm leverages the power of Topological Sorting to process nodes in an order that ensures the shortest distances are calculated correctly. 
By starting from the source node and exploring the graph in a topological order, the algorithm efficiently computes the shortest paths from the source 
to all other nodes, handling unreachable nodes gracefully. The algorithms time complexity is influenced by both the DFS for Topological Sorting and 
the Shortest Path calculation, resulting in a time complexity of O(N + M), where N is the number of nodes and M is the number of edges in the graph.

class Solution {
public:

    // Depth First Search (DFS) function to perform Topological Sorting
    // and store the nodes in a stack in the order of their finishing times.
    void dfsTopo(int node, vector<pair<int, int>> adj[], int vis[], stack<int>& s) {
        vis[node] = 1; // Mark the current node as visited.

        // Traverse all adjacent nodes of the current node.
        for (auto& it : adj[node]) {
            int adjNode = it.first;
            if (!vis[adjNode]) // If the adjacent node is not visited, then visit it.
            {
                dfsTopo(adjNode, adj, vis, s);
            }
        }

        s.push(node); // Push the current node into the stack after all its adjacent nodes are processed.
    }

    // Function to find the shortest path from node 0 to all other nodes in the graph.
    vector<int> shortestPath(int N, int M, vector<vector<int>>& edges) {
        vector<pair<int, int>> adj[N]; // Adjacency list to store the graph.

        // Building the adjacency list from the given edges.
        for (int i = 0; i < M; i++) {
            int u = edges[i][0];
            int v = edges[i][1];
            int wt = edges[i][2];
            adj[u].push_back({v, wt});
        }

        stack<int> st; // Stack to store nodes in topological order.

        int vis[N] = {0}; // Array to keep track of visited nodes.

        // Perform Topological Sort to get the order of nodes in the stack.
        for (int i = 0; i < N; i++) {
            if (!vis[i]) dfsTopo(i, adj, vis, st);
        }

        vector<int> dist(N, 1e9); // Initialize an array to store the shortest distances from node 0 to all other nodes.
        dist[0] = 0; // Distance from node 0 to itself is 0. (it can be any source)

        // Process nodes in topological order to find the shortest paths.
        while (!st.empty()) {
            int node = st.top();
            st.pop();

            // Relaxation: Update the distances of adjacent nodes if a shorter path is found.
            for (auto& it : adj[node]) {
                int adjNode = it.first;
                int wt = it.second;
                if (dist[node] + wt < dist[adjNode]) {
                    dist[adjNode] = dist[node] + wt;
                }
            }
        }

        // Convert nodes with a distance of 1e9 (unreachable) to -1.
        for (int i = 0; i < N; i++) {
            if (dist[i] == 1e9) {
                dist[i] = -1;
            }
        }

        return dist; // Return the array containing the shortest distances from node 0 to all other nodes.
    }
};

Time Complexity: O(N+M) {for the topological sort} + O(N+M) {for relaxation of vertices, each node and its adjacent nodes get traversed} ~ O(N+M).
                 Where N= number of vertices and M= number of edges.

Space Complexity:  O( N) {for the stack storing the topological sort} + O(N) {for storing the shortest distance for each node} 
                   + O(N) {for the visited array} + O( N+2M) {for the adjacency list} ~ O(N+M) .
                   Where N= number of vertices and M= number of edges.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
2) Shortest Path in Undirected Graph with unit distance

Simple BFS!
1) Create dist array, dist[src] = 0
2) Src node queue madhe push kar, ani traversal chalu kar.
3) Adjacent nodes cha distance update karat jaa, jar chota asel tr

Notes ani article vaach

class Solution {
public:
    vector<int> shortestPath(vector<vector<int>>& edges, int N, int M, int src) {
        // Create an adjacency list of size N for storing the undirected graph.
        vector<int> adj[N];
        for (auto it : edges) {
            adj[it[0]].push_back(it[1]);
            adj[it[1]].push_back(it[0]);
        }

        // A dist array of size N initialized with a large number to indicate that initially all the nodes are untraversed.
        vector<int> dist(N, 1e9);

        // BFS Implementation.
        dist[src] = 0; // The distance from the source node to itself is 0.
        queue<int> q;
        q.push(src);

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            // Traverse all adjacent nodes of the current node.
            for (auto adjNode : adj[node]) {
                // If a shorter path to the adjacent node is found, update the distance and add it to the queue for further exploration.
                if (dist[node] + 1 < dist[adjNode]) {
                    dist[adjNode] = 1 + dist[node]; // The weight of all edges is considered to be 1 in this unweighted graph.
                    q.push(adjNode);
                }
            }
        }

        // Updated shortest distances are stored in the resultant array ‘ans’.
        // Unreachable nodes are marked as -1.
        for (int i = 0; i < N; i++) {
            if (dist[i] == 1e9) {
                dist[i] = -1;
            }
        }

        return dist;
    }
};

Time Complexity: O(M) { for creating the adjacency list from given list ‘edges’} + O(N + 2M) { for the BFS Algorithm} 
                 + O(N) { for adding the final values of the shortest path in the resultant array} ~ O(N+2M).    
                 Where N= number of vertices and M= number of edges.

Space Complexity:  O( N) {for the stack storing the BFS} + O(N) {for the resultant array} 
                   + O(N) {for the dist array storing updated shortest paths} + O( N+2M) {for the adjacency list} ~ O(N+M) .
                   Where N= number of vertices and M= number of edges.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
3) Word Ladder 1 | BFS shortest path

1) BFS |  Level wise jaato.
2) Start word push karto queue madhe, set madhun erase krto
3) Dar veles queue madhun pop karun tyacha ek ek characters change karun to set
     madhe ahe ki nahi bghto, jar asel tr steps + 1 karun to word push karto ani set 
     madhun erase karto.
4) Queue madun pop kelayvr pratyek veles to endWord ahe ki nahi check krto, asel 
     tr tyache steps return krto, mhnje kay ki to tecdhya steps ne hit zala ahe, ani te
    minimum astil.

First time when I encounter 'endWord' I will stop there and return the current
distance we come so far.

Article ani tuze notes bagh!!

The algorithm uses a breadth-first search (BFS) approach to find the shortest transformation path from the `beginWord` to the `endWord` 
by making valid one-character changes at each step. It explores all possible words that can be formed from the `beginWord` and checks 
if they exist in the `wordList`. If a valid word is found, it is added to the queue with an incremented step count. The process continues 
until the `endWord` is reached or all valid transformations are explored. The BFS guarantees that the shortest path is found first, 
and it efficiently avoids revisiting words to ensure the shortest transformation sequence is obtained. If no transformation path is found, 
the algorithm returns 0. The time complexity is influenced by the number of words in the `wordList` and the average length of the words.

First time when I encounter 'endWord' I will stop there and return the current
distance we come so far.

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // Create an unordered_set 's' to efficiently check if a word exists in the wordList.
        unordered_set<string> s(wordList.begin(), wordList.end());

        // Create a queue 'q' to perform BFS and keep track of words and their corresponding steps.
        queue<pair<string, int>> q;

        // Push the initial word (beginWord) to get started with the BFS.
        q.push({beginWord, 1});

        // Remove the initial word from 's' to ensure we do not visit it again in the BFS.
        s.erase(beginWord);

        // Perform BFS, exploring words level by level to find the shortest transformation path.
        while (!q.empty()) {
            string word = q.front().first; // Get the current word from the queue.
            int steps = q.front().second; // Get the steps taken to reach the current word.
            q.pop();

            if (word == endWord) return steps; // If the current word matches the endWord, we found the shortest path.

            // Explore all possible one-character changes in the current word and check if the new word exists in 's'.
            // If it does, add it to the queue with an incremented step count and remove it from 's' to avoid revisiting.
            for (int i = 0; i < word.size(); i++) {
                char origChar = word[i]; // Store the original character to revert it later.

                // Try all possible characters 'ch' (a to z) at the current position 'i'.
                for (char ch = 'a'; ch <= 'z'; ch++) {
                    word[i] = ch; // Change the character at the current position.

                    // Check if the new word exists in 's', and if so, enqueue it with an incremented step count.
                    if (s.find(word) != s.end()) {
                        q.push({word, steps + 1});
                        s.erase(word); // Remove the word from 's' to avoid revisiting.
                    }
                }

                word[i] = origChar; // Revert the character back to its original state for the next iteration.
            }

	    // The above loop will always run for each word
        }

        return 0; // If there is no transformation path, return 0 as there is no way to reach endWord.
    }
};

Time Complexity: O(N * M * 26) (As for loop will run evertytime for each word!!, Where as in simple BFS inner for loop was running overall for 2E times!!)
                 Where N = size of wordList Array and M = word length of words present in the wordList..
                 Note that, hashing operations in an unordered set takes O(1) time, but if you want to use set here, then the time complexity 
		 would increase by a factor of log(N) as hashing operations in a set take O(log(N)) time.

Space Complexity:  O( N ) { for creating an unordered set and copying all values from wordList into it } 
                   Where N = size of wordList Array.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
4) Word Ladder 2 | BFS | Queue of vector of string

The algorithm aims to find all valid word sequences from `beginWord` to `endWord` using a breadth-first search (BFS) approach. 
It starts with an initial sequence containing only `beginWord` and enqueues it into a queue. The BFS explores all possible 
transformations of words from the `beginWord`, making one-character changes at each step, and checks if the new words exist in the `wordList`.

The BFS guarantees that the shortest transformation paths are found first, as it explores words level by level. During the BFS, 
it keeps track of the words used at each level to avoid revisiting them at subsequent levels, which ensures that all possible 
transformation paths are considered efficiently.

For each word in the queue, it explores all possible one-character changes and checks if the new word exists in the `wordList`. 
If a valid word is found, it is appended to the current word sequence and enqueued back into the queue for further exploration. 
The algorithm continues the BFS until all possible transformation paths are considered, and valid word sequences from `beginWord` to `endWord` are obtained.

The algorithm efficiently finds all valid sequences because it explores the word transformations level by level, starting from `beginWord`, 
and stops exploring further once it reaches the `endWord`. By keeping track of the used words at each level, it ensures that no word is revisited, 
which helps avoid unnecessary computation.

Overall, the algorithm guarantees that all valid transformation paths from `beginWord` to `endWord` are found and returned as a 
collection of word sequences. The time complexity is influenced by the number of words in the `wordList` and the average length 
of the words, and the space complexity is determined by the number of valid word sequences found.

class Solution {
public:
    vector<vector<string>> findSequences(string beginWord, string endWord, vector<string>& wordList) {
        // Create an unordered_set 's' to efficiently check if a word exists in the wordList.
        unordered_set<string> s(wordList.begin(), wordList.end());

        // Create a queue 'q' to perform BFS and keep track of word sequences.
        queue<vector<string>> q;

        // Push the initial word (beginWord) to get started with the BFS.
        q.push({beginWord});

        // Remove the initial word from 's' to ensure we do not visit it again in the BFS.
        s.erase(beginWord);

        vector<string> usedOnLevel; // Keep track of words used at the current level of BFS.
        usedOnLevel.push_back(beginWord);

        int level = 0; // Initialize the level of BFS to 0.
        vector<vector<string>> ans; // Initialize the vector to store the result.

        // Perform BFS to find word sequences from beginWord to endWord.
        while (!q.empty()) {
            vector<string> vec = q.front(); // Get the current word sequence from the queue.
            q.pop();
            
            // If size is not increased then, we are on the same level!!
            if (vec.size() > level) {
                // At the beginning of a new level, remove all words used at the previous level from 's'.
                for (auto& val : usedOnLevel) {
                    s.erase(val);
                }
                level++;
            }

            string word = vec.back(); // Get the last word in the current sequence.

            if (word == endWord) {
                // If the current word matches the endWord, we found a valid sequence.
                if (ans.size() == 0) {
                    ans.push_back(vec); // If ans is empty, directly add the word sequence to ans.
                }
                else if (ans[0].size() == vec.size()) {
                    ans.push_back(vec); // If the word sequence has the same length as the previous sequences in ans, add it to ans.
                }
            }

            // Explore all possible one-character changes in the current word and check if the new word exists in 's'.
            // If it does, add it to the queue with the updated word sequence and keep track of used words for the current level.
            for (int i = 0; i < word.size(); i++) {
                char origChar = word[i]; // Store the original character to revert it later.

                // Try all possible characters 'ch' (a to z) at the current position 'i'.
                for (char ch = 'a'; ch <= 'z'; ch++) {
                    word[i] = ch; // Change the character at the current position.

                    // Check if the new word exists in 's', and if so, enqueue it with the updated word sequence.
                    if (s.find(word) != s.end()) {
			// If the word is valid (exists in wordList), add it to the current word sequence 'vec'
                        vec.push_back(word);

    			// Also, keep track of the used word at the current level in 'usedOnLevel'.
                        usedOnLevel.push_back(word);

			// Push the updated word sequence 'vec' (with the new word appended) into the queue 'q'.
                        q.push(vec);

			// Remove the last word from the sequence 'vec', so that it can be updated with different words in the next iteration, on the same level
                        vec.pop_back();
                    }
                }

                word[i] = origChar; // Revert the character back to its original state for the next iteration.
            }
        }

        return ans; // Return the result containing valid word sequences from beginWord to endWord.
    }
};

Time Complexity and Space Complexity: It cannot be predicted for this particular algorithm because there can be multiple 
sequences of transformation from startWord to targetWord depending upon the example, so we cannot define a fixed range 
of time or space in which this program would run for all the test cases.

Note: This approach/code will give TLE when solved on the Leetcode platform due to the strict time constraints being put up there. 

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
5) Dijkstra’s Algorithm – Using Priority Queue 

Everytime you get a distance which is better than the previous distance that 
means you discovered a new path so you take that distance and put it again into 
the pq always

Mhnje jyacha distance update zala, tr tyachya adjacent pn kami distance madhe asu
shakta na, mhanun apan parat priority queue madhe push karto! Ani tula algorithm 
pn kalali ki baba kaa priorty queue use krto, karan aaplyala nodes with miniumum
distance pahijet pahile, jyane karun lvkr lvkr shortest distances assign hotil!!

Intuition of Dijkstra's Algorithm:
Dijkstra's algorithm is used to find the shortest path from a source vertex to all other vertices in a 
weighted graph with non-negative edge weights. The algorithm maintains a priority queue (min-heap) to 
efficiently explore nodes and updates the shortest distances while traversing the graph.

Initialize a priority queue to store nodes and their tentative distances from the source vertex. 
Initially, the distance of the source vertex is set to 0, and all other distances are set to a very large value (infinity).

Push the source vertex into the priority queue with its distance as 0.

Start a loop that continues until the priority queue is empty:

a. Extract the node with the smallest distance from the priority queue.

b. Iterate over all the adjacent nodes of the current node.

c. For each adjacent node, calculate the tentative distance from the source vertex through the current node.

d. If the tentative distance is smaller than the current distance stored for the adjacent node, update 
   the distance and push the adjacent node into the priority queue with the updated distance.

After the loop ends, the dist vector will contain the shortest distances from the source vertex to all other vertices.

The algorithm works by selecting the node with the smallest distance from the priority queue in each iteration, 
guaranteeing that the shortest path to that node has been found. It then explores its neighbors, updating their 
distances if a shorter path is found. This process continues until all nodes are processed and the shortest 
distances to all vertices are determined. Dijkstra's algorithm is optimal when all edge weights are non-negative 
and is commonly used in routing and network algorithms. However, it may not work correctly with negative edge 
weights (for that, youd need to use other algorithms like Bellman-Ford).

Article vaach!!!
https://takeuforward.org/data-structure/dijkstras-algorithm-using-priority-queue-g-32/

class Solution
{
public:
    // Function to find the shortest distance of all the vertices
    // from the source vertex S using Dijkstra's algorithm.
    vector<int> dijkstra(int V, vector<vector<int>> adj[], int S)
    {
        // Create a priority queue to keep track of nodes and their distances.
        // The priority queue will be a min-heap, so the node with the smallest distance
        // will be at the top.
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        // Push the source vertex 'S' into the priority queue with distance 0.
        pq.push({0, S});

        // Create a vector to store the shortest distances from the source vertex to all other vertices.
        // Initialize all distances to a very large value, except the source vertex which has a distance of 0.
        vector<int> dist(V, 1e9);
        dist[S] = 0;

        // Start the main loop to explore nodes and update distances.
        while (!pq.empty())
        {
            // Get the node with the smallest distance from the priority queue.
            int node = pq.top().second;
            int distNode = pq.top().first;
            pq.pop();

            // Iterate over all adjacent nodes of the current node and update their distances if necessary.
            for (auto &it : adj[node])
            {
                int adjNode = it[0]; // The adjacent node's index.
                int adjWeight = it[1]; // The weight of the edge between the current node and the adjacent node.

                // If the new distance to the adjacent node through the current node is smaller than the current distance,
                // update the distance and push the adjacent node with the updated distance into the priority queue.
                if (distNode + adjWeight < dist[adjNode])
                {
                    dist[adjNode] = distNode + adjWeight;
                    pq.push({dist[adjNode], adjNode});
                }
            }
        }

        // Return the vector containing the shortest distances from the source vertex 'S' to all other vertices.
        return dist;
    }
};

Time Complexity : O( E log(V) ) 
Where E = Number of edges and V = Number of Nodes.

Space Complexity : O( |E| + |V| ) 
Where E = Number of edges and V = Number of Nodes.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
6) Dijkstra’s Algorithm – Using Set 

Using set we can erase the node with higher distance from set, if the smaller 
distance has found!! This we reduce the extra computations!! But overall there
is no so much difference, bcoz we are erasing from set na

class Solution
{
public:
    // Function to find the shortest distance of all the vertices
    // from the source vertex S using Dijkstra's algorithm with a set.
    vector<int> dijkstra(int V, vector<vector<int>> adj[], int S)
    {
        // Create a set 'st' for storing nodes as pairs {dist, node},
        // where 'dist' is the distance from the source to the node.
        // The set stores the nodes in ascending order of the distances.
        set<pair<int, int>> st;

        // Initialize the 'dist' vector with a large number to indicate that
        // the nodes are unvisited initially. This list contains distances from
        // the source to all the nodes.
        vector<int> dist(V, 1e9);

        // Insert the source vertex 'S' into the set with distance 0.
        st.insert({0, S});

        // Source vertex initialized with distance 0.
        dist[S] = 0;

        // Now, erase the minimum distance node first from the set and traverse
        // its adjacent nodes to update the shortest distances.
        while (!st.empty())
        {
            auto it = *(st.begin()); // Get the node with the smallest distance from the set.
            int node = it.second; // Extract the node.
            int dis = it.first; // Extract the distance.
            st.erase(it); // Erase the extracted node from the set.

            // Check all adjacent nodes of the erased element and update their distances.
            for (auto it : adj[node])
            {
                int adjNode = it[0]; // The adjacent node's index.
                int edgW = it[1]; // The weight of the edge between the current node and the adjacent node.

                if (dis + edgW < dist[adjNode])
                {
                    // If the adjacent node was visited previously at a greater cost,
                    // erase it from the set to update its distance later.
                    if (dist[adjNode] != 1e9)
                        st.erase({dist[adjNode], adjNode});

                    // If the current distance is smaller,
                    // update the distance and push the node into the set with the new distance.
                    dist[adjNode] = dis + edgW;
                    st.insert({dist[adjNode], adjNode});
                }
            }
        }
        // Return the vector containing the shortest distances from the source vertex 'S' to all other vertices.
        return dist;
    }
};


Time Complexity : O( E log(V) ) 
Where E = Number of edges and V = Number of Nodes.

Space Complexity : O( |E| + |V| ) 
Where E = Number of edges and V = Number of Nodes.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
7) Print Shortest Path – Dijkstra’s Algorithm

Intuition:

The intuition behind the above problem is based on Dijkstra’s Algorithm with a combination of a little 
bit of memoization in order to print the shortest possible path and not just calculate the shortest distance 
between the source and the destination node. In order to print the path we will try to remember the node 
from which we came while traversing each node by Dijkstra’s Algorithm along with calculating the shortest distance. 

An array called ‘parent’ can be used for this purpose which would store the parent node for each node and will 
update itself if a shorter path from a node is found at some point in time. This will help us to print the path 
easily at the end by backtracking through the parent array till we reach the source node.

class Solution
{
public:
    vector<int> shortestPath(int n, int m, vector<vector<int>> &edges)
    {
        // Create an adjacency list of pairs of the form node1 -> {node2, edge weight}
        // where the edge weight is the weight of the edge from node1 to node2.
        vector<pair<int, int>> adj[n + 1];
        for (auto it : edges)
        {
            adj[it[0]].push_back({it[1], it[2]});
            adj[it[1]].push_back({it[0], it[2]});
        }
        // Create a priority queue for storing the nodes along with distances 
        // in the form of a pair { dist, node }.
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>>> pq;

        // Create a dist array for storing the updated distances and a parent array
        //for storing the nodes from where the current nodes represented by indices of
        // the parent array came from.
        vector<int> dist(n + 1, 1e9), parent(n + 1);
        for (int i = 1; i <= n; i++)
            parent[i] = i;

        dist[1] = 0;

        // Push the source node to the queue.
        pq.push({0, 1});
        while (!pq.empty())
        {
            // Topmost element of the priority queue is with minimum distance value.
            auto it = pq.top();
            pq.pop();
            int node = it.second;
            int dis = it.first;

            // Iterate through the adjacent nodes of the current popped node.
            for (auto it : adj[node])
            {
                int adjNode = it.first;
                int edW = it.second;

                // Check if the previously stored distance value is 
                // greater than the current computed value or not, 
                // if yes then update the distance value.
                if (dis + edW < dist[adjNode])
                {
                    dist[adjNode] = dis + edW;
                    pq.push({dis + edW, adjNode});

                    // Update the parent of the adjNode to the recent 
                    // node where it came from.
                    parent[adjNode] = node;
                }
            }
        }

        // If distance to a node could not be found, return an array containing -1.
        if (dist[n] == 1e9)
            return {-1};

        // Store the final path in the ‘path’ array.
        vector<int> path;
        int node = n;

        // Iterate backwards from destination to source through the parent array.
        while (parent[node] != node)
        {
            path.push_back(node);
            node = parent[node];
        }
        path.push_back(1);

        // Since the path stored is in a reverse order, we reverse the array
        // to get the final answer and then return the array.
        reverse(path.begin(), path.end());
        return path;
    }
};

Time Complexity: O( E log(V) ) { for Dijkstra’s Algorithm } + O(V) { for backtracking in order to find the parent for each node } 
                 Where E = Number of edges and V = Number of Nodes.

Space Complexity: O( |E| + |V| ) { for priority queue and dist array } + O( |V| ) { for storing the final path } 
                  Where E = Number of edges and V = Number of Nodes.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
8) Shortest Distance in a Binary Maze (Queue fakt) 

https://practice.geeksforgeeks.org/problems/shortest-path-in-a-binary-maze-1655453161/1

A simple BFS logic, but no need of priority queue, as we are moving
always with a unit distance

1) Queue of {dist, {row, col}}.
2) Push source with dist 0 into queue.
3) Go on exploring neighbors, and add them into queue with increased dist by 1
4) Whenever we get a destination coordinates while exploring neighbors, we return
    dist + 1 i.e.  ( dist[nRow][nCol] ).
5) Else below BFS, return -1.

class Solution {
public:
    int shortestPath(vector<vector<int>> &grid, pair<int, int> source, pair<int, int> destination) {
        // Edge Case: if the source is only the destination.
        if (source.first == destination.first && source.second == destination.second)
            return 0;

        // Create a queue for storing cells with their distances from source
        // in the form {dist,{cell coordinates pair}}.
        queue<pair<int, pair<int, int>>> q;
        int n = grid.size();
        int m = grid[0].size();

        // Create a distance matrix with initially all the cells marked as
        // unvisited and the source cell as 0.
        vector<vector<int>> dist(n, vector<int>(m, 1e9));
        dist[source.first][source.second] = 0;
        q.push({0, {source.first, source.second}});

        // The following delta rows and delta columns arrays are created such that
        // each index represents each adjacent node that a cell may have 
        // in a direction.
        int dr[] = {-1, 0, 1, 0};
        int dc[] = {0, 1, 0, -1};

        // Iterate through the maze by popping the elements out of the queue
        // and pushing whenever a shorter distance to a cell is found.
        while (!q.empty())
        {
            auto it = q.front();
            q.pop();
            
            int dis = it.first;
            int r = it.second.first;
            int c = it.second.second;

            // Through this loop, we check the 4 direction adjacent nodes
            // for a shorter path to the destination.
            for (int i = 0; i < 4; i++)
            {
                int newr = r + dr[i];
                int newc = c + dc[i];

                // Checking the validity of the cell and updating if the distance is shorter.
                if (newr >= 0 && newr < n && newc >= 0 && newc < m && grid[newr][newc] == 1 && dis + 1 < dist[newr][newc])
                {
                    dist[newr][newc] = 1 + dis;

                    // Return the distance until the point when
                    // we encounter the destination cell.
                    if (newr == destination.first && newc == destination.second)
                        return dis + 1;
                    
                    q.push({1 + dis, {newr, newc}});
                }
            }
        }
        // If no path is found from source to destination.
        return -1;
    }
};

Time Complexity: O( 4*N*M ) { N*M are the total cells, for each of which we also check 4 adjacent nodes for the shortest path length}, 
                 Where N = No. of rows of the binary maze and M = No. of columns of the binary maze.

Space Complexity: O( N*M ), Where N = No. of rows of the binary maze and M = No. of columns of the binary maze.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
9) Path with minimum effort

While traversing, we are storing the maximum difference of all the cells along
the path, and whenever we find a maximum ( newEffort) is less than the whatever
it has previously, we update it to that minimum and again push into the queue.

CHEXK FOR DESTINATION WHILE TAKING OUT OF THE PQ, AND NOT WHILE
INSERTING. Because it will be minimum in itself, as we are using min heap!!

It is not sure that we reach the destination with the minimum effort when we
encounter it while inserting. It might be larger na!! And whenever we pop from 
the pq, it will be the smallest among all the pairs having the destination.

OR RETURN THE dist[n-1][n-1], when the traversal gets complete, that will be
also the minimum one, bcoz we are updating the dist matrix whenever we got
some value less than current !!

In this problem, we need to minimize the effort of moving from the source cell (0,0) to the destination cell (n – 1,m – 1). 
The effort can be calculated as the maximum value of the difference between the node and its next node in the path from the 
source to the destination. Among all the possible paths, we have to minimize this effort. So, for these types of minimum path 
problems, there’s one standard algorithm that always comes to our mind and that is Dijkstra’s Algorithm which would be used in 
solving this problem also. We update the distance every time we encounter a value of difference less than the previous value. 
This way, whenever we reach the destination we finally return the value of difference which is also the minimum effort.

Intuition:
The code uses a modified Dijkstra's algorithm to find the minimum effort path in a grid with height differences as edge weights. 
The algorithm starts from the top-left cell and explores adjacent cells in a priority queue based on the minimum effort required 
to reach each cell. It keeps track of the minimum effort required to reach each cell using the dist matrix.

The priority_queue ensures that cells with lower effort (minimum distance) are explored first. During the exploration, 
the algorithm updates the minimum effort for each cell if a shorter path is found. The effort to reach a cell is defined as 
the maximum height difference encountered in the path to that cell.

By the end of the algorithm, the dist matrix will contain the minimum effort required to reach each cell from the top-left corner. 
The return value is the minimum effort required to reach the bottom-right cell (n-1, m-1), which represents the minimum effort path through the grid.



class Solution {
public:
    int minimumEffortPath(vector<vector<int>>& heights) {
        int n = heights.size();
        int m = heights[0].size();

        // Create a distance matrix to store the minimum effort required to reach each cell.
        vector<vector<int>> dist(n, vector<int>(m, 1e9));

        // Create a priority queue to prioritize cells with lower effort (minimum distance).
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

        // Start from the top-left cell (0,0).
        pq.push({0, {0, 0}});
        dist[0][0] = 0;

        // The algorithm will explore the cells in a BFS-like manner using the priority queue.
        while (!pq.empty()) {
            int diff = pq.top().first;       // Current effort (maximum height difference) to reach the cell.
            int row = pq.top().second.first;  // Current row of the cell.
            int col = pq.top().second.second; // Current column of the cell.
            pq.pop();

            int delr[4] = {-1, 0, 0, 1}; // Delta values for rows to explore adjacent cells.
            int delc[4] = {0, -1, 1, 0}; // Delta values for columns to explore adjacent cells.

            // Explore adjacent cells.
            for (int i = 0; i < 4; i++) {
                int nr = row + delr[i]; // New row coordinate of the adjacent cell.
                int nc = col + delc[i]; // New column coordinate of the adjacent cell.

                // Check if the new coordinates are within the grid bounds.
                if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
                    // Calculate the new effort (maximum height difference) to reach the adjacent cell.
                    int newEffort = max(abs(heights[nr][nc] - heights[row][col]), diff);

                    // If the new effort is less than the current recorded effort for the cell,
                    // update the distance matrix and add the cell to the priority queue for further exploration.
                    if (newEffort < dist[nr][nc]) {
                        dist[nr][nc] = newEffort;
                        pq.push({dist[nr][nc], {nr, nc}});
                    }
                }
            }
        }
        // Return the minimum effort required to reach the bottom-right cell (n-1, m-1).
        return dist[n - 1][m - 1];
    }
};

Time Complexity: O( 4*N*M * log( N*M) ) (Dijikstras-> E*logV) { N*M are the total cells, for each of which we also check 4 adjacent nodes for the minimum effort 
                 and additional log(N*M) for insertion-deletion operations in a priority queue } 
 		 Where, N = No. of rows of the binary maze and M = No. of columns of the binary maze.

Space Complexity: O( N*M ) { Distance matrix containing N*M cells + priority queue in the worst case containing all the nodes ( N*M) }.
		  Where, N = No. of rows of the binary maze and M = No. of columns of the binary maze.

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
10) Cheapest Flights Within K Stops

We store the elements in terms of the minimum number of stops in the priority
queue so that when the algorithm halts, we can get the minimum cost within 
limits.

1) Queue ahe (pq nahi), Dist array ahe
2) Queue of {stops, {node, dist}}
3) stops > k -> continue
4) Dijiktras logic ahe -> (dis + wt < dist[adjNode])
5) q.push({stops + 1, {adjNode, dist[adjNode]}})
6) return dist[dest], purn traversal hou de!!

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        // Create an adjacency list to store the flights from each source node.
        vector<pair<int, int>> adj[n];

        int m = flights.size();

        // Construct the adjacency list from the given flights data.
        for (int i = 0; i < m; i++) {
            adj[flights[i][0]].push_back({flights[i][1], flights[i][2]});
        }

        // Create a queue to perform BFS and traverse the graph.
        queue<pair<int, pair<int, int>>> q;

        // Start BFS from the source node with initial steps as 0 and distance from the source as 0.
        // {steps, {node, dist}} 
        q.push({0, {src, 0}});

        // Create a distance array to keep track of the minimum distance from the source node to each node.
        vector<int> dist(n, 1e9);

        // Distance from the source to the source is 0.
        dist[src] = 0;

        // Perform BFS to find the minimum distance to the destination node within 'k' steps.
        while (!q.empty()) {
            auto it = q.front();
            q.pop();

            int node = it.second.first;  // Current node being processed.
            int steps = it.first;       // Number of steps taken so far.
            int distNode = it.second.second; // Current distance from the source node.

            // If the number of steps exceeds 'k', skip further exploration for this node.
            if (steps > k) continue;

            // Explore the adjacent nodes of the current node.
            for (auto &it : adj[node]) {
                int adjNode = it.first; // Adjacent node.
                int adjWt = it.second;  // Weight (cost) of the flight from the current node to the adjacent node.

                // If taking the flight from the current node to the adjacent node
                // results in a shorter distance to the adjacent node, update the distance and add it to the queue.
                if (distNode + adjWt < dist[adjNode]) {
                    dist[adjNode] = distNode + adjWt;
                    q.push({steps + 1, {adjNode, dist[adjNode]}});
                }
            }
        }

        // If the distance to the destination node is still 1e9, there is no path within 'k' steps.
        // Return -1 in this case.
        if (dist[dst] == 1e9) return -1;
        
        // Otherwise, return the minimum distance to the destination node.
        return dist[dst];
    }
};

Time Complexity: O( N ) { Additional log(N) of time eliminated here because we’re using a simple queue rather than a 
                 priority queue which is usually used in Dijkstra’s Algorithm }.
  		 Where N = Number of flights / Number of edges.

Space Complexity:  O( |E| + |V| ) { for the adjacency list, priority queue, and the dist array }.
		   Where E = Number of edges (flights.size()) and V = Number of Airports. 

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
11) Minimum Multiplications to reach End

class Solution {
  public:
    int minimumMultiplications(vector<int>& arr, int start, int end) {
        if(start==end) return 0;
        // Create a queue for storing the numbers as a result of multiplication
        // of the numbers in the array and the start number.
        queue<pair<int, int>> q;
        q.push({start, 0});

        // Create a dist array to store the no. of multiplications to reach
        // a particular number from the start number.
        vector<int> dist(100000, 1e9);
        dist[start] = 0;
        int mod = 100000;

        // Multiply the start no. with each of numbers in the arr
        // until we get the end no.
        while (!q.empty())
        {
            int node = q.front().first;
            int steps = q.front().second;
            q.pop();

            for (auto it : arr)
            {
                int num = (it * node) % mod;

                // If the no. of multiplications are less than before
                // in order to reach a number, we update the dist array.
                if (steps + 1 < dist[num])
                {
                    dist[num] = steps + 1;

                    // Whenever we reach the end number
                    // return the calculated steps
                    if (num == end) return steps + 1;
                    q.push({num, steps + 1});
                }
            }
        }
        // If the end no. is unattainable.
        return -1;
    }
};

Using simple BFS!!

class Solution {
public:
    int minimumMultiplications(vector<int>& arr, int start, int end) {
        // Base case: If the start and end numbers are the same, no multiplications are needed.
        if (start == end) 
            return 0;

        // Create a queue for BFS traversal.
        queue<pair<int, int>> q;
        q.push({0, start});

        // Modulo value to keep the numbers in check.
        int mod = 100000;

        // Create a visited array to keep track of visited numbers during BFS traversal.
        vector<int> visited(mod, 0);
        visited[start] = 1;

        // Perform BFS to find the minimum number of multiplications needed to reach the end number.
        while (!q.empty()) {
            auto p = q.front();
            q.pop();
            int steps = p.first; // Number of steps taken so far.
            int node = p.second; // Current number.

            // Check each possible number that can be obtained by multiplying the current number with elements of 'arr'.
            for (auto x : arr) {
                int num = (x * node) % mod;

                // If the number is not visited yet, mark it as visited and check if it is the end number.
                if (!visited[num]) {
                    visited[num] = 1;

                    // If the end number is reached, return the number of steps taken to reach it.
                    if (num == end)
                        return steps + 1;

                    // Otherwise, add the number to the queue for further exploration.
                    q.push({steps + 1, num});
                }
            }
        }
        // If the end number is unattainable from the start number, return -1.
        return -1;
    }
};

Time Complexity : O(100000 * N) 
		  Where ‘100000’ are the total possible numbers generated by multiplication (hypothetical) 
		  and N = size of the array with numbers of which each node could be multiplied.

Space Complexity :  O(100000 * N) 
                    Where ‘100000’ are the total possible numbers generated by multiplication (hypothetical) and 
                    N = size of the array with numbers of which each node could be multiplied. 100000 * N is the max possible queue size. 
    		    The space complexity of the dist array is constant.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
12)  Number of Ways to Arrive at Destination

We should consider number of ways to arrive at dest, of each node in the path.

1) Shortest distacne will be handled by Dijkstra's
2) Number of ways will be handled by ways array.
3) If we found smaller distance, update replace ways of adjNode with current node
4) If dist are equal, add ways of current node to ways of adjNode
5) return ways of n-1.

The key lies in recording not only a single path for each node but all the shortest paths.

Read notes and article!!


class Solution {
public:
    int countPaths(int n, vector<vector<int>>& roads) {
        int mod = 1e9 + 7;
        vector<vector<pair<int, int>>> adj(n);

        // Create an adjacency list to store the roads between cities.
        for (auto& road : roads) {
            adj[road[0]].push_back({road[1], road[2]});
            adj[road[1]].push_back({road[0], road[2]});
        }

        // Initialize dist and ways arrays to keep track of the shortest distance and number of ways to reach each node.
        vector<long> dist(n, LONG_MAX);
        vector<long> ways(n, 0);

        // The starting city has a distance of 0 and only one way to reach it.
        dist[0] = 0;
        ways[0] = 1;

        // Create a priority queue to perform Dijkstra's algorithm.
        // {dist, node}
        priority_queue<pair<long, int>, vector<pair<long, int>>, greater<>> pq;

        // Push the starting city into the priority queue.
        pq.push({0, 0});

        // Perform Dijkstra's algorithm to find the shortest distance and number of ways to reach each city.
        while (!pq.empty()) {
            // Extract the node with the smallest distance from the priority queue.
            auto it = pq.top();
            pq.pop();

            long long distNode = it.first; // Current distance from the starting city.
            int node = it.second;          // Current city.

            // Traverse the adjacent cities of the current city.
            for (auto& it : adj[node]) {
                long long adjNode = it.first; // Adjacent city.
                long long adjWt = it.second;  // Weight (distance) to reach the adjacent city.

                // If the path to the adjacent city is shorter than the recorded distance,
                // update the distance and the number of ways to reach the adjacent city.
                if (distNode + adjWt < dist[adjNode]) {
                    dist[adjNode] = (distNode + adjWt);
                    ways[adjNode] = ways[node];
                    pq.push({dist[adjNode], adjNode});
                }
                // If the path to the adjacent city is of the same distance,
                // add the number of ways to reach the current city to the number of ways to reach the adjacent city.
                else if (distNode + adjWt == dist[adjNode]) {
                    ways[adjNode] = (ways[adjNode] + ways[node]) % mod;
                }
            }
        }

        // Return the number of ways to reach the last city (city `n-1`) modulo 1e9 + 7.
        return ways[n - 1] % mod;
    }
};

Time Complexity: O( E* log(V)) { As we are using simple Dijkstra’s algorithm here, the time complexity will be or the order E*log(V)}
    		 Where E = Number of edges and V = No. of vertices.

Space Complexity :  O(N) { for dist array + ways array + approximate complexity for priority queue }
  		    Where, N = Number of nodes.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
13) Bellman Ford Algorithm.

In this algorithm, the edges can be given in any order. The intuition is to relax all the edges for N-1( N = no. of nodes) times sequentially. 
After N-1 iterations, we should have minimized the distance to every node.

Computes shortest paths for graph having negative cycles and can also 
DETECT NEGATIVE CYCLE.

Only applicable for DG, if UG is given the add is directional edges in that graph

Bellman Ford: 
1) Relax all the edges n-1 times sequentially. Relaxing a edge means updating
     distance of a node with minimum, this will be performed n-1 times!!

2) Performing if(dist[u]+wt < dist[v]) dist[v] = dist[u] + wt over all the edges, 
     is the one iteration!!

3) In every iteration, distance of one node gets updated, in anther iteration
     that node will update distance of other node, and so on...
     In a graph of N nodes we will take at most N-1 edges to reach from the first 
     to the last node, we need exact N-1 iterations. It is impossible to draw a graph 
     that takes more than N-1 edges to reach any node.

4) Dist array will store the shortest distances of all nodes from 0.

5) Detect negative cycle:
 On Nth iteration, the relaxation will be done and if the dist array gets updated
 then there is a negative cycle. N-1 iterations madhe saglya nodes cha distance
 update hoel!!!

READ THE ARTICLE!!

class Solution {
public:
    vector<int> bellman_ford(int V, vector<vector<int>>& edges, int S) {
        // Initialize a distance array to keep track of the minimum distance from the source vertex to each vertex.
        vector<int> dist(V, 1e8);
        
        // The distance from the source vertex to itself is 0.
        dist[S] = 0;
        
        // Perform V-1 iterations (V-1 because any shortest path will have at most V-1 edges).
        for(int i = 0; i < V-1; i++) {
            // Traverse each edge and update the distances if a shorter path is found.
            for(auto &it : edges) {
                int u = it[0]; // Source vertex of the edge.
                int v = it[1]; // Destination vertex of the edge.
                int wt = it[2]; // Weight (cost) of the edge.

                // If the distance to the source vertex 'u' is not infinite (1e8) and
                // the distance to the destination vertex 'v' can be reduced by taking this edge,
                // update the distance to 'v'.
                if(dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                    dist[v] = dist[u] + wt;
                }
            }
        }
        
        // Check for negative cycles by performing one more iteration.
        // If a shorter path is found after V-1 iterations, it indicates the presence of a negative cycle.
        for(auto &it : edges) {
            int u = it[0]; // Source vertex of the edge.
            int v = it[1]; // Destination vertex of the edge.
            int wt = it[2]; // Weight (cost) of the edge.

            // If the distance to the source vertex 'u' is not infinite (1e8) and
            // the distance to the destination vertex 'v' can be reduced by taking this edge,
            // it indicates the presence of a negative cycle in the graph.
            if(dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                // Return a vector containing -1 to indicate the presence of a negative cycle.
                return {-1};
            }
        }
        
        // If there is no negative cycle, return the distance array containing the minimum distances.
        return dist;
    }
};

Time Complexity: O(V*E), where V = no. of vertices and E = no. of Edges.

Space Complexity: O(V) for the distance array which stores the minimized distances.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
14) Floyd Warshal Algorithm

Intuition:
The provided code implements the Floyd-Warshall algorithm, a dynamic programming algorithm used to find the shortest distance 
between all pairs of vertices in a weighted directed graph. The algorithm can handle graphs with both positive and negative edge 
weights but may not work correctly if the graph contains negative cycles.

The algorithm works by iteratively considering all vertices 'via' as potential intermediate vertices between every pair of vertices (i, j). 
It updates the distance between vertices i and j if the distance through vertex 'via' is shorter than the direct distance between them.

The algorithm uses a 2D matrix 'matrix' to represent the graph, where matrix[i][j] stores the distance from vertex i to vertex j. 
It initializes all the -1 values in the matrix to a large number (1e8) to represent infinity. During the execution of the 
Floyd-Warshall algorithm, it iterates through all vertices 'via', and for each pair of vertices (i, j), it checks if the 
distance from i to j through vertex 'via' is shorter than the current distance. If so, it updates the distance matrix with the new minimum distance.

After running the Floyd-Warshall algorithm, the original -1 values in the matrix are restored to represent unreachable vertices as -1 again, 
and all other values represent the shortest distance between the vertices in the graph. The function modifies the input 'matrix' in-place, 
updating it with the shortest distances.

 Until now, to store a graph we have used the adjacency list. But in this algorithm, we are going to use the adjacency matrix method. 
One additional point to remember is that the cost of reaching a node from itself must always be 0 i.e. dist[i][i] = 0, where i = current node.

#The intuition is to check all possible paths between every possible pair of nodes and to choose the shortest one. 
 Checking all possible paths means going via each and every possible node.  

// User function to find the shortest distance between all pairs of vertices in a graph.
class Solution {
public:
    // Function to find the shortest distance between all pairs of vertices in the graph.
    void shortest_distance(vector<vector<int>>& matrix) {
        int n = matrix.size();

        // Replace all -1 values with a large number (1e8) to represent infinity.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == -1)
                    matrix[i][j] = 1e8;
                if (i == j) matrix[i][j] = 0;
            }
        }

        // Floyd-Warshall algorithm implementation.
        // The outer loop runs via through all the vertices to use it as an intermediate vertex.
        for (int via = 0; via < n; via++) {
            // The two inner loops run through all the pairs of vertices (i, j) in the graph.
            // For each pair, if the distance from vertex i to vertex j through vertex 'via' is shorter than the direct distance,
            // update the distance to the minimum value.
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    matrix[i][j] = min(matrix[i][j], matrix[i][via] + matrix[via][j]);
                }
            }
        }

        // Restore the original -1 values in the matrix to represent unreachable vertices as -1 again.
        // All other values represent the shortest distance between vertices.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == 1e8)
                    matrix[i][j] = -1;
            }
        }

//      for (int i = 0; i < n; i++) {
// 			for (int j = 0; j < n; j++) {
// 				if (matrix[i][j] < 0 ) {
// 				    // NEGATIVE CYCLE!!
// 				    // BREAK
// 				}
// 			}
// 		}
    }
};

Detect negative cycle:
We have previously said that the cost of reaching a node from itself must be 0. But in the above graph, 
if we try to reach node 0 from itself we can follow the path: 0->1->2->0. In this case, the cost to reach node 0 
from itself becomes -3 which is less than 0. This is only possible if the graph contains a negative cycle.
So, if we find that the cost of reaching any node from itself is less than 0, we can conclude that the graph has a negative cycle.

Time Complexity: O(V3), as we have three nested loops each running for V times, where V = no. of vertices.

Space Complexity: O(V2), where V = no. of vertices. This space complexity is due to storing the adjacency matrix of the given graph.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
15)  Find the City With the Smallest Number of Neighbors at a Threshold Distance

For each node, the job is to find the shortest distances to every other node and
count the number of adjacent cities(Let’s say: cntCity) whose distance is at the 
most distanceThreshold. Finally, the task is to choose the node with the largest 
value and the minimum ‘cntCity’ value.

1) Apply Floyd Warshall algorithm and generate distance matrix which will contain
    distance of every node to every other node.

2) count the number of nodes with a distance lesser or equal to the 
    distanceThreshold by iterating each row of that matrix. Finally, we will choose the 
    node with the minimum number of adjacent cities (whose distance is at the most 
    distanceThreshold) and with the largest value.

class Solution {
public:
    int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold) {
        // Create a matrix to store the distances between cities.
        // Initialize all distances to be initially set to maximum (INT_MAX).
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));

        // Fill the matrix with the actual distances from the given edges.
        for (auto it : edges) {
            dist[it[0]][it[1]] = it[2];
            dist[it[1]][it[0]] = it[2]; // Since the graph is undirected, update both directions.
        }

        // Set the diagonal elements (distances from a city to itself) to 0.
        for (int i = 0; i < n; i++)
            dist[i][i] = 0;

        // Perform Floyd-Warshall algorithm to find the shortest distances between all pairs of cities.
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    // If the intermediate city 'k' allows for a shorter path from 'i' to 'j',
                    // update the distance between 'i' and 'j' through 'k'.
                    if (dist[i][k] == INT_MAX || dist[k][j] == INT_MAX)
                        continue;
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        // Initialize variables to keep track of the city with the minimum reachable cities within the threshold.
        int cntCity = n;
        int cityNo = -1;

        // Check each city to find the number of cities that can be reached within the given threshold.
        for (int city = 0; city < n; city++) {
            int cnt = 0; // Initialize a counter for the reachable cities from the current city.

            // Count the number of cities that can be reached from the current city within the threshold.
            for (int adjCity = 0; adjCity < n; adjCity++) {
                if (dist[city][adjCity] <= distanceThreshold)
                    cnt++;
            }

            // If the current city can reach fewer cities within the threshold than the previous best city,
            // update the variables to track the new best city.
            if (cnt <= cntCity) {
                cntCity = cnt;
                cityNo = city;
            }
        }

        // Return the city with the minimum reachable cities within the threshold.
        return cityNo;
    }
};


Time Complexity: O(V3), as we have three nested loops each running for V times, where V = no. of vertices.

Space Complexity: O(V2), where V = no. of vertices. This space complexity is due to storing the adjacency matrix of the given graph.
-----------------------------------------------------------------------------------------------------------------------------------------------------------------------
