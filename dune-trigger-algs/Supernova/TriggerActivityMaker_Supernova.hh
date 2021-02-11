#pragma once
#include "dune-trigger-algs/TriggerActivityMaker.hh"

#include <algorithm>
#include <limits>

namespace triggeralgs {
  class TriggerActivityMakerSupernova: public TriggerActivityMaker {

  
    /// This activity maker makes an activity with all the trigger primitives
    inline bool is_time_consistent(const TriggerPrimitive& input_tp) const {
    
      int64_t tend = input_tp.time_start+input_tp.time_over_threshold;
    
      bool is_close_to_edge = (m_time_tolerance > abs(input_tp.time_start - m_time_end  ) or
                               m_time_tolerance > abs(input_tp.time_start - m_time_start) or
                               m_time_tolerance > abs(tend - m_time_end  ) or
                               m_time_tolerance > abs(tend - m_time_start));
    
      bool is_in_between_edge = ((tend > m_time_start and tend < m_time_end) or
                                 (input_tp.time_start > m_time_start and input_tp.time_start < m_time_end));

      return is_in_between_edge or is_close_to_edge;
    }

    inline bool is_channel_consistent(const TriggerPrimitive& input_tp) const {
    
      bool is_close_to_edge = (m_channel_tolerance > abs((int32_t)input_tp.channel - (int32_t)m_channel_end  ) or
                               m_channel_tolerance > abs((int32_t)input_tp.channel - (int32_t)m_channel_start));
    
      bool is_in_between_edge = (input_tp.channel > m_channel_start and input_tp.channel < m_channel_end);

      return is_in_between_edge or is_close_to_edge;
    }
  
  public:
  
    void operator()(const TriggerPrimitive& input_tp, std::vector<TriggerActivity>& output_ta);
  
    void flush(std::vector<TriggerActivity>& tas) {
      tas.push_back(MakeTriggerActivity());
    }

  private:
  
    TriggerActivity MakeTriggerActivity() const {
      TriggerActivity ta {m_time_start,
                           m_time_end,
                           m_time_peak,
	                   m_time_formed,
                           m_channel_start,
                           m_channel_end,
                           m_channel_peak,
                           m_adc_integral,
                           m_adc_peak,
	                   m_detid,
	                   m_type,
	                   m_algorithm,
                 	   m_version,
                 	   m_tp_list};
      return ta;
    }
    
    int64_t  m_time_tolerance    = 250;  /// Maximum tolerated time difference between two primitives to form an activity (in 50 MHz clock ticks)
    int32_t  m_channel_tolerance = 2;    /// Maximum tolerated channel number difference between two primitives to form an activity
    int64_t  m_time_start        = 0;
    int64_t  m_time_end          = 0;
    int64_t  m_time_peak         = 0;
    int64_t  m_time_formed       = 0;
    uint32_t m_channel_start     = 0;
    uint32_t m_channel_end       = 0;
    uint32_t m_channel_peak      = 0;
    uint16_t m_adc_integral      = 0;
    uint16_t m_adc_peak          = 0;
    uint32_t m_detid             = 0;
    uint32_t m_type              = 0;
    uint32_t m_algorithm         = 0;
    uint16_t m_version           = 0;

    std::vector<TriggerPrimitive> m_tp_list;

  };
}
