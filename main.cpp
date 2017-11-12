#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstdarg>
#include<curses.h>
#include <ncurses.h>

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
//end of Matrix Class


Matrix::Matrix()
{
  num_rows = num_col = 0;
  values = NULL;
}

Matrix::~Matrix()
{
reset();
}

Matrix::Matrix(int num_rows, int num_col, int initialization, double initializationValue)
{
    this->num_rows = num_rows;
    this->num_col = num_col;
    if((num_col*num_rows) == 0){values = NULL; return;}

    values = new double* [num_rows];
    for(int iR = 0; iR<num_rows; iR++ )
    {
      values[iR] = new double[num_col];
      for(int iC = 0; iC<num_col; iC++)
      {
        switch (initialization)
        {
          case MI_ZEROS: values[iR][iC];
          case MI_ONES: values[iR][iC] = 1; break;
          case MI_EYE: values[iR][iC] = (iR==iC)?1:0; break;
          case MI_RAND: values[iR][iC] = (rand()%1000000)/1000000.0; break;
          case MI_VALUE: values[iR][iC] = initializationValue; break;
        }
      }
    }
}


Matrix::Matrix(int num_rows,int num_col, double first, ...)
{
  this-> num_rows = num_rows;
  this-> num_col = num_col;
  if ((num_col*num_rows) == 0 ){values = NULL; return;}

  values = new double* [num_rows];
  va_list va;
  va_start(va, first);

  for(int iR=0; iR<num_rows; iR++ )
  {
    values[iR] = new double[num_col];

    for(int iC=0; iC<num_col; iC++)
    {
      values[iR][iC] = (iC==0 && iR==0)?first : va_arg(va, double);
    }
  }
  va_end(va);
}

Matrix::Matrix(const Matrix& m)
{
  num_rows = num_rows = 0;
  values = NULL;
  copy(m);
}


void Matrix::copy(const Matrix& m)
{
  reset();

  this-> num_rows = m.num_rows;
  this-> num_col = m.num_col;
  if ((num_col*num_rows) == 0 ){values = NULL; return;}

  values = new double*[num_rows];
  for(int iR=0;iR<num_rows;iR++)
  {
    values[iR] = new double[num_col];
    for(int iC=0;iC<num_col;iC++)
    {
    values[iR][iC] = m.values[iR][iC];
    }
  }
}


void Matrix::copy(string s)
{
  reset();

  char* buffer = new char[s.length()+1];
  strcpy(buffer, s.c_str());
  //char* lineContext;
  const char* lineSeparators = ";\r\n";
  char* line = strtok(buffer, lineSeparators);
  while(line)
    {
      Matrix row;
      // char* context;
      const char* separators = " []";
      char* token = strtok(line, separators);
        while(token)
        {
          Matrix item = atof(token);
          row.addColumn(item);
          token = strtok(NULL, separators);
        }
        if(row.num_col>0 && (row.num_col==num_col || num_rows==0))
        addRow(row);
        line = strtok(NULL, lineSeparators);
    }
    delete[] buffer;
  }



Matrix::Matrix(double d)
{
  num_rows = num_rows = 0;
  values = NULL;
  copy(d);
}


void Matrix::copy(double d)
{
  reset();

  this->num_rows = 1;
  this->num_col = 1;
  values = new double*[1];
  values[0] = new double[1];
  values[0][0] = d;
}



void Matrix::reset()
{
  if (values)
  {
    for(int i=0; i<num_rows; i++){delete[] values[i];}
    delete[] values;
  }
  num_rows = num_col = 0;
  values = NULL;
}


Matrix Matrix::operator=(const Matrix& m)
{
  copy(m);
  return *this;
}

Matrix Matrix::operator=(double d)
{
  copy(d);
  return *this;
}

void Matrix::add(const Matrix& m)
{
  if(num_rows!=m.num_rows||num_col!=m.num_col)
    throw("Invalid Matrix dimensions for add operation");

  for(int iR=0; iR<num_rows; iR++ )
    for(int iC=0; iC<num_col; iC++)
      values[iR][iC] += m.values[iR][iC];
}

void Matrix::operator+=(Matrix& m)
{
  add(m);
}


void Matrix::operator+=(double d)
{
  add(Matrix(num_rows, num_col, MI_VALUE, d));
}


Matrix Matrix::operator+(Matrix& m)
{
  Matrix r = *this;
  r += m;
  return r;
}


Matrix Matrix::operator+(double d)
{
  Matrix r = *this;
  r += d;
  return r;
}


