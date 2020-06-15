#include "TriggerCandidateMaker.hh"

#include <algorithm>
#include <limits>

using namespace DuneTriggers;

class TriggerCandidateMakerSupernova: public TriggerCandidateMaker {
  /// This candidate maker makes a candidate with all the trigger primitives
public:
  void operator()(const TriggerPrimitive&, std::vector<TriggerCandidate>&) {};

};
