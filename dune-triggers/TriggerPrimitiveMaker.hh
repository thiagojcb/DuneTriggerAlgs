#pragma once
#include "includes/json.hpp"
#include "TriggerPrimitive.hh"
#include <vector>
#include <string>

namespace DuneTrigger {
  class TriggerPrimitiveMaker {
  public:
    TriggerPrimitiveMaker(std::string /*json*/) {};
    virtual void operator()(const void* data, std::vector<TriggerPrimitive>& tps) = 0;
  }
}
