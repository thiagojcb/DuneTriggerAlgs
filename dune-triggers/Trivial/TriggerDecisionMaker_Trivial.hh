#pragma once
#include "dune-triggers/TriggerDecisionMaker.hh"

#include <algorithm>
#include <limits>

namespace DuneTriggers {
  class TriggerDecisionMakerTrivial: public TriggerDecisionMaker {
    /// This candidate maker makes a candidate with all the trigger primitives
  public:
    TriggerDecisionMakerTrivial(std::string json):
      TriggerDecisionMaker(json) { };
  
    void operator()(const TriggerCandidate& /*cand*/, std::vector<TriggerDecision>& /*decisions*/) { }
  
  };
}
