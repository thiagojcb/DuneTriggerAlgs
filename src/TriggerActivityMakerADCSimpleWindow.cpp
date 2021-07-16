/**
 * @file TriggerActivityMakerADCSimpleWindow.cpp
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2021.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "triggeralgs/ADCSimpleWindow/TriggerActivityMakerADCSimpleWindow.hpp"

#include "TRACE/trace.h"
#define TRACE_NAME "TriggerActivityMakerADCSimpleWindow"

#include <vector>

using namespace triggeralgs;

void
TriggerActivityMakerADCSimpleWindow::operator()(const TriggerPrimitive& input_tp, std::vector<TriggerActivity>& output_ta)
{
  
  // The first time operator is called, reset
  // window object.
  if(m_current_window.is_empty()){
    m_current_window.reset(input_tp);
    m_primitive_count++;
    return;
  } 

  // If the difference between the current TP's start time and the start of the window
  // is less than the specified window size, add the TP to the window.
  if((input_tp.time_start - m_current_window.time_start) < m_window_length){
    //TLOG_DEBUG(TRACE_NAME) << "Window not yet complete, adding the input_tp to the window.";
    m_current_window.add(input_tp);
  }
  // If the addition of the current TP to the window would make it longer
  // than the specified window length, don't add it but check whether the sum of all adc in
  // the existing window is above the specified threshold. If it is, make a TA and start 
  // a fresh window with the current TP.
  else if(m_current_window.adc_integral > m_adc_threshold){
    //TLOG_DEBUG(TRACE_NAME) << "ADC integral in window is greater than specified threshold.";
    output_ta.push_back(construct_ta());
    //TLOG_DEBUG(TRACE_NAME) << "Resetting window with input_tp.";
    m_current_window.reset(input_tp);
  }
  // If it is not, move the window along.
  else{
    //TLOG_DEBUG(TRACE_NAME) << "Window is at required length but adc threshold not met, shifting window along.";
    m_current_window.move(input_tp, m_window_length);
  }
  
  TLOG_DEBUG(TRACE_NAME) << m_current_window;

  m_primitive_count++;

  return;
}

void
TriggerActivityMakerADCSimpleWindow::configure(const nlohmann::json &config)
{
  //FIXME use some schema here
  if (config.is_object()){
    if (config.contains("window_length")) m_window_length = config["window_length"];
    if (config.contains("adc_threshold")) m_adc_threshold = config["adc_threshold"];
  }
  else{
    TLOG_DEBUG(TRACE_NAME) << "The DEFAULT values of window_length and adc_threshold are being used.";
  }
  TLOG_DEBUG(TRACE_NAME) << "If the total ADC of trigger primitives with times within a "
                         << m_window_length << " tick time window is above " << m_adc_threshold << " counts, a trigger will be issued.";
}

TriggerActivity
TriggerActivityMakerADCSimpleWindow::construct_ta() const
{
  TLOG_DEBUG(TRACE_NAME) << "I am constructing a trigger activity!";
  TLOG_DEBUG(TRACE_NAME) << m_current_window;

  TriggerPrimitive latest_tp_in_window = m_current_window.tp_list.back();
  // The time_peak, time_activity, channel_* and adc_peak fields of this TA are irrelevent
  // for the purpose of this trigger alg.
  TriggerActivity ta{m_current_window.time_start, 
                     latest_tp_in_window.time_start+latest_tp_in_window.time_over_threshold,
                     latest_tp_in_window.time_peak,
                     latest_tp_in_window.time_peak,
                     latest_tp_in_window.channel,
                     latest_tp_in_window.channel,
                     latest_tp_in_window.channel,
                     m_current_window.adc_integral, 
                     latest_tp_in_window.adc_peak,
                     latest_tp_in_window.detid,
                     TriggerActivity::Type::kTPC,
                     TriggerActivity::Algorithm::kADCSimpleWindow, 
                     0,
                     m_current_window.tp_list}; 
  return ta;
}
