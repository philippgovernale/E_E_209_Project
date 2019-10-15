#include "i_rms.h"
#include "../drivers/adc.h"
#include "../conversions.h"
#include <math.h>

#define iSenseChannel                       2
#define NUMBER_OF_SAMPLES					38 // 1ms divided by 52us is 19 samples so double that for 2 waveforms


uint16_t get_rms_current(){
    uint16_t i_rms_count ; 


    for(int i = 0; i < NUMBER_OF_SAMPLES; i++){
		i_rms_count += (ADC_convert_channel(iSenseChannel)* 1000)^2 ;
	}

	i_rms_count /= NUMBER_OF_SAMPLES ;
	i_rms_count = sqrt(i_rms) ; //  root mean square ADC COUNT

	i_rms_count = convert_count_to_i_rms(i_rms); // convert to milliamps



}