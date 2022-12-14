#include<mpi.h> 
#include<stdio.h>
#include "lookup.cpp"

using std :: cout;
using std :: endl;
using std :: string;

// helper function to print arrays
void printArray(string arrayName , int n , double *array , int myPE)
{
  for ( int i = 0 ; i < n ; ++i )
    cout << "myPE: " << myPE << " " << arrayName << "[" << i << "] = " << array[i] << endl;
}

int main( int argc, char *argv[] ){
  // initialize the MPI
  MPI_Init ( &argc , &argv );
  int numPE = 4;      //  This must match the -n argument of mpiriun
  int myPE ;          //  My PE number, 0, 1, 2, ...
  MPI_Comm_size( MPI_COMM_WORLD , &numPE ); 
  MPI_Comm_rank( MPI_COMM_WORLD , &myPE  ); 
  printf("Hello, world from PE %d\n",myPE);

  // initialize the arrays as the table to be looked up
  // Size of the table n = 100
  int n = 100;  double x[n] , y[n];
  for ( int i = 0 ; i < n ; ++i ) {  x[i] = i; y[i] = i*i; }

  // initialized the arrays of values to be looked up
  // size of the array m = 40
  int m = 40; 
  double xval_array[m];
  double yval_array[m];
  // estalish the values for the xval_array
  if ( myPE == 0 ) {
    for ( int i = 0 ; i < m ; ++i ) {  xval_array[i] = i;}
  }

  // initialize the subarry for multiple processors
  // try with 4 processors
  int elems_per_proc = m/4; //should be integer
  double sub_xval_array[int(elems_per_proc)];
  double sub_yval_array[int(elems_per_proc)];

  MPI_Scatter(xval_array, elems_per_proc, MPI_DOUBLE, 
              sub_xval_array, elems_per_proc, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  // call the lookup function 
  for (int i = 0; i < elems_per_proc; i++) {
      sub_yval_array[i] = lookupVal(n,x,y,sub_xval_array[i], myPE);
  }
  MPI_Gather(sub_yval_array, elems_per_proc, MPI_DOUBLE, 
            yval_array, elems_per_proc, MPI_DOUBLE, 0, MPI_COMM_WORLD);

  // print out the final result, which is gathered in PE 0 
  for (int i = 0; i < m; i++) {
    if (myPE == 0) {
      printf("myPE: %d, yval_array[%d] = %f\n", myPE, i, yval_array[i]);
    }
  }          
  MPI_Finalize();
  return 0;
}
