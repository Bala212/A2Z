1) Number of Provinces

*Loop from 1 to V and count number of DFS/BFS.

void dfs(int i, vector<int> adj[], vector<int> &vis) {
    // Mark the current node as visited
    vis[i] = 1;
    
    // Visit all the adjacent nodes (neighbors) of the current node
    for (int &val : adj[i]) {
        // If the adjacent node is not visited yet, recursively call dfs on it
        if (!vis[val]) {
            dfs(val, adj, vis);
        }
    }
}

int findCircleNum(vector<vector<int>>& isConnected) {
    int n = isConnected.size();
    vector<int> adj[n + 1];

    // Construct an adjacency list representation of the given matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (isConnected[i][j] == 1) {
                // If there is a connection between nodes i and j, add them to each other's adjacency list
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    int ans = 0;
    vector<int> vis(n, 0); // Create a vector to keep track of visited nodes

    // Perform Depth-First Search (DFS) to find connected components (circles) in the graph
    for (int i = 0; i < n; i++) {
        // If the current node is not visited yet, start a new connected component and explore it using DFS
        if (!vis[i]) {
            ans++; // Increment the count of connected components (circles)
            dfs(i, adj, vis);
        }
    }
    return ans; // Return the total number of connected components (circles) found in the graph
}
Time Complexity: O(N) + O(V+2E) as we are not calling dfs for every i in for loop na, 
                 Where O(N) is for outer loop and inner loop runs in total a single DFS over entire graph,
                 and we know DFS takes a time of O(V+2E). 

Space Complexity: O(N) + O(N),Space for recursion stack space and visited array.
--------------------------------------------------------------------------------------------------------------------------
2) Number of Islands

class Solution {
public:
    // Helper function for Depth-First Search (DFS)
    void dfs(int i, int j, vector<vector<char>>& grid, vector<vector<int>>& vis) {
        vis[i][j] = 1; // Mark the current cell as visited
        int n = grid.size();
        int m = grid[0].size();

        int x[4] = {-1, 0, 1, 0}; // Possible movements in four directions: up, right, down, left
        int y[4] = {0, 1, 0, -1};

        // Traverse all four adjacent cells of the current cell (i, j)
        for (int k = 0; k < 4; k++) {
            int ni = i + x[k]; // New row index after movement
            int nj = j + y[k]; // New column index after movement

            // Check if the new cell (ni, nj) is within the grid boundaries and hasn't been visited yet
            // Also, ensure that the cell contains '1' (part of an island)
            if (ni >= 0 && ni < n && nj >= 0 && nj < m && !vis[ni][nj] && grid[ni][nj] == '1') {
                // Recursively call dfs on the new cell to explore it and its neighbors
                dfs(ni, nj, grid, vis);
            }
        }
    }

    // Helper function for Breadth-First Search (BFS)
    void bfs(int i, int j, vector<vector<char>>& grid, vector<vector<int>>& vis) {
        vis[i][j] = 1; // Mark the current cell as visited
        queue<pair<int, int>> q;
        q.push({i, j}); // Push the starting node (i, j) into the queue
        int n = grid.size();
        int m = grid[0].size();

        while (!q.empty()) {
            int row = q.front().first;
            int col = q.front().second;
            q.pop();

            int x[4] = {-1, 0, 1, 0}; // Possible movements in four directions: up, right, down, left
            int y[4] = {0, 1, 0, -1};

            // Traverse all four adjacent cells of the current cell (row, col)
            for (int k = 0; k < 4; k++) {
                int nR = row + x[k]; // New row index after movement
                int nC = col + y[k]; // New column index after movement

                // Check if the new cell (nR, nC) is within the grid boundaries and hasn't been visited yet
                // Also, ensure that the cell contains '1' (part of an island)
                if (nR >= 0 && nR < n && nC >= 0 && nC < m && !vis[nR][nC] && grid[nR][nC] == '1') {
                    // Mark the new cell as visited and push it into the queue for further exploration
                    q.push({nR, nC});
                    vis[nR][nC] = 1;
                }
            }
        }
    }

    // Function to find the number of islands in the grid using DFS
    int numIslands(vector<vector<char>>& grid) {
        int ans = 0;
        int n = grid.size();
        int m = grid[0].size();

        // Create a 2D visited matrix initialized with zeros
        vector<vector<int>> vis(n, vector<int>(m, 0));

        // Iterate through all cells in the grid
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // If the current cell is not visited and contains '1' (part of an island)
                if (!vis[i][j] && grid[i][j] == '1') {
                    ans++; // Increment the number of islands found
                    // Start a DFS from the current cell to explore the entire island
                    dfs(i, j, grid, vis);
                }
            }
        }
        return ans; // Return the total number of islands found using DFS
    }
};
Above code is for four durections, if we are given that all 8 directions can be moved then we need to do some changes
while visting the adjacent cells as follows:

