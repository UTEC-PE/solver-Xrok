
#ifndef NODE_H
#define NODE_H
#include <string>
using namespace std;

class node{
public:
    node * left;
    node * right;

    node() : left(nullptr), right(nullptr) {};
    node(node* left, node* right) : left(left), right(right){};
    virtual float result() {};
};

class number: public node {
public:
    float data;
    number(float n):data(n) {}
    float result(){
        return data;
    }
};

class Menos : node{
public:
    Menos(node* left_, node* right_) : node(left_, right_) {};
};

class Mas : public node {
public:
    Mas(node * left_, node* right_) : node(left_, right_) {};
    float result(){
        return left->result() + right->result();
    }
};

bool search(string equation, char element, int &pos){
    int parentesis=0;
    for(; pos < equation.length(); pos++) {
        if(equation[pos] == '(') parentesis++;
        if(equation[pos] == ')') parentesis--;
        if(parentesis == 0 && equation[pos] == element ) return true;
    }
    return false;
}
string cut_parentesis(string equation) {
    if (equation[0] == '(' && equation[equation.length() - 1] == ')')
        return equation.substr(1,equation.length()-2);
}

bool is_number(string equation){
    for (int i = 0; i < equation.length(); ++i){

        if ( !(equation[i] >= '0' && equation[i]<='9')){
            
            if (!(equation[i]=='.')){
                return false;
            }
        }
    }
    return true;
}

node * build(string equation) {
    int position = 0;
    
    if(search(equation,'+', position)) {
        string subcadena1 = equation.substr(0,position);
        string subcadena2 = equation.substr(position+1);

        return new Mas(build(subcadena1), build(subcadena2));

    }else if (is_number(equation)){

        float n = strtof(equation.c_str(),0);
        return new number(n);

    }else{
        equation= cut_parentesis(equation);
        return build(equation);
    }
}

#endif