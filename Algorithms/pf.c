#include "pf.h"
#include "math.h"
#include "../drivers/timer.h"

#define PI 3.14159

uint16_t get_pf(){
    float time = timer_count * (float)0.004;
    float theta = time * 2 * PI;
    float pf_f = cos(theta);
    uint16_t pf = pf_f * 1000;
    return pf;
}
