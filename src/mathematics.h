#ifndef T2_MATHEMATICS_H
#define T2_MATHEMATICS_H

#include <string>
#include <vector>

class Parser{
public:
    bool isNum(char c);
    std::vector<int> parse(std::string &s);
};

class BinaryParser: public Parser{
public:
    std::vector<int> parse(std::string &s);
};

class EquationParser: public Parser{
public:
    std::vector<int> parse(std::string &s);
};

class Operation{
public:
    virtual short getType() = 0;
    virtual std::vector<double> result(std::string &s) = 0;
};

class Binary: public Operation{
public:
    std::vector<double> result(std::string &s);
    virtual double calculate(std::vector<int> coef) = 0;
};

class Add: public Binary{
public:
    short getType();
    double calculate(std::vector<int> coef);
};

class Sub: public Binary{
public:
    short getType();
    double calculate(std::vector<int> coef);
};

class Mul: public Binary{
public:
    short getType();
    double calculate(std::vector<int> coef);
};

class Div: public Binary{
public:
    short getType();
    double calculate(std::vector<int> coef);
};

class Equation: public Operation{
public:
    short getType();
    std::vector<double> result(std::string &s);
};

class Solver{
std::vector<Operation*> op;
public:
    void add(Operation* operation);
    std::vector<double> solve(short type, std::string problem);
};



#endif //T2_MATHEMATICS_H
