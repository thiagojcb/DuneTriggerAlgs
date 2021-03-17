#pragma once
#include "dune-trigger-algs/TimingMessage.hh"
#include "dune-trigger-algs/TriggerPrimitive.hh"
#include "dune-trigger-algs/TriggerActivity.hh"
#include "dune-trigger-algs/TriggerCandidate.hh"
#include <vector>
#include <string>

namespace triggeralgs {

  class TriggerCandidateMaker_Timing {
  public:
    virtual void operator()(const TimingMessage& input_ta, std::vector<TriggerCandidate>& output_tc) = 0;
    virtual void flush(std::vector<TriggerCandidate>&) {};
  };
  
}
