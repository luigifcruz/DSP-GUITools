#include <stdlib.h>
#include "GUI.h"
#include <iostream>
#include <fstream>
#include <complex>
#include <vector>

#define BUFFER_SIZE 10000
#define SAMPLE_RATE 23437 

using namespace std;

void draw_constellation(GUI g, vector<complex<float> > iq) {
  g.clear();

  for (auto element : iq) {
    int x1 = int((element.real()+1)*100)+25;
    int x2 = int((element.imag()+1)*100)+25;

    g.draw_point(x1, x2);
  }
}

int main() {
  GUI g; 
  g.init(250, 250);

  chrono::time_point<std::chrono::high_resolution_clock> tick;

  ifstream ifs("BPSK_constellation.raw", ios::binary | ios::in);
  vector<complex<float> > iq(BUFFER_SIZE);

  float fPeriod = BUFFER_SIZE / (float)SAMPLE_RATE;
  chrono::milliseconds period((uint32_t) round(fPeriod * 1000));
  tick = chrono::high_resolution_clock::now() - period;

  while (1) {
    if ((chrono::high_resolution_clock::now() - tick) >= period) {
      ifs.read(reinterpret_cast<char*>(iq.data()), 4*BUFFER_SIZE*sizeof(float));
      draw_constellation(g, iq);
      tick = chrono::high_resolution_clock::now();
    }
  }
 
  ifs.close();
  g.close();
  return 0;
}
