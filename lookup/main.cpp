#include<mpi.h> 
#include<stdio.h>
#include "lookup.cpp"

using std :: cout;
using std :: endl;

int main( int argc, char *argv[] )
{
  int n = 100;  double x[n] , y[n];

  for ( int i = 0 ; i < n ; ++i ) {  x[i] = i; y[i] = i*i; }

//   double xval = 2.5;  double yval = lookupVal(n,x,y,xval);
//   double xval_arr[n] = 2.5 * n;
//   double yval_arr[n] 
  double xval_arry[n];
  double yval_arry[n];
  for ( int i = 0 ; i < n ; ++i ) {  xval_arry[i] = i;}
  for ( int i = 0 ; i < n ; ++i ) {
    yval_arry[i] = lookupVal(n,x,y,xval_arry[i]);
   }
  for ( int i = 0 ; i < n ; ++i ) {
    cout << "xval_arry[" << i << "] = " << xval_arry[i] << " yval_arry[" << i << "] = " << yval_arry[i] << endl;}
//   cout << "For xval = " << xval_arry[2] << " yval =  " << yval_arry[2] << endl;

  return 0;
}
