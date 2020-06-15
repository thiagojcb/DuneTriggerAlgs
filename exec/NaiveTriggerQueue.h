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
    
  bool get_next_in_queue_no_mutex(TriggerPrimitive& dat) {
    if (not queue_in.empty()) {
      dat = std::move(queue_in[0]);
      queue_in.pop_front();
      return true;
    }
    return false;
  }
    
public:
  TriggerCandidateMaker& tcm;
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

    // // Nothing will be sending data anymore
    // mtx_queue_in.lock();

    // if (not queue_in.empty()) {
    //   std::cout << "TPs queue not entirely consumed, doing that now.\n";
    //   TriggerPrimitive tp;

    //   while (get_next_in_queue_no_mutex(tp)) {

    //     std::vector<TriggerCandidate> tcs;
    //     tcm(tp,tcs);
    //     mtx_queue_out.lock();
        
    //     for (auto const& tc: tcs) {
    //       queue_out.push_back(tc);
    //     }
    //     mtx_queue_out.unlock();
    //   }
    //   std::cout << "TPs consumed\n";
    // }

    // mtx_queue_in.unlock(); // Doesn't matter anyway

    
    int n_tries=10, i_try=0;
    
    while (true) {

      mtx_queue_out.lock();
      bool should_try_again = (not queue_out.empty() and i_try++<n_tries);
      mtx_queue_out.unlock();

      if (!should_try_again) break;

      if (not i_try) {
        std::cout << "TC queue isn't empty, waiting for consumer";
      } else {
        std::cout <<".";
      }
      
      std::chrono::milliseconds millisec_wait(50);
      std::this_thread::sleep_for(millisec_wait);
    }
    std::cout << "\n";
    mtx_queue_out.lock();
    if (not queue_out.empty()) {
      std::cout << "The consumer of TC hasn't caught up\n";
    }
    
    mtx_queue_in.unlock();
    mtx_queue_out.unlock();
    mtx_process_on.lock();
    process_on = false;
    mtx_process_on.unlock();
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
