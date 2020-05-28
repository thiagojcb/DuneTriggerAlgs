#pragma once
#include "CommonDef.hh"
#include "TriggerPrimitive.hh"

#include <bitset>
#include <vector>

namespace DuneTriggers {
  struct TriggerCandidate {
    int time_start;
    int time_end;
    int time_peak;
    int channel_start;
    int channel_end;
    int channel_peak;
    std::bitset<DuneTriggers::n_apa> apa;
    int adc_integral;
    int adc_peak;
  
    TriggerCandidate(int time_start_,    int time_end_,    int time_peak_,
                     int channel_start_, int channel_end_, int channel_peak_,
                     std::bitset<150> apa_,
                     int adc_integral_,  int adc_peak_):
      time_start   (time_start_   ),
      time_end     (time_end_     ),
      time_peak    (time_peak_    ),
      channel_start(channel_start_),
      channel_end  (channel_end_  ),
      channel_peak (channel_peak_ ),
      apa          (apa_          ),
      adc_integral (adc_integral_ ),
      adc_peak     (adc_peak_     ) {}
  
    TriggerCandidate(std::vector<TriggerPrimitive>& prims):
      time_start   (std::numeric_limits<int>::max()),
      time_end     (0),
      time_peak    (0),
      channel_start(std::numeric_limits<int>::max()),
      channel_end  (0),
      channel_peak (0),
      apa          (),
      adc_integral (0),
      adc_peak     (0) {
    
      if (prims.empty()) {
        return;
      }
    
      for (auto const& it: prims) {
      
        if(it.channel<channel_start) {
          channel_start = it.channel;
        }
      
        if(it.channel>channel_end) {
          channel_end = it.channel;
        }
      
        if(it.time_start<time_start) {
          time_start = it.time_start;
        }

        if(it.time_start+it.time_over_threshold>time_end) {
          time_end = it.time_start+it.time_over_threshold;
        }

        if(it.adc_peak>adc_peak) {
          adc_peak = it.adc_peak;
          time_peak = it.time_peak;
          channel_peak = it.channel;
        }

        adc_integral += it.adc_integral;

        apa.set(it.apa);
      }

    }
  };
}
