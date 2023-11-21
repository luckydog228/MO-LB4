#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <limits>
using namespace std;

vector<double> multiplyMatrixAndVector(vector<vector<double>> matrix, vector<double> vec) {
    int numColsA = matrix[0].size();
    int numRowsB = vec.size();
    if (numColsA != numRowsB) {
        throw std::invalid_argument("Mismatch in matrix and vector sizes");
    }

    std::vector<double> result(matrix.size());

    for (int i = 0; i < matrix.size(); i++) {
        double sum = 0.0;
        for (int j = 0; j < numColsA; j++) {
            sum += matrix[i][j] * vec[j];
        }
        result[i] = sum;
    }

    return result;
}




int findMaxIndex(vector<double> vec) {
    double max = numeric_limits<int>::lowest();
    int maxIndex = -1;
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] > max) {
            max = vec[i];
            maxIndex = i;
        }
    }

    return maxIndex;
}

vector<vector<double>> getMatrix(vector<vector<double>> A,
    vector<vector<double>> B,
    vector<vector<double>> C,
    vector<vector<double>> D) {
    vector<vector<double>> res(A.size(), vector<double>(4));
    for (int i = 0; i < A.size(); i++) {
        res[i][0] = A[i][A[i].size() - 1];
        res[i][1] = B[i][B[i].size() - 1];
        res[i][2] = C[i][C[i].size() - 1];
        res[i][3] = D[i][D[i].size() - 1];
    }

    return res;
}

double sumColumn(vector<vector<double>> matrix, int columnIndex) {
    double sum = 0;
    for (auto row : matrix) {
        sum += row[columnIndex];
    }
    return sum;
}

vector<vector<double>> getPoln(vector<vector<double>> matrix) {
    vector<vector<double>> res;
    for (auto row : matrix) {
        double sum = 0;
        vector<double> resLine;
        for (auto value : row) {
            resLine.push_back(value);
            sum += value;
        }
        resLine.push_back(sum);
        res.push_back(resLine);
    }

    for (auto& row : res) {
        double normalizedSum = row[row.size() - 1] / sumColumn(res, row.size() - 1);
        row.push_back(normalizedSum);
    }

    return res;
}



string runAnalyticHierarchyProcess(vector<string> alternative,
    vector<vector<double>> A,
    vector<vector<double>> B,
    vector<vector<double>> C,
    vector<vector<double>> D,
    vector<vector<double>> critery) {
    vector<vector<double>> Apoln = getPoln(A);
    vector<vector<double>> Bpoln = getPoln(B);
    vector<vector<double>> Cpoln = getPoln(C);
    vector<vector<double>> Dpoln = getPoln(D);
    vector<vector<double>> critPoln = getPoln(critery);

    cout << "New matrix A:" << endl;
    for (auto item : Apoln) {
        for (auto value : item) {
            cout << setw(10) << value << " ";
        }
        cout << endl;
    }

    cout << "New matrix B:" << endl;
    for (auto item : Bpoln) {
        for (auto value : item) {
            cout << setw(10) << value << " ";
        }
        cout << endl;
    }

    cout << "New matrix C:" << endl;
    for (auto item : Cpoln) {
        for (auto value : item) {
            cout << setw(10) << value << " ";
        }
        cout << endl;
    }

    cout << "New matrix D:" << endl;
    for (auto item : Dpoln) {
        for (auto value : item) {
            cout << setw(10) << value << " ";
        }
        cout << endl;
    }

    cout << "New matrix criteria:" << endl;
    for (auto item : critPoln) {
        for (auto value : item) {
            cout << setw(10) << value << " ";
        }
        cout << endl;
    }

    cout << "Matrix normalized sum:" << endl;
    vector<vector<double>> matrix = getMatrix(Apoln, Bpoln, Cpoln, Dpoln);
    for (auto item : matrix) {
        for (auto value : item) {
            cout << setw(10) << value << " ";
        }
        cout << endl;
    }

    cout << "Matrix normalized sum criteria:" << endl;
    vector<double> critMatrix;
    for (auto item : critPoln) {
        critMatrix.push_back(item[item.size() - 1]);
    }
    for (auto value : critMatrix) {
        cout << setw(10) << value << " ";
    }
    cout << endl;

    vector<double> resultVector = multiplyMatrixAndVector(matrix, critMatrix);
    cout << "Result matrix:" << endl;
    for (auto value : resultVector) {
        cout << setw(10) << value << " ";
    }
    cout << endl;

    int maxIndex = findMaxIndex(resultVector);
    return alternative[maxIndex];
}

int main() {
    vector<vector<double>> A = {
        {1, 0.333, 7, 5},
        {3, 1, 9, 7},
        {0.143, 0.111, 1, 0.333},
        {0.2, 0.143, 3, 1},
    };
    vector<vector<double>> B = {
        {1, 0.2, 0.333, 3},
        {5, 1, 3, 7},
        {3, 0.333, 1, 5},
        {0.333, 0.143, 0.2, 1},
    };
    vector<vector<double>> C = {
        {1, 3, 0.143, 0.111},
        {0.333, 1, 0.143, 0.2},
        {9, 7, 1, 0.2},
        {7, 5, 5, 1},
    };
    vector<vector<double>> D = {
        {1, 0.2, 0.333, 0.2},
        {5, 1, 3, 7},
        {3, 0.333, 1, 5},
        {5, 0.143, 0.2, 1},
    };
    vector<vector<double>> critery = {
        {1, 5, 7, 3},
        {0.2, 1, 3, 0.333},
        {0.143, 0.333, 1, 0.2},
        {0.333, 3, 5, 1},
    };
    vector <string> alternative = { "Tatyana", "Larisa", "Natalya", "Olga" };
    string result = runAnalyticHierarchyProcess(alternative, A, B, C, D, critery);
    cout << "Result: " << result;
    return 0;
}
