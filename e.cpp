#include <bits/stdc++.h>
#define int long long
using namespace std;

struct G{double a,b,c,d;};      // segment: (a,b)->(c,d)
struct V{double x,y;};

static constexpr double EPS=1e-9;
static constexpr double PI = 3.1415926535897932384626433832795;

inline pair<int,int> q2(double x,double y){return {(int)llround(x*100.0),(int)llround(y*100.0)};}
inline V d2(pair<int,int> p){return {p.first/100.0,p.second/100.0};}
inline long long K(pair<int,int> p){return ((long long)p.first<<32) ^ (unsigned long long)(p.second&0xffffffffu);}

inline double CR(double ax,double ay,double bx,double by){return ax*by-ay*bx;}
inline double DP(double ax,double ay,double bx,double by){return ax*bx+ay*by;}
inline double L2(double x1,double y1,double x2,double y2){x1-=x2; y1-=y2; return sqrt(x1*x1+y1*y1);}

bool interP(const G& s,const G& t,double& ix,double& iy){
    double x1=s.a,y1=s.b,x2=s.c,y2=s.d;
    double x3=t.a,y3=t.b,x4=t.c,y4=t.d;
    double dx1=x2-x1,dy1=y2-y1,dx2=x4-x3,dy2=y4-y3;
    double d=CR(dx1,dy1,dx2,dy2);
    if(fabs(d)<EPS) return false;
    double u = CR(x3-x1,y3-y1,dx1,dy1)/d;
    double v = CR(x3-x1,y3-y1,dx2,dy2)/d;
    if(u<-EPS||u>1+EPS||v<-EPS||v>1+EPS) return false;
    ix = x3 + u*dx2; iy = y3 + u*dy2; return true;
}

bool onSeg(const G& s,double x,double y){
    double dx=s.c-s.a, dy=s.d-s.b;
    if(fabs(CR(x-s.a,y-s.b,dx,dy))>1e-6) return false;
    double d1=DP(x-s.a,y-s.b,dx,dy), d2=DP(x-s.c,y-s.d,dx,dy);
    return !(d1<-1e-6 || d2>1e-6);
}

double tpar(const G& s,double x,double y){
    double dx=s.c-s.a, dy=s.d-s.b, den=dx*dx+dy*dy;
    return den<EPS?0.0:DP(x-s.a,y-s.b,dx,dy)/den;
}

double areaS(const vector<V>& p){
    int n=(int)p.size(); if(n<3) return 0.0;
    double s=0; for(int i=0;i<n;i++){int j=(i+1)%n; s += p[i].x*p[j].y - p[j].x*p[i].y;}
    return 0.5*s;
}

