/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef SCARAB_SIMULATOR_HPP
#define SCARAB_SIMULATOR_HPP

#include <rapidjson/document.h>

#include "Scarab/simulatorSettings.hpp"

namespace scarab
{

//! Execute simulator.
/*!
 * Executes simulator using parameters specified by user in JSON input file.
 *
 * @param[in] config User-defined configuration options (extracted from JSON input file)
 */
void executeSimulator( const rapidjson::Document& config );

//! Check simulator settings.
/*!
 * Checks that all settings for the simulator are valid. If not, an error is thrown with a short
 * description of the problem.
 *
 * If all settings are valid, a data struct containing all the settings is returned, which is
 * subsequently used to execute the simulator and related functions.
 *
 * @sa executeSimulator, SimulatorSettings
 * @param[in] config User-defined configuration options (extracted from JSON input file)
 * @return           Struct containing all valid simulator settings
 */
SimulatorSettings checkSimulatorSettings( const rapidjson::Document& config );

} // namespace scarab

#endif // SCARAB_SIMULATOR_HPP
