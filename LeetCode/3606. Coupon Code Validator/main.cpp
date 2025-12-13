class Solution {
    bool isAlpha(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    bool isNum(char c) {
        return (c >= '0' && c <= '9');
    }

    bool isValidCode(const string& code) {
        for(char c : code) {
            if(!isAlpha(c) && !isNum(c) && (c != '_')) {
                return false;
            }
        }
        return (code.size() > 0);
    }

    bool isValidBusinessLine(const string& bl) {
        return (bl == "electronics")
                || (bl == "grocery")
                || (bl == "pharmacy")
                || (bl == "restaurant");
    }

public:
    // Suppose the largest stringin code, businessLine has size O(K)
    // Suppose there are O(n) cupons
    // Time: O(nk log(n))
    // Space: O(n)
    vector<string> validateCoupons(vector<string>& code, vector<string>& businessLine, vector<bool>& isActive) {
        vector<int> validCupomIndexes;
        for (int i=0; i<code.size(); ++i) {
            if(isValidCode(code[i]) && isValidBusinessLine(businessLine[i]) && isActive[i]) {
                validCupomIndexes.emplace_back(i);
            }
        }

        // Sort valid cupons
        unordered_map<string, int> priority {
            {"electronics", 0},
            {"grocery", 1},
            {"pharmacy", 2},
            {"restaurant", 3}
        };
        sort(validCupomIndexes.begin(), validCupomIndexes.end(), 
            [&code, &businessLine, &priority](int i, int j) {
                if(priority[businessLine[i]] < priority[businessLine[j]]) {
                    return true;
                }
                else if(priority[businessLine[i]] > priority[businessLine[j]]) {
                    return false;
                }
                else {
                    return (code[i] < code[j]);
                }
            });

        
        vector<string> orderedCupons;
        for(int cupomIndex : validCupomIndexes) {
            orderedCupons.emplace_back(code[cupomIndex]);
        }

        return orderedCupons;

    }
};
