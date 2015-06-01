/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef SCARAB_INTEGRATOR_SETTINGS_HPP
#define SCARAB_INTEGRATOR_SETTINGS_HPP

#include "Scarab/typedefs.hpp"

namespace scarab
{

//! Numerical integrator settings.
/*!
 * Data struct containing all valid settings parameters for the numerical integrator. This struct
 * is populated by the checkSimulatorSettings() function.
 *
 * @sa checkSimulatorSettings, executeSimulator
 */
struct IntegratorSettings
{
public:

    //! Construct data struct.
    /*!
     * Constructs data struct based on verified simulator settings.
     *
     * @sa checkSimulatorSettings, executeSimulator
     * @param[in] anInitialState          Initial state
     * @param[in] aStartTime              Simulation start time                    [s]
     * @param[in] anEndTime               Simulation end time                      [s]
     * @param[in] anInitialStep           Simulation initial time step             [s]
     */
    IntegratorSettings( const State&            anInitialState,
                        const double            aStartTime,
                        const double            anEndTime,
                        const double            anInitialStep )
        : initialState( anInitialState ),
          startTime( aStartTime ),
          endTime( anEndTime ),
          initialStep( anInitialStep )
    { }

    //! Initial state.
    const State initialState;

    //! Start time for numerical integration [s].
    const double startTime;

    //! End time for numerical integration [s].
    const double endTime;

    //! Initial step for numerical integration [s].
    const double initialStep;

protected:

private:
};

} // namespace scarab

#endif // SCARAB_INTEGRATOR_SETTINGS_HPP
