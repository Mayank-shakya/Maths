#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define int long long
#define F first
#define S second
#define endl '\n'



const int M=1e9+7;
const long long N=1e17+9;



void solve() {
  int n;
  cin>>n;
  vector<int>v(n);
  for(auto &i:v)cin>>i;

//   sort(v.begin(),v.end());

  int lo=0,hi=accumulate(v.begin(), v.end(), 0LL);

  int ans=-1;


 vector<long long> pf(n + 1, 0);
  for (int i = 1; i <= n; ++i) pf[i] = pf[i - 1] + v[i - 1];

//   for(auto i:pf)cout<<i<<' ';

  auto ff=[&](int md)->bool{  // no of sub having sum<=m >=((n+1)/2)
    int cnt=0;
      int total_subarrays = n*(n+1)/2;
 
    int req=(total_subarrays + 1)/2;

    vector<int>mp;

    for(int i=0;i<n+1;i++){
        int tofind=pf[i]-md;

        int ub=mp.end()-lower_bound(mp.begin(),mp.end(),tofind);
        // cout<<ub<<endl;
        cnt+=ub;


// cout<<cnt<<endl;
        if(cnt>=req)return 1;

        mp.push_back(pf[i]);
    }

    return cnt>=req;

  };

//   cout<<ff(2)<<endl;
    // cout<<ff(3)<<endl;

  while(lo<=hi){
    int md=(lo+hi)/2;
    

    if(ff(md)){
       
        ans=md;
        hi=md-1;
    }else{
        lo=md+1;
    }
  }
cout<<ans<<endl;
// // cout<<f(0);
// //   cout<<ans<<endl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
    
    int _t=1;
    cin >> _t;
    while (_t--){
        solve();
    }
    return 0;
}


Sample Input 1
5
3
1 2 3
1
5
2
1 5
10
1 2 2 3 3 4 5 4 6 7
15
100 222 333 511 555 232 444 555 777 888 999 1000 1112 12345 123456
Sample Output 1
3
5
5
13
3629
Note
For the first test case, all subarray sums are {1, 3, 6, 2, 5, 3}, sorted becomes {1, 2, 3, 3, 5, 6} and the median (smaller middle) is 3.
For the second test case, only one subarray sum {5} so median is 5.
For the third test case, subarray sums are {1, 5, 5} and the median is 5.
For larger cases, same method applies using the algorithm described.
