#include "triggeralgs/TriggerCandidateMaker_Timing.hpp"

#include <algorithm>
#include <limits>
#include <chrono>

using namespace triggeralgs;
using pd_clock = std::chrono::duration<double, std::ratio<1, 50'000'000>>;

void TriggerCandidateMakerTiming::operator()(const TimeStampedData& data,
                                               std::vector<TriggerCandidate>& cand) {
  int64_t time = (int64_t)data.time_stamp;
  FlushOldActivity(time); // get rid of old activities in the buffer
  


   m_data.push_back(data);

   std::chrono::time_point<std::chrono::steady_clock> now;

    // set all bits to one (probably this will mean down the line: "record every part of the detector")
    uint32_t detid = 0;
    std::vector<uint16_t> detid_vector;
    detid_vector.push_back(detid);
    
//    Timestamp
//  auto system_clock = std::chrono::steady_clock::now();
//  uint32_t tc_timestamp = (uint32_t)pd_clock(system_clock.time_since_epoch()).count();
// empty vectors
    TriggerPrimitive primitive {0,0,0,0,0,0,0,0,0,0,0};
    std::vector<TriggerPrimitive> primitive_vector;
    primitive_vector.push_back(primitive);
    TriggerActivity activity {0,0,0,0,0,0,0,0,0,0,0,0,0,primitive_vector};
    std::vector<TriggerActivity> activity_vector;
    activity_vector.push_back(activity);

    TriggerCandidate trigger {time - m_map[data.signal_type].first, // time_start (
                             time + m_map[data.signal_type].second, // time_end, 
                             int64_t(pd_clock(now.time_since_epoch()).count()), // this is now in dune time, with a cast to avoid narrowing warning
                             detid_vector, // all the detector
	                     data.signal_type, //type ( flag that says what type of trigger might be (e.g. SN/Muon/Beam) )
	                     data.counter, //algorithm ( flag that says which algorithm created the trigger (e.g. SN/HE/Solar) )
	                     0, //version of the above
                             activity_vector}; // TAs used to form this trigger candidate
    m_data.clear();
    // Give the trigger word back
    cand.push_back(trigger);
    return;
  }
  