#8directions:

	for(int delrow = -1; delrow<=1;delrow++) {
        for(int delcol = -1; delcol <= 1; delcol++) {
            int nrow = row + delrow; 
            int ncol = col + delcol; 
            // neighbour row and column is valid, and is an unvisited land
            if(nrow >= 0 && nrow < n && ncol >= 0 && ncol < m 
            && grid[nrow][ncol] == '1' && !vis[nrow][ncol]) {
                vis[nrow][ncol] = 1; 
                q.push({nrow, ncol}); 
            }
        }
    }

#4directions:

            int x[4] = {-1, 0, 1, 0}; // Possible movements in four directions: up, right, down, left
            int y[4] = {0, 1, 0, -1};

            // Traverse all four adjacent cells of the current cell (row, col)
            for (int k = 0; k < 4; k++) {
                int nR = row + x[k]; // New row index after movement
                int nC = col + y[k]; // New column index after movement

                // Check if the new cell (nR, nC) is within the grid boundaries and hasn't been visited yet
                // Also, ensure that the cell contains '1' (part of an island)
                if (nR >= 0 && nR < n && nC >= 0 && nC < m && !vis[nR][nC] && grid[nR][nC] == '1') {
                    // Mark the new cell as visited and push it into the queue for further exploration
                    q.push({nR, nC});
                    vis[nR][nC] = 1;
                }
            }


Time Complexity ~ O(N² + NxMx4), N² for the nested loops, and NxMx9 for the overall 
DFS of the matrix, that will happen throughout if all the cells are filled with 1.

Space Complexity: O(N²) for visited array max queue space O(N²), If all are marked as 1
then the maximum queue space will be N².

--------------------------------------------------------------------------------------------------------------------------
3) Flood fill

Given a {sr, sc} and newColor we have to color all the cells with newColor whose initial color was color having color of {sr, sc}

class Solution {
public:
    // Helper function for Depth-First Search (DFS)
    void dfs(int row, int col, vector<vector<int>>& ans, vector<vector<int>>& image, int color, int delRow[], int delCol[], int iniColor) {
        ans[row][col] = color; // Update the current cell color to the target color
        int n = image.size();
        int m = image[0].size();

        // Arrays to represent the possible movements in four directions: up, right, down, left
        int x[4] = {-1, 0, 1, 0};
        int y[4] = {0, 1, 0, -1};

        // Traverse all four adjacent cells of the current cell (row, col)
        for (int i = 0; i < 4; i++) {
            int nRow = row + delRow[i]; // New row index after movement
            int nCol = col + delCol[i]; // New column index after movement

            // Check if the new cell (nRow, nCol) is within the grid boundaries
            if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m) {
                // If the new cell has the same color as the initial color and it is not yet updated,
                // perform a recursive DFS call to continue filling the connected region with the target color.
                if (image[nRow][nCol] == iniColor && ans[nRow][nCol] != color) {
                    dfs(nRow, nCol, ans, image, color, delRow, delCol, iniColor);
                }
            }
        }
    }

    // Function to perform flood fill on the given image
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int iniColor = image[sr][sc]; // Store the initial color of the starting cell
        vector<vector<int>> ans = image; // Create a copy of the image to store the result

        // Arrays to represent the possible movements in four directions: up, right, down, left
        int delRow[] = {-1, 0, 1, 0};
        int delCol[] = {0, 1, 0, -1};

        // Start the DFS from the starting cell (sr, sc) to fill the connected region with the target color
        dfs(sr, sc, ans, image, color, delRow, delCol, iniColor);

        return ans; // Return the image with the flooded region
    }
};

Time Complexity: O(NxM + NxMx4) ~ O(N x M)
For the worst case, all of the pixels will have the same colour, so DFS function will be called for 
(N x M) nodes and for every node we are traversing for 4 neighbours, so it will take O(N x M x 4) time.

Space Complexity: O(N x M) + O(N x M)
O(N x M) for copied input array and recursive stack space takes up N x M locations at max. 

--------------------------------------------------------------------------------------------------------------------------
4) Rotting Oranges

We HAVE to use BFS here!! To go level wise to each orange!!

1) Push all rotted oranges from matrix into queue {node, time}
2) Go on rotting the neighbor fresh oranges and not rotted previously!!
3) When we rot a orange, push it into queue with time increased by 1.
4) Maximize the time always.
5) At last check rotted count == freshOranges before traversal, if not return -1
   else return time.

