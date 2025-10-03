struct bag
{
    int K;
    multiset<int> mt1, mt2;
    int sumK;

    void init(int _K)
    {
        K = _K;
        sumK = 0;
        mt1.clear();
        mt2.clear();
    }

    void insert(int x)   //O(logn)
    {
        mt1.insert(x);
        sumK += x;
        if (mt1.size() > K)
        {
            auto it = mt1.begin();
            sumK -= *it;
            mt2.insert(*it);
            mt1.erase(it);
        }
    }

    void remove(int x)   //O(logn)
    {
        if (mt1.find(x) != mt1.end())
        {
            mt1.erase(mt1.find(x));
            sumK -= x;
        }
        else if (mt2.find(x) != mt2.end())
        {
            mt2.erase(mt2.find(x));
        }
        if (mt1.size() < K && !mt2.empty())
        {
            auto it = mt2.end();
            it--;
            int val = *it;
            mt2.erase(it);
            mt1.insert(val);
            sumK += val;
        }
    }

    int getSum()
    {
        return sumk;
    }
};