void Matrix::sub(const Matrix& m)
{
  if(num_rows!=m.num_rows||num_col!=m.num_col)
    throw("Invalid Matrix dimensions for sub operation");

  for(int iR=0; iR<num_rows; iR++ )
    for(int iC=0; iC<num_col; iC++)
      values[iR][iC] -= m.values[iR][iC];
}

void Matrix::operator-=(Matrix& m)
{
  sub(m);
}


void Matrix::operator-=(double d)
{
  sub(Matrix(num_rows, num_col, MI_VALUE, d));
}


Matrix Matrix::operator-(Matrix& m)
{
  Matrix r = *this;
  r -= m;
  return r;
}


Matrix Matrix::operator-(double d)
{
  Matrix r = *this;
  r -= d;
  return r;
}


void Matrix::mul(Matrix& m)
{
    if(num_col!=m.num_rows)
      throw("Invalid dimensions for mul operation");

    Matrix r(num_rows, m.num_col);
	for(int i=0;i<num_rows;i++)
		for(int s=0;s<m.num_col;s++)
		{
			r.values[i][s] = 0;
		}

    for(int iC=0; iC<num_col; iC++)
      for(int iR=0; iR<num_rows; iR++)
      {
        for(int k=0; k<m.num_col; k++)
          r.values[iR][k] += values[iR][iC] * m.values[iC][k];
      }
      copy(r);
}

void Matrix::operator*=(Matrix& m)
{
  mul(m);
}

void Matrix::operator*=(double d)
{
    for(int iR=0;iR<num_rows;iR++)
      for(int iC=0;iC<num_col;iC++)
        values[iR][iC] *= d;
}


Matrix Matrix::operator*(Matrix& m)
{
  Matrix r = *this;
  r*=m;
  return r;
}


Matrix Matrix::operator*(double d)
{
  Matrix r = *this;
  r*=d;
  return r;
}

Matrix Matrix::operator++()
{
  const double d = 1.0;
  add(Matrix(num_rows, num_col, MI_VALUE, d));
  return  *this;
}

Matrix Matrix::operator++(int)
{
  Matrix c = *this;
  add(Matrix(num_rows, num_col, MI_VALUE, 1.0));
  return  c;
}


Matrix Matrix::operator--()
{
  add(Matrix(num_rows, num_col, MI_VALUE, -1.0));
  return *this;
}

Matrix Matrix::operator--(int)
{
  Matrix c = *this;
  add(Matrix(num_rows, num_col, MI_VALUE, -1.0));
  return  c;
}

Matrix Matrix::operator-()
{
  for(int iR=0;iR<num_rows;iR++)
    for(int iC=0;iC<num_col;iC++)
      values[iR][iC] = -values[iR][iC];
  return *this;
}

Matrix Matrix::operator+()
{
  return *this;
}


void Matrix::setSubMatrix(int r, int c, Matrix& m)
{
  if ((r+m.num_rows)>num_rows||(c+m.num_col)>num_col)
    throw("Invalid matrix dimensions for this operation");

    for(int iR =0; iR < num_rows; iR++)
      for(int iC=0; iC<num_col; iC++)
        values[iR+r][iC+c] = m.values[iR][iC];
}


Matrix Matrix::getSubMatrix(int r, int c, int nr, int nc)
{
  if((r+nr)>num_rows || (c+nc)>num_col  )throw("Invalid matrix dimension");

  Matrix m(nr, nc);
  for(int iR=0;iR<m.num_rows;iR++)
    for(int iC=0;iC<m.num_col;iC++)
      m.values[iR][iC] = values[r+iR][c+iC];
  return m;
}


void Matrix::addColumn(Matrix& m)
{
  Matrix n(max(num_rows, m.num_rows), num_col+m.num_col);
  n.setSubMatrix(0, 0, *this);
  n.setSubMatrix(0, num_col, m);
  *this = n;
}

void Matrix::addRow(Matrix& m)
{
  Matrix n(num_rows+n.num_rows, max(num_col,m.num_col));
  n.setSubMatrix(0, 0, *this);
  n.setSubMatrix(num_rows, 0, m);
  *this = n;
}





Matrix Matrix::getCofactor(int r, int c)
{
  if(num_rows<=1 || num_col<=1)throw("Invalid matrix dimensions");

  Matrix m(num_rows-1, num_col-1);

  for(int iR=0; iR<m.num_rows; iR++)
    for(int iC=0; iC<m.num_col; iC++)
    {
      int sR = (iR<r)? iR : iR+1;
      int sC = (iC<c)? iC : iC+1;
      m.values[iR][iC] = values[sR][sC];
    }
    return m;
}




