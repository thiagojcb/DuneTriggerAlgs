#pragma once

struct TriggerCandidate {
  int channel_start;
  int channel_end;
  int time_start;
  int time_end;
  int apa;
  int adc_peak;
  int adc_integral;
  TriggerCandidate(int channel_start_, int channel_end_,
                   int time_start_,    int time_end_,
                   int apa_,
                   int adc_peak_,      int adc_integral_):
    channel_start(channel_start_),
    channel_end  (channel_end_  ),
    time_start   (time_start_   ),
    time_end     (time_end_     ),
    apa          (apa_          ),
    adc_peak     (adc_peak_     ),
    adc_integral (adc_integral_ ) {}
};
