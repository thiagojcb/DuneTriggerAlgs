#pragma once
#include "CommonDef.hh"
#include <bitset>

namespace DuneTriggers {
  struct TriggerDecision {
    int time_start; /// 
    int time_end;
    int time_triggered;
    std::bitset<DuneTriggers::n_apa> apa;

    TriggerDecision(int time_start_, int time_end_,
                    int time_triggered_,
                    std::bitset<DuneTriggers::n_apa> apa_) :
      time_start    (time_start    ),
      time_end      (time_end      ),
      time_triggered(time_triggered),
      apa           (apa           ) {}
  };
}
