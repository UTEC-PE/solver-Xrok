#include <iostream>
#include "solver.h"

using namespace std;

/*
void menu() {
      system("cls");
      cout<<"==========================================================="<<endl;
      cout<<"\t\tPractica Operaciones"<<endl;
      cout<<"==========================================================="<<endl;

      //char* str="7/4*((a+b)*a)+3";
      //char* str="7/4*((a+-+--b)*a)+3";
      //char* str="2+(3)";
      char* str="7/4*((a+b)^4*a)+3";
}*/

// No opera unarios -(3+8)
// Faltaron operaciones con variables

int main(int argc, char const *argv[]) {
   /* menu();

    cout << "\nPress enter to continue ..."; 
    cin.get(); 
    return EXIT_SUCCESS;*/

   string expresion;
    if (argc == 2) {
        expresion = argv[1];
    }
    else {
      throw "One argument expected";
    }

  //string expresion = "4-2+4^0.5";
  node* solito =build(expresion);
  cout<<solito->result()<<endl;
}

