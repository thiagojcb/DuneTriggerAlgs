#pragma once
#include "TriggerCandidate.hh"
#include "TriggerDecision.hh"

namespace DuneTriggers {
  class TriggerDecisionMaker {
    TriggerDecisionMaker() = default;
    ~TriggerDecisionMaker() = default;
    std::vector<TriggerDecision> MakeDecision(std::vector<TriggerCandidate>&) = 0;
  }
}
