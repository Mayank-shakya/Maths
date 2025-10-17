#include <vector>
using namespace std;

// Convert matrix to prefix sum in single 2D loop
void buildPrefixSum(vector<vector<int>>& mat) {
    int n = mat.size(), m = mat[0].size();
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(i > 0) mat[i][j] += mat[i-1][j];
            if(j > 0) mat[i][j] += mat[i][j-1];
            if(i > 0 && j > 0) mat[i][j] -= mat[i-1][j-1];
        }
    }
}

// Get sum of submatrix [r1,c1] to [r2,c2]
int getSubmatrixSum(vector<vector<int>>& pf, int r1, int c1, int r2, int c2) {
    int sum = pf[r2][c2];
    if(r1 > 0) sum -= pf[r1-1][c2];
    if(c1 > 0) sum -= pf[r2][c1-1];
    if(r1 > 0 && c1 > 0) sum += pf[r1-1][c1-1];
    return sum;
}