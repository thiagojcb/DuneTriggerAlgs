#pragma once
#include "TriggerCandidate.hh"
#include "TriggerDecision.hh"
#include <vector>

namespace DuneTriggers {
  class TriggerDecisionMaker {
  public:
    virtual void operator()(const TriggerCandidate input_tc, std::vector<TriggerDecision>& output_tds) = 0;
    virtual void operator()(const TriggerDecision input_td, std::vector<TriggerDecision>& output_tds) = 0;
  }
}
