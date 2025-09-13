class Solution {
  bool canTalk(vector<vector<int>>& languages, int a, int b) {
      int ia = 0;
      int ib = 0;
      while(ia < languages[a].size() && ib < languages[b].size()) {
          if(languages[a][ia]==languages[b][ib]) {
              return true;
          }

          if(languages[a][ia] < languages[b][ib]) {
              ia++;
          }
          else {
              ib++;
          }
      }

      return false;
  }
  public:
  // Complexity: O(n*m*log(n))
  int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {
      // We sort in increasing order each user's language set
      for(int i=0; i<languages.size(); i++) {
          sort(languages[i].begin(), languages[i].end());
      }

      // We will work only with the non satisfied friendships
      vector<bool> hasUnfilledFriendship(languages.size(), false);
      for(int i=0; i<friendships.size(); i++) {
          int u = friendships[i][0];
          int v = friendships[i][1];
          // Correcting indexing
          --u;
          --v;
          if(!canTalk(languages, u, v)) {
              hasUnfilledFriendship[u] = true;
              hasUnfilledFriendship[v] = true;
          }
      }

      int minUsers = languages.size() + 1;
      for(int lang=1; lang<=n; lang++) {
          int currSol = 0;
          for(int j=0; j<languages.size(); j++) {
              if(hasUnfilledFriendship[j]) {
                  auto itj = lower_bound(languages[j].begin(), languages[j].end(), lang);
                  if(itj==languages[j].end() || *itj != lang) {
                      currSol++;
                  }
              }
          }
          minUsers = min(minUsers, currSol);
      }

      return minUsers;
  }
};
