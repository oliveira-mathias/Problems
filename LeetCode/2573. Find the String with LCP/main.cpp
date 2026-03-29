class Solution {
    void DFS(vector<vector<int>>& adj, vector<int>& component, vector<bool>& visited, int node) {
        if(visited[node]) return;

        int n = adj.size();
        visited[node] = true;
        component.push_back(node);
        for(int i=0; i<n; ++i) {
            if(adj[node][i] && !visited[i]) {
                DFS(adj, component, visited, i);
            }
        }
    }
public:
    // Time: O(n²)
    // Space: O(n)
    string findTheString(vector<vector<int>>& lcp) {
        int n = lcp.size();

        // Check for symetry and DP consistency
        for(int i=0; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                // Symetry check
                if(lcp[i][j] != lcp[j][i]) {
                    return "";
                }

                // DP consistency check
                if(i==n-1 || j==n-1) {
                    if(lcp[i][j] != 0 && lcp[i][j] != 1) {
                        return "";
                    }
                }
                else {
                    if(lcp[i][j] != 0 && lcp[i][j] != lcp[i+1][j+1] + 1) {
                        return "";
                    }
                }
            }
        }

        // We collect the conected components
        vector<bool> visited(n, false);
        vector<vector<int>> components;
        for(int i=0; i<n; ++i) {
            if(visited[i]) {
                continue;
            }

            components.emplace_back(vector<int>());
            DFS(lcp, components.back(), visited, i);
        }

        // We only have 26 characters, so we can't have more than 26 components
        if(components.size() > 26) {
            return "";
        }

        // We create a candidate
        string res;
        res.resize(n);
        for(int i=0; i<components.size(); ++i) {
            for(int j=0; j<components[i].size(); ++j) {
                res[components[i][j]] = 'a' + i;
            } 
        }

        // We validate the candidate
        for(int i=0; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                if((lcp[i][j] > 0 && res[i] != res[j]) || (lcp[i][j]==0 && res[i] == res[j])) {
                    return "";
                }
            }
        }

        return res;
    }
};
