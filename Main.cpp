/*
Matrix Manipulation Algorithm
Written by Matthew Hahn
Version 0.2.5

Input command (Add, Multiply, RREF, etc)
Input desired graphs/values via legal brackets

TODO:
Main
  -Bulletproof the code

Matrix_Calculator
  -RREF doesn't work if starting value is 0
    -Division by zero problem (If no initial pivot, problems apparently)
  -Add Determinant method
  -Comment previous methods to more detail
*/
#include "Matrix_Calculator.cpp"
#include<string>
#include<locale>
#include<algorithm>

struct UserCommand {
  std::string Command;
  Matrix M_1, M_2;
  double Constant = INT_MIN;
};

int ValidateSize(Matrix M) {
  int currentMeta = M[0].size();
  for(int i=0;i<M.size();++i)
    if(M[i].size() != currentMeta)
      return -1;
  return currentMeta;
}

void printError(std::string Error) {
  std::cout << "  Error: " + Error << "; " << "See 'help'\n";
}

UserCommand ReadIn(std::string UserString) {
  UserCommand toReturn; int i;
  std::vector<std::string> LC{"Add","Sub","Multiply",
  "Smultiply","Transpose","RREF","Inverse","Rank","Det",
  "Exit","Help"};
  try {
    UserString.erase(std::remove(UserString.begin(),UserString.end(),' '), UserString.end());
    for(i=0;i<UserString.size();++i) { //Gets the user Command
        if(i+1 < UserString.size() && UserString[i+1] == '{') {
          toReturn.Command.push_back(UserString[i]); break;
        } else
          toReturn.Command.push_back(UserString[i]);
      } toReturn.Command[0] = toupper(toReturn.Command[0]);
    if(!(std::find(LC.begin(), LC.end(), toReturn.Command) != LC.end()))
      throw "Unknown Command";
    } catch(const std::exception& e) {
        toReturn.Command = "Illegal command";
        return toReturn;
    } catch(const char *e) {
        toReturn.Command = e;
        return toReturn;
    } std::string Brackets; std::string toPass; int j; int k; int l;
  try {
    for(j=i+1;j<UserString.size();++j) { //Gets the first matrix/parameter to pass
      if(UserString[j] == '{') {
        Brackets.push_back(UserString[j]);
        if(Brackets.size() == 2)
          toReturn.M_1.push_back(std::vector<double>());
      } else if(UserString[j] == '}') {
        Brackets.pop_back();
        if(Brackets.size() != 0)
          toReturn.M_1.back().push_back(std::stod(toPass)); toPass.clear();
      } else if((isdigit(UserString[j]) || UserString[j] == '.' || UserString[j] == '-') && Brackets.size() == 2) {
        toPass.push_back(UserString[j]);
      } else if(UserString[j] == ',' && !Brackets.empty()) {
        toReturn.M_1.back().push_back(std::stod(toPass)); toPass.clear();
      } else if(UserString[j] == ',' && Brackets.empty())
        break;
  }} catch(const std::invalid_argument& e) {
    toReturn.Command = "Wrong 1st parameter syntax";
    return toReturn;
  } Brackets.clear(); toPass.clear();
  if(j != UserString.size() && UserString[j+1] == '{') {
    try {
      for(k=j+1;k<UserString.size();++k) { //Gets the second matrix/parameter to pass
        if(UserString[k] == '{') {
          Brackets.push_back(UserString[k]);
          if(Brackets.size() == 2)
            toReturn.M_2.push_back(std::vector<double>());
        } else if(UserString[k] == '}') {
          Brackets.pop_back();
          if(Brackets.size() != 0)
            toReturn.M_2.back().push_back(std::stod(toPass)); toPass.clear();
        } else if((isdigit(UserString[k]) || UserString[k] == '-'
        || UserString[k] == '.') && Brackets.size() == 2) {
          toPass.push_back(UserString[k]);
        } else if(UserString[k] == ',' && !Brackets.empty()) {
          toReturn.M_2.back().push_back(std::stod(toPass)); toPass.clear();
        } else if(UserString[k] == ',' && Brackets.empty())
          break;
        } Brackets.clear(); toPass.clear();
      } catch(const std::invalid_argument& e) {
        toReturn.Command = "Wrong 2nd parameter syntax";
        return toReturn;
      } toPass.clear();
  } else if(j != UserString.size() && (isdigit(UserString[j+1])
  || UserString[j+1] == '-' || UserString[j+1] == '.')) {
    try {
      for(l=j+1;l<UserString.size();++l)
        toPass.push_back(UserString[l]);
      toReturn.Constant = std::stod(toPass);
    } catch(const std::exception& e) {
        toReturn.Command = "Wrong constant syntax";
        return toReturn;
  }} return toReturn;
}

