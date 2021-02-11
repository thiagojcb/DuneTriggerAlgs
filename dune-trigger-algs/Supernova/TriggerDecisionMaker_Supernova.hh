#pragma once
#include "dune-trigger-algs/TriggerDecisionMaker.hh"

#include <algorithm>
#include <limits>
#include <atomic>

namespace triggeralgs {
  class TriggerDecisionMakerSupernova: public TriggerDecisionMaker {
    /// This decision maker just spits out the trigger candidates
    
  public:
    /// The function that returns the final trigger decision (copy of a candidate for now)
    void operator()(const TriggerCandidate&, std::vector<TriggerDecision>&);
  
  };
  
}
