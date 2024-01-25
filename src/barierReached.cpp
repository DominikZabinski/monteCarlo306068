#include "barierReached.h"
#include "getOneGaussianByBoxMueller.h"
#include <cmath>

bool barierReached(double r,
                   double Expiry,
                   double Vol,
                   double Spot,
                   double barrier,
                   double nInt){
  double thisDrift = (r * Expiry - 0.5 * Vol * Vol * Expiry) / double(nInt);
  double cumShocks = 0;
  bool reached = false;
  double multiplier = Vol * sqrt(Expiry / double(nInt));

  int i = 0;
  while (i < nInt && !reached){
    cumShocks += (thisDrift + multiplier * getOneGaussianByBoxMueller());
    if (Spot * exp(cumShocks) < barrier) reached = true;
    i++;
  }
  return reached;
}
