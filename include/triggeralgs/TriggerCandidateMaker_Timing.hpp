#pragma once
#include "triggeralgs/TimeStampedData.hpp"
#include "triggeralgs/TriggerPrimitive.hpp"
#include "triggeralgs/TriggerActivity.hpp"
#include "triggeralgs/TriggerCandidate.hpp"
#include <vector>
#include <string>

namespace triggeralgs {

  class TriggerCandidateMaker_Timing {
  public:
    virtual void operator()(const TimeStampedData& input_ta, std::vector<TriggerCandidate>& output_tc) = 0;
    virtual void flush(std::vector<TriggerCandidate>&) {};
  };
  
}
