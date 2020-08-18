#pragma once
#include "dune-trigger-algs/TriggerPrimitive.hh"
#include "dune-trigger-algs/TriggerCandidate.hh"
#include <vector>
#include <string>

namespace DuneTriggerAlgs {

  class TriggerCandidateMaker {
  public:
    virtual void operator()(const TriggerPrimitive& input_tp, std::vector<TriggerCandidate>& output_tc) = 0;
    virtual void flush(std::vector<TriggerCandidate>&) {};
  };
  
}
