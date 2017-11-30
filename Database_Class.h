#include "Database_Helpers.h"
#include <stdlib.h>
#include <algorithm.h>

#define INT 1
#define STR 2

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

}

class Column{
public:
  Database parent;
  int length;
  string type;
  string varname;
  string description;
}

class Str_Column: public Column{
public:
  vector<string> vals;
  Num_Column(){
    type = "";
    parent  = NULL;
    varname = "";
    description = "";
    vals = std::vector<string>;
    length = 0;
  };
  //constructor
  Str_Column(Database p, string name, string descript, vector<string> new_vals){
    type = "str";
    parent = p;
    varname = name;
    description = descript;
    vals = new_vals;
    length = new_vals.size();
  };
  //Returns a numeric equivalent column
  Num_Column str_to_num(){
    vector<string>::iterator old_iter = vals.begin();
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
    return Num_Column(parent,varname,description,new_vec);
  };
}

class Num_Column: public Column{
public:
  vector<double> vals;
  Num_Column(){
    type = "";
    parent  = NULL;
    varname = "";
    description = "";
    vals = std::vector<double>;
    length = 0;
  };
  Num_Column(Database p, string name, string descript, vector<double> new_vals){
    type = "num";
    parent = p;
    varname = name;
    description = descript;
    vals = new_vals;
    length = new_vals.size();
  };
  Str_Column num_to_str(){
    std::vector<string> new_vec;
    new_vec.resize(vals.size());
    std:transform(vals.begin(),vals.end(),new_vec.begin(),std::to_string())
    return Str_Column(parent, varname, description, new_vec);
  }
}

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
}
