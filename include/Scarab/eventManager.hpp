/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef SCARAB_EVENT_MANAGER_HPP
#define SCARAB_EVENT_MANAGER_HPP

#include "Scarab/typedefs.hpp"

namespace scarab
{

//! Event manager.
/*!
 * Event manager that excutes after each step taken by the numerical integrator.
 */
class EventManager
{
public:

    //! Default constructor.
    /*!
     * Calls default constructor.
     *
     * @param[in] aStateHistory State history (key=epoch, value=State)
     */
    EventManager( StateHistory& aStateHistory )
        : stateHistory( aStateHistory )
    { }

    //! Execute event manager.
    /*!
     * Executes event manager by overloading ()-operator.
     *
     * @param[in] state Current state
     * @param[in] time  Current time
     */
    void operator( )( const State& state, const double time )
    {
        stateHistory[ time ] = state;
    }

    //! State history (key=epoch, value=State)
    StateHistory& stateHistory;

protected:

private:

};

} // namespace scarab

#endif // SCARAB_EVENT_MANAGER_HPP




// //[ integrate_observer
// struct push_back_state_and_time
// {

//     Data< Real, State, Acceleration >& data;

//     push_back_state_and_time( std::vector< State > &states , std::vector< double > &timeHistory,
//                               Data< Real, State, Acceleration >& aDataStore )
//         : m_states( states ) , m_timeHistory( timeHistory ), data( aDataStore )
//     { }

//     void operator( )( const State &x , double t )
//     {
//         m_states.push_back( x );
//         m_timeHistory.push_back( t );
//         data.state = x;
//     }
// };
// //]