class Solution {
public:
    // Time: (N log(N) + Q log(N))
    // Space: O(N log(N))
    vector<int> pathExistenceQueries(int n, const vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<int> nodes(n);
        for(int i=0; i<n; ++i) nodes[i] = i;

        // Sort nodes on the real line
        sort(nodes.begin(), nodes.end(), 
        [&nums](int i, int j) -> bool {
            return (nums[i] < nums[j]);
        });
        vector<int> nodeToPos(n);
        for(int i=0; i<n; ++i) {
            int node = nodes[i];
            nodeToPos[node] = i;
        }
        vector<int> dist(n);
        for(int i=0; i<n; ++i) dist[i] = nums[nodes[i]];

        // Binary lifting table
        int logN = ceil(log2(n));
        vector<vector<int>> right(n, vector<int>(logN + 1));
        for(int i=n-1; i>=0; --i) {
            int currentNode = nodes[i];
            auto it = upper_bound(dist.begin(), dist.end(), dist[i] + maxDiff);
            int nextNodePos = (it - dist.begin()) - 1;
            right[currentNode][0] = nodes[nextNodePos];
            
            for(int k=1; k<=logN; ++k) {
                int halfPathNode = right[currentNode][k-1];
                right[currentNode][k] = right[halfPathNode][k-1];
            }
        }
        auto shortestDist = [&right, &nodeToPos, &dist, logN](int u, int v) -> int {
            // Edge case
            if(u == v) return 0;

            int uPos = nodeToPos[u];
            int uDist = dist[uPos];

            int vPos = nodeToPos[v];
            int vDist = dist[vPos];

            if(vDist < uDist) {
                swap(u, v);
                swap(uPos, vPos);
                swap(uDist, vDist);
            }

            int pathDist = 0;
            for(int k=logN; k>=0; --k) {
                int candidate = right[u][k];
                int candidatePos = nodeToPos[candidate];
                int candidateDist = dist[candidatePos];

                if(candidateDist < vDist) {
                    u = candidate;
                    pathDist += (1U << k);
                }

            }

            int lastNeigh = right[u][0];
            int lastNeighPos = nodeToPos[lastNeigh];
            int lastNeighDist = dist[lastNeighPos];
            if(lastNeighDist < vDist) return -1;
            else return pathDist + 1;
        };

        // Answering queries
        vector<int> ans(queries.size());
        for(int i=0; i<queries.size(); ++i) {
            const vector<int>& query = queries[i];
            int u = query[0];
            int v = query[1];

            ans[i] = shortestDist(u, v);
        }
        return ans;
    }
};
