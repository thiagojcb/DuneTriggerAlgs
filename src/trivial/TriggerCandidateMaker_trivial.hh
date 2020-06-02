#include "TriggerCandidateMaker.hh"

#include <algorithm>
#include <limits>

using namespace DuneTriggers;

class TriggerCandidateMakerTrivial: public TriggerCandidateMaker {
  /// This candidate maker makes a candidate with all the trigger primitives
public:
  void Process() {
    TriggerPrimitive tp;
    while (get_next_in_queue_no_mutex(tp)) {
        // do something with tps
        // create candidates tc from it
        // queue_out.push_back(tc);
    }

  }

  // std::vector<TriggerCandidate> MakeCandidate(std::vector<TriggerPrimitive>& prims) {

  //   std::vector<TriggerCandidate> vect = {};
  //   if (prims.empty()) {
  //     /// returns nothing if no primitives
  //     return vect;
  //   }
    
  //   /// sort by apa
  //   std::sort(prims.begin(), prims.end(), [](TriggerPrimitive& a, TriggerPrimitive& b)->bool { return (a.detid > b.detid); });
    
  //   std::vector<TriggerPrimitive> temp;

  //   uint32_t detid = prims.begin()->detid;

  //   for (auto const& it: prims) {
  //     if(it.detid != detid) {
  //       TriggerCandidate cand; // FIXME
  //       temp.clear();
  //       vect.push_back(cand);
  //     } else {
  //       temp.push_back(it);
  //     }
  //   }
    
  //   if (not temp.empty()) {
  //     TriggerCandidate cand;//FIXME
  //     vect.push_back(cand);
  //   }
    
  //   return vect;
    
  // }
  
};
