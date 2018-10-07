
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
    virtual float result() {}; // No hay return, debió haber sido un virtual float result() = 0
};

//---------------------SUBCLASES-------------------------------------------
class number: public node {
public:
    float data;
    number(float n):data(n) {}
    float result(){
        return data;
    }
};

class Menos : public node{
public:
    Menos(node* left_, node* right_) : node(left_, right_) {};
    float result(){
        return left->result() - right->result();
    }
};

class Mas : public node {
public:
    Mas(node * left_, node* right_) : node(left_, right_) {};
    float result(){
        return left->result() + right->result();
    }
};

class Por : public node {
public:
    Por(node * left_, node* right_) : node(left_, right_) {};
    float result(){
        return left->result() * right->result();
    }
};

class Entre : public node {
public:
    Entre(node * left_, node* right_) : node(left_, right_) {};
    float result(){
        return left->result() / right->result();
    }
};
class Elevado : public node {
public:
    Elevado(node * left_, node* right_) : node(left_, right_) {};
    float result(){
        float temp=1;
        float x = left->result();
        for (int i = 0; i < right->result(); ++i)
        {
            temp=temp*x;
        }
        return temp;
    }
};
//-------------FUNCIONES    --------------------------------------------------
bool search(string equation, char element1, char element2, int &pos){
    int parentesis=0;
    
    for(; pos > 0; pos--) {
        if(equation[pos] == '(') parentesis++;
        if(equation[pos] == ')') parentesis--;
        if(parentesis == 0 && equation[pos] == element1 ) return true;
        if(parentesis == 0 && equation[pos] == element2 ) return true;
    }
    pos=equation.length();
    return false;
}
string cut_parentesis(string equation) { // Que retorna si no entras al if?
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
    int position = equation.length();
    cout<<"equation: "<<equation<<endl;
    //cin.get();
    if(search(equation,'+','-' ,position) ) {
        //cout<<"position: "<<position<<endl;
        if (equation[position]=='+'){
        string subcadena1 = equation.substr(0,position);
        string subcadena2 = equation.substr(position+1);     
        return new Mas(build(subcadena1), build(subcadena2));
        
        }else if (equation[position]=='-'){

        string subcadena1 = equation.substr(0,position);
        string subcadena2 = equation.substr(position+1);
        return new Menos(build(subcadena1), build(subcadena2));
        }

    }else if (search(equation,'*','/', position)) {
        if (equation[position]=='*')
        {
        string subcadena1 = equation.substr(0,position);
        string subcadena2 = equation.substr(position+1);
        return new Por(build(subcadena1), build(subcadena2));        
        }else if (equation[position]=='/')
        {
        string subcadena1 = equation.substr(0,position);
        string subcadena2 = equation.substr(position+1);
        return new Entre(build(subcadena1), build(subcadena2));
        }
    }else if (search(equation,'^',' ',position)){
        if (equation[position]=='^')
        {
        string subcadena1 = equation.substr(0,position);
        string subcadena2 = equation.substr(position+1);
        return new Elevado(build(subcadena1), build(subcadena2));        
        }
        
    }
    else if (is_number(equation)){

        float n = strtof(equation.c_str(),0);
        return new number(n);

    }else{
        equation= cut_parentesis(equation);
        return build(equation);
    }
}

#endif