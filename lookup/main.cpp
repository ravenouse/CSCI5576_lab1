#include<mpi.h> 
#include<stdio.h>
#include "lookup.cpp"

using std :: cout;
using std :: endl;

int main( int argc, char *argv[] )
{
  int n = 100;  double x[n] , y[n];

  for ( int i = 0 ; i < n ; ++i ) {  x[i] = i; y[i] = i*i; }

//   double xval_arry[n];
//   double yval_arry[n];
//   for ( int i = 0 ; i < n ; ++i ) {
//     yval_arry[i] = lookupVal(n,x,y,xval_arry[i]);
//    }
//   for ( int i = 0 ; i < n ; ++i ) {
//     cout << "xval_arry[" << i << "] = " << xval_arry[i] << " yval_arry[" << i << "] = " << yval_arry[i] << endl;}
//   cout << "For xval = " << xval_arry[2] << " yval =  " << yval_arry[2] << endl;

  double xval_arry[n];
  double yval_arry[n];
  for ( int i = 0 ; i < n ; ++i ) {  xval_arry[i] = i;}

  float elems_per_proc = n/4;

  float sub_xval_arry[int(elems_per_proc)];
  MPI_Init ( &argc , &argv );

  MPI_Scatter(xval_arry, elems_per_proc, MPI_FLOAT, sub_xval_arry, elems_per_proc, MPI_FLOAT, 0, MPI_COMM_WORLD);

  float sub_yval_arry[int(elems_per_proc)];

    for (int i = 0; i < elems_per_proc; i++) {
        sub_yval_arry[i] = lookupVal(int(n/4),x,y,sub_xval_arry[i]);
        cout<< "sub_yval_arry[" << i << "] = " << sub_yval_arry[i] << endl;
    }

  MPI_Gather(sub_yval_arry, elems_per_proc, MPI_FLOAT, yval_arry, elems_per_proc, MPI_FLOAT, 0, MPI_COMM_WORLD);

//   for ( int i = 0 ; i < n/4 ; ++i ) {  xval_arry[i] = i;}
//   for ( int i = 0 ; i < n ; ++i ) {
//     yval_arry[i] = lookupVal(n,x,y,xval_arry[i]);
//    }
  for ( int i = 0 ; i < n ; ++i ) {
    cout << "xval_arry[" << i << "] = " << xval_arry[i] << " yval_arry[" << i << "] = " << yval_arry[i] << endl;}

  return 0;
}