int main() {
  printf("Matrix Calculator\nVersion 0.2.5\n\n");
  Matrix_Manipulation *Mod = new Matrix_Manipulation();
  Matrix Matrix_Solution; int Integer_Solution;
  UserCommand UC; std::string UserString;
  while(true) {
    printf(">>"); std::getline(std::cin,UserString);
    UC = ReadIn(UserString);
    if(UC.Command == "Add") {
      if((UC.M_1.size() == UC.M_2.size()) &&
      (ValidateSize(UC.M_1) == ValidateSize(UC.M_2))) {
        Matrix_Solution = Mod->Add(UC.M_1, UC.M_2);
        Mod->printMatrix(Matrix_Solution);
      } else
        printError("Illegal matrices' size");
    } else if(UC.Command == "Sub") {
      if((UC.M_1.size() == UC.M_2.size()) &&
      (ValidateSize(UC.M_1) == ValidateSize(UC.M_2))) {
        Matrix_Solution = Mod->Subtract(UC.M_1, UC.M_2);
        Mod->printMatrix(Matrix_Solution);
      } else
        printError("Illegal matrices' size");
    } else if(UC.Command == "Multiply") {
      if(ValidateSize(UC.M_1) == UC.M_2.size()) {
        Matrix_Solution = Mod->Multiply(UC.M_1, UC.M_2);
        Mod->printMatrix(Matrix_Solution);
      } else
        printError("Illegal matrices' size");
    } else if(UC.Command == "Smultiply") {
      if(UC.M_2.empty() && UC.Constant != INT_MIN) {
        if(ValidateSize(UC.M_1) != -1) {
          Matrix_Solution = Mod->S_Multiply(UC.M_1, UC.Constant);
          Mod->printMatrix(Matrix_Solution);
        } else
        printError("Illegal matrix size");
      } else
        printError("Illegal format");
    } else if(UC.Command == "Transpose") {
      if(UC.M_2.empty() && UC.Constant == INT_MIN) {
        if(ValidateSize(UC.M_1) != -1) {
          Matrix_Solution = Mod->Transpose(UC.M_1);
          Mod->printMatrix(Matrix_Solution);
        } else
          printError("Illegal matrix size");
      } else
        printError("Illegal format");
    } else if(UC.Command == "RREF") {
      if(UC.M_2.empty() && UC.Constant == INT_MIN) {
        if(ValidateSize(UC.M_1) != -1) {
          Matrix_Solution = Mod->RR_Echelon_Form(UC.M_1, UC.M_1.size());
          Mod->printMatrix(Matrix_Solution);
        } else
          printError("Illegal matrix size");
      } else
        printError("Illegal format");
    } else if(UC.Command == "Inverse") {
      if(UC.M_2.empty() && UC.Constant == INT_MIN) {
        int Size = ValidateSize(UC.M_1);
         if(Size != -1 && Size == UC.M_1.size()) {
          Matrix_Solution = Mod->Inverse(UC.M_1);
          Mod->printMatrix(Matrix_Solution);
        } else
          printError("Illegal matrix size");
      } else
        printError("Illegal format");
    } else if(UC.Command == "Rank") {
      if(UC.M_2.empty() && UC.Constant == INT_MIN) {
        if(ValidateSize(UC.M_1) != -1) {
          Integer_Solution = Mod->Rank(UC.M_1);
          std::cout << "  " << Integer_Solution << "\n";
        } else
          printError("Illegal matrix size");
      } else
        printError("Illegal format");
    } else if(UC.Command == "Det") {
      if(UC.M_2.empty() && UC.Constant == INT_MIN) {
        if(ValidateSize(UC.M_1) != -1) {
          Integer_Solution = Mod->Determinant(UC.M_1);
          std::cout << "  " << Integer_Solution << "\n";
        } else
          printError("Illegal matrix size");
      } else
        printError("Illegal format");
    } else if(UC.Command == "Exit") {
      break; exit(EXIT_SUCCESS);
    } else if(UC.Command == "Help") {
      printf("  Legal Commands\n"
      "   -Add (Adds 2 same sized matrices)\n"
      "   -Sub (Subtracts 2 same sized matrices)\n"
      "   -Multiply (Multiplies two legally sized matrices)\n"
      "   -SMultiply (Multiplies a matrix by a constant)\n"
      "   -Tranpose (Transposes a single matrix)\n"
      "   -RREF (Reduces a matrix to row reduced echelon form)\n"
      "   -Inverse (Gives the inverse of a given matrix)\n"
      "   -Rank (Gives the rank of a given matrix)\n"
      "   -Det (Gives the determinant of a given matrix)\n"
      "   -Exit\n\n"
      "  Legal Syntax\n"
      "   -Command{{Row 1}{Row 2}{Row 3}}\n"
      "   -Command{{Row 1}{Row 2}},{{Row 1}{Row 2}}\n"
      "   -Command{{Row 1}{Row 2}},Constant\n\n"
      "  Miscellaneous\n"
      "   -Rows/Columns must be the same length as other Rows/Columns\n"
      "   -Arithmetic is limited to 4 byte integers\n"
      "   -INT_MIN (-2147483647) is unavailable\n");
    } else
      printError(UC.Command);
  } return 0;
}
