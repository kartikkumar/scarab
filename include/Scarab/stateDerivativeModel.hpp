/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef SCARAB_STATE_DERIVATIVE_MODEL_HPP
#define SCARAB_STATE_DERIVATIVE_MODEL_HPP

#include <boost/array.hpp>

#include "Scarab/accelerationModelId.hpp"
#include "Scarab/dataStore.hpp"
#include "Scarab/typedefs.hpp"

namespace scarab
{


//! State derivative model.
/*!
 * State derivative model that can be used to compute the state derivative for a given state and
 * parameter values at a given epoch. This model fulfills the requirements to be used with the
 * Boost odeint library (K. Ahnert and M. Mulansky, 2011).
 *
 * @sa <a href="http://www.odeint.com">odeint</a>
 */
class StateDerivativeModel
{
public:

    //! Default constructor.
    /*!
     * Calls default constructor.
     *
     * @param[in] simulationData Data store containing simulation data
     */
    StateDerivativeModel( DataStore& simulationData )
        : data( simulationData )
    { }

    // void operator( )( const State& state, State& stateDerivative, double time )
    void operator( )( const State& state, State& stateDerivative, double time )
    {
        Acceleration acceleration;
        acceleration[ 0 ] = 0.0;
        acceleration[ 1 ] = 0.0;
        acceleration[ 2 ] = 0.0;
        ListOfAccelerationModels modelList = data.listOfAccelerationModels;
        for ( ListOfModelsIt it = modelList.begin( ); it != modelList.end( ); it++ )
        {
            Acceleration _acceleration = ( *it->second )( state, time );

            for ( unsigned int i = 0; i < _acceleration.size( ); i++ )
            {
                acceleration[ i ] += _acceleration[ i ];
            }
        }

        stateDerivative[ 0 ] = state[ 3 ];
        stateDerivative[ 1 ] = state[ 4 ];
        stateDerivative[ 2 ] = state[ 5 ];
        stateDerivative[ 3 ] = acceleration[ 0 ];
        stateDerivative[ 4 ] = acceleration[ 1 ];
        stateDerivative[ 5 ] = acceleration[ 2 ];
    }

protected:

private:

    //! Simulation data store.
    const DataStore& data;
};

} // namespace scarab

#endif // SCARAB_STATE_DERIVATIVE_MODEL_HPP

/*!
 * K. Ahnert and M. Mulansky, Odeint - Solving Ordinary Differential Equations in C++, AIP Conf.
 *  Proc. 1389, pp. 1586-1589 (2011), doi:http://dx.doi.org/10.1063/1.3637934.
 */
