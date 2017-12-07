#include "Database_Class.cc"
#include <iostream>
#include <fstream>
#include <list>
#include <boost/tokenizer.hpp>

// Function which reads in a csv and creates a Database
Database* read_csv(std::string filename){
  //Initialize a database object
  Database* new_data_addr = new Database;
  Database new_data = *new_data_addr;
  //Open the file as an input
  std::ifstream file;
  file.open(filename);
  //Read the first line of the file and create the proper columns all initialized as string values
  std::string line;
  getline(file,line);
  boost::tokenizer<boost::escaped_list_separator<char>> tok(line);
  int len = std::distance(tok.begin(),tok.end());
  for(boost::tokenizer<boost::escaped_list_separator<char>>::iterator i = tok.begin(); i!=tok.end();i++){
    std::vector<boost::variant<double,std::string>> new_vals;
    new_data.add_col(new_vals, "str", *i, "");
  }
  //Filling in the data for each column as a string value
  while(getline(file,line)){
    boost::tokenizer<boost::escaped_list_separator<char>> tok(line);
    boost::tokenizer<boost::escaped_list_separator<char>>::iterator i = tok.begin();
    boost::tokenizer<boost::escaped_list_separator<char>>::iterator end = tok.end();
    if(std::distance(i,end)!=len){
      fprintf(stderr,"Error: Rows not of uniform length in CSV file");
      return NULL;
    }
    for((void)i;i!=end;i++){
      new_data.cols[std::distance(tok.begin(),i)]->vals.push_back(*i);
    }
    new_data.length++;
  }
  //Check the type of each column
  bool num_cols[new_data.width];
  for(int i = 0; i<new_data.width; i++){
    num_cols[i] = true;
    for(int j = 0; j<new_data.length; j++){
      if(!is_num(boost::get<std::string>(new_data.cols[i]->vals[j]))){
        num_cols[i] = false;
      }
    }
    if(num_cols[i]){
      new_data.cols[i]->str_to_num();
    }
  }
  return new_data_addr;
}
//TODO Function which prints out the data in a database
void print_database(Database* data){
  for(int i = 0; i< data->width; i++){
    printf("%s  ", data->cols[i]->varname.c_str());
  }
  printf("\r\n");
  for(int j = 0; j< data->length; j++){
    for(int i = 0; i< data->width; i++){
      if(data->cols[i]->type == "str"){
        printf("%s  ", boost::get<std::string>(data->cols[i]->vals[j]).c_str());
      }else{
        printf("%f  ", boost::get<double>(data->cols[i]->vals[j]));
      }
    }
    printf("\r\n");
  }
  return;
}
//TODO Function which calculates mean data for each numeric column

//TODO Function which does linear regression
