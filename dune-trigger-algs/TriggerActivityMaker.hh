#pragma once
#include "dune-trigger-algs/TriggerPrimitive.hh"
#include "dune-trigger-algs/TriggerActivity.hh"
#include <vector>
#include <string>

namespace triggeralgs {

  class TriggerActivityMaker {
  public:
    virtual void operator()(const TriggerPrimitive& input_tp, std::vector<TriggerActivity>& output_ta) = 0;
    virtual void flush(std::vector<TriggerActivity>&) {};
  };
  
}
