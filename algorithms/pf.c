#include <avr/interrupt.h>
#include <math.h>
#include "pf.h"
#include "../drivers/timer.h"
#include "../constants.h"

/*returns 1000 * power factor*/
uint16_t get_pf(){
    float time = get_timer_count() * CLOCK_PERIOD; 
	/*since the period is 1ms we do not need to divide by the period */
    float theta = time * 2 * PI; /*angle in radians*/
    float pf_f = cos(theta);
    uint16_t pf = pf_f * 100;
    return pf;
}
