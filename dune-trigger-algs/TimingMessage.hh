#pragma once
#include <cstdint>

namespace triggeralgs {
  struct TimingMessage {
    uint32_t  signal_type    = {0};
    int64_t  time_stamp     = {0};
    uint32_t  counter	    = {0};
  };
}
