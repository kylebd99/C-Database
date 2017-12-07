#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <boost/variant.hpp>
#include <cctype>
#include <cfloat>
#include <memory>
#include <iterator>
#define NA -DBL_MAX
class Database;

bool is_num(std::string entry){
  if(entry=="N/A"){
    return true;
  }
  for(std::string::iterator i = entry.begin();i!=entry.end();i++){
    if(!isdigit(*i)&&!ispunct(*i)&&!isspace(*i)){
      return false;
    }
  }
  return true;
}

//This class is what the actual data will be stored in and will essentially represent a single
//variable in the dataset which can be either numeric or string
class Column{
public:
  Database* parent;
  int length;
  std::string type;
  std::string varname;
  std::string description;
  std::vector<boost::variant<double,std::string>> vals;
  Column(Database* p = NULL, int l = 0, std::string t = std::string(), std::string name = std::string(), std::string descript = std::string(), std::vector<boost::variant<double,std::string>> new_vals = std::vector<boost::variant<double,std::string>>())
  {
    parent = p;
    length = l;
    type = t;
    varname = name;
    description = descript;
    vals = new_vals;
  }
  void str_to_num(){
    if(type!="str"){
      fprintf(stderr,"Error: Attempt to convert a column already containing numeric values to numeric");
      return;
    }
    std::vector<boost::variant<double,std::string>>::iterator old_iter = vals.begin();
    int sz = vals.size();
    std::vector<boost::variant<double,std::string>> new_vec;
    for(int i = 0; i < sz; i++){
      std::string val = boost::get<std::string>(*old_iter);
      if(is_num(val) && val!="N/A"){
        new_vec.push_back(stod(val));
      }
      else{
        new_vec.push_back(NA);
      }
      old_iter++;
    }
    vals = new_vec;
    type = "num";
    return;
  }
  void num_to_str(){
    if(type!="num"){
      fprintf(stderr,"Error: Attempt to convert a column already containing string values to string");
      return;
    }
    std::vector<boost::variant<double,std::string>> new_vec;
    new_vec.resize(vals.size());
    for(std::vector<boost::variant<double,std::string>>::iterator i = vals.begin(), j = new_vec.begin(); i!=vals.end();i++,j++){
      *j = std::to_string(boost::get<double>(*i));
    }
    vals = new_vec;
    return;
  }
};



class Database{
public:
  int width;
  int length;
  std::vector<std::shared_ptr<Column>> cols;

  // Method which allows the creation  of columns
  void add_col(std::vector<boost::variant<double,std::string>> vals, std::string type, std::string name, std::string description){

    Column new_col = *(new Column(this, length, type, name, description, vals));
    cols.push_back(std::make_shared<Column>(new_col));
    width++;
    return;
  }
  // Param Varname, return 0 success return 1 fail not found col
  int del_col(std::string name){
    for(std::vector<std::shared_ptr<Column>>::iterator i = cols.begin(); i!=cols.end(); i++){
      if((*i)->varname!=name){
        cols.erase(i);
        return 0;
      }
    }
    return 1;
  }
  //TODO Method which allows the creation of rows
  int add_row(std::vector<boost::variant<double,std::string>> vals){
    if(vals.size()!=(unsigned)length){
      fprintf(stderr,"Error: Only inputed %d values but there are %d columns\n", (int) vals.size(), length);
      return 1;
    }
    std::vector<boost::variant<double,std::string>>::iterator j = vals.begin();
    for(std::vector<std::shared_ptr<Column>>::iterator i = cols.begin(); i!=cols.end();i++){
      if(((*i)->type == "str" && (*j).type()!=typeid(std::string))||((*i)->type == "num" && (*j).type()!=typeid(double))){
        fprintf(stderr,"Error: Wrong value type attempted for row addition");
        return 1;
      }
      (*i)->vals.push_back((*j));
      j++;
    }
  }
  //Method which allows the deletion of rows at a given zero-indexed location
  int del_row(int index){
    if(index>=length){
      fprintf(stderr,"Error: Attempting to delete a row at index %d beyond length of database %d", index,length);
      return 1;
    }
   for(std::vector<std::shared_ptr<Column>>::iterator i = cols.begin(); i!=cols.end();i++){
      (*i)->vals.erase(((*i)->vals).begin()+index);
   }
  }
};

class Matrix{

public:
  int rows;
  int cols;
  std::vector<double> data;
  Matrix();
  //TODO Matrix Multiplication
  //TODO Matrix Addition
  //TODO Scalar Multiplication
  //TODO Transposition
  //TODO Function to create matrix from a Database's cols vector
};
