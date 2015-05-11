/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef SCARAB_ACCELERATION_MODEL_ID_HPP
#define SCARAB_ACCELERATION_MODEL_ID_HPP

#include <map>

#include "Scarab/accelerationModel.hpp"

namespace scarab
{

//! Acceleration Model ID.
/*!
 * Acceleration model identifier.
 */
enum AccelerationModelId
{
    centralGravityModel = 0
};

//! List of acceleration models.
/*!
 * List of acceleration models, stored with a unique identifier.
 */
typedef std::map< AccelerationModelId, AccelerationModel3dPtr > ListOfAccelerationModels;

typedef ListOfAccelerationModels::iterator ListOfModelsIt;
typedef ListOfAccelerationModels::const_iterator ListOfModelsConstIt;

} // namespace scarab

#endif // SCARAB_ACCELERATION_MODEL_ID_HPP
