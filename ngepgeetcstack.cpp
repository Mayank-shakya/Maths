#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Template for next/previous greater/smaller elements
vector<int> nextGreater(const vector<int>& arr) {
    int n = arr.size();
    vector<int> res(n, n);
    stack<int> st;
    for(int i = 0; i < n; i++) {
        while(!st.empty() && arr[st.top()] < arr[i]) {
            res[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return res;
}

vector<int> prevGreater(const vector<int>& arr) {
    int n = arr.size();
    vector<int> res(n, -1);
    stack<int> st;
    for(int i = n-1; i >= 0; i--) {
        while(!st.empty() && arr[st.top()] < arr[i]) {
            res[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return res;
}

vector<int> nextSmaller(const vector<int>& arr) {
    int n = arr.size();
    vector<int> res(n, n);
    stack<int> st;
    for(int i = 0; i < n; i++) {
        while(!st.empty() && arr[st.top()] > arr[i]) {
            res[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return res;
}

vector<int> prevSmaller(const vector<int>& arr) {
    int n = arr.size();
    vector<int> res(n, -1);
    stack<int> st;
    for(int i = n-1; i >= 0; i--) {
        while(!st.empty() && arr[st.top()] > arr[i]) {
            res[st.top()] = i;
            st.pop();
        }
        st.push(i);
    }
    return res;
}