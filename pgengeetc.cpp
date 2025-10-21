    vector<int> prev_g(n, -1), next_g(n, n);
    vector<int> prev_s(n, -1), next_s(n, n);

    // prev greater
    {
        stack<int> st;
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && a[st.top()] < a[i]) st.pop();
            prev_g[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }
    }

    // next greater
    {
        stack<int> st;
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && a[i] > a[st.top()]) {
                next_g[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
    }

    // prev smaller
    {
        stack<int> st;
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && a[st.top()] > a[i]) st.pop();
            prev_s[i] = st.empty() ? -1 : st.top();
            st.push(i);
        }
    }

    // next smaller
    {
        stack<int> st;
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && a[i] < a[st.top()]) {
                next_s[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
    }
