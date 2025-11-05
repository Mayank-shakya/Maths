#include <bits/stdc++.h>
using namespace std;
struct Q{int r,c,d;};
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int R,C;
    if(!(cin>>R>>C)) return 0;
    vector<string> A(R);
    for(int i=0;i<R;++i){
        cin>>A[i];
        if((int)A[i].size()!=C){
            string rest; getline(cin, rest);
            string m=A[i]+rest, t;
            for(char ch: m) if(!isspace((unsigned char)ch)) t.push_back(ch);
            if((int)t.size()<C){ cout<<"Impossible\n"; return 0; }
            A[i]=t.substr(0,C);
        }
    }
    vector<pair<int,int>> s, g;
    for(int r=0;r<R;++r) for(int c=0;c<C;++c){
        if(A[r][c]=='l') s.emplace_back(r,c);   // source uses lowercase 'l'
        if(A[r][c]=='L') g.emplace_back(r,c);   // target uses uppercase 'L'
    }
    if(s.empty()||g.empty()){ cout<<"Impossible\n"; return 0; }
    int k = (int)s.size();
    auto center = [&](const vector<pair<int,int>>&v){
        int rmin=INT_MAX,rmax=INT_MIN,cmin=INT_MAX,cmax=INT_MIN;
        for(auto &p: v){ rmin=min(rmin,p.first); rmax=max(rmax,p.first);
                         cmin=min(cmin,p.second); cmax=max(cmax,p.second); }
        return tuple<int,int,int>(rmin+rmax, cmin+cmax, (rmin==rmax?0:1));
    };
    int sr2,sc2,sd,tr2,tc2,td;
    tie(sr2,sc2,sd)=center(s);
    tie(tr2,tc2,td)=center(g);
    int MR = 2*(R-1), MC = 2*(C-1);
    auto inside = [&](int r2,int c2){ return r2>=0 && r2<=MR && c2>=0 && c2<=MC; };
    auto cells = [&](int r2,int c2,int dir){
        vector<pair<int,int>> out;
        for(int t=0;t<k;++t){
            int off = 2*t - (k-1);
            if(dir==0) out.emplace_back(r2/2, (c2+off)/2);
            else out.emplace_back((r2+off)/2, c2/2);
        }
        return out;
    };
    auto placeOK = [&](int r2,int c2,int dir)->bool{
        if(!inside(r2,c2)) return false;
        auto v = cells(r2,c2,dir);
        for(auto &p: v){
            int rr=p.first, cc=p.second;
            if(rr<0||rr>=R||cc<0||cc>=C) return false;
            if(A[rr][cc]=='B') return false;
        }
        return true;
    };
    auto canRotTo = [&](int cr2,int cc2,int cd,int nr2,int nc2,int nd)->bool{
        if(nd==cd) return false;
        if(!placeOK(nr2,nc2,nd)) return false;
        auto a = cells(cr2,cc2,cd);
        auto b = cells(nr2,nc2,nd);
        int rmin=INT_MAX,rmax=INT_MIN,cmin=INT_MAX,cmax=INT_MIN;
        for(auto&p:a){ rmin=min(rmin,p.first); rmax=max(rmax,p.first); cmin=min(cmin,p.second); cmax=max(cmax,p.second); }
        for(auto&p:b){ rmin=min(rmin,p.first); rmax=max(rmax,p.first); cmin=min(cmin,p.second); cmax=max(cmax,p.second); }
        if(rmax-rmin+1!=k || cmax-cmin+1!=k) return false;
        for(int rr=rmin; rr<=rmax; ++rr) for(int cc=cmin; cc<=cmax; ++cc){
            if(rr<0||rr>=R||cc<0||cc>=C) return false;
            if(A[rr][cc]=='B') return false;
        }
        return true;
    };
    if(!placeOK(sr2,sc2,sd) || !placeOK(tr2,tc2,td)){ cout<<"Impossible\n"; return 0; }
    vector<vector<array<int,2>>> dist(MR+1, vector<array<int,2>>(MC+1, {-1,-1}));
    deque<Q> dq;
    dist[sr2][sc2][sd]=0;
    dq.push_back({sr2,sc2,sd});
    int dR[4]={-2,2,0,0}, dC[4]={0,0,-2,2};
    int ans=-1;
    while(!dq.empty()){
        Q cur = dq.front(); dq.pop_front();
        int cd = dist[cur.r][cur.c][cur.d];
        if(cur.r==tr2 && cur.c==tc2 && cur.d==td){ ans=cd; break; }
        for(int m=0;m<4;++m){
            int nr=cur.r + dR[m], nc=cur.c + dC[m], nd=cur.d;
            if(nr<0||nr>MR||nc<0||nc>MC) continue;
            if(dist[nr][nc][nd]!=-1) continue;
            if(!placeOK(nr,nc,nd)) continue;
            dist[nr][nc][nd]=cd+1;
            dq.push_back({nr,nc,nd});
        }
        // try rotations: test candidate centers (grid small so brute-force is fine)
        for(int nr=0; nr<=MR; ++nr){
            for(int nc=0; nc<=MC; ++nc){
                int nd = 1 - cur.d;
                if(dist[nr][nc][nd]!=-1) continue;
                if(canRotTo(cur.r,cur.c,cur.d,nr,nc,nd)){
                    dist[nr][nc][nd] = cd+1;
                    dq.push_back({nr,nc,nd});
                }
            }
        }
    }
    if(ans==-1) cout<<"Impossible\n"; else cout<<ans<<"\n";
    return 0;
}