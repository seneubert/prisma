// This Class' Header ------------------
#include "cauchyIntMultiPole.h"

// C/C++ Headers ----------------------
#include "TMath.h"
#include <iostream>

// Collaborating Class Headers --------
#include "gsl/gsl_sf_legendre.h"
#include "gsl/gsl_integration.h"

// Class Member definitions -----------

using namespace std;


cauchyIntMultiPole::cauchyIntMultiPole(TF1* func, const std::set<double>& poles,
		 double threshold)
  : _poles(poles),_threshold(threshold),_func(func)
{
  /// calculate interval boundaries
  // loop over poles

}


double
cauchyIntMultiPole::trafo(double t){
  return 0.5*(_range+_diff*t);
}

double
cauchyIntMultiPole::ofart(double x){
  //if(x>_rup || x<_rlow){
  //  cout << "cauchyIntergral:: x out of range: " << x 
  //	 << " ("<< _rlow << "," << _rup << ")" << endl;
  //  throw;
  //}
  return (2.* x-_range)/_diff;
}

