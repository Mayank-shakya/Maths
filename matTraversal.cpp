#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class MatrixTraversals {
public:
    // 1. BASIC MATRIX TRAVERSALS
    static void rowWiseTraversal(const vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        cout << "Row-wise traversal:" << endl;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    static void columnWiseTraversal(const vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        cout << "Column-wise traversal:" << endl;
        for(int j = 0; j < m; j++) {
            for(int i = 0; i < n; i++) {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    static void spiralTraversal(const vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        int top = 0, bottom = n-1, left = 0, right = m-1;
        cout << "Spiral traversal: ";
        
        while(top <= bottom && left <= right) {
            // Top row (left to right)
            for(int j = left; j <= right; j++) 
                cout << mat[top][j] << " ";
            top++;
            
            // Right column (top to bottom)
            for(int i = top; i <= bottom; i++) 
                cout << mat[i][right] << " ";
            right--;
            
            // Bottom row (right to left)
            if(top <= bottom) {
                for(int j = right; j >= left; j--) 
                    cout << mat[bottom][j] << " ";
                bottom--;
            }
            
            // Left column (bottom to top)
            if(left <= right) {
                for(int i = bottom; i >= top; i--) 
                    cout << mat[i][left] << " ";
                left++;
            }
        }
        cout << endl;
    }
    
    static void diagonalTraversal(const vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        cout << "Main diagonals traversal:" << endl;
        
        // Top-left to bottom-right diagonals
        for(int d = 0; d < n + m - 1; d++) {
            cout << "Diagonal " << d << ": ";
            for(int i = 0; i < n; i++) {
                int j = d - i;
                if(j >= 0 && j < m) 
                    cout << mat[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    // 2. FIXED SIZE SUBMATRIX TRAVERSALS
    static void traverseAllSubmatrices(const vector<vector<int>>& mat, int n1, int m1) {
        int n = mat.size(), m = mat[0].size();
        cout << "All " << n1 << "x" << m1 << " submatrices:" << endl;
        
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                // Check bounds using i+n1-1 and j+m1-1
                if(i + n1 - 1 >= n || j + m1 - 1 >= m) 
                    continue;
                
                cout << "Submatrix at (" << i << "," << j << "):" << endl;
                for(int x = i; x <= i + n1 - 1; x++) {
                    for(int y = j; y <= j + m1 - 1; y++) {
                        cout << mat[x][y] << " ";
                    }
                    cout << endl;
                }
                cout << "---" << endl;
            }
        }
    }
    
    static void traverseAllSquareSubmatrices(const vector<vector<int>>& mat, int k) {
        int n = mat.size(), m = mat[0].size();
        cout << "All " << k << "x" << k << " square submatrices:" << endl;
        
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                // Check bounds using i+k-1 and j+k-1
                if(i + k - 1 >= n || j + k - 1 >= m) 
                    continue;
                
                cout << "Square at (" << i << "," << j << "):" << endl;
                for(int x = i; x <= i + k - 1; x++) {
                    for(int y = j; y <= j + k - 1; y++) {
                        cout << mat[x][y] << " ";
                    }
                    cout << endl;
                }
                cout << "---" << endl;
            }
        }
    }
    
    // 3. BOUNDARY TRAVERSALS
    static void traverseSubmatrixBoundary(const vector<vector<int>>& mat, int i, int j, int n1, int m1) {
        int n = mat.size(), m = mat[0].size();
        
        // Check if submatrix fits
        if(i + n1 - 1 >= n || j + m1 - 1 >= m) {
            cout << "Submatrix doesn't fit!" << endl;
            return;
        }
        
        cout << "Boundary of submatrix at (" << i << "," << j << "): ";
        
        // Top row (left to right)
        for(int y = j; y <= j + m1 - 1; y++) 
            cout << mat[i][y] << " ";
        
        // Right column (excluding corners)
        for(int x = i + 1; x <= i + n1 - 2; x++) 
            cout << mat[x][j + m1 - 1] << " ";
        
        // Bottom row (right to left, if height > 1)
        if(n1 > 1) {
            for(int y = j + m1 - 1; y >= j; y--) 
                cout << mat[i + n1 - 1][y] << " ";
        }
        
        // Left column (excluding corners, if width > 1)
        if(m1 > 1) {
            for(int x = i + n1 - 2; x > i; x--) 
                cout << mat[x][j] << " ";
        }
        cout << endl;
    }
    
    // 4. EFFICIENT SUM CALCULATIONS USING PREFIX SUM
    static vector<vector<int>> buildPrefixSum(const vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        vector<vector<int>> pf(n + 1, vector<int>(m + 1, 0));
        
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= m; j++) {
                pf[i][j] = mat[i-1][j-1] + pf[i-1][j] + pf[i][j-1] - pf[i-1][j-1];
            }
        }
        return pf;
    }
    
    static int getSubmatrixSum(const vector<vector<int>>& pf, int r1, int c1, int r2, int c2) {
        // Using prefix sum array to get sum of submatrix [r1,c1] to [r2,c2]
        return pf[r2+1][c2+1] - pf[r1][c2+1] - pf[r2+1][c1] + pf[r1][c1];
    }
    
    static void efficientSubmatrixSums(const vector<vector<int>>& mat, int n1, int m1) {
        auto pf = buildPrefixSum(mat);
        int n = mat.size(), m = mat[0].size();
        
        cout << "Efficient submatrix sums (" << n1 << "x" << m1 << "):" << endl;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(i + n1 - 1 >= n || j + m1 - 1 >= m) 
                    continue;
                
                int sum = getSubmatrixSum(pf, i, j, i + n1 - 1, j + m1 - 1);
                cout << "Sum at (" << i << "," << j << "): " << sum << endl;
            }
        }
    }
    
    // 5. ZIG-ZAG AND SPECIAL TRAVERSALS
    static void zigzagTraversal(const vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        cout << "Zigzag traversal: ";
        
        for(int i = 0; i < n; i++) {
            if(i % 2 == 0) {
                // Left to right
                for(int j = 0; j < m; j++) 
                    cout << mat[i][j] << " ";
            } else {
                // Right to left
                for(int j = m - 1; j >= 0; j--) 
                    cout << mat[i][j] << " ";
            }
        }
        cout << endl;
    }
    
    static void waveTraversal(const vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        cout << "Wave traversal: ";
        
        for(int j = 0; j < m; j++) {
            if(j % 2 == 0) {
                // Top to bottom
                for(int i = 0; i < n; i++) 
                    cout << mat[i][j] << " ";
            } else {
                // Bottom to top
                for(int i = n - 1; i >= 0; i--) 
                    cout << mat[i][j] << " ";
            }
        }
        cout << endl;
    }
};

