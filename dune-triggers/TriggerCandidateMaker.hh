#pragma once
#include "TriggerPrimitive.hh"
#include "TriggerCandidate.hh"
#include <vector>
#include <string>

namespace DuneTriggers {
  class TriggerCandidateMaker {
  public:
    TriggerCandidateMaker(std::string/* json*/) {};

    virtual void operator()(const TriggerPrimitive& input_tp, std::vector<TriggerCandidate>& output_tc) = 0;

    virtual bool GetLastCluster(TriggerCandidate& tc) const {
      return false;
    };
  };
}
