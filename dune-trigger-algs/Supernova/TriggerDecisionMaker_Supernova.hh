#pragma once
#include "dune-trigger-algs/TriggerDecisionMaker.hh"

#include <algorithm>
#include <limits>
#include <atomic>

namespace DuneTriggerAlgs {
  class TriggerDecisionMakerSupernova: public TriggerDecisionMaker {
    /// This decision maker just counts the number of clusters in the time_window and triggers
    /// if the number of clusters exceeds that.
    
  public:
    /// The function that gets call when there is a new cluster
    void operator()(const TriggerCandidate&, std::vector<TriggerDecision>&);
    
  protected:
    std::vector<TriggerCandidate> m_cluster;
    std::atomic<int64_t > m_time_window   = {500'000'000};
    std::atomic<uint16_t> m_threshold     = {6};
    std::atomic<uint16_t> m_hit_threshold = {3};


    /// this function gets rid of the old clusters
    void FlushOldCandidate(int64_t time_now) {
      int64_t how_far = time_now - m_time_window;
      std::remove_if(m_cluster.begin(), m_cluster.end(),
                     [how_far, this] (auto& c) -> bool {
                       return (c.time_start<how_far);
                     });
    }
  };
  
}
