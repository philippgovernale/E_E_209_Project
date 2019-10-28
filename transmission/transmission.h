#include <stdint.h>

void transmit_all(uint16_t v_peak, uint16_t i_rms, uint16_t p_avg, uint16_t pf);
void transmit_number(uint8_t decimal_position, uint16_t number, uint8_t num_of_digits);
void transmit_readings(uint16_t reading);