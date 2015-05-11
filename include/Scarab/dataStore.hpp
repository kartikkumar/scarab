/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef SCARAB_DATA_STORE_HPP
#define SCARAB_DATA_STORE_HPP

#include "Scarab/accelerationModelId.hpp"
#include "Scarab/typedefs.hpp"

namespace scarab
{

//! Data store.
/*!
 * Data store containing all inputs and parameters required for the simulator.
 */
struct DataStore
{
public:

    //! Default constructor.
    /*!
     * Calls default constructor.
     *
     * @param[in] aGravitationalParameter   Gravitational parameter of central body [km^3 s^-2]
     * @param[in] aState                    Current state
     * @param[in] aListOfAccelerationModels List of acceleration models executed by simulator.
     */
    DataStore( const double aGravitationalParameter,
               const State& aState,
               const ListOfAccelerationModels& aListOfAccelerationModels )
        : gravitationalParameter( aGravitationalParameter ),
          currentState( aState ),
          listOfAccelerationModels( aListOfAccelerationModels )
    { }

    //! Gravitational parameter of central body [km^3 s^-2].
    double gravitationalParameter;

    //! Current state vector.
    State currentState;

    //! List of acceleration models.
    ListOfAccelerationModels listOfAccelerationModels;

protected:

private:
};

} // namespace scarab

#endif // SCARAB_DATA_STORE_HPP
