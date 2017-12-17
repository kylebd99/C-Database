#ifndef Matrix_H
#define Matrix_H
#include "Database_Class.cpp"

class Matrix{
public:
  int rows;
  int cols;
  std::vector<double> data;
  // Default constructor
  Matrix(){
    rows = 0;
    cols = 0;
    data = *new std::vector<double>;
  }
  // Constructor with list of variable names
  Matrix(Database* p, std::vector<std::string> col_names){
    cols = col_names.size();
    rows = p->length;
    std::vector<std::shared_ptr<Column>> input_cols;
    for(std::vector<std::string>::iterator i = col_names.begin();i!=col_names.end();i++){
        for(int j = 0; j<p->width;j++){
          if(*i == p->cols[j]->varname){
            input_cols.push_back(p->cols[j]);
          }
        }
    }
    for(int i = 0; i<rows;i++){
      for(int j = 0;j<cols;j++){
        data.push_back(boost::get<double>(input_cols[j]->vals[i]));
      }
    }
  }
  // Constructor without list of variables
  Matrix(Database* p){
      std::vector<std::shared_ptr<Column>> input_cols;
      for(int i =0; i<p->width;i++){
        if(p->cols[i]->type=="num"){
          input_cols.push_back(p->cols[i]);
        }
      }
      cols = input_cols.size();
      rows = p->length;
      for(int i = 0; i<rows;i++){
        for(int j = 0;j<cols;j++){
          data.push_back(boost::get<double>(input_cols[j]->vals[i]));
        }
      }
    }
  // Function to retrieve values from a matrix
  double get(int row, int col){
    return data[row*cols+col];
  }
};
// Function to multiply matrices
void mat_mult(Matrix* dest, Matrix* left, Matrix* right){
  if(left->cols!=right->rows){
    fprintf(stderr,"Error: Columns of left matrix do not match rows of right matrix\n");
    return;
  }
  dest->data = *new std::vector<double>;
  dest->rows = left->rows;
  dest->cols = right->cols;
  for(int i = 0; i<dest->rows; i++){
    for(int j = 0; j<dest->cols; j++){
      double new_data = 0;
      for(int k =0; k<left->cols;k++){
        new_data += left->get(i,k)*right->get(k,i);
      }
      dest->data.push_back(new_data);
    }
  }
  return;
};
// Function to add matrices
void mat_add(Matrix* dest, Matrix* left, Matrix* right){
  if(left->cols!=right->cols||left->rows!=right->rows){
    fprintf(stderr,"Error: Dimensions of left matrix do not dimensions of right matrix\n");
    return;
  }
  dest->data = *new std::vector<double>;
  dest->rows = left->rows;
  dest->cols = right->cols;
  for(int i = 0; i<dest->rows; i++){
    for(int j = 0; j<dest->cols; j++){
      dest->data.push_back(left->get(i,j)+right->get(i,j));
    }
  }
  return;
};
//Function to subtract matrices
void mat_sub(Matrix* dest, Matrix* left, Matrix* right){
  if(left->cols!=right->cols||left->rows!=right->rows){
    fprintf(stderr,"Error: Dimensions of left matrix do not dimensions of right matrix\n");
    return;
  }
  dest->data = *new std::vector<double>;
  dest->rows = left->rows;
  dest->cols = right->cols;
  for(int i = 0; i<dest->rows; i++){
    for(int j = 0; j<dest->cols; j++){
      dest->data.push_back(left->get(i,j)-right->get(i,j));
    }
  }
  return;
};
//TODO Transposition
void mat_trans(Matrix* m){
  Matrix* new_mat = new Matrix;
  new_mat->cols = m->rows;
  new_mat->rows = m->cols;
  for(int i = 0; i<new_mat->rows;i++){
    for(int j = 0; j<new_mat->cols; j++){
      new_mat->data.push_back(m->get(j,i));
    }
  }
  *m = *new_mat;
  return;
};
//Scalar Multiplication
void mat_smult(Matrix* m, double k){
  for(int i = 0; i<m->rows;i++){
    for(int j = 0; j<m->cols; j++){
      m->data[i*m->cols+j]= (m->get(i,j)*k);
    }
  }
  return;
};
//Scalar division
void mat_sdiv(Matrix* m, double k){
  for(int i = 0; i<m->rows;i++){
    for(int j = 0; j<m->cols; j++){
      m->data[i*m->cols+j]= (m->get(i,j)/k);
    }
  }
  return;
};
//Scalar addition
void mat_sadd(Matrix* m, double k){
  for(int i = 0; i<m->rows;i++){
    for(int j = 0; j<m->cols; j++){
      m->data[i*m->cols+j]= (m->get(i,j)+k);
    }
  }
  return;
};
//Scalar subtraction
void mat_ssub(Matrix* m, double k){
  for(int i = 0; i<m->rows;i++){
    for(int j = 0; j<m->cols; j++){
      m->data[i*m->cols+j]= (m->get(i,j)-k);
    }
  }
  return;
};
#endif
