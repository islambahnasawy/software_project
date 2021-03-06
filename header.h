#include <iostream>
#include <ostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstdarg>
//#include<curses.h>
//#include <ncurses.h>
#include <algorithm>
using namespace std;


class Matrix{

public:
  int num_rows, num_col;



  double** values;


  //hussien
  Matrix();
  ~Matrix();
//Doaa
 enum MI{MI_ZEROS, MI_ONES, MI_EYE, MI_RAND, MI_VALUE};

//rowan
  Matrix(int num_rows, int num_col, int initialization= MI_ZEROS, double initializationValue = 0.0 );
  Matrix(int num_rows, int num_col, double first, ...);
  Matrix(const Matrix& m);
  Matrix(double d);
  Matrix(std::string s);


//rawan
  void copy(const Matrix& m);
  void copy(double d);
  void copy(string s);
  void reset();

  string getString();

  Matrix operator=(const Matrix& m);
  Matrix operator=(double d);
  Matrix operator=(string s);

//hossam
  void add(const Matrix& m);
  void operator+=(Matrix& m);
  void operator+=(double d);
  Matrix operator+(Matrix& m);
  Matrix operator+(double d);


  void sub(const Matrix& m);
  void operator-=(Matrix& m);
  void operator-=(double d);
  Matrix operator-(Matrix& m);
  Matrix operator-(double d);

//hussien
  void mul(Matrix& m);
  void operator*=(Matrix& m);
  void operator*=(double d);
  Matrix operator*(Matrix& m);
  Matrix operator*(double d);

//Doaa & zeinab
 Matrix division(Matrix a, Matrix b);

  Matrix multiply_by_no( double d);
  Matrix getMinormatrix();
  Matrix cofactor();
  Matrix operator/(Matrix b);
  Matrix inverse();
  Matrix operator/(double d);
  void operator/=( Matrix b);
  void operator/=(double b);

//bahnsasay
  Matrix operator++();//Pre Increment
  Matrix operator++(int);//Post Increment ,int is not used
  Matrix operator--();//Pre Increment
  Matrix operator--(int);//Post Increment ,int is not used

  Matrix operator-();
  Matrix operator+();


friend istream& operator >> (istream &is, Matrix& C); //Stream
friend ostream& operator << (ostream &os, Matrix& C); //Stream

//mostafa
  void setSubMatrix(int iR,int iC, Matrix& m);
  Matrix getSubMatrix(int r, int c, int nr, int nc);
  Matrix getCofactor(int r,int c);

  void addColumn(Matrix& m);
  void addRow(Matrix& m);

//samir
  double& operator[](int i){return values[i/num_col][i%num_col];}
  double& operator()(int i){return values[i/num_col][i%num_col];}
  double& operator()(int r, int c){return values[r][c];}

  int getn(){return num_rows*num_col;};
  int getnR(){return num_rows;};
  int getnC(){return num_col;};
//doaa & zienab
  double getDeterminant();
  Matrix getTranspose();
  Matrix getInverse();

};
