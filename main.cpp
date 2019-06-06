#include <iostream>
#include "src/mathematics.h"
#include <fstream>

using namespace std;

void print(vector<double>& arr){
    int n = arr.size();
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
}


int main(int argc, char **argv) {
    if (argc == 1){
        return -1;
    }
    Solver solver;
    solver.add(new Add);
    solver.add(new Sub);
    solver.add(new Div);
    solver.add(new Mul);
    solver.add(new Equation);
    fstream file(argv[1]);
    if (!file){
        cout << "File not found." << endl;
    } else {
        int type;
        file >> type;
        string problem;
        file.seekg(3, ios::beg);
        getline(file, problem);
        vector<double> result = solver.solve(type, problem);
        cout << "Problem: " << problem << endl << "Result: ";
        print(result);
    }
    return 0;
}