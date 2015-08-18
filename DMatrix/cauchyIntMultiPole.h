///////////////////////////////////////////////////////////////////////////
//
//    Copyright 2009 Sebastian Neubert
//
//    This file is part of rootpwa
//
//    rootpwa is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    rootpwa is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with rootpwa.  If not, see <http://www.gnu.org/licenses/>.
//
///////////////////////////////////////////////////////////////////////////

/** @brief numerical evaluation of cauchy integrals with several poles
    using gsl QAWC integration on disjunct intervals
    \f[
    I = \int_a^\infty ds \frac{f(s)}{\prod_i(s-s_i)} 
    \f]
    
    \f$ a \f$ is the lower boundary of the integration interval

    \f$ f(s) \f$ is the function without any poles \f$ s_i \f$
 */


#ifndef CAUCHYINTEGRAL_HH
#define CAUCHYINTEGRAL_HH

#include "TF1.h"
#include <set>


// Base Class Headers ----------------


// Collaborating Class Declarations --

class cauchyIntMultiPole {
public:

  cauchyIntMultiPole(TF1* func, const std::set<double>& poles,
		 double threshold);

  /// calculates principal value using the gsl
  double eval_Gsl(); ///


  // Allow to set an upper cutoff ??
  //void setRange(double low, double up){_rlow=low;_rup=up;}
 


private:
  std::set<double> _poles; /// Poles of the function
  double _threshold;       /// lower boundary of integration range
  TF1* _func;

  double trafo(double t);
  double ofart(double x);

};


#endif
