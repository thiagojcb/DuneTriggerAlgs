#pragma once
#include "CommonDef.hh"
#include <bitset>

namespace DuneTriggers {
  struct TriggerDecision {
    int time_start = {0}; 
    int time_end = {0};
    int time_triggered = {0};
    std::bitset<DuneTriggers::n_apa> apa = {};
  };
}
