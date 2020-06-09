#pragma once
#include "TriggerPrimitive.hh"

namespace DuneTrigger {
  class TriggerPrimitiveMaker {
  public:
    virtual void operator()(const void* data, std::vector<TriggerPrimitive>& tps) = 0;
  }
}
