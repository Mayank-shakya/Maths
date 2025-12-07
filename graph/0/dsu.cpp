

struct UnionFind{
         vector<int> par,rank;
         int set_size; // #ofcc
         UnionFind(int n){ // initialization
            par.resize(n+1);
            rank.assign(n+1,1);
            set_size=n;
            for(int i=1; i<=n; i++)par[i]=i,rank[i]=1;
         }
         int find(int x){
               if(par[x]==x)return x;
               else return par[x]=find(par[x]);
         }
         void merge(int x, int y){
              x=find(x);
              y=find(y);
              if(x==y)return;
              if(rank[x]<rank[y]){
                   rank[y]+=rank[x];
                   par[x]=y;
              }
              else{
                rank[x]+=rank[y];
                par[y]=x;
              }
              set_size--;
         }
         void reset(int n){
            for(int i=1; i<=n; i++)par[i]=i;
            rank.assign(n+1,1);
            set_size=n;
         }


};
