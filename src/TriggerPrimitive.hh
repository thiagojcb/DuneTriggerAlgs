#pragma once

namespace DuneTriggers{
  struct TriggerPrimitive {
    int time_start = {0};
    int time_peak = {0};
    int time_over_threshold = {0};
    int channel = {0};
    int adc_integral = {0};
    int adc_peak = {0};
    int apa = {0};
  };
}
