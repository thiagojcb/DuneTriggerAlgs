#pragma once
#include "dune-trigger-algs/TriggerActivity.hh"
#include "dune-trigger-algs/TriggerCandidate.hh"
#include <vector>
#include <string>

namespace DuneTriggerAlgs {

  class TriggerCandidateMaker {
  public:
    virtual void operator()(const TriggerActivity& input_tp, std::vector<TriggerCandidate>& output_tc) = 0;
    virtual void flush(std::vector<TriggerCandidate>&) {};
  };
  
}
