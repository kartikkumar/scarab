/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef SCARAB_ACCELERATION_MODEL_LIST_GENERATOR_HPP
#define SCARAB_ACCELERATION_MODEL_LIST_GENERATOR_HPP

#include "Scarab/accelerationModelId.hpp"
#include "Scarab/dataStore.hpp"

namespace scarab
{

//! Generate list of acceleration models.
/*!
 * Generates a list of acceleration models. The data to construct the acceleration models is
 * retrieved from the simulator data provided.
 *
 * @param[in] data  Data store containing all simulation data, including populated list of
 *                  acceleration models
 */
void generateAccelerationModelList( DataStore& data );

} // namespace scarab

#endif // SCARAB_ACCELERATION_MODEL_LIST_GENERATOR_HPP
