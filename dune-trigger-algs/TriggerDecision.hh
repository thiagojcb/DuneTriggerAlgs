#pragma once
#include <cstdint>
#include <vector>
#include "dune-trigger-algs/TriggerCandidate.hh"

namespace triggeralgs {
  struct TriggerDecision {
    int64_t  time_start     = {0}; 
    int64_t  time_end       = {0};
    int64_t  time_triggered = {0};
    uint32_t detid          = {0};
    uint32_t type           = {0};
    uint32_t algorithm      = {0};
    uint16_t version        = {0};

    std::vector<TriggerCandidate> tc_list;
  };
}
