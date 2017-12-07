#include "Database_Helpers.cc"


int main(int argc, char** args){

  if(argc!= 2){
    printf("Usage: ./a.exe [filename]\n");
    return 1;
  }
  std::string filename = args[1];
  Database* data = read_csv(filename);
  print_database(data);
  descriptive_info(data);
  return 0;
}
