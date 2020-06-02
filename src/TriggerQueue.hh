#pragma once
#include <boost/circular_buffer/base.hpp>

namespace DuneTriggers {
  template <class data_in,class data_out>
  class TriggerQueue {
  protected:
    boost::circular_buffer<data_in> queue_in;
    boost::circular_buffer<data_out> queue_out;
    virtual void Process() = 0;
    
    bool get_next_in_queue_in(data_in& data) {
      if (not queue_in.empty()) {
        dat = std::move(queue_in[0]);
        queue_in.pop_front();
        return true;
      }
      return false;
    }
    
  public:
    void AddToQueue(const data_in& dat) {
      queue.push_back(dat);
    };
    
    void AddToQueue(const std::vector<data_in>& dats) {
      std::for_each(dats.begin(), dats.end(), [queue_in&](data_in dat)->void {queue_in.push_back(dat);});
    };

    void Worker() {
      Process();
    }

    const bool GetNextProcessed(data_out& dat) {
      if (not queue_out.empty()) {
        dat = std::move(queue_out[0]);
        queue_out.pop_front();
        return true;
      }
      return false;
    }
  }
}

