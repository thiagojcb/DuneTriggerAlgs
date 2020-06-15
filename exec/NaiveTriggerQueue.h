#pragma once
#include <mutex>
#include "trivial/TriggerCandidateMaker_trivial.hh"
class NaiveTriggerQueue {
protected:
  boost::circular_buffer<TriggerPrimitive> queue_in;
  boost::circular_buffer<TriggerCandidate> queue_out;
  std::mutex mtx_queue_in;
  std::mutex mtx_queue_out;
  std::mutex mtx_process_on;
  
  bool process_on;
  TriggerCandidateMaker& tcm;
    
  bool get_next_in_queue_no_mutex(TriggerPrimitive& dat) {
    if (not queue_in.empty()) {
      dat = std::move(queue_in[0]);
      queue_in.pop_front();
      // std::cout << "\033[32m1 TP consumed to the queue (size=" << queue_in.size() << ")\033[0m\n";
      return true;
    }
    return false;
  }
    
public:
  NaiveTriggerQueue(TriggerCandidateMaker& tcm_, size_t depth_in=100, size_t depth_out=100):
    queue_in  (depth_in ),
    queue_out (depth_out),
    mtx_queue_in (),
    mtx_queue_out(),
    mtx_process_on(),
    process_on(false),
    tcm(tcm_) { }
    
  void AddToQueue(const TriggerPrimitive& dat) {
    mtx_queue_in.lock();
    queue_in.push_back(dat);
    mtx_queue_in.unlock();
    // std::cout << "\033[32m1 TP added to the queue (size=" << queue_in.size() << ")\033[0m\n";
  }
    
  void AddToQueue(const std::vector<TriggerPrimitive>& dats) {
    mtx_queue_in.lock();
    std::for_each(dats.begin(), dats.end(), [this](TriggerPrimitive dat)->void {this->queue_in.push_back(dat);});
    mtx_queue_in.unlock();
  }

  void Worker() {
    while (true) {
      mtx_queue_in.lock();
      mtx_queue_out.lock();

      TriggerPrimitive tp;
      std::vector<TriggerCandidate> tcs;

      if (get_next_in_queue_no_mutex(tp))
        tcm(tp, tcs);

      for (auto const& tc: tcs) {
        queue_out.push_back(tc);
      }
      
      mtx_queue_in.unlock();
      mtx_queue_out.unlock();

      mtx_process_on.lock();
      if (not process_on) break;
      mtx_process_on.unlock();
    }
  }

  void Start() {
    mtx_process_on.lock();
    process_on = true;
    mtx_process_on.unlock();
  }
    
  void Stop() {
    mtx_process_on.lock();
    process_on = false;
    mtx_process_on.unlock();
  }
    
  void SoftStop() {
    mtx_process_on.lock();
    mtx_queue_in.lock();
    mtx_queue_out.lock();
    if (not queue_out.empty() or not queue_in.empty()) {
      mtx_queue_in.unlock();
      mtx_queue_out.unlock();
      std::chrono::milliseconds millisec_wait(500);
      std::this_thread::sleep_for(millisec_wait);
    }
    process_on = false;
    mtx_process_on.unlock();
    mtx_queue_in.unlock();
    mtx_queue_out.unlock();
  }
    
  const bool GetNextProcessed(TriggerCandidate& dat) {
    mtx_queue_out.lock();
    if (not queue_out.empty()) {
      dat = std::move(queue_out[0]);
      queue_out.pop_front();
      mtx_queue_out.unlock();
      return true;
    }
    mtx_queue_out.unlock();
    return false;
  }
};
