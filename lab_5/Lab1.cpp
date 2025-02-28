#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

const int N = 10;
const char LETTERS[N] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

void loadMatrix(const string& filename, vector<vector<int>>& matrix) {
    ifstream file(filename);
    if (!file) {
        cout << "\nОшибка с файлом" << endl;
        return;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            file >> matrix[i][j];
        }
    }
    file.close();
}

void makeUndirected(vector<vector<int>>& matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (matrix[i][j] == 1 || matrix[j][i] == 1) {
                matrix[i][j] = matrix[j][i] = 1;
            }
        }
    }
}

vector<vector<int>> computeReachabilityMatrix(vector<vector<int>> matrix) {
    vector<vector<int>> reachability = matrix;
    for (int p = 0; p < N; p++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                reachability[i][j] |= (reachability[i][p] & reachability[p][j]);
            }
        }
    }
    return reachability;
}

void findConnectedComponents(const vector<vector<int>>& reachability) {
    vector<bool> visited(N, false);
    vector<vector<int>> components;

    for (int i = 0; i < N; i++) {
        if (!visited[i]) {
            vector<int> component;
            queue<int> q;
            q.push(i);
            visited[i] = true;

            while (!q.empty()) {
                int node = q.front();
                q.pop();
                component.push_back(node);

                for (int j = 0; j < N; j++) {
                    if (reachability[node][j] && !visited[j]) {
                        visited[j] = true;
                        q.push(j);
                    }
                }
            }
            components.push_back(component);
        }
    }

    cout << "\nКоличество компонент связанности: " << components.size() << "\n";
    for (size_t i = 0; i < components.size(); i++) {
        cout << "Компонента " << i + 1 << ": ";
        for (int v : components[i]) {
            cout << LETTERS[v] << " ";
        }
        cout << "\n";
    }
}

void printMatrix(const vector<vector<int>>& matrix) {
    cout << "  ";
    for (int i = 0; i < N; i++) {
        cout << LETTERS[i] << " ";
    }
    cout << "\n";

    for (int i = 0; i < N; i++) {
        cout << LETTERS[i] << " ";
        for (int j = 0; j < N; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    while (true) {
        string filename;
        cout << "Введите имя файла (или 'exit' для выхода): ";
        cin >> filename;
        if (filename == "exit") break;

        vector<vector<int>> matrix(N, vector<int>(N));
        loadMatrix(filename, matrix);
        makeUndirected(matrix);
        
        cout << "\nМатрица смежности:" << endl;
        printMatrix(matrix);
        
        vector<vector<int>> reachability = computeReachabilityMatrix(matrix);
        
        cout << "\nМатрица достижимости:" << endl;
        printMatrix(reachability);
        
        findConnectedComponents(reachability);
    }
    return 0;
}
