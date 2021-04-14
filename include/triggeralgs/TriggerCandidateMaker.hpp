#pragma once
#include "triggeralgs/TriggerActivity.hpp"
#include "triggeralgs/TriggerCandidate.hpp"
#include <vector>
#include <string>

namespace triggeralgs {

  class TriggerCandidateMaker {
  public:
    virtual void operator()(const TriggerActivity& input_ta, std::vector<TriggerCandidate>& output_tc) = 0;
    virtual void flush(std::vector<TriggerCandidate>&) {};
  };
  
}