class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        // vis
        int rottened[n][m]; // Create a 2D array to keep track of rotten oranges

        queue<pair<pair<int, int>, int>> q; // Create a queue to perform BFS
        int iniFresh = 0; // Variable to store the initial count of fresh oranges

        // Initialize the queue and the rottened array
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 2) {
                    q.push({{i, j}, 0}); // Push rotten oranges into the queue with time t = 0
                    rottened[i][j] = 1; // Mark rotten oranges as visited
                } else {
                    rottened[i][j] = 0; // Mark fresh oranges as unvisited
                }
                if (grid[i][j] == 1) {
                    iniFresh++; // Count the initial number of fresh oranges
                }
            }
        }

        int time = 0, rotCount = 0; // Variables to track the time and count of rotten oranges
        int delRow[] = {-1, 0, 1, 0}; // Possible movements in four directions: up, right, down, left
        int delCol[] = {0, 1, 0, -1};

        // Perform BFS until the queue becomes empty
        while (!q.empty()) {
            int row = q.front().first.first;
            int col = q.front().first.second;
            int t = q.front().second; // Time taken for the current orange to rot
            time = max(t, time); // Update the maximum time taken for an orange to rot
            q.pop();

            // Traverse all four adjacent cells of the current cell (row, col)
            for (int i = 0; i < 4; i++) {
                int nRow = row + delRow[i]; // New row index after movement
                int nCol = col + delCol[i]; // New column index after movement

                // Check if the new cell (nRow, nCol) is within the grid boundaries,
                // it is an unvisited fresh orange (grid[nRow][nCol] == 1),
                // and update it as a rotten orange
                if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && rottened[nRow][nCol] == 0 && grid[nRow][nCol] == 1) {
                    q.push({{nRow, nCol}, t + 1}); // Push the new orange into the queue with updated time t+1
                    rottened[nRow][nCol] = 1; // Mark the new orange as visited (rotten)
                    rotCount++; // Increment the count of rotten oranges
                }
            }
        }

        // If the count of initial fresh oranges is not equal to the count of rotten oranges, return -1
        if (iniFresh != rotCount) {
            return -1;
        }

        return time; // Return the maximum time taken for an orange to rot
    }
};

Time Complexity: O ( n x n ) x 4    
Reason: Worst-case – We will be making each fresh orange rotten in the grid and for each rotten orange will check in 4 directions

Space Complexity: O ( n x n )
Reason: worst-case –  If all oranges are Rotten, we will end up pushing all rotten oranges into the Queue data structure

--------------------------------------------------------------------------------------------------------------------------
5) Detect a Cycle in an Undirected Graph using BFS

If someone is visited, and it did not come from it. We say there is a cycle.
a) Keep track of parent nodes in BFS by pushing current node with the adjacent node into queue (current node will be a parent for adjacent node)
b) While traversing, if we found that the adjacent node is visited previously then normally it must be the parent,
   because it has came from there only na, if its not the parent that means some other node has visited it means there is a cycle!!

class Solution {
public:
    // Helper function to detect a cycle in an undirected graph starting from a given source node
    bool detect(int src, vector<int> adj[], int vis[]) {
        vis[src] = 1; // Mark the current node as visited
        queue<pair<int, int>> q; // Queue to store the current node and its parent node
        q.push({src, -1}); // Push the source node into the queue with parent as -1 (no parent)
        
        // Traverse until the queue is not empty
        while (!q.empty()) {
            int node = q.front().first; // Current node
            int parent = q.front().second; // Parent node of the current node
            q.pop();
            
            // Go through all adjacent nodes of the current node
            for (auto adjacentNode : adj[node]) {
                // If the adjacent node is unvisited
                if (!vis[adjacentNode]) {
                    vis[adjacentNode] = 1; // Mark the adjacent node as visited
                    q.push({adjacentNode, node}); // Push the adjacent node into the queue with its parent node
                }
                // If the adjacent node is visited and is not the same as its own parent node
                else if (parent != adjacentNode) {
                    // It indicates that there's a cycle in the graph
                    return true;
                }
            }
        }
        // There's no cycle in the graph
        return false;
    }
    // Function to detect cycle in an undirected graph.
    bool isCycle(int V, vector<int> adj[]) {
        int vis[V] = {0}; // Initialize all nodes as unvisited
        for (int i = 0; i < V; i++) {
	    // Pratyek component check kara graph cha, jar eka pn component madhe cycle ahe true return kara.
            if (!vis[i]) {
                if (detect(i, adj, vis)) return true; // Call the detect function from each unvisited node
            }
        }
        return false; // If no cycle is found, return false
    }
};


Time Complexity: O(N + 2E) + O(N), N+2E is for BFS. In the case of connected components of a graph, it will take another O(N) time.

Space Complexity: O(N) + O(N) ~ O(N), Space for queue data structure and visited array.
--------------------------------------------------------------------------------------------------------------------------
6) Detect a Cycle in an Undirected Graph using DFS

If someone is visited, and it did not come from it. We say there is a cycle.


a) Keep track of parent nodes in DFS call itself by passing adjacent node 
   and  current node as a parent node of adjacent node.
