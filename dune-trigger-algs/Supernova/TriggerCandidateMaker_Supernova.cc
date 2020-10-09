#include "dune-trigger-algs/Supernova/TriggerCandidateMaker_Supernova.hh"

#include <algorithm>
#include <limits>
#include <chrono>

using namespace DuneTriggerAlgs;
using pd_clock = std::chrono::duration<double, std::ratio<1, 50'000'000>>;

void TriggerCandidateMakerSupernova::operator()(const TriggerActivity& cand,
                                               std::vector<TriggerCandidate>& decisions) {
  int64_t time = cand.time_start;
  FlushOldActivity(time); // get rid of old clusters in the buffer
  if (cand.tp_list.size()>m_hit_threshold)
    m_cluster.push_back(cand);

  // Yay! we have a trigger!
  if (m_cluster.size() > m_threshold) {
    std::chrono::time_point<std::chrono::steady_clock> now;

    // set all bits to one (probably this will mean down the line: "record every part of the detector")
    uint32_t detid = 0xFFFFFFFF;
    
    TriggerCandidate trigger {time - 500'000'000, // time_start (10 seconds before the start of the cluster)
                             cand.time_end, // time_end, but that should probably be _at least_ this number
                             int64_t(pd_clock(now.time_since_epoch()).count()), // this is now in dune time, with a cast to avoid narrowing warning
                             detid, // all the detector
	                     0, //type ( flag that says what type of trigger might be (e.g. SN/Muon/Beam) )
	                     0, //algorithm ( flag that says which algorithm created the trigger (e.g. SN/HE/Solar) )
	                     0, //version of the above
                             m_cluster}; // TAs used to form this trigger candidate
    m_cluster.clear();
    // Give the trigger word back
    decisions.push_back(trigger);
    return;
  }
  
}
