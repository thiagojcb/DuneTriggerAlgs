#pragma once
#include "TriggerCandidate.hh"
#include "TriggerDecision.hh"

namespace DuneTriggers {
  class TriggerDecisionMaker {
  public:
    std::vector<TriggerDecision> MakeDecision(const std::vector<TriggerCandidate>&) = 0;
  }
}