b) While traversing, if we found that the adjacent node is visited previously then 
   normally it must be the parent, because it has came from there only na, if its not 
   the parent that means some other node has visited it means there is a cycle!!

class Solution {
public:
    // Helper function to detect a cycle in an undirected graph starting from a given node
    bool detect(int node, int parent, int vis[], vector<int> adj[]) {
        vis[node] = 1; // Mark the current node as visited
          
        // Traverse all adjacent nodes of the current node
        for (auto &val : adj[node]) {
            // If the adjacent node is unvisited, recursively call detect on it
            if (!vis[val]) {
                if (detect(val, node, vis, adj)) {
                    return true; // If a cycle is found in the adjacent subtree, return true
                }
            }
            // If the adjacent node is visited and is not the parent of the current node, it indicates a cycle
            else if (val != parent) {
                return true;
            }
        }
        
        return false; // There's no cycle in the current subtree
    }

    // Function to detect cycle in an undirected graph.
    bool isCycle(int V, vector<int> adj[]) {
        int vis[V] = {0}; // Initialize all nodes as unvisited
        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                if (detect(i, 0, vis, adj)) {
                    return true; // If a cycle is found in any connected component, return true
                }
            }
        }
        
        return false; // If no cycle is found, return false
    }
};

Time Complexity: O(N + 2E) + O(N), Where N = Nodes, 2E is for total degrees as we traverse all adjacent nodes. 
In the case of connected components of a graph, it will take another O(N) time.

Space Complexity: O(N) + O(N) ~ O(N), Space for recursive stack space and visited array.

--------------------------------------------------------------------------------------------------------------------------
7) Distance of Nearest Cell having 1

a) We have to replace 0 with distance of nearest 1 from it.
b) Let's GO FROM 1 TO ALL 0'S STEP WISE AND SET THE DISTANCE.
c) We will obviously be using a BFS traversal.
d) Push all 1's into queue, and go the neighbouring 0's level wise and set the 
    distances.
e) Use queue of {node, distance}.
f) We need vis, dist to store ans.
g) Everytime when we push a node into queue if it's zero we increase steps by 1.
h) When we pop out from queue, assign it's distance in the dist matrix.

class Solution {
public:
    // Function to find the distance of the nearest 1 in the grid for each cell.
    vector<vector<int>> nearest(vector<vector<int>> grid) {
        int n = grid.size();
        int m = grid[0].size();

        // Create two matrices to store visited status and distance from the nearest 1 for each cell
        vector<vector<int>> vis(n, vector<int>(m, 0));
        vector<vector<int>> dist(n, vector<int>(m, 0));

        // Create a queue to perform BFS
        queue<pair<pair<int, int>, int>> q;

        // Traverse the entire grid to find all cells containing 1
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (grid[i][j] == 1) {
                    q.push({{i, j}, 0}); // Push cells containing 1 into the queue with initial distance 0
                    vis[i][j] = 1; // Mark the cells containing 1 as visited
                } else {
                    vis[i][j] = 0; // Mark other cells as unvisited
                }
            }
        }

        int delrow[] = {-1, 0, +1, 0}; // Possible movements in four directions: up, right, down, left
        int delcol[] = {0, +1, 0, -1};

        // Perform BFS until the queue becomes empty
        while (!q.empty()) {
            int row = q.front().first.first; // Current row index
            int col = q.front().first.second; // Current column index
            int steps = q.front().second; // Current distance from the nearest 1
            q.pop();

            dist[row][col] = steps; // Update the distance for the current cell, bcoz this node is visited at this distance by 1

            // Traverse all four adjacent cells of the current cell (row, col)
            for (int i = 0; i < 4; i++) {
                int nrow = row + delrow[i]; // New row index after movement
                int ncol = col + delcol[i]; // New column index after movement

                // Check if the new cell (nrow, ncol) is within the grid boundaries,
                // it is an unvisited cell, and update it with the current distance + 1
                if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m && vis[nrow][ncol] == 0) {
	            // Here we are not checking for cell to be 0, because 1 cells are already visited initially.
                    vis[nrow][ncol] = 1; // Mark the new cell as visited
                    q.push({{nrow, ncol}, steps + 1}); // Push the new cell into the queue with updated distance
                }
            }
        }

        // Return the matrix containing the distances from the nearest 1 for each cell
        return dist;
    }
};

Time Complexity: O(NxM + NxMx4) ~ O(N x M)
For the worst case, the BFS function will be called for (N x M) nodes, and for every node, 
we are traversing for 4 neighbors, so it will take O(N x M x 4) time.

Space Complexity: O(N x M) + O(N x M) + O(N x M) ~ O(N x M)
O(N x M) for the visited array, distance matrix, and queue space takes up N x M locations at max. 

--------------------------------------------------------------------------------------------------------------------------
8) Surrounded Regions | Replace O’s with X’s

