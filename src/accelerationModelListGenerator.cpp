/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <boost/make_shared.hpp>

#include "Scarab/accelerationModel.hpp"
#include "Scarab/accelerationModelId.hpp"
#include "Scarab/accelerationModelListGenerator.hpp"
#include "Scarab/centralGravityModel.hpp"

namespace scarab
{

//! Generate list of acceleration models.
void generateAccelerationModelList( DataStore& data )
{
    // Create central gravity model and add to list.
    data.listOfAccelerationModels[ centralGravityModelId ]
        = boost::make_shared< CentralGravityModel >( data.gravitationalParameter );
}

} // namespace scarab