// Demo function to show all traversals
void demonstrateAllTraversals() {
    vector<vector<int>> matrix = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    
    cout << "=== MATRIX TRAVERSALS DEMO ===" << endl;
    cout << "Matrix:" << endl;
    for(auto& row : matrix) {
        for(int val : row) cout << val << " ";
        cout << endl;
    }
    cout << endl;
    
    // Basic traversals
    MatrixTraversals::rowWiseTraversal(matrix);
    cout << endl;
    
    MatrixTraversals::columnWiseTraversal(matrix);
    cout << endl;
    
    MatrixTraversals::spiralTraversal(matrix);
    cout << endl;
    
    MatrixTraversals::diagonalTraversal(matrix);
    cout << endl;
    
    MatrixTraversals::zigzagTraversal(matrix);
    cout << endl;
    
    MatrixTraversals::waveTraversal(matrix);
    cout << endl;
    
    // Submatrix traversals
    MatrixTraversals::traverseAllSubmatrices(matrix, 2, 3);
    cout << endl;
    
    MatrixTraversals::traverseAllSquareSubmatrices(matrix, 2);
    cout << endl;
    
    // Boundary traversal
    MatrixTraversals::traverseSubmatrixBoundary(matrix, 1, 1, 2, 2);
    cout << endl;
    
    // Efficient sum calculation
    MatrixTraversals::efficientSubmatrixSums(matrix, 2, 2);
}

int main() {
    demonstrateAllTraversals();
    return 0;
}