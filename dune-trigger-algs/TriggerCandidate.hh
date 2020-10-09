#pragma once
#include <cstdint>
#include <vector>
#include "dune-trigger-algs/TriggerActivity.hh"

namespace DuneTriggerAlgs {
  struct TriggerCandidate {
    int64_t  time_start    = {0};
    int64_t  time_end      = {0};
    int64_t  time_decided  = {0};
    uint32_t detid         = {0};
    uint32_t type          = {0};
    uint32_t algorithm     = {0};
    uint16_t version       = {0};

    std::vector<TriggerActivity> ta_list;
  };
    
}
