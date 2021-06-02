/**
 * @file Types.hpp
 *
 * This is part of the DUNE DAQ Application Framework, copyright 2020.
 * Licensing/copyright details are in the COPYING file that you should have
 * received with this code.
 */

#ifndef TRIGGERALGS_INCLUDE_TRIGGERALGS_TYPES_HPP_
#define TRIGGERALGS_INCLUDE_TRIGGERALGS_TYPES_HPP_

#include <cstdint>

namespace triggeralgs {

// A data timestamp in timing system clock ticks (50 MHz for
// ProtoDUNE-I, 62.5 MHz for ProtoDUNE-II and DUNE FD). If/when we
// depend on dataformats, we can get these from there
using timestamp_t = uint64_t; // NOLINT

using timestamp_diff_t = int64_t;

// A logical region of the detector from which DS objects may be
// formed, eg an APA or a module
//
// TODO P. Rodrigues 2021-06-01: it would be nice to have this be just
// dataformats::GeoID, if/when we can depend on the dataformats
// package
using detid_t = uint16_t;

// A channel number
using channel_t = int32_t;

} // namespace triggeralgs

#endif // TRIGGERALGS_INCLUDE_TRIGGERALGS_TRIGGERCANDIDATEMAKER_HPP_
