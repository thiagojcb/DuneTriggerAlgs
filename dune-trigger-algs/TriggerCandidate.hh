#pragma once
#include <cstdint>

namespace DuneTriggerAlgs {
  struct TriggerCandidate {
    int64_t  time_start    = {0};
    int64_t  time_end      = {0};
    int64_t  time_peak     = {0};
    uint32_t ntps          = {0};
    uint32_t channel_start = {0};
    uint32_t channel_end   = {0};
    uint32_t channel_peak  = {0};
    uint16_t adc_integral  = {0};
    uint16_t adc_peak      = {0};
    uint32_t detid         = {0};
    uint32_t flags         = {0};
  };
    
}
