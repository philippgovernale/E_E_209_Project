#include "avg_power.h"
#include "../drivers/adc.h"
#include "../conversions.h"

/*these need to be changed*/
#define VOLTAGE_CHANNEL 0
#define CURRENT_CHANNEL 1

#define N_WAVEFORMS 2
#define N_SAMPLES 19*N_WAVEFORMS

uint16_t* inst_pow(uint16_t first_v)
{
    uint16_t current_r = ADC_convert_channel(CURRENT_CHANNEL);
    uint16_t second_v = ADC_convert_channel(VOLTAGE_CHANNEL);

    avg_voltage = (first_v + second_v)/2;

    avg_voltage = convert_count_to_v_peak(avg_voltage);
    current_r = convert_count_to_i_rms(current_r);

    uint32_t inst_pow = avg_voltage * current_r;
    uint16_t inst_pow_mw = (uint16_t) (inst_pow/100); /*conversion to mW*/

    //array of 2 including inst_pow and last value;
    uint16_t *arr = malloc(sizeof(uint16_t)*2);
    arr[0] = inst_pow_mw;
    arr[1] = second_v;
    return arr;

}

uint16_t get_avg_power()
{
    uint16_t first_v = ADC_convert_channel(VOLTAGE_CHANNEL);
    uint32_t power_sum = 0;
    uint32_t *data_pair = 0;

    int i;
    for(i=0; i < N_SAMPLES; i++){
        free(data_pair);
        uint32_t *data_pair = inst_pow(first_v);
        power_sum += data_pair[0];
        first_v = data_pair[1];
    }

    uint16_t avg_power_mw = power_sum/ N_SAMPLES;
    return avg_power_mv;
}
