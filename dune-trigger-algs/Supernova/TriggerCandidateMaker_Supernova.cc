#include "dune-trigger-algs/Supernova/TriggerCandidateMaker_Supernova.hh"

#include <algorithm>
#include <limits>
#include <chrono>

using namespace triggeralgs;
using pd_clock = std::chrono::duration<double, std::ratio<1, 50'000'000>>;

void TriggerCandidateMakerSupernova::operator()(const TriggerActivity& activity,
                                               std::vector<TriggerCandidate>& cand) {
  int64_t time = activity.time_start;
  FlushOldActivity(time); // get rid of old activities in the buffer
  if (activity.tp_list.size()>m_hit_threshold)
    m_activity.push_back(activity);

  // Yay! we have a trigger!
  if (m_activity.size() > m_threshold) {
    std::chrono::time_point<std::chrono::steady_clock> now;

    // set all bits to one (probably this will mean down the line: "record every part of the detector")
    uint32_t detid = 0xFFFFFFFF;
    
    auto system_clock = std::chrono::steady_clock::now();
//    Timestamp
    uint32_t algorithm = (uint32_t)pd_clock(system_clock.time_since_epoch()).count();
    TriggerCandidate trigger {time - 500'000'000, // time_start (10 seconds before the start of the activity)
                             activity.time_end, // time_end, but that should probably be _at least_ this number
                             int64_t(pd_clock(now.time_since_epoch()).count()), // this is now in dune time, with a cast to avoid narrowing warning
                             detid, // all the detector
	                     0, //type ( flag that says what type of trigger might be (e.g. SN/Muon/Beam) )
	                     algorithm, //algorithm ( flag that says which algorithm created the trigger (e.g. SN/HE/Solar) )
	                     0, //version of the above
                             m_activity}; // TAs used to form this trigger candidate
    m_activity.clear();
    // Give the trigger word back
    cand.push_back(trigger);
    return;
  }
  
}
