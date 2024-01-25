#include <Rcpp.h>
using namespace Rcpp;

#include <Rcpp.h>
#include "runSimpleMonteCarlo.h"

using namespace Rcpp;
using namespace std;

//' Runs MC simulation
//'
//' @param Expiry Time to maturity
//' @param Strike strike price
//' @param Spot price of the underlying at the moment of option pricing
//' @param Vol annualized volatility rate
//' @param r annualized risk-free rate
//' @param barrier barrier level
//' @param NumberOfPaths number of simulations
//' @return option price
// [[Rcpp::export]]
double getCallPrice(
    double Expiry = 0.5,
    double Strike = 100,
    double Spot   = 120,
    double Vol    = 0.2,
    double r      = 0.06,
    double barrier = 50,
    unsigned long NumberOfPaths = 10000){
  double result = runSimpleMonteCarlo(Expiry,
                                      Strike,
                                      Spot,
                                      Vol,
                                      r,
                                      barrier,
                                      NumberOfPaths);

  return result;
}