a) Do DFS/BFS from boundary 0s, and mark all nodes along the path as visited.
     Indicating that this nodes are not surrounded by x.

b) At last, replace those 0s with Xs which are not visited and is 0.

class Solution {
public:

    // Helper DFS function to traverse and mark Os connected to the boundary as visited.
    void dfs(int r, int c, vector<vector<int>> &vis, vector<vector<char>> &board) {
        vis[r][c] = 1; // Mark the current cell as visited.

        int delRow[] = {-1, 0, 1, 0}; // Possible movements in four directions: up, right, down, left.
        int delCol[] = {0, 1, 0, -1};
        int n = board.size();
        int m = board[0].size();

        for (int i = 0; i < 4; i++) {
            int nRow = r + delRow[i]; // New row index after movement.
            int nCol = c + delCol[i]; // New column index after movement.

            // Check if the new cell (nRow, nCol) is within the grid boundaries,
            // unvisited, and contains 'O', then explore it further.
            if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && !vis[nRow][nCol] && board[nRow][nCol] == 'O') {
                dfs(nRow, nCol, vis, board);
            }
        }
    }

    // Main function to solve the surrounded regions problem.
    void solve(vector<vector<char>>& board) {
        int n = board.size();
        int m = board[0].size();

        vector<vector<int>> vis(n, vector<int>(m, 0)); // Create a visited matrix to mark cells that are already visited.

        // Traverse and mark the boundary cells (first and last row and column) connected to 'O' as visited.
        for (int j = 0; j < m; j++) {
            if (vis[0][j] == 0 && board[0][j] == 'O') {
                dfs(0, j, vis, board);
            }
            if (vis[n - 1][j] == 0 && board[n - 1][j] == 'O') {
                vis[n - 1][j] = 1;
                dfs(n - 1, j, vis, board);
            }
        }
        for (int i = 0; i < n; i++) {
            if (vis[i][0] == 0 && board[i][0] == 'O') {
                dfs(i, 0, vis, board);
            }
            if (vis[i][m - 1] == 0 && board[i][m - 1] == 'O') {
                dfs(i, m - 1, vis, board);
            }
        }

        // Mark the cells with 'O' which are not visited means they connected to the boundary as 'X'.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (vis[i][j] != 1 && board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
            }
        }
    }
};

Time Complexity: O(N) + O(M) + O(NxMx4) ~ O(N x M), For the worst case, every element will be marked as ‘O’ 
                 in the matrix, and the DFS function will be called for (N x M) nodes and for every node, we are traversing 
                 for 4 neighbors, so it will take O(N x M x 4) time. Also, we are running loops for boundary elements so it 
                 will take O(N) + O(M).

Space Complexity ~ O(N x M), O(N x M) for the visited array, and auxiliary stack space takes up N x M locations at max. 

--------------------------------------------------------------------------------------------------------------------------
9) Number of Enclaves

a) Do DFS/BFS from boundary 1's, and mark all 1's along the path as visited.
     Indicating that this 1's  can go out of boundary/walk off.

b) At last, count 1's which are not visited, means this 1's are not connected to
    boundary 1's

This is multisource BFS, if solved using BFS.


class Solution {
public:
    // Function to count the number of enclaves.
    int numEnclaves(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        
        // Create a queue to store boundary cells with value 1.
        queue<pair<int, int>> q;
        
        // Create a visited matrix to mark visited cells.
        vector<vector<int>> vis(n, vector<int>(m, 0));

        // Traverse the first and last rows, and first and last columns to find boundary cells.
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
                    if (grid[i][j] == 1) {
                        q.push({i, j}); // Push boundary cells into the queue.
                        vis[i][j] = 1; // Mark boundary cells as visited.
                    }
                }
            }
        }
        
        // Perform BFS to mark all connected cells with value 1 as visited.
        while (!q.empty()) {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();
            
            int delRow[] = {-1, 0, 1, 0}; // Possible movements in four directions: up, right, down, left.
            int delCol[] = {0, 1, 0, -1};
            
            for (int i = 0; i < 4; i++) {
                int nRow = r + delRow[i]; // New row index after movement.
                int nCol = c + delCol[i]; // New column index after movement.
                
                // Check if the new cell (nRow, nCol) is within the grid boundaries,
                // unvisited, and contains value 1, then mark it as visited and push into the queue.
                if (nRow >= 0 && nRow < n && nCol >= 0 && nCol < m && !vis[nRow][nCol] && grid[nRow][nCol] == 1) {
                    q.push({nRow, nCol});
                    vis[nRow][nCol] = 1;
                }
            }
        }
        
        // Count the number of enclaves by counting unvisited cells with value 1.
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!vis[i][j] && grid[i][j] == 1) {
                    ans++;
                }
            }
        }
        
        return ans; // Return the number of enclaves.
    }
};

