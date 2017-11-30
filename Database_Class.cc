#include "Database_Helpers.h"
#include <cstdlib>
#include <algorithm>

typedef union value{
  string strval;
  double numval;
};


class Database{
public:
  int width;
  int length;
  vector<std::unique_ptr(Column)> cols;
  //TODO Method which allows the creation of columns
  void add_num_col(std::vector<double> vals, string name, string description){
    Num_Column new_col = Num_Column(this,name,description,vals);
    cols.push_back(std::make_unique<Num_Column>(new_col));
    width++;
  }
  void add_str_col(std::vector<string> vals, string name, string description){
    Num_Column new_col = Str_Column(this,name,description,vals);
    cols.push_back(std::make_unique<Num_Column>(new_col));
    width++;
  }
  // Param Varname, return 0 success return 1 fail not found col
  int del_col(string name){
    for(std::iterator i = cols.begin(); i!=cols.end(); i++){
      if(strcmp(*i->varname,name)==0){
        cols.erase(i);
        return 0;
      }
    }
    return 1;
  }
  //TODO Method which allows the creation of rows
  //TODO Method which allows the deletion of rows

};

class Column{
public:
  Database parent;
  int length;
  string type;
  string varname;
  string description;
  vector<value> vals;
  Column(){
    type = "";
    parent  = NULL;
    varname = "";
    description = "";
    vals = std::vector<value>;
    length = 0;
  };
  Column(string t, Database p, string name, string descript, vector<value> new_vals){
    type = t;
    parent = p;
    varname = name;
    description = descript;
    vals = new_vals;
    length = new_vals.size();
  };
  //Returns a numeric equivalent column
  void str_to_num(){
    if(strcmp(type,"num")!=0){
      fprintf(stderr,"Error: Attempt to convert a column already containing numeric values to numeric");
      return;
    }
    vector<value>::iterator old_iter = vals.begin();
    int sz = vals.size();
    vector<double> new_vec;
    for(int i = 0; i < sz; i++){
      double val = atof(*old_iter);
      if(val!=0){
        new_vec.push_back(val):
      }
      else{
        new_vec.push_back(NULL);
      }
      old_iter++;
    }
    vals = new_vec;
    return;
  };
  void num_to_str(){
    if(strcmp(type,"str")!=0){
      fprintf(stderr,"Error: Attempt to convert a column already containing string values to string");
      return;
    }
    std::vector<value> new_vec;
    new_vec.resize(vals.size());
    std:transform(vals.begin(),vals.end(),new_vec.begin(),std::to_string())
    vals = new_vec;
    return;
  };
};

class Matrix{

public:
  int rows;
  int cols;
  double data[][];
  Matrix(){
    rows = 0;
    cols = 0;
    data = NULL;
  };
  //TODO Matrix Multiplication
  //TODO Matrix Addition
  //TODO Scalar Multiplication
  //TODO Transposition
  //TODO Function to create matrix from a Database's cols vector
};
