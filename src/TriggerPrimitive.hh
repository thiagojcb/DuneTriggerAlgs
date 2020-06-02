#pragma once
#include <cstdint>

namespace DuneTriggers{
  struct TriggerPrimitive {
    int64_t time_start = {0};
    int64_t time_peak = {0};
    int time_over_threshold = {0};
    int channel = {0};
    int adc_integral = {0};
    int adc_peak = {0};
    int apa = {0};
  };
}