Time Complexity: O(NxMx4) ~ O(N x M), For the worst case, assuming all the pieces as land, 
                 the BFS function will be called for (N x M) nodes and for every node, we are traversing for 
                 4 neighbors, so it will take O(N x M x 4) time. 

Space Complexity ~ O(N x M), O(N x M) for the visited array, and queue space takes up N x M locations at max. 

--------------------------------------------------------------------------------------------------------------------------
10) Number of Distinct Islands

Certainly! The algorithm aims to count the number of distinct islands in a given grid. Here's an in-depth intuition of how the algorithm works:

1. We start by initializing an empty set (`s`) to store the distinct islands found in the grid.

2. We traverse the grid in a row-by-row manner. For each cell in the grid:
   - If the cell is unvisited (`!vis[i][j]`) and represents a part of an island (`grid[i][j] == 1`), we proceed to explore the island.
   - We perform Depth-First Search (DFS) starting from the current cell to explore all connected cells that belong to the same island. 
     During the DFS, we mark the visited cells (`vis[row][col] = 1`) to avoid revisiting them.
   - During the DFS exploration, we collect the relative coordinates of each visited cell within the island. The relative coordinates 
     are calculated with respect to the starting cell of the island (`rowStart`, `colStart`).
   - Once the DFS completes, we obtain a vector (`island`) containing the relative coordinates of all cells in the island.

3. We insert the island vector into the set `s`. Since sets store unique elements only, this automatically eliminates duplicates 
   and ensures that only distinct islands are stored in `s`.

4. After traversing the entire grid, we return the size of the set `s`, which represents the count of distinct islands.

The algorithm uses Depth-First Search to explore each island and collect its relative coordinates. By storing these relative 
coordinates in a set, we ensure that only distinct islands are counted. The use of relative coordinates allows us to compare islands 
regardless of their absolute positions in the grid, resulting in an accurate count of distinct islands.


class Solution {
public:
    // Depth-First Search (DFS) to explore and collect island coordinates
    void dfs(int row, int col, vector<vector<int>>& grid, vector<vector<int>>& vis,
             vector<pair<int, int>>& island, int rowStart, int colStart) {

        vis[row][col] = 1; // Mark the current cell as visited

        island.push_back({row - rowStart, col - colStart}); // Store relative coordinates of the current cell
        
        int n = grid.size();
        int m = grid[0].size();

        int delRow[] = {-1, 0, 1, 0}; // Possible movements in four directions: up, right, down, left
        int delCol[] = {0, 1, 0, -1};
        
        // Explore all neighboring cells
        for (int i = 0; i < 4; i++) {
            int nRow = row + delRow[i]; // New row index after movement
            int nCol = col + delCol[i]; // New column index after movement
            
            // Check if the new cell (nRow, nCol) is within the grid boundaries,
            // unvisited, and represents a part of the current island (grid value 1)
            if (nRow >= 0 && nCol >= 0 && nRow < n && nCol < m && !vis[nRow][nCol] && grid[nRow][nCol] == 1) {
		// Start Row ani start Col (Base coordinates) ch pass kar ya dfs la
                dfs(nRow, nCol, grid, vis, island, rowStart, colStart); // Recursively explore the neighbor
            }
        }
    }
  
    int countDistinctIslands(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        
        vector<vector<int>> vis(n, vector<int>(m, 0)); // Create a visited matrix
        
        set<vector<pair<int, int>>> s; // Use a set to store distinct islands
        
        // Traverse the grid
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (!vis[i][j] && grid[i][j] == 1) { // If a new unvisited island is found
                    vector<pair<int, int>> island; // Create a vector to store the island coordinates
                    dfs(i, j, grid, vis, island, i, j); // Perform DFS to explore and collect island coordinates
                    s.insert(island); // Insert the island into the set (automatically eliminates duplicates)
                }
            }
        }
        
        return s.size(); // Return the count of distinct islands
    }
};

Time Complexity ~ O(N² + NxMx9), N² for the nested loops, and NxMx9 for the overall DFS of the matrix, 
		  that will happen throughout if all the cells are filled with 1.

Space Complexity: O(N²) for visited array max queue space O(N²), If all are marked as 1 then the maximum queue space will be N².

-------------------------------------------------------------------------------------------------------------------------
11) Is Graph Bipartite?

We use the logic of Cycle detection using BFS/DFS.

In Cycle detection we were storing parent node, with each node. And whenever we
found that adjacent node is visited but it is not the parent then there is a cycle.

Here, instead of visited array we will maintain a color array.
Start traversal from starting node with color 0, and start traversing by BFS/DFS
whenever the adjacent node of current traversing node is colored and is colored
with the same color as current node. Then the Graph is not Bipartite.

While traversing adjacent nodes of an node, we set the check whether it is colored
or not. If it is not we colored it with opposite color of the current node.
Initial colors are all -1.