Matrix Matrix::getMinormatrix()
{
Matrix c(num_rows,num_col,0);
Matrix m;
double d;
for(int i=0;i<num_rows;i++)
for(int j=0;j<num_col;j++)
{

m=this->getCofactor(i,j);
d=m.getDeterminant();
c.values[i][j]=d;




}

return c;


}
void print(Matrix m )
{
  for(int i=0; i<m.num_rows; i++)
  {
    for(int j=0; j<m.num_col; j++)
    {
      cout<<m.values[i][j]<<" ";
    }
    cout<<endl;
  }
}

Matrix Matrix::cofactor()
{
 Matrix c(num_rows,num_col,0);
 c=this->getMinormatrix();



 for(int i=0;i<num_rows;i++)
  for(int j=0;j<num_col;j++)
   {
    if((i+j)%2==1)
    c.values[i][j]=-c.values[i][j];
    else
    c.values[i][j]=c.values[i][j];




   }
   return c;





}





double Matrix::getDeterminant()
{
  if(num_rows!=num_col)throw("Invalid matrix dimensions");
  if(num_rows==1 && num_col==1)return values[0][0];

  double value = 0 , m = 1;
  for(int iR=0; iR<num_rows; iR++)
  {
    value+= m * values[0][iR] * getCofactor(0, iR).getDeterminant(); m *= -1;
  }
  return value;
}
string Matrix::getString()
{
string s;
for(int iR=0;iR<num_rows;iR++)
{
for(int iC=0;iC<num_col;iC++)
{
char buffer[50];
sprintf(buffer, "%g\t", values[iR][iC]);
s += buffer;
}
s+="\n";
}
return s;
}

// istream& operator >> (istream &is, Matrix& m)
// {
//   string s;
//   getline(is, s, ']');
//   s+="]";
//   m = Matrix(s);
//   return is;
// }
// ostream& operator << (ostream &os, Matrix& m)
// {
//   os<<m.getString();
//   return os;
// }

Matrix Matrix::getTranspose()

{

  Matrix temp(num_col, num_rows, 0);

  for(int iR=0;iR<num_rows;iR++)
 {
   for(int iC=0;iC<num_col;iC++)

   {
   temp.values[iC][iR] = values[iR][iC];
   }
 }
 return temp;
}

Matrix Matrix::multiply_by_no( double d)
{
  Matrix m;
  m=*this;
   for(int i=0;i<num_rows;i++)

     for(int j=0;j<num_col ;j++)
     {
        m.values[i][j]=(m.values[i][j])*d;
     }
   return m;


}




Matrix Matrix::inverse()
{
  Matrix c;
  Matrix s;
  Matrix inversed_mat;
  c=*this;

  double d,one_over_det;
  d=(*this).getDeterminant();

  one_over_det=1/d;

  c=this->cofactor();

  s=c.getTranspose();

  inversed_mat=s.multiply_by_no(one_over_det);

  return inversed_mat;






}

Matrix Matrix::division(Matrix a, Matrix b)
{
Matrix output;
Matrix c;
c=b.inverse();
output=a*c;
return output;
}


Matrix Matrix::operator/(Matrix b)
{
   Matrix c;
   c=this->division(*this,b);
   return c;


}

Matrix Matrix::operator/(double d)
{
Matrix c;
double number=1/d;
c=this->multiply_by_no(number);
return c;

}

void Matrix::operator/=( Matrix b)
{
*this=this->division(*this,b);


}

void Matrix::operator/=(double b)
{
  double number =1/b;

*this=this->multiply_by_no(number);


}




int main()
{
  Matrix c(3, 3, -1.443, 0.3246, 1.82425, -1.663, -0.557, 3.9724, 0.409, 0.0868, 0.6839);
  Matrix n(3,3,3.0,0.0,2.0,2.0,0.0,-2.0,0.0,1.0,1.0);
  Matrix m(3, 3, 1.2, 2.1, 3.4, 4.1, 7.2, 3.4, 7.1, 5.2, 4.6);
  Matrix a(2,2,1.0,2.0,2.0,2.0);
  Matrix b(2,2,3.0,2.0,1.0,1.0);
  cout<<">>>"<<"Matrix A ="<<endl;;
  /*print(n);
  cout<<">>> "<<"Matrix B ="<<endl;;
  print(m);
  cout<<">>> "<<"A + B = "<<endl;
  print(m+n);
  cout<<">>> "<<"A - B = "<<endl;
  print(n-m);
  cout<<">>> "<<"A * B = "<<endl;
  print(m*n);
  cout<<">>> "<<"B / A = "<<endl;
  print(c);
  cout<<">>> "<<"A' = "<<endl;
  Matrix k = n.getTranspose();*
  Matrix d=n.inverse();
  print(d);


  print(k);*/

Matrix l;
l=a/b;
print(l);

  


  return 0;
}