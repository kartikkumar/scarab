/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef SCARAB_SIMULATOR_SETTINGS_HPP
#define SCARAB_SIMULATOR_SETTINGS_HPP

#include <string>

#include "Scarab/centralGravitySettings.hpp"
#include "Scarab/chaserSettings.hpp"
#include "Scarab/integratorSettings.hpp"
#include "Scarab/outputSettings.hpp"
#include "Scarab/radiationPressureSettings.hpp"
#include "Scarab/targetSettings.hpp"

namespace scarab
{

//! Simulator settings.
/*!
 * Data struct containing all valid settings parameters for the simulator. This struct is populated
 * by the checkSimulatorSettings() function.
 *
 * @sa checkSimulatorSettings, executeSimulator
 */
struct SimulatorSettings
{
public:

    //! Construct data struct.
    /*!
     * Constructs data struct based on verified input parameters.
     *
     * @sa checkSimulatorSettings, executeSimulator, IntegratorSettings
     * @param[in] integratorUserSettings        User-defined numerical integrator settings
     * @param[in] chaserUserSettings            User-defined chaser settings
     * @param[in] targetUserSettings            User-defined target settings
     * @param[in] centralGravityUserSettings    User-defined central gravity model settings
     * @param[in] radiationPressureUserSettings User-defined radiation pressure model settings
     * @param[in] outputUserSettings            User-defined output settings
     */
    SimulatorSettings( const IntegratorSettings&        integratorUserSettings,
                       const ChaserSettings&            chaserUserSettings,
                       const TargetSettings&            targetUserSettings,
                       const CentralGravitySettings&    centralGravityUserSettings,
                       const RadiationPressureSettings& radiationPressureUserSettings,
                       const OutputSettings&            outputUserSettings )
        : integratorSettings( integratorUserSettings ),
          chaserSettings( chaserUserSettings ),
          targetSettings( targetUserSettings ),
          centralGravitySettings( centralGravityUserSettings ),
          radiationPressureSettings( radiationPressureUserSettings ),
          outputSettings( outputUserSettings )
    { }

    //! Numerical integrator settings.
    const IntegratorSettings integratorSettings;

    //! Chaser settings.
    const ChaserSettings chaserSettings;

    //! Target settings.
    const TargetSettings targetSettings;

    //! Central gravity model settings.
    const CentralGravitySettings centralGravitySettings;

    //! Radiation pressure model settings.
    const RadiationPressureSettings radiationPressureSettings;

    //! Output settings.
    const OutputSettings outputSettings;

protected:

private:
};

} // namespace scarab

#endif // SCARAB_SIMULATOR_SETTINGS_HPP
