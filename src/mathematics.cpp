#include "mathematics.h"
#include <cmath>

using namespace std;

bool Parser::isNum(char c) {
    return (c >= 0x30 && c <= 0x39);
}

std::vector<int> BinaryParser::parse(string &s) {
    vector<int> num;
    int length = s.length();
    int i = 0;

    while (i < length){
        if (isNum(s[i]) == false){
            i++;
        } else {
            int number = 0;
            bool neg = false;
            if (i > 0 && s[i] - 1 == '-'){
                neg = true;
            }
            for (i; i < length && isNum(s[i]); i++){
                number = number * 10 + (s[i] - 0x30);
            }
            if (neg == true){
                number = -1 * number;
            }
            num.push_back(number);
        }
    }
    if (num.size() != 2){
        throw (std::invalid_argument) "Incorrect line";
    }
    return num;
}

std::vector<double> Binary::result(std::string &s) {
    BinaryParser parser;
    vector<int> coef = parser.parse(s);
    vector<double> result;
    result.push_back(calculate(coef));
    return result;
}

short Add::getType() {
    return 1;
}

double Add::calculate(std::vector<int> coef) {
    return (double)(coef[0] + coef[1]);
}

short Sub::getType() {
    return 2;
}

double Sub::calculate(std::vector<int> coef) {
    return (double)(coef[0] - coef[1]);
}

short Mul::getType() {
    return 3;
}

double Mul::calculate(std::vector<int> coef) {
    return (double)(coef[0] * coef[1]);
}

short Div::getType() {
    return 4;
}

double Div::calculate(std::vector<int> coef) {
    if (coef[1] == 0){
        throw (std::invalid_argument) "Can't divide by zero";
    }
    return (double)(coef[0] / coef[1]);
}

std::vector<int> EquationParser::parse(string &s) {
    vector<int> coef;
    int n = s.find("x^2");
    coef.push_back(stoi(s.substr(0, n))) ;
    int k = s.find('x', n + 3);
    coef.push_back(stoi(s.substr(n + 3, k - n)));
    n = k + 1;
    k = s.find('=');
    coef.push_back(stoi(s.substr(n, k - n)));
    return coef;
}

short Equation::getType() {
    return 5;
}

std::vector<double> Equation::result(string &s) {
    EquationParser parser;
    vector<int> coef = parser.parse(s);
    vector<double> result;
    int D = (coef[1]*coef[1]) - 4*coef[0]*coef[2];
    if (D < 0){
        return result;
    }
    if (D == 0){
        result.push_back((double)-1*coef[1]/(2*coef[0]));
        return result;
    }
    result.push_back((-1 * coef[1] + sqrt(D)) / (2 * coef[0]));
    result.push_back((-1 * coef[1] - sqrt(D)) / (2 * coef[0]));
    return result;
}

void Solver::add(Operation *operation) {
    op.push_back(operation);
}

std::vector<double> Solver::solve(short type, std::string problem) {
    int n = op.size();
    int i = 0;
    while (i < n && op[i]->getType() != type){
        i++;
    }
    if (i == n){
        throw (std::logic_error) "No operation found.";
    }
    return op[i]->result(problem);
}