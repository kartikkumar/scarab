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
 * Data store containing all simulator data.
 */
struct DataStore
{
public:

    //! Default constructor.
    /*!
     * Calls default constructor.
     *
     * @param[in] aCurrentState             Current state
     * @param[in] aCurrentTime              Current time
     * @param[in] aGravitationalParameter   Gravitational parameter of central body     [km^3 s^-2]
     * @param[in] aListOfAccelerationModels List of acceleration models executed by
     *                                      simulator
     */
    DataStore( const State&                     aCurrentState,
               const double                     aCurrentTime,
               const double                     aGravitationalParameter,
               const ListOfAccelerationModels&  aListOfAccelerationModels )
        : currentState( aCurrentState ),
          currentTime( aCurrentTime ),
          gravitationalParameter( aGravitationalParameter ),
          listOfAccelerationModels( aListOfAccelerationModels )
    { }

    //! Current state vector.
    State currentState;

    //! Current time.
    double currentTime;

    //! Gravitational parameter [km^3 s^-2].
    double gravitationalParameter;

    //! List of acceleration models.
    ListOfAccelerationModels listOfAccelerationModels;

protected:

private:
};

} // namespace scarab

#endif // SCARAB_DATA_STORE_HPP
