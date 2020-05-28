#pragma once

namespace DuneTriggers{
  struct TriggerPrimitive {
    int time_start;
    int time_peak;
    int time_over_threshold;
    int channel;
    int adc_integral;
    int adc_peak;
    int apa;
  };
}
