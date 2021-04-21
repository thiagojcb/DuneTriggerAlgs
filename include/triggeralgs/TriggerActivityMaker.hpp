#pragma once
#include "triggeralgs/TriggerPrimitive.hpp"
#include "triggeralgs/TriggerActivity.hpp"
#include <vector>
#include <string>

namespace triggeralgs {

  class TriggerActivityMaker {
  public:
    virtual void operator()(const TriggerPrimitive& input_tp, std::vector<TriggerActivity>& output_ta) = 0;
    virtual void flush(std::vector<TriggerActivity>&) {};
  };
  
}
