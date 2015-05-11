/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef SCARAB_CENTRAL_GRAVITY_MODEL_HPP
#define SCARAB_CENTRAL_GRAVITY_MODEL_HPP

#include <boost/shared_ptr.hpp>

#include <SML/sml.hpp>

#include "Scarab/accelerationModel.hpp"
#include "Scarab/typedefs.hpp"

namespace scarab
{

//! Central gravitational acceleration model.
class CentralGravityModel : public AccelerationModel< Acceleration >
{
public:

    CentralGravityModel( const double& aGravitationalParameter )
        : gravitationalParameter( aGravitationalParameter )
    { }

    Acceleration operator( )( const State& state, const double /* time */ )
    {
        Acceleration acceleration;

        Position position;
        position[ 0 ] = state[ 0 ];
        position[ 1 ] = state[ 1 ];
        position[ 2 ] = state[ 2 ];

        const double positionNorm = sml::norm< double >( position );

        acceleration[ 0 ] = -gravitationalParameter * position[ 0 ]
                                / ( positionNorm * positionNorm * positionNorm );
        acceleration[ 1 ] = -gravitationalParameter * position[ 1 ]
                                / ( positionNorm * positionNorm * positionNorm );
        acceleration[ 2 ] = -gravitationalParameter * position[ 2 ]
                                / ( positionNorm * positionNorm * positionNorm );

        return acceleration;
    }

protected:

private:

    //! Gravitational parameter of central body [km^3 s^-2].
    const double& gravitationalParameter;
};

typedef boost::shared_ptr< CentralGravityModel > CentralGravityModelPtr;

} // namespace scarab

#endif // SCARAB_CENTRAL_GRAVITY_MODEL_HPP
