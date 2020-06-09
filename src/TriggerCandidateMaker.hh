#pragma once
#include "TriggerQueue.hh"
#include "TriggerPrimitive.hh"
#include "TriggerCandidate.hh"
#include <vector>

namespace DuneTriggers {
  class TriggerCandidateMaker:public TriggerQueue<TriggerPrimitive,TriggerCandidate> {
  public:
    virtual void operator()(const TriggerPrimitive& input_tp, std::vector<TriggerCandidate>& output_tc) = 0;
  };
}
