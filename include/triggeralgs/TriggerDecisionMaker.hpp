#pragma once
#include "triggeralgs/TriggerCandidate.hpp"
#include "triggeralgs/TriggerDecision.hpp"
#include <vector>
#include <string>

namespace triggeralgs {
  
  class TriggerDecisionMaker {
  public:
    virtual void operator()(const TriggerCandidate& input_tc, std::vector<TriggerDecision>& output_tds) = 0;
    virtual void flush(std::vector<TriggerDecision>&) {};
  };
  
}
