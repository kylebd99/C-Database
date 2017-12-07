#include "Database_Class.cpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <boost/tokenizer.hpp>

// Function which reads in a csv and creates a Database
Database* read_csv(std::string filename){

  //Initialize a database object
  Database* new_data = new Database;
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
    std::string name = (*i);
    if(name.find("\r")!=std::string::npos){
      name.replace(name.find("\r"),1,"");
    }
    if(name.empty()){
      name = "N/A";
    }
    new_data->add_col(new_vals, "str", name, "");
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
      //Delete any pesky carriage return characters
      std::string new_val = (*i);
      if(new_val.find("\r")!=std::string::npos){
        new_val.replace(new_val.find("\r"),1,"");
      }
      if(new_val.empty()){
        new_val = "N/A";
      }
      new_data->cols[std::distance(tok.begin(),i)]->vals.push_back(new_val);
    }

    new_data->length++;
  }
  //Check the type of each column
  bool num_cols[new_data->width];
  for(int i = 0; i<new_data->width; i++){
    num_cols[i] = true;
    for(int j = 0; j<new_data->length; j++){
      if(!is_num(boost::get<std::string>(new_data->cols[i]->vals[j]))){
        num_cols[i] = false;
      }
    }
    if(num_cols[i]){
      new_data->cols[i]->str_to_num();
    }
  }
  return new_data;
}
//Function which prints out the data in a database row by row
void print_database(Database* data){
  printf("Printing Out Data....\n");
  //Begin by printing variable names
  for(int i = 0; i< data->width; i++){
    printf("%-12.12s  ", data->cols[i]->varname.c_str());
  }
  printf("\n");
  //print out each line of data
  for(int j = 0; j< data->length; j++){
    for(int i = 0; i< data->width; i++){
      if(data->cols[i]->type == "str"){
        printf("%-12.12s  ", boost::get<std::string>(data->cols[i]->vals[j]).c_str());
      }else{
        if(boost::get<double>(data->cols[i]->vals[j])!=NA){
          printf("%-12.3f  ", boost::get<double>(data->cols[i]->vals[j]));
        }else{
          printf("%-12.12s  ","NA");
        }
      }
    }
    printf("\n");
  }
  return;
}
//Function which calculates mean data for each numeric column
void descriptive_info(Database* data){
  printf("Printing out descriptive statistics for numeric columns....\n");
  //Create vectors to hold names and descriptive values
  std::vector<std::string> names;
  std::vector<double> means;
  std::vector<double> sdevs;
  std::vector<double> ranges;
  //Iterate through each variable
  for(int i = 0; i<data->width; i++){
    //Do nothing with string columns
    if(data->cols[i]->type == "str"){
      continue;
    }
    //intialize values for each value and count the useable observations for
    //calculation purposes
    names.push_back(data->cols[i]->varname);
    means.push_back(0);
    ranges.push_back(0);
    sdevs.push_back(0);
    int c_obs = 0;
    double r_min = DBL_MAX;
    double r_max = -DBL_MAX;
    for(int j = 0; j<data->length; j++){
      double val = boost::get<double>(data->cols[i]->vals[j]);
      if(val == NA){
        continue;
      }
      //Calculate Max and Mins
      if(val>r_max){
        r_max = val;
      }
      if(val<r_min){
        r_min = val;
      }
      means[means.size()-1]+= val;
      c_obs++;
    }
    means[means.size()-1] = means[means.size()-1]/c_obs;
    ranges[ranges.size()-1] = r_max-r_min;
    for(int j = 0; j<data->length; j++){
      double val = boost::get<double>(data->cols[i]->vals[j]);
      if(val == NA){
        continue;
      }
      sdevs[sdevs.size()-1]+=abs(val-means[sdevs.size()-1]);
    }
    sdevs[sdevs.size()-1] = sdevs[sdevs.size()-1]/c_obs;
  }
  printf("          ");
  for(unsigned int i = 0; i<names.size(); i++){
    printf("%-12.12s", names[i].c_str());
  }
  printf("\nMean:     ");
  for(unsigned int i = 0; i<means.size(); i++){
    printf("%-12.3f", means[i]);
  }
  printf("\nStdDev:   ");
  for(unsigned int i = 0; i<sdevs.size(); i++){
    printf("%-12.3f", sdevs[i]);
  }
  printf("\nRange:    ");
  for(unsigned int i = 0; i<ranges.size(); i++){
    printf("%-12.3f", ranges[i]);
  }
}
//TODO Function which does linear regression
