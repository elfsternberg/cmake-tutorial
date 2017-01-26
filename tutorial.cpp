#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "tutorial_config.h"
#ifdef USE_MYMATH
#include "mathfunctions.h"
#endif


int main(int argc, char **argv) {
  if (argc < 2) { 
    std::cerr << argv[0] << " version " << tutorial_VERSION_MAJOR 
              << "." << tutorial_VERSION_MINOR << std::endl;
    std::cerr << "Usage: " << argv[0] << " number\n";
    return 1;
  }

  double inputvalue = atof(argv[1]);
#ifdef USE_MYMATH
  std::cerr << "Using MYMATH" << std::endl;
  double outputvalue = mysqrt(inputvalue);
#else
  std::cerr << "Using sqrt" << std::endl;
  double outputvalue = sqrt(inputvalue);
#endif  
  std::cout << "THe square root of " << inputvalue << " is " << outputvalue << std::endl;
  return 0;
}
