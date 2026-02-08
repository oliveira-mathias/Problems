class Solution {
    void Dijkstra(vector<vector<int>>& adj, vector<vector<int>>& cost, int start, vector<int>& distFromStart) {
        int n = adj.size();

        vector<bool> visited(n, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;

        // Inserting node
        heap.push({0, start});
        while(!heap.empty()) {
            const auto[dist, node] = heap.top();
            heap.pop();

            if(visited[node]) continue;
            
            distFromStart[node] = dist;
            visited[node] = true;
            for(int neigh : adj[node]) {
                if(!visited[neigh]) {
                    heap.push({dist + cost[node][neigh], neigh});
                }
            }
        }
    }
public:
    // n = source.size(), m = original.size(), k=alphaSize
    // Time: O(n + m + k³log(k))
    // Space: O(k²)
    // We can assume k is constant
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        constexpr int alphaSize = 26;

        // Building the adjacency of the graph
        vector<vector<int>> adj(alphaSize, vector<int>());
        vector<vector<int>> costTable(alphaSize, vector<int>(alphaSize, -1));

        for(int i=0; i<original.size(); ++i) {
            int from = original[i] - 'a';
            int to = changed[i] - 'a';

            if(costTable[from][to] >= 0) {
                costTable[from][to] = min(costTable[from][to], cost[i]);
            } else {
                costTable[from][to] = cost[i];
            }
        }

        for(int i=0; i<alphaSize; ++i) {
            for(int j=0; j<alphaSize; ++j) {
                if(costTable[i][j] >= 0) {
                    adj[i].push_back(j);
                }
            }
        }

        // Building the distance table
        vector<vector<int>> dist(alphaSize, vector<int>(alphaSize, -1));
        for(int start=0; start<alphaSize; ++start) {
            Dijkstra(adj, costTable, start, dist[start]);
        }

        // Computing change cost
        long long convertCost = 0;
        for(int i=0; i<source.size(); ++i) {
            int from = source[i] - 'a';
            int to = target[i] - 'a';
            if(dist[from][to] >= 0) {
                convertCost += dist[from][to];
            }
            else {
                // Here it is impossible to convert source into target
                return -1;
            }
        }

        return convertCost;
    }
};
