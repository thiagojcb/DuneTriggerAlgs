#pragma once
#include "TriggerPrimitive.hh"
#include "TriggerCandidate.hh"
#include <vector>

namespace DuneTriggers {

  class TriggerCandidateMaker {
  public:
    TriggerCandidateMaker() = default;
    ~TriggerCandidateMaker() = default;
    virtual std::vector<TriggerCandidate> MakeCandidate(std::vector<TriggerPrimitive>&) = 0;
  };
}
