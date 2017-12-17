#include "Database_Helpers.cpp"
#include <boost/version.hpp>



int main(int argc, char** args){
  printf("%s",BOOST_LIB_VERSION);
  if(argc!= 2){
    printf("Usage: ./a.exe [filename]\n");
    return 1;
  }
  std::string filename = args[1];
  Database* data = read_csv(filename);
  print_database(data);
  descriptive_info(data);
  std::vector<std::string> mat_names;
  for(int i = 0; i<data->width;i++){
    if(data->cols[i]->type == "num"){
      mat_names.push_back(data->cols[i]->varname);
    }
  }
  Matrix* new_mat = new Matrix(data, mat_names);
  print_matrix(new_mat);
  return 0;
}
