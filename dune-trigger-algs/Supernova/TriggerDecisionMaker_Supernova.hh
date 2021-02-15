#pragma once
#include "dune-trigger-algs/TriggerDecisionMaker.hh"

#include <algorithm>
#include <limits>
#include <atomic>

namespace triggeralgs {
  class TriggerDecisionMakerSupernova: public TriggerDecisionMaker {
    /// This decision maker just spits out the trigger candidates
    
  public:
    /// The function that returns the final trigger decision (copy of a candidate for now)
    void operator()(const TriggerCandidate&, std::vector<TriggerDecision>&);
  
  protected:
    std::vector<TriggerCandidate> m_candidate;
    std::atomic<int64_t > m_time_window   = {500'000'000};   /// Slinding time window to count activities
    std::atomic<uint16_t> m_threshold     = {1};             /// Minimum number of activities in the time window to issue a trigger
    std::atomic<uint16_t> m_hit_threshold = {1};             /// Minimum number of primities in an activity


    /// this function gets rid of the old activities
    void FlushOldCandidate(int64_t time_now) {
      int64_t how_far = time_now - m_time_window;
      auto end = std::remove_if(m_candidate.begin(), m_candidate.end(),
				[how_far, this] (auto& c) -> bool {
				  return (c.time_start<how_far);
				});
      m_candidate.erase(end, m_candidate.end());
    }
  };
  
}
