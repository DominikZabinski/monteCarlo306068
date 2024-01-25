#include "runSimpleMonteCarlo.h"
#include "barierReached.h"
#include "getOneGaussianByBoxMueller.h"
#include <cmath>

// definition of the function
double runSimpleMonteCarlo(double Expiry,
                           double Strike,
                           double Spot,
                           double Vol,
                           double r,
                           double barrier,
                           unsigned long int NumberOfPaths){

  double variance = Vol * Vol * Expiry;
  double rootVariance = sqrt(variance);
  double itoCorrection = -0.5 * variance;

  double movedSpot = Spot * exp(r * Expiry + itoCorrection);
  double thisSpot;
  double runningSum = 0;

  // assuming 252 working days in a year
  double nInt = Expiry * 252;

  // 1. Draw a random variable x ∼ N(0, 1) and compute f(S) (do it multiple times)
  for (unsigned long i = 0; i < NumberOfPaths; i++) {
    double thisGaussian = getOneGaussianByBoxMueller();
    thisSpot = movedSpot * exp(rootVariance * thisGaussian);

    // 1a. Calculate payoff
    double thisPayoff = thisSpot - Strike;

    // 1b. Check whether barrier has been reached in any moment
    bool barierFlag = barierReached(r, Expiry, Vol, Spot, barrier, nInt);

    if (thisPayoff > 0 && !barierFlag) runningSum += thisPayoff;
  }

  // 2. Calculate the average
  double mean = runningSum / NumberOfPaths;

  // 3. Multiply this average by e^(−rT) .
  mean = mean * exp(-r * Expiry);

  return mean;
}
