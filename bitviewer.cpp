#include <stdlib.h>
#include "GUI.h"
#include <iostream>
#include <fstream>
#include <complex>
#include <vector>

#define FRAME_SIZE 8192
#define MAX_FRAME_SIZE 8190
#define MAX_LINES 1000

using namespace std;

bool is_bit_set(uint8_t byte, int index) {
  return (byte >> index) & 1;
}

void draw_bitmap(GUI g, vector<uint8_t> binary) {
  uint64_t frame_count = 0;
  uint64_t bit_count = 0;

  for (uint8_t element : binary) {
    for (int i = 0; i < 8; i++) {
      if (!is_bit_set(element, i) && MAX_FRAME_SIZE > bit_count) {
        g.draw_point(bit_count, frame_count);
      }
      bit_count++;
    
      if (bit_count % FRAME_SIZE == 0) {
        frame_count++;
        bit_count = 0;
      }
    }
  }
}

int main(int argc, char* argv[]) {
  GUI g; 

  ifstream ifs("./A_NRZM.raw", ios::binary | ios::in);

  ifs.seekg (0, ifs.end);
  int bytes = ifs.tellg();
  ifs.seekg (0, ifs.beg);

  int lines = int((bytes*8)/FRAME_SIZE);

  if (lines > MAX_LINES) {
    lines = MAX_LINES;
    bytes = int(MAX_LINES*FRAME_SIZE/8);
  }
  
  vector<uint8_t> binary(bytes);
  g.init((FRAME_SIZE > MAX_FRAME_SIZE) ? MAX_FRAME_SIZE : FRAME_SIZE, lines);

  ifs.read(reinterpret_cast<char*>(binary.data()), bytes);

  while (1) {
    XNextEvent(g.d, &g.e);
    if (g.e.type == Expose) {
      draw_bitmap(g, binary);
    }
  }

  ifs.close();
  g.close();
  return 0;
}
