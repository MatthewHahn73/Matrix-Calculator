#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<stdlib.h>
#define Matrix std::vector<std::vector<double>>

class Matrix_Manipulation {
public:
  Matrix_Multiplication() {

  }

  //Prints a given matrix to console
  void printMatrix(Matrix M) { //Matrix[y][x]
    for(int i = 0; i < M.size(); i++) {
      if(i!=0) std::cout << "\n";
      for(int j = 0; j < M[i].size(); j++)
        std::cout << M[i][j] << " ";
     } std::cout << "\n";
  }

  //Adds the two matrices
  Matrix Add(Matrix M_1, Matrix M_2) {
    for(int i=0;i<M_1.size();i++) {
      for(int j=0;j<M_1[i].size();j++)
        M_1[i][j] += M_2[i][j];
      } return M_1;
  }

  //Subtracts the two matrices
  Matrix Subtract(Matrix M_1, Matrix M_2) {
    for(int i=0;i<M_1.size();i++) {
      for(int j=0;j<M_1[i].size();j++)
        M_1[i][j] -= M_2[i][j];
      } return M_1;
  }

  //Multiplies the two matrices
  Matrix Multiply(Matrix M_1, Matrix M_2) {
    Matrix endProduct;
    for(int x=0;x<M_1.size();x++) {
      endProduct.push_back(std::vector<double>());
      for(int y=0;y<M_2[x].size();y++)
        endProduct.back().push_back(0);
    } int a, b, c;
    for(a=0;a<M_1.size();a++)
      for(b=0;b<M_2[0].size();b++)
        for(c=0;c<M_1[0].size();c++)
          endProduct[a][b] += (M_1[a][c]*M_2[c][b]);
    return endProduct;
  }

  //Multiplies the matrix by given number
  Matrix S_Multiply(Matrix M, int Number) {
    for(int i=0;i<M.size();i++) {
      for(int j=0;j<M[i].size();j++)
        M[i][j] = (Number*M[i][j]);
      } return M;
  }

  //Transposes the matrix and returns
  Matrix Transpose(Matrix M) {
    Matrix TM_1;
    for(int i=0;i<M[0].size();i++) {
      TM_1.push_back(std::vector<double>());
      for(int j=0;j<M.size();j++) {
        TM_1.back().push_back(M[j][i]);
      }} return TM_1;
  }

  //Row reduces the matrix to either echelon form, RR echelon form, or the identity
  Matrix RR_Echelon_Form(Matrix M) {
    int lead = 0;
    int rowCount = M.size();
    int colCount = M[0].size();
    for(int r=0;r<rowCount;++r) {
      if(colCount <= lead)
        return M;
      int i=r;
      while(M[i][lead] == 0) {
        ++i;
        if(rowCount = i) {
          i=r; ++lead;
          if(colCount == lead)
            return M;
        }} for(int j=0;j<colCount;++j) {
        int temp = M[r][j];
        M[r][j] = M[i][j];
        M[i][j] = temp;
      } int div = M[r][lead];
      if(div != 0)
        for(int j=0;j<colCount;++j)
          M[r][j] /= div;
      for(int j=0;j<rowCount;++j) {
        if(j != r) {
          int sub = M[j][lead];
          for(int k=0;k<colCount;++k)
            M[j][k] -= (sub * M[r][k]);
        }} ++lead;
      } return M;
    }

  //Gets and returns the multiplicative inverse
  Matrix Inverse(Matrix M) {
    //Generate Identity Matrix and append to M_1
    Matrix Identity(M.size(),std::vector<double>(M[0].size(), 0));
    for(int i=0;i<M.size();++i)
      Identity[i][i] = 1;
    for(int j=0;j<Identity.size();++j)
      for(int k=0;k<Identity[j].size();++k)
        M[j].push_back(Identity[j][k]);

    //Run row reduction until the original is the Identity
    //M = RR_Echelon_Form(M);
    return M;
  }

  int Rank(Matrix M) {
    //Write some code to reutn the rank of a given matrix
  }

  int Determinant(Matrix M) {
    //Write some code to return the determinant of a given matrix
  }
};
