#include<iostream>
#include <vector>
#include <climits>
#include <limits>

std::vector<std::vector<int>> tropicalMultiply(const std::vector<std::vector<int>> &A, const std::vector<std::vector<int>> &B) {
    size_t n = A.size();
    std::vector<std::vector<int>> result(n, std::vector<int>(n, INT_MAX)); 

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            for (size_t k = 0; k < n; ++k) {
                if (A[i][k] != INT_MAX && B[k][j] != INT_MAX) {
                    result[i][j] = std::min(result[i][j], A[i][k] + B[k][j]);
                }
            }
        }
    }

    return result;
}

std::vector<std::vector<int>> exponentation(std::vector<std::vector<int>> &A, int n) {
    std::vector<std::vector<int>> An (n, std::vector<int>(n));
    An = A;
    for (int i = 0; i < n - 2; ++i) {
        An = tropicalMultiply(An, A);
    }
    return An;
}

void dfs(size_t v, size_t t, std::vector<bool> visited, std::vector<std::vector<int>> B, std::vector<std::vector<int>> bloc) {
    if(v == t) {
        return;
    }
    visited[v] = true;
    for (int i = 0; i < B.size(); i++) {
        if(bloc[v][i] != 1 && B[v][i] != 0 && B[v][i] != INT_MAX && !visited[i]) {
            dfs(i, t, visited, B, bloc);
        }
        if(bloc[v][i] == 1) {
            B[v][i] = INT_MAX;
        }
    }
}

double calculateCompetitiveRatio(std::vector<std::vector<int>> matrix, std::vector<std::vector<int>> B, size_t s, size_t t) {
    if (matrix[s-1][t-1] == INT_MAX || B[s-1][t-1] == INT_MAX) return std::numeric_limits<double>::infinity();
    return static_cast<double>(B[s-1][t-1]) / matrix[s-1][t-1];
}
int main() {
    size_t n, s, t;
    std::cout<<"Ввод:" <<std::endl;
    std::cin >> n;
    std::cin >> s >> t;
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));
    std::vector<std::vector<int>> bloc(n, std::vector<int>(n,0));
    std::vector<std::vector<int>> B (n, std::vector<int>(n));
    std::vector<bool> visited(n, false);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> matrix[i][j];
            if (matrix[i][j] == 0 && i != j) {
                matrix[i][j] = INT_MAX;
            }
        }
    }
    B = matrix;
    matrix = exponentation(matrix, n);
    //можно брать любой другой набор препятствий 
    bloc[1][2] = 1;
    dfs(s-1, t-1, visited, B, bloc);
    B = exponentation(B, n);

    std::cout << "Вывод:" << std::endl;
    double ratio = calculateCompetitiveRatio(matrix, B,s, t);
    std::cout << "Competitive Ratio is "  << ratio << std::endl;
    return 0;
}
