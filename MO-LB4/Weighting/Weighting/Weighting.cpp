#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <string>

using namespace std;

vector<double> multiplyMatrixAndWeight(vector<vector<double>>& matrix, vector<double>& weight) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    if (cols != weight.size()) {
        throw invalid_argument("Несоответствие размеров матрицы и веса");
    }

    vector<double> result(rows);

    for (int i = 0; i < rows; i++) {
        double sum = 0.0;
        for (int j = 0; j < cols; j++) {
            sum += matrix[i][j] * weight[j];
        }
        result[i] = sum;
    }

    return result;
}

vector<double> normalizeWeight(vector<double>& weight) {
    vector<double> normalize;
    double sum = 0.0;
    for (double w : weight) {
        sum += w;
    }
    for (double w : weight) {
        normalize.push_back(w / sum);
    }
    return normalize;
}

vector<double> getWeight(int columns, map<string, double>& markCriteria) {
    vector<double> weight(columns);
    for (int i = 0; i < columns; i++) {
        double a = 0;
        for (int j = 0; j < columns; j++) {
            if (i != j) {
                string key = to_string(i + 1) + to_string(j + 1);
                a += markCriteria[key];
            }
        }
        weight[i] = a;
    }
    return weight;
}

vector<vector<double>> normalizeMatrix(vector<vector<double>>& A) {
    int columns = A[0].size();
    for (int j = 0; j < columns; j++) {
        double sum = 0;
        for (int i = 0; i < A.size(); i++) {
            sum += A[i][j];
        }
        for (int i = 0; i < A.size(); i++) {
            A[i][j] /= sum;
        }
    }

    return A;
}

int findMaxIndex(vector<double>& array) {
    double max = -INFINITY;
    int maxIndex = -1;
    for (int i = 0; i < array.size(); i++) {
        if (array[i] > max) {
            max = array[i];
            maxIndex = i;
        }
    }

    return maxIndex;
}

string runCriteriaCombination(vector<vector<double>>& A,
    map<string, double>& markCriteria,
    vector<string>& alternative) {
    // Нормализуем матрицу
    vector<vector<double>> normalizeA = normalizeMatrix(A);
    cout << "Normalized matrix A:" << endl;
    for (vector<double> row : normalizeA) {
        for (double element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
    int columns = A[0].size();
    // Получаем αᵢ для всего
    vector<double> weight = getWeight(columns, markCriteria);
    cout << "Vector a: ";
    for (double element : weight) {
        cout << element << " ";
    }
    cout << endl;
    // Нормализуем этот вектор
    vector<double> normalizeW = normalizeWeight(weight);
    cout << "Normalized vector a: ";
    for (double element : normalizeW) {
        cout << element << " ";
    }
    cout << endl;

    // Перемножаем полученные нормализованные матрицы
    vector<double> multiplyResult = multiplyMatrixAndWeight(normalizeA, normalizeW);
    cout << "A x a: ";
    for (double element : multiplyResult) {
        cout << element << " ";
    }
    cout << endl;

    // Ищем максимальный индекс
    int indexMax = findMaxIndex(multiplyResult);
    cout << "Index max element: " << indexMax << endl;

    return alternative[indexMax];
}

int main() {
    // Карта для γ
    map<string, double> markCriteria;
    markCriteria["12"] = 1.0;
    markCriteria["13"] = 1.0;
    markCriteria["14"] = 1.0;
    markCriteria["21"] = 0.0;
    markCriteria["23"] = 1.0;
    markCriteria["24"] = 0.0;
    markCriteria["31"] = 0.0;
    markCriteria["32"] = 0.0;
    markCriteria["34"] = 0.0;
    markCriteria["41"] = 1.0;
    markCriteria["42"] = 1.0;
    markCriteria["43"] = 0.0;
    vector<vector<double>> A = {
        {7, 3, 2, 6},
        {8, 7, 1, 8},
        {3, 5, 6, 6},
        {5, 2, 5, 2},
    };
    vector <string> alternative = { "Tatyana", "Larisa", "Natalya", "Olga" };
    string result = runCriteriaCombination(A, markCriteria, alternative);
    cout << "Result: " << result;
    return 0;
}
