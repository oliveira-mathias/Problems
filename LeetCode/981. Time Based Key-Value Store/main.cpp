class TimeMap {
    unordered_map<string, vector<pair<int, string>>> data;
public:
    TimeMap() = default;
    
    // Time: O(1)
    void set(const string& key, const string& value, int timestamp) {
        data[key].emplace_back(timestamp, value);
    }
    
    // Time: O(log(n))
    string get(const string& key, int timestamp) {
        if(!data.contains(key)) return "";

        vector<pair<int, string>>& registers = data[key];
        if(registers.empty()) return "";

        const pair<int, string> target = {timestamp, ""};
        auto it = upper_bound(registers.begin(), registers.end(), target,
            [](const pair<int, string>& a, const pair<int, string>& b) -> bool {
                return a.first < b.first;
            }
        );
        if(it == registers.begin()) return "";
        --it;
        return it->second;
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */
