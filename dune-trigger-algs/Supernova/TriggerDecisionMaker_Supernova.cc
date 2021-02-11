#include "dune-trigger-algs/Supernova/TriggerDecisionMaker_Supernova.hh"

#include <algorithm>
#include <limits>
#include <chrono>

using namespace triggeralgs;

void TriggerDecisionMakerSupernova::operator()(const TriggerCandidate& cand,
                                               std::vector<TriggerDecision>& decisions) {

  std::vector<TriggerCandidate> vCand;
  vCand.push_back(cand);
  

  TriggerDecision trigger {cand.time_start,
                           cand.time_end,
                           cand.time_decided,
                           cand.detid,
                           cand.type,
                           cand.algorithm,
                           cand.version,
                           vCand}; 

    // Give the trigger word back
    decisions.push_back(trigger);
    return;
}
