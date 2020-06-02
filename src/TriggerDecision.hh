#pragma once
#include "CommonDef.hh"
#include <bitset>
#include <cstdint>

namespace DuneTriggers {
  struct TriggerDecision {
    int64_t time_start = {0}; 
    int64_t time_end = {0};
    int64_t time_triggered = {0};
    std::bitset<DuneTriggers::n_apa> apa = {};
  };
}
