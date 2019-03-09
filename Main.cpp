/*
Matrix Manipulation Algorithm
Written by Matthew Hahn
Version 0.1.7

Input command (Add, Multiply, RREF, etc)
Input desired graphs/values via legal brackets

TODO:
Main
  -Clean up the exception handling
    -Spaces after command and after dividing ',' between matrices throws error.
      -Find why

Matrix_Calculator
  -Row reduction doesn't reduce to row reduced echelon form always. Why?
    -Double problem?
      -Seems to work when passed values are integers
  -Finish inversion method
    -Look into finding inverse via determinant instead of using identity
  -Add Determinant method
  -Add Rank method
  -Comment previous methods to more detail
*/
#include "Matrix_Calculator.cpp"
#include<string>
#include<locale>
#include<algorithm>

struct UserCommand{
  std::string Command;
  Matrix M_1, M_2;
  double Constant = INT_MIN;
};

UserCommand ReadIn(std::string UserString) {
  UserCommand toReturn; int i;
  std::vector<std::string> LC{"Add","Sub","Multiply",
  "Smultiply","Transpose","Echelon","Inverse","Exit","Help"};
  try {
    for(i=0;i<UserString.size();++i) { //Gets the user Command
      if(!isspace(UserString[i])) {
        if(UserString[i+1] == '{') {
          toReturn.Command.push_back(UserString[i]); break;
        } else
          toReturn.Command.push_back(UserString[i]);
      }} toReturn.Command[0] = toupper(toReturn.Command[0]);
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
      std::cout << toReturn.Constant << "\n";
    } catch(const std::exception& e) {
        toReturn.Command = "Wrong constant syntax";
        return toReturn;
  }} return toReturn;
}

void printError(std::string Error) {
  std::cout << "  Error: " + Error << "; " << "See 'help'\n";
}

int main() {
  printf("Matrix Calculator\nVersion 0.1.7\n\n");
  Matrix_Manipulation *Mod = new Matrix_Manipulation();
  Matrix Solution; UserCommand UC; std::string UserString;
  while(true) {
    printf(">>"); std::getline(std::cin,UserString);
    UC = ReadIn(UserString);
    if(UC.Command == "Add") {
      if((UC.M_1.size() == UC.M_2.size()) &&
      (UC.M_1[0].size() == UC.M_2[0].size())) {
        Solution = Mod->Add(UC.M_1, UC.M_2);
        Mod->printMatrix(Solution);
      } else
        printError("Illegal matrice sizes");
    } else if(UC.Command == "Sub") {
      if((UC.M_1.size() == UC.M_2.size()) &&
      (UC.M_1[0].size() == UC.M_2[0].size())) {
        Solution = Mod->Subtract(UC.M_1, UC.M_2);
        Mod->printMatrix(Solution);
      } else
        printError("Illegal matrice sizes");
    } else if(UC.Command == "Multiply") {
      if(UC.M_1[0].size() == UC.M_2.size()) {
        Solution = Mod->Multiply(UC.M_1, UC.M_2);
        Mod->printMatrix(Solution);
      } else
        printError("Illegal matrice sizes");
    } else if(UC.Command == "Smultiply") {
      if(UC.M_2.empty() && UC.Constant != INT_MIN) {
        Solution = Mod->S_Multiply(UC.M_1, UC.Constant);
        Mod->printMatrix(Solution);
      } else
        printError("Illegal format");
    } else if(UC.Command == "Transpose") {
      if(UC.M_2.empty() && UC.Constant == INT_MIN) {
        Solution = Mod->Transpose(UC.M_1);
        Mod->printMatrix(Solution);
      } else
        printError("Illegal format");
    } else if(UC.Command == "Echelon") {
      if(UC.M_2.empty() && UC.Constant == INT_MIN) {
        Solution = Mod->RR_Echelon_Form(UC.M_1);
        Mod->printMatrix(Solution);
      } else
        printError("Illegal format");
    } else if(UC.Command == "Inverse") {
      if(UC.M_2.empty() && UC.Constant == INT_MIN) {
        Solution = Mod->Inverse(UC.M_1);
        Mod->printMatrix(Solution);
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
      "   -Echelon (Reduces a matrix to row reduced echelon form)\n"
      "   -Inverse (Gives the inverse of a single given matrix)\n"
      "   -Exit\n"
      "  Legal Syntax\n"
      "   -Command{{Row 1}{Row 2}}\n"
      "   -Command{{Row 1}{Row 2}},{{Row 1}{Row 2}}\n"
      "   -Command{{Row 1}{Row 2}},Constant\n"
      "  Miscellaneous\n"
      "   -Rows/Columns must be the same length as other Rows/Columns\n"
      "   -Arithmetic is limited to 4 byte integers\n"
      "   -INT_MIN (-2147483647) is unavailable\n"
      "   -Unnecessary spaces are not recommended\n");
    } else
      printError(UC.Command);
  } return 0;
}
