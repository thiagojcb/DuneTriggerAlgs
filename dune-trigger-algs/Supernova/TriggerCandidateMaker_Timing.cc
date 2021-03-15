#include "dune-trigger-algs/Supernova/TriggerCandidateMaker_Timing.hh"

#include <algorithm>
#include <limits>
#include <chrono>

using namespace triggeralgs;
using pd_clock = std::chrono::duration<double, std::ratio<1, 50'000'000>>;

void TriggerCandidateMakerTiming::operator()(const TriggerPrimitive& primitive,
                                               std::vector<TriggerCandidate>& cand) {
  int64_t time = primitive.time_start;
  FlushOldActivity(time); // get rid of old activities in the buffer
  


   m_primitive.push_back(primitive);

   std::chrono::time_point<std::chrono::steady_clock> now;

    // set all bits to one (probably this will mean down the line: "record every part of the detector")
    uint32_t detid = primitive.detid;
    
//    Timestamp
//    auto system_clock = std::chrono::steady_clock::now();
//    uint32_t algorithm = (uint32_t)pd_clock(system_clock.time_since_epoch()).count();
    std::vector<uint16_t> detid_vector;
    std::vector<TriggerPrimitive> primitive_vector;
    detid_vector.push_back(detid);
    primitive_vector.push_back(primitive);
    TriggerActivity activity {0,0,0,0,0,0,0,0,0,0,0,0,0,primitive_vector};
    std::vector<TriggerActivity> activity_vector;
    activity_vector.push_back(activity);

    TriggerCandidate trigger {primitive.time_start - m_map[primitive.detid].first, // time_start (10 seconds before the start of the primitive)
                             primitive.time_start + m_map[primitive.detid].second, // time_end, but that should probably be _at least_ this number
                             int64_t(pd_clock(now.time_since_epoch()).count()), // this is now in dune time, with a cast to avoid narrowing warning
                             detid_vector, // all the detector
	                     0, //type ( flag that says what type of trigger might be (e.g. SN/Muon/Beam) )
	                     primitive.algorithm, //algorithm ( flag that says which algorithm created the trigger (e.g. SN/HE/Solar) )
	                     0, //version of the above
                             activity_vector}; // TAs used to form this trigger candidate
    m_primitive.clear();
    // Give the trigger word back
    cand.push_back(trigger);
    return;
  }
  

