#pragma once
#include "TriggerQueue.hh"
#include "TriggerPrimitive.hh"
#include "TriggerCandidate.hh"
#include <vector>

namespace DuneTriggers {

  class TriggerCandidateMaker:public TriggerQueue<TriggerPrimitive,TriggerCandidate> {
  public:
    virtual void Process() = 0;
    TriggerCandidateMaker():
      TriggerQueue(100, 100){}
  };
}
