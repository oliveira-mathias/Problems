class Solution {
public:
    // Let M be the output size
    // Besides the sorting, the tree depth is at most O(n)
    // Clearly the set returned by generateStrings is O(M)
    // Thus, inthe worst case, which is the concatenation rule,
    // We may spent O(n) for each of the O(M²) loop iterations
    // Time: O(M log(M) + n²*M²)
    // Space: O(M + n)
    vector<string> braceExpansionII(const string& expression) {
        // The grammar
        // E := letter | E_1E_2 | {E} | {E_1,E_2,...,E_n} n>=2
        unordered_map<int, int> closing;
        stack<int> s;
        // Parse the brackets
        for(int i=0; i<expression.size(); ++i) {
            if(expression[i]=='{') {
                s.push(i);
            }
            else if(expression[i]=='}') {
                int bracketOpen = s.top();
                s.pop();
                closing[bracketOpen] = i;
            }
        }
        const auto generateStrings = [&closing, &expression](this auto&& generateStrings, int start, int end) -> unordered_set<string> {
            // Base case
            // E := letter
            if(start == end) {
                unordered_set<string> ans;
                string s;
                s += expression[start];
                ans.insert(s);
                return ans;
            }

            // Recursive case
            // Check which case we are
            // E := {E} | {E_1,E_2,...,E_n} n>=2
            if(expression[start]=='{' && closing[start]==end) {
                vector<pair<int, int>> subExp;
                int exprStart = start+1;
                for(int i=exprStart; i<end;) {
                    if(expression[i]=='{') {
                        i = closing[i];
                    }
                    if(expression[i]==',') {
                        subExp.push_back({exprStart, i-1});
                        exprStart = i+1;
                        i = exprStart;
                    }
                    else {
                        i++;
                    }
                }
                // We must push the last sub expression
                subExp.push_back({exprStart, end-1});

                unordered_set<string> ans;
                for(int i=0; i<subExp.size(); ++i) {
                    // We merge the itens so that they end up sorted
                    unordered_set<string> nextSet = generateStrings(subExp[i].first, subExp[i].second);
                    ans.insert(nextSet.begin(), nextSet.end());
                }
                return ans;
            }
            // E := E_1E_2
            else {
                unordered_set<string> leftExpAns;
                unordered_set<string> rightExpAns;
                if(expression[start]=='{') {
                    leftExpAns = generateStrings(start, closing[start]);
                    rightExpAns = generateStrings(closing[start] + 1, end);
                }
                else {
                    string s;
                    s += expression[start];
                    leftExpAns.insert(s);
                    rightExpAns = generateStrings(start+1, end);
                }

                unordered_set<string> ans;
                for(const string& left : leftExpAns) {
                    for(const string& right :  rightExpAns) {
                        ans.insert(left + right);
                    }
                }
                return ans;
            }
        };
        unordered_set<string> ansSet = generateStrings(0, expression.size()-1);
        vector<string> ans;
        ans.reserve(ansSet.size());
        for(const string& item : ansSet) {
            ans.push_back(item);
        }
        sort(ans.begin(), ans.end());
        return ans;
    }
};
