#pragma once
#include <cstdint>
#include <vector>
#include "triggeralgs/TriggerCandidate.hpp"

namespace triggeralgs {
  struct TriggerDecision {
    int64_t  time_start     = {0}; 
    int64_t  time_end       = {0};
    int64_t  time_trigger   = {0};
    uint32_t trigger_number = {0};
    uint32_t run_number     = {0};
    uint32_t subrun_number  = {0};
    uint32_t type           = {0};
    uint32_t algorithm      = {0};
    uint16_t version        = {0};

    std::vector<TriggerCandidate> tc_list;
  };
}
