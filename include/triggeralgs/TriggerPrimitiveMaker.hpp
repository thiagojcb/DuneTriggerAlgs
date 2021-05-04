#pragma once
#include "triggeralgs/TriggerPrimitive.hpp"
#include <vector>
#include <string>

namespace triggeralgs {
  
  class TriggerPrimitiveMaker {
  public:
    virtual void operator()(const void* input_rawdata, std::vector<TriggerPrimitive>& output_tp) = 0;
    virtual void flush(std::vector<TriggerPrimitive>&) {};
  };
  
}
