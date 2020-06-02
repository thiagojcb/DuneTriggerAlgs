#include "TriggerCandidateMaker.hh"

#include <algorithm>
#include <limits>

using namespace DuneTriggers;

class TriggerCandidateMakerTrivial: public TriggerCandidateMaker {
  /// This candidate maker makes a candidate with all the trigger primitives
public:
  
  std::vector<TriggerCandidate> MakeCandidate(std::vector<TriggerPrimitive>& prims) {

    std::vector<TriggerCandidate> vect = {};
    if (prims.empty()) {
      /// returns nothing if no primitives
      return vect;
    }
    
    /// sort by apa
    std::sort(prims.begin(), prims.end(), [](TriggerPrimitive& a, TriggerPrimitive& b)->bool { return (a.apa > b.apa); });
    
    std::vector<TriggerPrimitive> temp;

    int apa = prims.begin()->apa;

    for (auto const& it: prims) {
      if(it.apa != apa) {
        TriggerCandidate cand; // FIXME
        temp.clear();
        vect.push_back(cand);
      } else {
        temp.push_back(it);
      }
    }
    
    if (not temp.empty()) {
      TriggerCandidate cand;//FIXME
      vect.push_back(cand);
    }
    
    return vect;
    
  }
  
};
