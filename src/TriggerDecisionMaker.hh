#pragma once
#include "TriggerCandidate.hh"
#include "TriggerDecision.hh"

namespace DuneTriggers {
  class TriggerDecisionMaker {
  public:
    virtual void operator()(const TriggerCandidate input_tc, std::vector<TriggerDecision>& output_tds) = 0;
  }
}
