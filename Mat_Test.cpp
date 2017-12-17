#include "Database_Helpers.cpp"
#include <boost/version.hpp>



int main(int argc, char** args){
  printf("%s",BOOST_LIB_VERSION);
  if(argc!= 3){
    printf("Usage: ./a.exe [filename] [filename]\n");
    return 1;
  }
  std::string filename_1 = args[1];
  Database* data_1 = read_csv(filename_1);
  std::string filename_2 = args[2];
  Database* data_2 = read_csv(filename_2);
  Matrix* mat_1 = new Matrix(data_1);
  Matrix* mat_2 = new Matrix(data_2);
  printf("Matrix 1 has contents: \n");
  print_matrix(mat_1);
  printf("Matrix 2 has contents: \n");
  print_matrix(mat_2);
  printf("Matrix 1 + Matrix 2: \n");
  Matrix* result = new Matrix();
  mat_add(result, mat_1, mat_2);
  print_matrix(result);
  printf("Matrix 1 * Matrix 2: \n");
  mat_mult(result, mat_1, mat_2);
  print_matrix(result);
  printf("Matrix 1 * 10: \n");
  mat_smult(mat_1,10);
  print_matrix(mat_1);
  printf("Matrix 1/10: \n");
  mat_sdiv(mat_1, 10);
  print_matrix(mat_1);

  return 0;
}