When we end up with all coloring the graph, we conclude that the graph is bipartite.

#BFS:

class Solution {
public:
    bool bfs(int startNode,vector<vector<int>>& graph,vector<int> &color){

        // Create a queue for BFS traversal
        queue<int> q;

        // Push the starting node to the queue
        q.push(startNode);

        // Assign the starting node color as 0
        color[startNode]=0;
        
        // Perform BFS traversal
        while(!q.empty()){

            // Get the front node from the queue
            int node = q.front();
            q.pop();

            // Traverse all adjacent nodes of the current node
            for(auto &adjacentNode : graph[node]){

                // If the adjacent node is not colored yet
                if(color[adjacentNode]==-1){
                    // Assign the opposite color to the adjacent node
                    color[adjacentNode] = !color[node];
                    // Push the adjacent node to the queue for further traversal
                    q.push(adjacentNode);
                }

                // If the adjacent node has the same color as the current node
                else if(color[adjacentNode] == color[node]){
                    // The graph is not bipartite, return false
                    return false;
                }
            }
        }

        // All nodes are colored without any conflict, the graph is bipartite
        return true;
    }

    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        // Create a vector to store colors for each node
        vector<int> color(n,-1);
        
        // Iterate through all nodes(components) of the graph
        for(int i=0;i<n;i++){
            // If the node is not colored yet
            if(color[i]==-1){
                // Perform BFS traversal from the current node
                if(bfs(i,graph,color)==false){
                    // If the graph is not bipartite, return false
                    return false;
                }       
            }
        }
        // All nodes are colored without any conflict, the graph is bipartite
        return true;
    }
};

#DFS:

class Solution {
public:

    bool dfs(int node,int col,vector<vector<int>>& graph,vector<int> &color){
        // Assign the current node with the given color
        color[node] = col;

        // Traverse all adjacent nodes of the current node
        for(auto &adj:graph[node]){
            // If the adjacent node is not colored yet
            if(color[adj]==-1){
                // Recursively call DFS on the adjacent node with the opposite color
                if(dfs(adj,!col,graph,color)==false){
                    // If the recursive call returns false, the graph is not bipartite
                    return false;
                }
            }
            // If the adjacent node has the same color as the current node
            else if(color[adj]==color[node]){
                // The graph is not bipartite, return false
                return false;
            }
        }
        // All nodes are colored without any conflict, the graph is bipartite
        return true;
    }

    bool isBipartite(vector<vector<int>>& graph) {
        int n = graph.size();
        // Create a vector to store colors for each node
        vector<int> color(n,-1);

        // Iterate through all nodes(components) of the graph
        for(int i=0;i<n;i++){
            // If the node is not colored yet
            if(color[i]==-1){
                // Perform DFS traversal from the current node with color 0
                if(dfs(i,0,graph,color)==false){
                    // If the graph is not bipartite, return false
                    return false;
                }
            }
        }
        // All nodes are colored without any conflict, the graph is bipartite
        return true;
    }
};


Time Complexity: O(V + 2E), Where V = Vertices, 2E is for total degrees as we traverse all adjacent nodes.

Space Complexity: O(3V) ~ O(V), Space for DFS stack space, colour array and an adjacency list.

--------------------------------------------------------------------------------------------------------------------------
12) Detect cycle in a directed graph (using DFS) 

*PATH VISITED !!

class Solution {
  public:
  
	// Function to perform DFS and detect cycle in a directed graph.
	bool dfsCheck(int node, vector<int> adj[], int vis[], int pathVis[]) {
		// Mark the current node as visited in the current traversal
		vis[node] = 1;
		// Jattana path visited kara.
		pathVis[node] = 1;

		// Traverse all adjacent nodes of the current node
		for (auto it : adj[node]) {
			// When the adjacent node is not visited yet
			if (!vis[it]) {
				// If we get a cycle by any from any of the adjacent node, return true.
				if (dfsCheck(it, adj, vis, pathVis) == true)
					return true;
			}
			// If the adjacent node has been previously visited on the same path, there is a cycle
			else if (pathVis[it]) {
				return true;
			}
		}
		
		// Fucntion ithe ala mhnje ya path madhe cycle nhiye!!

		// Mark the current node as not visited in the current traversal
		pathVis[node] = 0;
        
		// No cycle found for the current path
		return false;
	}
  
    // Function to detect cycle in a directed graph.
    bool isCyclic(int V, vector<int> adj[]) {
		// Create an array to track visited nodes
		int vis[V] = {0};
		// Create an array to track visited nodes in the current traversal
		int pathVis[V] = {0};

		// Iterate through all nodes of the graph
		for (int i = 0; i < V; i++) {
			// If the node is not visited yet, perform DFS traversal
			if (!vis[i]) {
				if (dfsCheck(i, adj, vis, pathVis) == true)
					return true;
			}
		}

		// No cycle found in the graph
		return false;
    }
};

