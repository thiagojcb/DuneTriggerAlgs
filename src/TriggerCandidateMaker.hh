#pragma once
#include "TriggerPrimitive.hh"
#include "TriggerCandidate.hh"
#include <vector>

namespace DuneTriggers {
  class TriggerCandidateMaker {
  public:
    virtual void operator()(const TriggerPrimitive& input_tp, std::vector<TriggerCandidate>& output_tc) = 0;

    virtual bool GetLastCluster(TriggerCandidate& tc) const {
      return false;
    };
  };
}
