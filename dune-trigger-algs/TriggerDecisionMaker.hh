#pragma once
#include "dune-trigger-algs/TriggerCandidate.hh"
#include "dune-trigger-algs/TriggerDecision.hh"
#include <vector>
#include <string>

namespace DuneTriggerAlgs {
  
  class TriggerDecisionMaker {
  public:
    virtual void operator()(const TriggerCandidate& input_tc, std::vector<TriggerDecision>& output_tds) = 0;
    virtual void flush(std::vector<TriggerDecision>&) {};
  };
  
}
