#include <chrono>
#include <random>
#include <thread>
#include <iostream>

#include "trivial/TriggerCandidateMaker_trivial.hh"

int main() {
  int n_second_generating = 2;
  std::default_random_engine generator;
  // millisec or kHz
  std::exponential_distribution<double> tp_coming(1./1000.);
  std::exponential_distribution<double> electronic_delay(1./500.);
  std::uniform_int_distribution<double> channel(0, 2560);
  std::normal_distribution<double> adc(20, 5);
  std::normal_distribution<double> tp_time_over_threshold(20, 2);
  
  auto start = std::chrono::steady_clock::now();
  auto now   = std::chrono::steady_clock::now();
  using pd_clock = std::chrono::duration<double, std::ratio<50000000, 1>>;
  
  TriggerCandidateMakerTrivial tcmt;
  std::thread worker_thread(&TriggerCandidateMakerTrivial::Worker, &tcmt);
  tcmt.Start();
  while(true) {
    now = std::chrono::steady_clock::now();
    // create random object:
    TriggerPrimitive tp;
    double tot = tp_time_over_threshold(generator);
    std::chrono::milliseconds tot_time((int)tot);
    tp.time_start          = pd_clock(now.time_since_epoch()).count();
    tp.time_over_threshold = pd_clock(tot_time).count();
    tp.channel             = channel(generator);
    tp.adc_integral        = adc(generator);
    tp.adc_peak            = adc(generator);
    tp.detid               = tp.channel;
    
    uint64_t wait = electronic_delay(generator);
    std::chrono::milliseconds millisec_wait(wait);
    std::this_thread::sleep_for(millisec_wait);
    // put them in the queue
    tcmt.AddToQueue(tp);
    
    wait = tp_coming(generator);
    millisec_wait = std::chrono::milliseconds(wait);
    std::this_thread::sleep_for(millisec_wait);
    if (now-start > std::chrono::seconds(n_second_generating)){
      break;
    }
  }
  
  tcmt.Stop();
  worker_thread.join();

}
