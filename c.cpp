#include <bits/stdc++.h>
using namespace std;
static inline string trim(string s){
    size_t i=0,j=s.size(); while(i<j && isspace((unsigned char)s[i])) ++i;
    while(j>i && isspace((unsigned char)s[j-1])) --j; return s.substr(i,j-i);
}
static inline bool isNum(const string& t){
    if(t.empty()) return false; size_t i=0; if(t[0]=='-'||t[0]=='+') i=1;
    if(i>=t.size()) return false; for(;i<t.size();++i) if(!isdigit((unsigned char)t[i])) return false;
    return true;
}
struct Node{ virtual ~Node(){};};
struct NPrint:Node{ string tok; NPrint(string t):tok(move(t)){} };
struct NFor:Node{ string v, lo, hi; vector<Node*> body; NFor(string V,string L,string H):v(move(V)),lo(move(L)),hi(move(H)){} };
struct NIf:Node{
    string L,op,R; vector<Node*> yes,no;
    NIf(string l,string o,string r):L(move(l)),op(move(o)),R(move(r)){}
};
int64_t getVal(const string& t, unordered_map<string,long long>& mem){
    if(isNum(t)) return stoll(t);
    auto it=mem.find(t); return (it==mem.end()?0:it->second);
}
bool evalCond(const string& L,const string& op,const string& R, unordered_map<string,long long>& mem){
    long long a=getVal(L,mem), b=getVal(R,mem);
    if(op=="==") return a==b;
    if(op=="!=") return a!=b;
    if(op=="<")  return a<b;
    if(op==">")  return a>b;
    return false;
}
void runBody(const vector<Node*>& B, unordered_map<string,long long>& mem, vector<long long>& out);
void run(Node* p, unordered_map<string,long long>& mem, vector<long long>& out){
    if(auto q=dynamic_cast<NPrint*>(p)){
        out.push_back(getVal(q->tok,mem));
    }else if(auto q=dynamic_cast<NFor*>(p)){
        long long L=getVal(q->lo,mem), H=getVal(q->hi,mem);
        long long step = (L<=H? 1 : -1);
        for(long long i=L; (step==1? i<=H : i>=H); i+=step){
            mem[q->v]=i;
            runBody(q->body,mem,out);
        }
    }else if(auto q=dynamic_cast<NIf*>(p)){
        if(evalCond(q->L,q->op,q->R,mem)) runBody(q->yes,mem,out);
        else runBody(q->no,mem,out);
    }
}

void runBody(const vector<Node*>& B, unordered_map<string,long long>& mem, vector<long long>& out){
    for(Node* n: B) run(n,mem,out);
}




int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    
    vector<string> raw; string line;
    while (getline(cin,line)) raw.push_back(line);

   
    while(!raw.empty() && trim(raw.back()).empty()) raw.pop_back();
    if(raw.size()<3) return 0;

    string varsLine = trim(raw[raw.size()-2]);
    string valsLine = trim(raw[raw.size()-1]);
    vector<string> prog(raw.begin(), raw.end()-2);

    unordered_map<string,long long> mem;
    {
        vector<string> V; string t; stringstream ss(varsLine);
        while(ss>>t) V.push_back(t);
        vector<long long> X; long long z; stringstream tt(valsLine);
        while(tt>>z) X.push_back(z);
        for(size_t i=0;i<V.size()&&i<X.size();++i) mem[V[i]]=X[i];
    }
    vector<unique_ptr<Node>> store;
    auto mk = [&](auto* p)->Node*{ store.emplace_back(p); return p; };

    vector<Node*> root;
    struct B{ enum Type{FORB,IFB_THEN,IFB_ELSE} tp; Node* ptr; };
    vector<vector<Node*>*> bodyStk; bodyStk.push_back(&root);
    vector<B> blk;             
    vector<NIf*> ifWaiting;    

    for(size_t i=0;i<prog.size();++i){
        string s=trim(prog[i]);
        if(s.empty()) continue;

        if(s.rfind("for ",0)==0){
            string tok; stringstream ss(s);
            ss>>tok; string v,lo,hi; ss>>v>>lo>>hi;
            auto* nd = static_cast<NFor*>(mk(new NFor(v,lo,hi)));
            (*bodyStk.back()).push_back(nd);
            blk.push_back({B::FORB,nd});
            bodyStk.push_back(&nd->body);
        }
        else if(s.rfind("if ",0)==0){
            string cond = trim(s.substr(3));
            string op; size_t pos=string::npos;
            if((pos=cond.find("=="))!=string::npos) op="==";
            else if((pos=cond.find("!="))!=string::npos) op="!=";
            else if((pos=cond.find('<'))!=string::npos)  op="<";
            else if((pos=cond.find('>'))!=string::npos)  op=">";
            string L=trim(cond.substr(0,pos));
            string R=trim(cond.substr(pos+op.size()));
            auto* nd = static_cast<NIf*>(mk(new NIf(L,op,R)));
            (*bodyStk.back()).push_back(nd);
            ifWaiting.push_back(nd); 
        }
        else if(s=="Yes"){
            if(ifWaiting.empty()){  }
            else{
                NIf* nd = ifWaiting.back();
                blk.push_back({B::IFB_THEN,nd});
                bodyStk.push_back(&nd->yes);
            }
        }
        else if(s=="No"){
            if(ifWaiting.empty()){ }
            else{
                if(!blk.empty() && blk.back().tp==B::IFB_THEN){
                    blk.pop_back();
                    bodyStk.pop_back();
                }
                NIf* nd = ifWaiting.back();
                blk.push_back({B::IFB_ELSE,nd});
                bodyStk.push_back(&nd->no);
            }
        }
        else if(s=="end"){
            if(!blk.empty()){
                if(blk.back().tp==B::FORB){
                    blk.pop_back(); bodyStk.pop_back();
                }else if(blk.back().tp==B::IFB_THEN){
                    blk.pop_back(); bodyStk.pop_back(); if(!ifWaiting.empty()) ifWaiting.pop_back();
                }else{ 
                    blk.pop_back(); bodyStk.pop_back(); if(!ifWaiting.empty()) ifWaiting.pop_back();
                }
            } 
        }
        else if(s.rfind("print",0)==0){
            string arg = trim(s.substr(5)); 
            if(!arg.empty() && arg[0]==' ') arg=trim(arg);
            (*bodyStk.back()).push_back(mk(new NPrint(arg)));
        }
       else{}
    }

    vector<long long> out; out.reserve(256);
    runBody(root,mem,out);

    for(size_t i=0;i<out.size();++i){
        if(i) cout << "\n";
        cout << out[i];
    }
    return 0;
}