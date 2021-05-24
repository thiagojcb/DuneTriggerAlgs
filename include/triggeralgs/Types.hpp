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
// ProtoDUNE-I, 62.5 MHz for ProtoDUNE-II and DUNE FD). Ideally we
// would get this definition from somewhere else, but we don't have a
// package that we depend on that provides it
using timestamp_t = uint64_t; // NOLINT

} // namespace triggeralgs

#endif // TRIGGERALGS_INCLUDE_TRIGGERALGS_TRIGGERCANDIDATEMAKER_HPP_
