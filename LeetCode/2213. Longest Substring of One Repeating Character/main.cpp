class SegTree {
    int n;
    vector<int> tree;

    void updateRec(int node, int L, int R, int target, int val) {
        // Base case
        if(L==R && L==target) {
            tree[node] = val;
            return;
        }

        // Recursive step
        int mid = L + (R-L)/2;
        int leftChild = 2*node;
        int rightChild = 2*node+1;
        if(L <= target && target <= mid) {
            updateRec(leftChild, L, mid, target, val);
        }
        else {
            updateRec(rightChild, mid+1, R, target, val);
        }
        tree[node] = max(tree[leftChild], tree[rightChild]);
    }

    public:
    SegTree(int _n) : n(_n) {
        tree = vector<int>(4*n);
    }

    void update(int index, int val) {
        updateRec(1, 0, n-1, index, val);
    }

    int treeMax() {
        return tree[1];
    }
};

class Solution {
public:
    // Time: O(n log(n) + k log(n))
    // Space: O(n)
    vector<int> longestRepeating(string s, const string& queryCharacters, const vector<int>& queryIndices) {
        int n = s.size();
        map<int, int> inter;
        SegTree rmq(n);

        // Creating the interval tree and rmq structures
        char currChar = s[0];
        int streak = 0;
        for(int i=0; i<n; ++i) {
            if(s[i]!=currChar) {
                int start = i-streak;
                inter[start] = i-1;
                rmq.update(start, streak);

                currChar = s[i];
                streak = 1;
            }
            else {
                streak++;
            }
        }
        inter[n-streak] = n-1;
        rmq.update(n-streak, streak);

        int k = queryIndices.size();
        vector<int> lengths(k);
        for(int i=0; i<k; ++i) {
            int index = queryIndices[i];
            char newChar = queryCharacters[i];

            if(s[index] == newChar) {
                // Nothing changes
                lengths[i] = rmq.treeMax();
                continue;
            }

            s[index] = newChar;
            auto it = inter.upper_bound(index);
            --it;

            // Updating the inteval
            int itIntervalStart = it->first;
            int itIntervalEnd = it->second;
            if(index != itIntervalStart && index != itIntervalEnd) {
                // We break the current interval into tree
                inter[index+1] = itIntervalEnd;
                inter[itIntervalStart] = index-1;
                inter[index] = index;
                rmq.update(itIntervalStart, index-itIntervalStart);
                rmq.update(index, 1);
                rmq.update(index+1, itIntervalEnd-index);
            }
            else if(index == itIntervalStart && index != itIntervalEnd) {
                // We split the interval into two intervals
                inter[index] = index;
                inter[index+1] = itIntervalEnd;
                rmq.update(index, 1);
                rmq.update(index+1, itIntervalEnd-index);
            }
            else if(index != itIntervalStart && index == itIntervalEnd) {
                // We split the interval into two intervals
                inter[itIntervalStart] = index-1;
                inter[index] = index;
                rmq.update(itIntervalStart, index-itIntervalStart);
                rmq.update(index, 1);
            }

            // Now we check if we can merge the affected interval with its neighbors
            const auto mergeIntervals = [&s, &inter, &rmq](map<int, int>::iterator& prev, map<int, int>::iterator& it) {
                int prevStartIndex = prev->first;
                int prevEndIndex = prev->second;
                int itStartIndex = it->first;
                int itEndIndex = it->second;
                if(s[itStartIndex]==s[prevStartIndex]) {
                    inter[prevStartIndex] = itEndIndex;
                    rmq.update(itStartIndex, 0);
                    rmq.update(prevStartIndex, itEndIndex-prevStartIndex+1);
                    inter.erase(it);
                    it = prev;
                }
            };
            it = inter.lower_bound(index);
            if(it != inter.begin()) {
                auto prev = it;
                --prev;
                mergeIntervals(prev, it);
            }
            auto next = it;
            ++next;
            if(next != inter.end()) {
                mergeIntervals(it, next);
            }

            lengths[i] = rmq.treeMax();
        }

        return lengths;
    }
};
