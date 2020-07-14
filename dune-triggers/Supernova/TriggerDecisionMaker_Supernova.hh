#pragma once
#include "dune-triggers/TriggerDecisionMaker.hh"

#include <algorithm>
#include <limits>

namespace DuneTriggers {
  class TriggerDecisionMakerSupernova: public TriggerDecisionMaker {
    /// This decision maker just counts the number of clusters in the time_window and triggers
    /// if the number of clusters exceeds that.
    
  public:
    TriggerDecisionMakerSupernova(std::string json):
      TriggerDecisionMaker(json),
      m_times_cluster() {
      
      auto params = nlohmann::json::parse(json);
      m_time_window = params["time_window"];
      m_threshold = params["threshold"];
      
    };
    
    /// The function that gets call when there is a new cluster
    void operator()(const TriggerCandidate&, std::vector<TriggerDecision>&);
    
  protected:
    std::vector<int64_t> m_times_cluster;
    int64_t m_time_window;
    uint16_t m_threshold;


    /// this function gets rid of the old clusters
    void FlushOldCandidate(int64_t time_now) {
      int64_t how_far = time_now - m_time_window;
      std::remove_if(m_times_cluster.begin(), m_times_cluster.end(),
                     [how_far] (auto& c) -> bool {
                       return c<how_far;
                     });
    }
  };
  
}
