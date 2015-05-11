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

#include <map>

#include "Scarab/accelerationModelId.hpp"
#include "Scarab/dataStore.hpp"

namespace scarab
{

//! Generate list of acceleration models.
/*!
 * Generates a list of acceleration models, given string names specified by the user. The data to
 * construct the acceleration models is retrieved from the data store provided.
 *
 * @param[in] listOfModelNames List of string-names of acceleration models specified by user
 * @param[in] data             Data store containing simulation data
 * @return                     List of acceleration model objects.
 */
ListOfAccelerationModels generateAccelerationModelList( const ListOfModelNames& listOfModelNames,
                                                        const DataStore& data );

} // namespace scarab

#endif // SCARAB_ACCELERATION_MODEL_LIST_GENERATOR_HPP
