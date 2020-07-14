#pragma once

#include "dune-triggers/TriggerCandidateMaker.hh"
#include "includes/json.hpp"

#include <algorithm>
#include <limits>

namespace DuneTriggers{
  class TriggerCandidateMakerSupernova: public TriggerCandidateMaker, public TriggerCandidate{

  
    /// This candidate maker makes a candidate with all the trigger primitives
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
  
    void operator()(const TriggerPrimitive& input_tp, std::vector<TriggerCandidate>& output_tc);
  
    TriggerCandidateMakerSupernova(std::string json):
      TriggerCandidateMaker(json) {
      auto params = nlohmann::json::parse(json);
      m_time_tolerance    = params["time_tolerance"];
      m_channel_tolerance = params["channel_tolerance"];
      m_time_start        = 0;
      m_time_end          = 0;
      m_time_peak         = 0;
      m_channel_start     = 0;
      m_channel_end       = 0;
      m_channel_peak      = 0;
      m_adc_integral      = 0;
      m_adc_peak          = 0;
      m_detid             = 0;
    };
  
    bool GetLastCluster(TriggerCandidate& tc) const {
      tc = MakeTriggerCandidate();
      return true;
    }

  private:
  
    TriggerCandidate MakeTriggerCandidate() const {
      TriggerCandidate tc {m_time_start,
                           m_time_end,
                           m_time_peak,  
                           m_channel_start,
                           m_channel_end,
                           m_channel_peak,
                           m_adc_integral,
                           m_adc_peak,
                           m_detid};
      return tc;
    }
    
    int64_t m_time_tolerance;
    int32_t m_channel_tolerance;
  
    int64_t  m_time_start;
    int64_t  m_time_end;
    int64_t  m_time_peak;
    uint32_t m_channel_start;
    uint32_t m_channel_end;
    uint32_t m_channel_peak;
    uint16_t m_adc_integral;
    uint16_t m_adc_peak;
    uint32_t m_detid;

  };
}
