#include<bits/stdc++.h>
using namespace std;using G=vector<vector<vector<int>>>;
int main(){
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int R,C;if(!(cin>>R>>C))return 0;
    string t;getline(cin,t);string l;getline(cin,l);
    stringstream ss(l);vector<string>a;while(ss>>t)a.push_back(t);
    G s(R,vector<vector<int>>(C));int id=1;
    for(int i=0;i<R;i++)for(int j=0;j<C;j++)s[i][j].push_back(id++);
    for(auto&x:a){
        char o=x[0];int k=stoi(x.substr(1));
        if(o=='v'){
            int r=s.size(),c=s[0].size(),L=k,RR=c-L,N=max(L,RR);
            G ns(r,vector<vector<int>>(N));
            int sh=N-L;
            for(int i=0;i<r;i++)for(int j=0;j<L&&j<c;j++){
                int nj=sh+j;if(nj>=0&&nj<N)ns[i][nj]=s[i][j];
            }
            for(int i=0;i<r;i++)for(int j=0;j<RR;j++){
                int src=L+j;if(src<c){
                    int nj=N-1-j;
                    if(nj>=0&&nj<N&&!s[i][src].empty()){
                        auto v=s[i][src];
                        reverse(v.begin(),v.end());
                        ns[i][nj].insert(ns[i][nj].end(),v.begin(),v.end());
                    }
                }
            }
            s.swap(ns);
        }else if(o=='h'){
            int r=s.size(),c=s[0].size(),T=k,B=r-T,N=max(T,B);
            G ns(N,vector<vector<int>>(c));
            int sh=N-T;
            for(int i=0;i<T&&i<r;i++){
                int ni=sh+i;
                if(ni>=0&&ni<N)for(int j=0;j<c;j++)ns[ni][j]=s[i][j];
            }
            for(int i=0;i<B;i++){
                int src=T+i;if(src<r){
                    int ni=N-1-i;
                    if(ni>=0&&ni<N)for(int j=0;j<c;j++){
                        if(!s[src][j].empty()){
                            auto v=s[src][j];
                            reverse(v.begin(),v.end());
                            ns[ni][j].insert(ns[ni][j].end(),v.begin(),v.end());
                        }
                    }
                }
            }
            s.swap(ns);
        }
    }
    int up=-1,down=-1;
    for(int i=0;i<(int)s.size();i++)
        for(int j=0;j<(int)s[0].size();j++)
            if(!s[i][j].empty()){
                down=s[i][j].front();
                up=s[i][j].back();
            }
    cout<<up<<" "<<down;
}