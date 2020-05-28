#include "TriggerCandidateMaker.hh"

#include <algorithm>
#include <limits>


class TriggerCandidateMakerSupernova: public TriggerCandidateMaker {
  /// This candidate maker makes a candidate with all the trigger primitives
public:
  TriggerCandidateMakerSupernova() = default;
  ~TriggerCandidateMakerSupernova() = default;
  
  std::vector<TriggerCandidate> MakeCandidate(std::vector<TriggerPrimitive>& prims) {

    std::vector<TriggerCandidate> vect = {};
    if (prims.empty()) {
      /// returns nothing if no primitives
      return vect;
    }
    
    /// sort by apa
    std::sort(prims.begin(), prims.end(), [](TriggerPrimitive& a, TriggerPrimitive& b)->bool { return (a.apa > b.apa); });
    int channel_start = std::numeric_limits<int>::max();
    int channel_end   = 0;
    int time_start    = std::numeric_limits<int>::max();
    int time_end      = 0;
    int apa           = prims[0].apa;
    int adc_peak      = 0;
    int adc_integral  = 0;

    for (auto const& it: prims) {
      
      if(it.channel<channel_start) {
        channel_start = it.channel;
      }
      
      if(it.channel>channel_end) {
        channel_end = it.channel;
      }
      
      if(it.time<time_start) {
        time_start = it.time;
      }

      if(it.time+it.time_over_threshold>time_end) {
        time_end = it.time+it.time_over_threshold;
      }

      if(it.adc_peak>adc_peak) {
        adc_peak = it.adc_peak;
      }

      adc_integral += it.adc_integral;

      if(it.apa != apa) {
        TriggerCandidate cand(channel_start, channel_end,
                              time_start,    time_end,
                              apa,
                              adc_peak, adc_integral);
        vect.push_back(cand);
        channel_start = std::numeric_limits<int>::max();
        channel_end   = 0;
        time_start    = std::numeric_limits<int>::max();
        time_end      = 0;
        apa           = it.apa;
        adc_peak      = 0;
        adc_integral  = 0;

      }
    }
    
    TriggerCandidate cand(channel_start, channel_end,
                          time_start,    time_end,
                          apa,
                          adc_peak, adc_integral);
    vect.push_back(cand);

    return vect;
    
  }
  
};
