#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv) {
  int i;
  double result;
  
  if (argc < 2) {
    return 1;
  }

  std::ofstream fout;
  fout.open(argv[1]);
  fout << "double sqrtTable[] = {" << std::endl;
  for(int i = 0; i < 10; ++i) {
    fout << sqrt(static_cast<double>(i)) << "," << std::endl;
  }
  fout << "0};" << std::endl;
  fout.close();
  return 0;
}
