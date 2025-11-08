class Solution {
    void dfs(vector<vector<int>>& adj, vector<bool>& visited, vector<vector<int>>& components, vector<int>& nodeToComponent, int node) {
        if(visited[node]) {
            return;
        }

        components.back().push_back(node);
        visited[node] = true;
        nodeToComponent[node] = components.size()-1;

        for(int neigh : adj[node]) {
            dfs(adj, visited, components, nodeToComponent, neigh);
        }
    }
public:
    vector<int> processQueries(int c, vector<vector<int>>& connections, vector<vector<int>>& queries) {
        // Build the graph
        vector<vector<int>> adj(c, vector<int>());
        for(const vector<int>& edge : connections) {
            int u = edge[0];
            int v = edge[1];
            --u;
            --v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // Collect the conected components
        vector<bool> visited (c, false);
        vector<int> nodeToComponent (c, 0);
        vector<vector<int>> conectedComponents;

        for(int i=0; i<c; i++) {
            if(!visited[i]) {
                conectedComponents.push_back(vector<int>());
                dfs(adj, visited, conectedComponents, nodeToComponent, i);
            }
        }

        // Sort the power grids
        for(int i=0; i<conectedComponents.size(); i++) {
            sort(conectedComponents[i].begin(), conectedComponents[i].end());
        }

        // Process the queries
        int nPowerGrids = conectedComponents.size();
        vector<int> powerGridMask (nPowerGrids, 0);
        vector<bool> onlineStations(c, true);

        vector<int> opResults;
        for(const vector<int>& query : queries) {
            int opType = query[0];
            int targetStation = query[1];
            --targetStation;
            int componentId = nodeToComponent[targetStation];
            const vector<int>& component = conectedComponents[componentId];

            if(opType==1) {
                if(onlineStations[targetStation]) {
                    opResults.push_back(targetStation+1);
                }
                else {
                    if(powerGridMask[componentId]==component.size()) {
                        opResults.push_back(-1);
                    }
                    else {
                        opResults.push_back(component[powerGridMask[componentId]]+1);
                    }
                }
            }
            else {
                onlineStations[targetStation] = false;
                while(powerGridMask[componentId] < component.size() && !onlineStations[component[powerGridMask[componentId]]]) {
                    powerGridMask[componentId]++;
                }
            }
        }

        return opResults;
    }
};
