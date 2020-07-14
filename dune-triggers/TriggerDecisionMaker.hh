#pragma once
#include "includes/json.hpp"
#include "TriggerCandidate.hh"
#include "TriggerDecision.hh"
#include <vector>
#include <string>

namespace DuneTriggers {
  class TriggerDecisionMaker {
  public:
    TriggerDecisionMaker(std::string/* json*/) {};
    virtual void operator()(const TriggerCandidate& input_tc, std::vector<TriggerDecision>& output_tds) = 0;
  };
}
