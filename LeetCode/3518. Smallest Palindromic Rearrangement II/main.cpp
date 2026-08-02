class Solution {
public:
    string smallestPalindrome(const string& s, int k) {
        int n = s.size();

        constexpr int ALPHA_SIZE = 26;
        vector<int> freq(ALPHA_SIZE);


        for(int i=0; i<n/2; ++i) {
            freq[s[i]-'a']++;
        }

        const auto boundedNChoosel = [&k](int n, int l) -> int {
            l = min(l, n-l);
            long long ans = 1;
            for(long long i=1; i<=l; ++i) {
                ans = (ans*(n-i+1))/i;
                if(ans > k) {
                    return k + 1;
                }
            }
            return ans;
        };
        const auto numberOfPerm = [&k, ALPHA_SIZE, &boundedNChoosel](int n, const vector<int>& freq) -> int {
            long long ans = 1;
            for(int i=0; i<ALPHA_SIZE; ++i) {
                int amnt = freq[i];
                if(amnt) {
                    int factor = boundedNChoosel(n, amnt);
                    n -= amnt;
                    if(factor > k) return k+1;
                    ans *= factor;
                    if(ans > k) return k + 1;
                }
            }
            return ans;
        };
        string ans(n, '1');
        if(n%2) {
            ans[n/2] = s[n/2];
        }
        int toChoose = n/2;
        for(int i=0; i<n/2; ++i) {
            char choosen = 0;
            for(int j=0; j<ALPHA_SIZE; ++j) {
                if(!freq[j]) continue;
                freq[j]--;
                int numPerm = numberOfPerm(toChoose-1, freq);
                if(numPerm < k) {
                    k -= numPerm;
                }
                else {
                    choosen = 'a' + j;
                    toChoose--;
                    break;
                }
                freq[j]++;
            }
            if(choosen) {
                ans[i] = choosen;
                ans[n-1-i] = choosen;
            }
            else {
                // Here there is no solution
                break;
            }
        }
        return (ans[0]=='1') ? "" : ans;
    }
};
