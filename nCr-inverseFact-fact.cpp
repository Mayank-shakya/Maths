int fact[1000100];
int invfact[1000100];
void pre(){
    fact[0]=1;
    for(int i=1;i<=1000000;i++)
        fact[i] = 1LL*i*fact[i-1]%MOD;
    invfact[1000000] = inv(fact[1000000],MOD);
    for(int i=1000000-1;i>=0;i--){
        invfact[i] = 1LL*invfact[i+1]*(i+1)%MOD;
    }
}

int ncr(int n,int r){
    if(r<0||r>n) return 0;
    int ans = fact[n];
    ans = 1LL*ans*invfact[n-r]%MOD;
    ans = 1LL*ans*invfact[r]%MOD;
    return ans;
}