Time Complexity: O(V+E)+O(V) , where V = no. of nodes and E = no. of edges. There can be at most V components. So, another O(V) time complexity.

Space Complexity: O(2N) + O(N) ~ O(2N): O(2N) for two visited arrays and O(N) for recursive stack space.

--------------------------------------------------------------------------------------------------------------------------
13) Find Eventual Safe States – DFS

the intuition is to figure out the nodes which are either a part of a cycle or incoming to the cycle. 
We can do this easily using the cycle detection technique that was used previously to detect cycles in a directed graph (using DFS). 

Note: Points to remember that any node which is a part of a cycle or leads to the cycle through an incoming edge 
towards the cycle, cannot be a safe node. Apart from these types of nodes, every node is a safe node.

For approach refer my notes.

class Solution {
public:
    // Function to perform DFS and check for eventual safe nodes
    bool dfsCheck(int node, vector<int>& vis, vector<int>& pathVis, vector<int>& check, vector<vector<int>>& graph){
        // Mark the current node as visited
        vis[node] = 1;

        // Mark the current node as visited in the current path
        pathVis[node] = 1;

        // Traverse all adjacent nodes of the current node
        for(auto &adjNode : graph[node]){
            // If the adjacent node is not visited yet
            if(!vis[adjNode]){
                // Recursively call DFS on the adjacent node
                if(dfsCheck(adjNode, vis, pathVis, check, graph)){
                    // If a cycle is found in the path, return true
                    return true;
                }
            }
            // If the adjacent node is visited in the current path, there is a cycle
            else if(pathVis[adjNode]){
                return true;
            }
        }

        // Function ithe ala mhnje current path madhe cycle nhiye, mg backtrack kartana
        // path madhle sagle nodes as a safe mark kara/check 1 kara

        // Mark the current node as checked (eventually safe)
        check[node] = 1;

        // Mark the current node as not visited in the current path
        pathVis[node] = 0;

        // No cycle found for the current node
        return false;
    }

    // Function to find the eventual safe nodes in the graph
    vector<int> eventualSafeNodes(vector<vector<int>>& graph) {
        int n = graph.size();

        // Create arrays to track visited nodes, nodes visited in the current path, and checked nodes
        vector<int> vis(n,0), pathVis(n,0), check(n, 0);

        // Iterate through all nodes of the graph
        for(int i=0;i<n;i++){
            // If the node is not visited yet, perform DFS traversal
            if(!vis[i]){
                dfsCheck(i, vis, pathVis, check, graph);
            }
        }

        // Collect all the eventually safe nodes
        vector<int> ans;
        for(int i=0;i<n;i++){
            if(check[i]) ans.push_back(i);
        }

        // Return the eventually safe nodes
        return ans;
    }
};

Time Complexity: O(V+E)+O(V), where V = no. of nodes and E = no. of edges. There can be at most V components. So, another O(V) time complexity.

Space Complexity: O(3N) + O(N) ~ O(3N): O(3N) for three arrays required during dfs calls and O(N) for recursive stack space.

--------------------------------------------------------------------------------------------------------------------------
14) Mother Vertex

https://practice.geeksforgeeks.org/problems/mother-vertex/1

class Solution 
{
    public:
    
    // Depth-First Search (DFS) function to explore the graph
    void dfs(int node, vector<int> adj[], int vis[]){
        
        // Mark the current node as visited
        vis[node] = 1;
        
        // Visit all adjacent nodes that haven't been visited yet
        for(auto &adjNode : adj[node]){
            if(!vis[adjNode]){
                dfs(adjNode, adj, vis);
            }
        } 
    }
    
    // Function to find a mother vertex in the given graph
	int findMotherVertex(int V, vector<int> adj[])
	{
	    // Initialize the answer as -1 (no mother vertex found yet)
	    int ans = -1;
	    
	    // Initialize an array to keep track of visited nodes
	    int vis[V] = {0};
	    
	    // Loop through all vertices in the graph
	    for(int i=0; i<V; i++){
	        // If the current vertex hasn't been visited, start a DFS from it
	        if(!vis[i]){
	            dfs(i, adj, vis);
	            // Update the potential mother vertex
	            ans = i;
	        }
	    }
	    
	    // Reset the visited array for a fresh DFS
	    for(int i=0; i<V; i++){
	        vis[i] = 0;
	    }
	    
	    // Perform DFS from the potential mother vertex to check if it's indeed a mother vertex
	    dfs(ans, adj, vis);
	    
	    // Check if all vertices were visited in the second DFS
	    for(int i=0; i<V; i++){
	        if(!vis[i]){
	            // If not all vertices were visited, there's no mother vertex
	            return -1;
	        }
	    }
	    
	    // Return the potential mother vertex found
	    return ans;
	}
};

--------------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------------

