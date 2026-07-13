class Solution {
public:
    void dfs(int node,
             vector<vector<int>>& graph,
             vector<bool>& visited,
             int& vertices,
             int& degreeSum) {
        
        visited[node] = true;
        vertices++;
        degreeSum += graph[node].size();

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, graph, visited, vertices, degreeSum);
            }
        }
    }

    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);

        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];

            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        vector<bool> visited(n, false);
        int completeComponents = 0;

        for (int node = 0; node < n; node++) {
            if (!visited[node]) {
                int vertices = 0;
                int degreeSum = 0;

                dfs(node, graph, visited, vertices, degreeSum);

                int componentEdges = degreeSum / 2;
                int requiredEdges = vertices * (vertices - 1) / 2;

                if (componentEdges == requiredEdges) {
                    completeComponents++;
                }
            }
        }

        return completeComponents;
    }
};