signed main(){
    ios::sync_with_stdio(false); cin.tie(nullptr);

    int n; if(!(cin>>n)) return 0;
    vector<G> S(n); for(int i=0;i<n;i++) cin>>S[i].a>>S[i].b>>S[i].c>>S[i].d;

    // ---- collect vertices (2-decimal grid) ----
    unordered_set<long long> seen;
    vector<pair<int,int>> P2;
    auto addV=[&](double x,double y){auto r=q2(x,y); long long k=K(r); if(!seen.count(k)){seen.insert(k); P2.push_back(r);}};

    for(auto& s:S){ addV(s.a,s.b); addV(s.c,s.d); }
    for(int i=0;i<n;i++) for(int j=i+1;j<n;j++){
        double ix,iy;
        if(interP(S[i],S[j],ix,iy)) addV(ix,iy);
        else{
            // collinear overlap endpoints
            double dx1=S[i].c-S[i].a, dy1=S[i].d-S[i].b;
            double dx2=S[j].c-S[j].a, dy2=S[j].d-S[j].b;
            if(fabs(CR(dx1,dy1,dx2,dy2))<1e-9 && fabs(CR(S[j].a-S[i].a,S[j].b-S[i].b,dx1,dy1))<1e-9){
                double t1=tpar(S[i],S[j].a,S[j].b), t2=tpar(S[i],S[j].c,S[j].d);
                double lo=max(0.0,min(t1,t2)), hi=min(1.0,max(t1,t2));
                if(hi+1e-9>=lo){ addV(S[i].a+lo*dx1,S[i].b+lo*dy1); addV(S[i].a+hi*dx1,S[i].b+hi*dy1); }
            }
        }
    }

    unordered_map<long long,int> id; vector<V> P; P.reserve(P2.size());
    for(auto& r:P2){ long long k=K(r); if(!id.count(k)){ id[k]=(int)P.size(); P.push_back(d2(r)); } }
    int Vn=(int)P.size(); if(!Vn){ cout<<"Abandoned"; return 0; }

    vector<unordered_set<int>> Eset(Vn);
    for(auto& s:S){
        vector<pair<double,int>> lst;
        for(int v=0; v<Vn; ++v) if(onSeg(s,P[v].x,P[v].y)) lst.push_back({tpar(s,P[v].x,P[v].y), v});
        sort(lst.begin(),lst.end(),[](auto&a,auto&b){ return a.first<b.first || (fabs(a.first-b.first)<1e-9 && a.second<b.second); });
        for(int k=1;k<(int)lst.size();++k){ int u=lst[k-1].second, v=lst[k].second; if(u!=v){ Eset[u].insert(v); Eset[v].insert(u); } }
    }

    vector<vector<int>> Nbr(Vn);
    int Ecnt=0; for(int u=0;u<Vn;++u){ for(int v:Eset[u]) Nbr[u].push_back(v); Ecnt += (int)Nbr[u].size(); }
    if((Ecnt/2)==0){ cout<<"Abandoned"; return 0; }

    for(int u=0;u<Vn;++u)
        sort(Nbr[u].begin(),Nbr[u].end(),[&](int a,int b){
            double A=atan2(P[a].y-P[u].y,P[a].x-P[u].x), B=atan2(P[b].y-P[u].y,P[b].x-P[u].x);
            if(fabs(A-B)<1e-12) return a<b; return A<B;
        });
/*fthcggggggwq hcqlcqhq	xh hh	zzzzg ghwx	wf*/
    unordered_set<long long> used;
    auto DKey=[&](int a,int b){ return ((long long)a<<32) ^ (unsigned long long)(b&0xffffffffu); };

    vector<vector<int>> Faces; Faces.reserve(256);
    unordered_set<string> Fseen;

    auto canon=[&](const vector<pair<int,int>>& seq)->string{
        int m=(int)seq.size(); string best;
        for(int r=0;r<m;r++){
            string t; t.reserve(m*16);
            for(int i=0;i<m;i++){ auto p=seq[(r+i)%m]; t+=to_string(p.first)+","+to_string(p.second)+";"; }
            if(best.empty()||t<best) best=t;
        }
        return best;
    };

    for(int u=0;u<Vn;++u) for(int v: Nbr[u]){
        long long dk=DKey(u,v); if(used.count(dk)) continue;
        int cu=u, cv=v; vector<int> cyc; bool bad=false;
        while(true){
            used.insert(DKey(cu,cv)); cyc.push_back(cu);
            auto& L = Nbr[cv]; int pos=-1, d=L.size();
            for(int i=0;i<d;i++) if(L[i]==cu){ pos=i; break; }
            if(pos<0){ bad=true; break; }
            int nxt=L[(pos-1+d)%d]; int nu=cv, nv=nxt; cu=nu; cv=nv;
            if(cu==u && cv==v) break;
            if((int)cyc.size() > Vn*12){ bad=true; break; }
        }
        if(bad || (int)cyc.size()<3) continue;

        vector<V> poly; poly.reserve(cyc.size());
        for(int i:cyc) poly.push_back(P[i]);
        double a=areaS(poly); if(fabs(a)<1e-8) continue;
        if(a<0){ reverse(cyc.begin(),cyc.end()); reverse(poly.begin(),poly.end()); a=-a; }
        if(a<1e-9) continue;

        vector<pair<int,int>> seq; seq.reserve(poly.size());
        for(auto& z:poly) seq.push_back(q2(z.x,z.y));
        auto rev=seq; reverse(rev.begin(),rev.end());
        string sig = min(canon(seq), canon(rev));
        if(!Fseen.count(sig)){ Fseen.insert(sig); Faces.push_back(cyc); }
    }

    if(Faces.empty()){ cout<<"Abandoned"; return 0; }

    // areas of all faces
    int m=(int)Faces.size(); vector<double> FA(m,0.0);
    for(int i=0;i<m;i++){ vector<V> poly; for(int id:Faces[i]) poly.push_back(P[id]); FA[i]=fabs(areaS(poly)); }

    // drop the outer (largest) face
    int outer=-1; double mx=-1;
    for(int i=0;i<m;i++) if(FA[i]>mx){ mx=FA[i]; outer=i; }

    int pick=-1; double best=-1;
    for(int i=0;i<m;i++) if(i!=outer && FA[i]>best){ best=FA[i]; pick=i; }

    if(pick<0 || best<=1e-9){ cout<<"Abandoned"; return 0; }

    // perimeter used by chosen face
    vector<V> C; for(int id:Faces[pick]) C.push_back(P[id]);
    double per=0.0; for(int i=0;i<(int)C.size();i++){ int j=(i+1)%C.size(); per += L2(C[i].x,C[i].y,C[j].x,C[j].y); }

    // total original length
    double tot=0.0; for(auto& s:S) tot += L2(s.a,s.b,s.c,s.d);
    double left = max(0.0, tot - per);

    double kalyan = best;
    double comp   = (left>1e-12)? (left*left)/(4.0*PI) : 0.0;

    cout << (kalyan > comp + 1e-9 ? "Kalyan" : "Computer");
}