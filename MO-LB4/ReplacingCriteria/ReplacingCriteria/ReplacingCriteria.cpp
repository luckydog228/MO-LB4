#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <limits>

using namespace std;

vector<double> normalizeWeigths(vector<double> weigths) { //Функция для нормализации весов критериев
    double suma = 0.0;
    for (double weight : weigths) {
        suma += weight;
    }

    vector<double> normalizedWeights(weigths.size());

    for (int i = 0; i < weigths.size(); i++) {
        normalizedWeights[i] = weigths[i] / suma;
    }

    return normalizedWeights;
}

double Min(vector<vector<double>>& A, int j) { //Функция для нахождения минимального значения столбца
    double min = numeric_limits<double>::max();
    for (vector<double>& doubles : A) {
        if (doubles[j] < min) {
            min = doubles[j];
        }
    }
    return min;
}

double Max(vector<vector<double>>& A, int j) {  //Функция для нахождения максимального значения столбца
    double max = numeric_limits<double>::lowest();
    for (vector<double>& doubles : A) {
        if (doubles[j] > max) {
            max = doubles[j];
        }
    }
    return max;
}


string startReplacingCriteria(vector<vector<double>>& A, vector<double>& weigth, vector<double>& minimalValue, vector<string>& alternative) { //функция для метода замены критериев ограничениями
    vector<double> normalWeigth = normalizeWeigths(weigth);  //нормализуем веса критериев
    cout << "Normalized weights: ";
    for (double value : normalWeigth) {
        cout << value << " ";
    }
    cout << endl;
    int columns = A[0].size();

    int index = -1;
    for (int i = 0; i < minimalValue.size(); i++) {
        if (minimalValue[i] == 1) {
            index = i;
            break;
        }
    }

    vector<double> maxFound(columns);
    vector<double> minFound(columns);
    for (int j = 0; j < columns; j++) {
        maxFound[j] = Max(A, j);
        minFound[j] = Min(A, j);
    }

    cout << "Max and min:\n" << "Max: ";
    for (double value : maxFound) {
        cout << value << " ";
    }
    cout << "\nMin: ";
    for (double value : minFound) {
        cout << value << " ";
    }
    cout << endl;

    cout << "Normalized matrix A:" << endl;
    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; j < columns; j++) {
            if (j != index && j < A[i].size()) {
                A[i][j] = (A[i][j] - minFound[j]) / (maxFound[j] - minFound[j]);
            }
        }
        for (double val : A[i]) {
            cout << setw(10) << val << " ";
        }
        cout << endl;
    }

    vector<int> indexes; //создвём индексы для каждого элемента матрицы
    for (int i = 0; i < A.size(); i++) {
        bool isMax = true;
        for (int j = 0; j < columns; j++) {
            if (j < A[i].size() && A[i][j] != maxFound[j] && A[i][j] >= maxFound[j] * minimalValue[j]) {
                isMax = false;
                break;
            }
        }
        if (isMax) {
            indexes.push_back(i);
        }
    }


    map<int, double> value;
    for (int i : indexes) {
        double val = 0;
        bool hasZero = false;
        for (int j = 0; j < columns; j++) {
            if (j != index && j < A[i].size()) {
                if (A[i][j] == 0) {
                    hasZero = true;
                    break;
                }
                val += A[i][j] * normalWeigth[j];
            }
        }
        if (!hasZero) {
            value.insert(pair<int, double>(i, val));
        }
    }

    double maxVal = numeric_limits<double>::lowest();
    int maxIndex = -1;
    for (const pair<int, double>& entry : value) {
        if (entry.second > maxVal) {
            maxVal = entry.second;
            maxIndex = entry.first;
        }
    }

    return alternative[maxIndex];
}

int main() {
    vector<vector<double>> A = { //матрица оценок критериев для альтернатив
        {7, 3, 2, 6},
        {8, 7, 1, 8},
        {3, 5, 6, 6},
        {5, 2, 5, 2},
    };
    vector<double> w = { 8, 4, 2, 6 }; //вектор весов критериев
    vector<double> d = { 1, 0.2, 0.1, 0.5 }; //вектор минимально допустимых уровней для значений
    vector <string> alternative = { "Tatyana", "Larisa", "Natalya", "Olga" }; //вектор альтернатив(спутниц жизни)
    string result = startReplacingCriteria(A, w, d, alternative);
    cout << "Result: " << result;
    return 0;

}