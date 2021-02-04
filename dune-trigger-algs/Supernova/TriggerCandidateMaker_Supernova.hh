#pragma once
#include "dune-trigger-algs/TriggerCandidateMaker.hh"

#include <algorithm>
#include <limits>
#include <atomic>

namespace DuneTriggerAlgs {
  class TriggerCandidateMakerSupernova: public TriggerCandidateMaker {
    /// This decision maker just counts the number of activities in the time_window and triggers
    /// if the number of activities exceeds that.
    
  public:
    /// The function that gets call when there is a new activity
    void operator()(const TriggerActivity&, std::vector<TriggerCandidate>&);
    
  protected:
    std::vector<TriggerActivity> m_activity;
    std::atomic<int64_t > m_time_window   = {500'000'000};
    std::atomic<uint16_t> m_threshold     = {6};
    std::atomic<uint16_t> m_hit_threshold = {3};


    /// this function gets rid of the old activities
    void FlushOldActivity(int64_t time_now) {
      int64_t how_far = time_now - m_time_window;
      std::remove_if(m_activity.begin(), m_activity.end(),
                     [how_far, this] (auto& c) -> bool {
                       return (c.time_start<how_far);
                     });
    }
  };
  
}
