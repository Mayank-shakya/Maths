class Solution {
public:
#define F first
#define S second



struct DS{

    unordered_map<int,int>mp;

    void add(pair<int,int>&p){
        int x=p.S;
        mp[x]++;
    }
    void remove(pair<int,int>&p){
        int x=p.S;
        mp[x]--;
        if(mp[x]==0)mp.erase(x);
    }

    bool canEat(pair<int,int>&p,int K){
        // if(mp.size()<K-1 && mp.find(p.S) != mp.end()){
        //     return 0;
        // }

        if(mp.size()<K-1)return true;
        if(mp.size()==K-1 && mp.find(p.S) != mp.end())return true;
        
        return false;


    }

};
    vector<int> smallestRange(vector<vector<int>>& nums) {
        int k=nums.size();
        // cout<<k<<endl;
      DS ds;
      pair<int,int>pr;
      int ans=1e9;
        vector<pair<int,int>>v;
        for(int i=0;i<nums.size();i++){
            for(int j=0;j<nums[i].size();j++){
                v.push_back({nums[i][j],i});
            }
        }

        sort(v.begin(),v.end());
            //   for(auto [a,b]:v)cout<<a<<' '<<b<<endl;

        int head=-1,tail=0,n=v.size();

        while(tail<n){
           

            while(head+1<n && (ds.canEat(v[head+1],k))){
                head++;
                // cout<<head<<endl;
                ds.add(v[head]);
            }
// cout<<endl<<endl;
            //up
            if(head+1<n){
               
                int res=v[head+1].F-v[tail].F;
                if(res<ans){
                    ans=res;
                    pr={v[tail].F,v[head+1].F};
                }else if(res==ans){
                    if(v[tail].F<pr.F){
                        pr={v[tail].F,v[head+1].F};
                    }
                }
            }


            if(tail<=head){
                ds.remove(v[tail]);
                tail++;
            }else{
                tail++;
                head=tail-1;
            }
        }

  


        vector<int>vv;
        vv.push_back(pr.F);
        vv.push_back(pr.S);
        return vv;
    }
};
/// shortest window containing k different elements

// https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/description/