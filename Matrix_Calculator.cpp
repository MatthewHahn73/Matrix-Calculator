//Finish unfinished methods. Check book

#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#define Matrix std::vector<std::vector<double>>

class Matrix_Manipulation {
public:
  Matrix_Multiplication() {

  }

  Matrix ReadIn(std::string toRead) {
    std::ifstream in(toRead);
    Matrix fields;
    std::string buffer;
      if(in) {
        std::string line;
        while (getline(in, line)) {
          std::stringstream sep(line);
          std::string field;
          fields.push_back(std::vector<double>());
          while (getline(sep, field, ',')) {
            fields.back().push_back(atoi(field.c_str()));
          }}
        } in.close();
    return fields;
  }

  void printMatrix(Matrix Mat) { //Matrix[y][x]
    for(int i = 0; i < Mat.size(); i++) {
      if(i!=0) std::cout << "\n";
      for(int j = 0; j < Mat[i].size(); j++)
        std::cout << Mat[i][j] << " ";
     }
  }

  Matrix Add(Matrix M_1, Matrix M_2) {
    for(int i=0;i<M_1.size();i++) {
      for(int j=0;j<M_1[i].size();j++)
        M_1[i][j] += M_2[i][j];
      } return M_1;
  }

  Matrix Subtract(Matrix M_1, Matrix M_2) {
    for(int i=0;i<M_1.size();i++) {
      for(int j=0;j<M_1[i].size();j++)
        M_1[i][j] -= M_2[i][j];
      } return M_1;
  }

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

  Matrix S_Multiply(Matrix M_1, int Number) {
    for(int i=0;i<M_1.size();i++) {
      for(int j=0;j<M_1[i].size();j++)
        M_1[i][j] = (Number*M_1[i][j]);
      } return M_1;
  }

  Matrix Transpose(Matrix M_1) {
    Matrix TM_1;
    for(int i=0;i<M_1[0].size();i++) {
      TM_1.push_back(std::vector<double>());
      for(int j=0;j<M_1.size();j++) {
        TM_1.back().push_back(M_1[j][i]);
      }} return TM_1;
  }

  //Only returns regular echelon form, not row reduced (FIX)
  Matrix Echelon_Form(Matrix M_1) {
    const int nrows = M_1.size();
    const int ncols = M_1[0].size();
    int lead = 0;
    while (lead < nrows) {
        float d, m;
        for (int r=0;r<nrows;r++) { // for each row ...
            d = M_1[lead][lead];
            m = M_1[r][lead] / M_1[lead][lead];
            for (int c=0;c<ncols;c++) { // for each column ...
                if (r == lead) {//If current value is a pivot
                    M_1[r][c] /= d;                    // make pivot = 1
                  }
                else           //Reduce value or zero it out?
                    M_1[r][c] -= M_1[lead][c] * m;  // make other = 0
        }} lead++; }
    return M_1;
  }

  Matrix Inverse(Matrix M_1) {
    //TODO: Write some code to find and return the inverse of the parameter matrix
    return M_1;
  }
};
