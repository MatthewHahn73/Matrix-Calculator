#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<math.h>
#define Matrix std::vector<std::vector<double>>

class Matrix_Manipulation {
public:
  void Matrix_Multiplication() {

  }

  //Prints a given matrix to console
  void printMatrix(Matrix M) { //Matrix[y][x]
    for(int i = 0; i < M.size(); i++) {
      if(i!=0) std::cout << "\n";
      for(int j = 0; j < M[i].size(); j++) {
        if(j == 0) std::cout << "  ";
        std::cout << M[i][j] << " ";
     }} std::cout << "\n";
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

  //Row reduces the matrix to row reduced echelon form
  Matrix RR_Echelon_Form(Matrix M, int rowCount) {
    int lead = 0; int colCount = M[0].size();
    for(int r=0;r<rowCount;++r) {
      if(colCount <= lead)
        break;
      int i=r;
      while(M[i][lead] == 0) {
        ++i;
        if(rowCount == i) {
          i=r; ++lead;
          if(colCount == lead) {
            lead--; break;
          }}
      }
      for(int j=0;j<colCount;++j) {
        double temp = M[r][j];
        M[r][j] = M[i][j];
        M[i][j] = temp;
      } double div = M[r][lead];
      if(div != 0)
        for(int j=0;j<colCount;++j)
          M[r][j] /= div;
      for(int j=0;j<rowCount;++j) {
        if(j != r) {
          double sub = M[j][lead];
          for(int k=0;k<colCount;++k)
            M[j][k] -= (sub * M[r][k]);
        }} ++lead;
      } return M;
    }

  //Gets and returns the multiplicative inverse of a matrix
  Matrix Inverse(Matrix M) {
    Matrix Identity(M.size(),std::vector<double>(M[0].size(), 0));
    for(int i=0;i<M.size();++i)
      Identity[i][i] = 1;
    for(int j=0;j<Identity.size();++j)
      for(int k=0;k<Identity[j].size();++k)
        M[j].push_back(Identity[j][k]);
    M = RR_Echelon_Form(M, Identity.size());
    for(int i=0;i<M.size();++i)
      for(int j=0;j<=M[i].size()/2;++j)
        M[i].erase(M[i].begin());
    return M;
  }

  //Calculates and returns rank of a matrix
  int Rank(Matrix M) {
    int Rank = 0;
    Matrix RR_M = RR_Echelon_Form(M, M.size());
    for(int i=0;i<RR_M.size();++i)
      for(int j=0;j<RR_M[i].size();++j)
        if(RR_M[i][j] != 0) {
          ++Rank; break;
    } return Rank;
  }

  //Calculates and returns the determinant of a matrix
  int Determinant(Matrix M, int n) {
    int det = 0;
    Matrix subM(M.size(), std::vector<double>(M[0].size(), 0));
    if(n == 2)
      return ((M[0][0] * M[1][1]) - (M[1][0] * M[0][1]));
    else {
      for(int i=0;i<n;++i) { int subj = 0;
        for(int j=0;j<n;++j) { int subk = 0;
          for(int k=0;k<n;++k) {
            if(k == i)
              continue;
            subM[subj][subk] = M[i][j];
            ++subk;
        } ++subj;
      } det = det + (pow(-1, i) * M[0][i] * Determinant(subM, n-1));
    }} return det;
  }

  int Onto(Matrix M) {
    M = RR_Echelon_Form(M, M.size());
    for(int i=0;i<M.size();++i)
      if(!(std::find(M[i].begin(), M[i].end(), 1) != M[i].end()))
        return 1;
    return 0;
  }

  int One_to_One(Matrix M) {
    std::vector<double> tVec;
    M = RR_Echelon_Form(M, M.size());
    for(int i=0;i<M[0].size();++i) {
      for(int j=0;j<M.size();++j)
        tVec.push_back(M[j][i]);
      if(!(std::find(tVec.begin(), tVec.end(), 1) != tVec.end()))
        return 1;
      tVec.clear();
    } return 0;
  }

  std::vector<double> Eigenvalues(Matrix M) {
    std::vector<double> EV;
    return EV;
  }

  std::vector<double> Eigenvectors(Matrix M) {
    std::vector<double> EV;
    return EV;
  }
};
