
#include <iostream>

using std :: cout ;
using std :: endl ;


double lookupVal(int n , double *x , double *y , double xval, int myPE)
{
  for ( int i = 0 ; i < n-1 ; ++ i )
    if ( xval >= x[i] &&  xval <= x[i+1] )
      {
	return y[i] + (xval - x[i]) * ( y[i+1] - y[i] ) / ( x[i+1] - x[i] );
      }
  return -99.0;
}




