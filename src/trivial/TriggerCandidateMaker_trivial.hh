#pragma once
#include <iostream>
#include "TriggerCandidateMaker.hh"

using namespace DuneTriggers;

class TriggerCandidateMakerTrivial: public TriggerCandidateMaker {
  /// This candidate maker makes a candidate with all the trigger primitives
public:
  
  void operator()(const TriggerPrimitive& input_tp, std::vector<TriggerCandidate>& output_tc) {

    int64_t tend = input_tp.time_start+input_tp.time_over_threshold;
    
    if (m_time_start==0) {
      m_time_start    = input_tp.time_start;
      m_time_end      = tend;
      m_time_peak     = input_tp.time_peak;
      m_channel_start = input_tp.channel;
      m_channel_end   = input_tp.channel;
      m_channel_peak  = input_tp.channel;
      m_adc_integral  = input_tp.adc_integral;
      m_adc_peak      = input_tp.adc_peak;
      m_detid         = input_tp.detid;
      return;
    }
    
    bool is_close_to_edge = (m_time_tolerance > abs(input_tp.time_start - m_time_end  ) or
                             m_time_tolerance > abs(input_tp.time_start - m_time_start) or
                             m_time_tolerance > abs(tend - m_time_end  ) or
                             m_time_tolerance > abs(tend - m_time_start));
    
    bool is_in_between_edge = ((tend > m_time_start and tend < m_time_end) or
                               (input_tp.time_start > m_time_start and input_tp.time_start < m_time_end));
    
    if (not is_close_to_edge and not is_in_between_edge) {
      output_tc.push_back(MakeTriggerCandidate());
      
      m_time_start    = input_tp.time_start;
      m_time_end      = tend;
      m_time_peak     = input_tp.time_peak;
      m_channel_start = input_tp.channel;
      m_channel_end   = input_tp.channel;
      m_channel_peak  = input_tp.channel;
      m_adc_integral  = input_tp.adc_integral;
      m_adc_peak      = input_tp.adc_peak;
      m_detid         = input_tp.detid;
      return;
    }

    if (input_tp.time_start < m_time_start)
      m_time_start = input_tp.time_start;

    if (tend > m_time_end)
      m_time_end = tend;

    if (input_tp.adc_peak > m_adc_peak) {
      m_time_peak    = input_tp.time_peak;
      m_adc_peak     = input_tp.adc_peak;
      m_channel_peak = input_tp.channel;
    }

    if (input_tp.channel > m_channel_end)
      m_channel_end = input_tp.channel;
    
    if (input_tp.channel < m_channel_start)
      m_channel_start = input_tp.channel;
    
    m_adc_integral += input_tp.adc_integral;
    m_detid        |= input_tp.detid;
  }
  
  TriggerCandidateMakerTrivial():
    m_time_tolerance(10),
    m_time_start    (0),
    m_time_end      (0),
    m_time_peak     (0),
    m_channel_start (0),
    m_channel_end   (0),
    m_channel_peak  (0),
    m_adc_integral  (0),
    m_adc_peak      (0),
    m_detid         (0) {};
  
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
