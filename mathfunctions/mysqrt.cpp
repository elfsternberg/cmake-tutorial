#include "mathfunctions.h"
#include "tutorial_config.h"
#include "table.h"
#include <iostream>

double improve(double guess, double x) {
  double newguess = x / guess;
  return (newguess + guess) / 2;
}

bool goodenough(double guess, double x) {
  return abs((guess * guess) - x) < 0.00000001;
}

double mysqrt(double x) {
  if (x < 10) {
    std::cerr << "Using Table" << std::endl;
    return sqrtTable[static_cast<int>(x)];
  }

#if defined (HAVE_LOG) && defined(HAVE_EXP)
  std::cerr << "USING LOG" << std::endl;
  return exp(log(x) * 0.5);
#else
  double guess = 1.0;
  double t = x;
  while(1) {
    if (goodenough(guess, t)) {
      return guess;
    }
    guess = improve(guess, t);
  }
#endif
}
      
