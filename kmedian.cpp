struct MedianTracker
{
    multiset<int> low, high;
    
    void balance()
    {
        int target_k = (low.size() + high.size() + 1) / 2;
        
        // Move excess elements from low to high
        while (low.size() > target_k) {
            int x = *low.rbegin();
            low.erase(low.find(x));
            high.insert(x);
        }
        
        // Move elements from high to low if needed
        while (low.size() < target_k && !high.empty()) {
            low.insert(*high.begin());
            high.erase(high.begin());
        }
    }

    void insert(int x)
    {
        if (low.empty() || x <= *low.rbegin()) {
            low.insert(x);
        } else {
            high.insert(x);
        }
        balance();
    }

    void remove(int x)
    {
        if (low.find(x) != low.end()) {
            low.erase(low.find(x));
        } else if (high.find(x) != high.end()) {
            high.erase(high.find(x));
        }
        balance();
    }

    double median()
    {
        int total = low.size() + high.size();
        if (total == 0) {
            throw runtime_error("Cannot compute median of empty set");
        }
        
        if (total % 2 == 1) {
            return *low.rbegin();
        } else {
            return (*low.rbegin() + *high.begin()) / 2.0;
        }
    }
    
    int total_size() const {
        return low.size() + high.size();
    }
    
    bool empty() const {
        return low.empty() && high.empty();
    }
};


// https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-ii/submissions/1821276425/?envType=daily-question&envId=2025-11-05
// https://leetcode.com/problems/sequentially-ordinal-rank-tracker/description/
// https://leetcode.com/problems/finding-mk-average/description/
// https://leetcode.com/problems/find-median-from-data-stream/description/
// https://leetcode.com/problems/sliding-window-median/description/
