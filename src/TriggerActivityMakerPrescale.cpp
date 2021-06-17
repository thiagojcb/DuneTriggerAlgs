/**
 * @file TriggerActivityMakerPrescale.cpp
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#include "triggeralgs/Prescale/TriggerActivityMakerPrescale.hpp"

#include <vector>
#include <iostream>

using namespace triggeralgs;

void
TriggerActivityMakerPrescale::operator()(const TriggerPrimitive& input_tp, std::vector<TriggerActivity>& output_ta)
{
  if ((m_primitive_count++) % m_prescale == 0) 
  {
    //std::cout << "Emitting prescaled TriggerActivity " << m_primitive_count << std::endl;
    std::vector<TriggerPrimitive> tp_list;
    tp_list.push_back(input_tp);
    TriggerActivity ta { 
      input_tp.time_start, 
      input_tp.time_start+input_tp.time_over_threshold, 
      input_tp.time_peak, 
      /*time_activity*/ 0, 
      input_tp.channel, 
      input_tp.channel,
      input_tp.channel, 
      input_tp.adc_integral,
      input_tp.adc_peak, 
      input_tp.detid, 
      0, 
      0, 
      0, 
      tp_list 
    };
    output_ta.push_back(ta);
  }
}

void
TriggerActivityMakerPrescale::configure(const nlohmann::json &config)
{
  //FIXME use some schema here
  if (config.is_object() && config.contains("prescale"))
  {
    m_prescale = config["prescale"]; 
  }
  std::cout << "Using activity prescale " << m_prescale << std::endl;
}
