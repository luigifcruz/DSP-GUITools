#ifndef _PUNCTURE_H_
#define _PUNCTURE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define P23 4
#define P34 6
#define P56 10
#define P78 14
    
class Puncture {
  private:
    int p;
    int enc_len;
    int dec_len;
    uint8_t* p_vec;

    // CCSDS Puncturing Pattern
    // 2/3: 1101
    // 3/4: 110110
    // 5/6: 1101100110
    // 7/8: 11010101100110

    uint8_t p23[P23] = {0xFF, 0xFF, 0x00, 0xFF};
    uint8_t p34[P34] = {0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00};
    uint8_t p56[P56] = {0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00};
    uint8_t p78[P78] = {0xFF, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0x00};
    
    uint8_t* getPattern(int p);

  public:
    Puncture(int p, int enc_len, int dec_len);

    void encode(uint8_t *input, uint8_t *output);
    void decode(uint8_t *input, uint8_t *output);
  
};

#endif

