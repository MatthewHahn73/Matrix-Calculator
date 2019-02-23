/*
Matrix Manipulation Algorithm
Written by Matthew Hahn
Version 0.0.7

Input command (Add, Multiply, RREF, etc)
Input desired graph file names (Must be .csvs)
*/

#include<iostream>
#include "Matrix_Calculator.cpp"

int main() {
  Matrix_Manipulation *Mod = new Matrix_Manipulation();
  Matrix Matrix_1 = Mod->ReadIn("Matrices/Tester_1.csv");
  Matrix Matrix_2 = Mod->ReadIn("Matrices/Tester_2.csv");

  //Matrix Solution = Mod->Add(Matrix_1, Matrix_2);
  //Matrix Solution = Mod->Subtract(Matrix_1, Matrix_2);
  //Matrix Solution = Mod->Multiply(Matrix_1, Matrix_2);
  //Matrix Solution = Mod->S_Multiply(Matrix_1, 5);
  //Matrix Solution = Mod->Transpose(Matrix_1);
  Matrix Solution = Mod->Echelon_Form(Matrix_2);
  Mod->printMatrix(Solution);
  std::cin.get();
  return 0;
}
