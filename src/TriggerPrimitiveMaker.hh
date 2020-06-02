#pragma once
#include "TriggerPrimitive.hh"

namespace DuneTrigger {
  class TriggerPrimitiveMaker {
  public:
    std::vector<TriggerPrimitive> MakePrimitive() = 0;
  }
}
