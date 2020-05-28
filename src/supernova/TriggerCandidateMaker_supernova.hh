#include "TriggerCandidateMaker.hh"

#include <algorithm>
#include <limits>

using namespace DuneTriggers;

class TriggerCandidateMakerSupernova: public TriggerCandidateMaker {
  /// This candidate maker makes a candidate with all the trigger primitives
public:
  TriggerCandidateMakerSupernova() = default;
  ~TriggerCandidateMakerSupernova() = default;
  
  std::vector<TriggerCandidate> MakeCandidate(std::vector<TriggerPrimitive>& prims) {

    std::vector<TriggerCandidate> vect = {};
    if (prims.empty()) {
      /// returns nothing if no primitives
      return vect;
    }
    
    /// sort by apa
    
    return vect;
    
  }
  
};
