class Solution {
public:
    // Time: O((km)log(kn))
    // Space: O(kn)
    int shortestPath(int n, const vector<vector<int>>& edges, const string& labels, int k) {
        const int INF = numeric_limits<int>::max();
        
        // Building the graph
        vector<vector<pair<int, int>>> adj(n, vector<pair<int, int>>());
        for(const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            adj[u].push_back({v, w});
        }
        
        vector<vector<int>> dist(n, vector<int>(k, INF));
        typedef pair<int, pair<int, int>> WorkUnit;
        priority_queue<WorkUnit, vector<WorkUnit>, greater<WorkUnit>> pq;

        // We perform the search
        dist[0][0] = 0;
        pq.push({0, {0,0}});
        while(!pq.empty()) {
            auto wu = pq.top();
            pq.pop();
            auto [nodeDist, nodePair] = wu;
            auto [node, seq] = nodePair;

            // Discarding redundant work units
            if(nodeDist > dist[node][seq]) continue;
            // Check if we reached destination
            // First time we reach n-1 is the answer
            if(node == n-1) return nodeDist;

            // Visiting neighboors
            for(auto [neigh, weight] :  adj[node]) {
                int neighSeq = (labels[node]==labels[neigh]) ? (seq+1) : 0;
                // This node would crete a illegal sequence
                if(neighSeq == k) continue;
                int neighDist = nodeDist + weight;
                if(neighDist < dist[neigh][neighSeq]) {
                    // Add the neighbor to the heap
                    dist[neigh][neighSeq] = neighDist;
                    pq.push({neighDist, {neigh, neighSeq}});
                }
            }

        }

        // Here it wasn't possible to reach node n-1 
        return -1;
    }
};
