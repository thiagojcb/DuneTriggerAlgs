#pragma once
#include <chrono>
#include <thread>
#include <mutex>
#include <iostream>
#include <boost/circular_buffer.hpp>

namespace DuneTriggers {
  template <class data_in,class data_out>
  class TriggerQueue {
  protected:
    boost::circular_buffer<data_in> queue_in;
    boost::circular_buffer<data_out> queue_out;
    std::mutex mtx_queue_in;
    std::mutex mtx_queue_out;
    std::mutex mtx_process_on;
    virtual void Process() = 0;
    bool process_on;
    
    bool get_next_in_queue_no_mutex(data_in& dat) {
      if (not queue_in.empty()) {
        dat = std::move(queue_in[0]);
        queue_in.pop_front();
        return true;
      }
      return false;
    }
    
  public:
    TriggerQueue(size_t depth_in, size_t depth_out):
      queue_in  (depth_in ),
      queue_out (depth_out),
      mtx_queue_in (),
      mtx_queue_out(),
      mtx_process_on(),
      process_on(false) {
    }
    
    void AddToQueue(const data_in& dat) {
      mtx_queue_in.lock();
      queue_in.push_back(dat);
      mtx_queue_in.unlock();
    }
    
    void AddToQueue(const std::vector<data_in>& dats) {
      mtx_queue_in.lock();
      std::for_each(dats.begin(), dats.end(), [this](data_in dat)->void {this->queue_in.push_back(dat);});
      mtx_queue_in.unlock();
    }

    void Worker() {
      while (true) {
        mtx_queue_in.lock();
        mtx_queue_out.lock();
        Process();
        mtx_queue_in.unlock();
        mtx_queue_out.unlock();

        std::chrono::milliseconds millisec_wait(50);
        std::this_thread::sleep_for(millisec_wait);

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
      if (not queue_out.empty or not queue_in.empty()) {
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
    
    const bool GetNextProcessed(data_out& dat) {
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
}

