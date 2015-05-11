/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <sstream>
#include <stdexcept>

#include <boost/make_shared.hpp>

#include "Scarab/accelerationModel.hpp"
#include "Scarab/accelerationModelListGenerator.hpp"
#include "Scarab/centralGravityModel.hpp"

namespace scarab
{

//! Generate list of acceleration models.
ListOfAccelerationModels generateAccelerationModelList( const ListOfModelNames& listOfModelNames,
                                                        const DataStore& data )
{
    ListOfAccelerationModels listOfAccelerationModels;

    for ( unsigned int i = 0; i < listOfModelNames.size( ); i++ )
    {
        if ( !listOfModelNames[ i ].compare( "central_gravity" ) )
        {
            AccelerationModel3dPtr centralGravity
                = boost::make_shared< CentralGravityModel >( data.gravitationalParameter );
            listOfAccelerationModels[ centralGravityModel ] = centralGravity;
        }

        else
        {
            std::ostringstream errorMessage;
            errorMessage << "ERROR: \"" <<  listOfModelNames[ i ]
                         << "\" is an invalid model name!" << std::endl;
            throw std::runtime_error( errorMessage.str( ) );
        }
    }
    return listOfAccelerationModels;
}

} // namespace scarab
