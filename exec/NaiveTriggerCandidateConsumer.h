#pragma once

#include <fstream>

#include <mutex>

#include "TriggerCandidateMaker.hh"
/// A simple class that just dumps every candidate it receives in a txt file, and wait random times in between

class NaiveTriggerCandidateConsumer {
protected:
  std::ofstream file_out;

public:

  NaiveTriggerCandidateConsumer(NaiveTriggerQueue& tq_):
    tq(tq_),
    consume_on (false),
    mtx(),
    n_tc(0){
    file_out.open("candidate_dump.txt");
    file_out << "tstart\t\ttend\t\ttpeak\t\tchannel_start\tchannel_end\tchannel_peak\tadc_integral\tadc_peak\tdetid\n";
  }
  
  NaiveTriggerQueue& tq;
  bool consume_on;
  std::mutex mtx; // to protect above
  int n_tc;
  
  void Worker() {
    while (true) {
      TriggerCandidate tc;
      if (tq.GetNextProcessed(tc))
        PrintToFile(tc);
      
      mtx.lock();
      if (not consume_on) break;
      mtx.unlock();
    }
    mtx.unlock();
  }

  void Start() {
    std::cout << "\033[32mStarting Candidate consumer\033[0m\n";
    mtx.lock();
    consume_on = true;
    mtx.unlock();
  }
    
  void Stop() {
    mtx.lock();
    consume_on = false;
    mtx.unlock();
    TriggerCandidate tc;
    if (tq.tcm.GetLastCluster(tc))
      PrintToFile(tc);
    
    std::cout << "Created "<< n_tc << " TCs.\n";
  }
    
  void PrintToFile(TriggerCandidate& tc) {
    n_tc++;
    std::string str = (std::to_string(tc.time_start   )+"\t"+
                       std::to_string(tc.time_end     )+"\t"+
                       std::to_string(tc.time_peak    )+"\t"+
                       std::to_string(tc.channel_start)+"\t\t"+
                       std::to_string(tc.channel_end  )+"\t\t"+
                       std::to_string(tc.channel_peak )+"\t\t"+
                       std::to_string(tc.adc_integral )+"\t\t"+
                       std::to_string(tc.adc_peak     )+"\t\t"+
                       std::to_string(tc.detid        )+"\n");
    file_out << str;
      
  }
};
