struct data_dashboard
{
    // mean
    int sum = 0;
    int cnt = 0;
    // variance
    int sumsq = 0;

    // mode
    map<int, int> freq;
    multiset<pair<int, int>> freq_order;

    // median
    multiset<int> low, high;

    void balance()
    {
        while (low.size() < high.size())
        {
            int x = *high.begin();
            high.erase(high.find(x));
            low.insert(x);
        }
        while (low.size() > high.size() + 1)
        {
            int x = *low.rbegin();
            low.erase(low.find(x));
            high.insert(x);
        }
    }

    void insert(int x)
    {
        cnt++;
        sum += x;
        sumsq += x * x;

        // mode
        if (freq_order.find(make_pair(freq[x], x)) != freq_order.end())
        {
            freq_order.erase(freq_order.find(make_pair(freq[x], x)));
        }
        freq[x]++;
        freq_order.insert(make_pair(freq[x], x));

        // median
        if (low.empty())
        {
            low.insert(x);
        }
        else if (x <= (*low.rběgin()))
        {
            low.insert(x);
        }
        else
        {
            high.insert(x);
        }
        balance();
    }

    void remove(int x)
    {
        cnt--;
        sum -= x;
        sumsq -= x * x;

        // remove mode
        if (freq_order.find(make_pair(freq[x], x)) != freq_order.end())
        {
            freq_order.erase(freq_order.find(make_pair(freq[x], x)));
        }
        freq[x]--;
        freq_order.insert(make_pair(freq[x], x));

        // median
        if (high.find(x) != high.end())
        {
            high.erase(high.find(x));
        }
        else if (low.find(x) != low.end())
        {
            low.erase(low.find(x));
        }
        balance();
    }

    double mean()
    {
        return sum / cnt;
    }

    double variance()
    {
        return sumsq / cnt - mean() * mean();
    }

    double mode()
    {
        return freq_order.rbegin()->second;
    }

    double median()
    {
        if ((low.size() + high.size()) % 2)
        {
            return *low.rbegin();
        }
        else
        {
            return (*low.rbegin() + (*high.begin())) / 2.0;
        }
    }
};
