/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef SCARAB_RADIATION_PRESSURE_SETTINGS_HPP
#define SCARAB_RADIATION_PRESSURE_SETTINGS_HPP

#include "Scarab/typedefs.hpp"

namespace scarab
{

//! Radiation pressure model settings.
/*!
 * Data struct containing all valid input parameters for the radiation pressure model. This struct
 * is populated by the checkSimulatorSettings() function.
 *
 * @sa checkSimulatorSettings, executeSimulator
 */
struct RadiationPressureSettings
{
public:

    //! Construct data struct.
    /*!
     * Constructs data struct based on verified input parameters.
     *
     * @sa checkSimulatorSettings, executeSimulator
     * @param[in] aStatus                       Flag indicating if model is on or off
     * @param[in] aRadiationPressure            Radiation pressure                          [N m^2]
     * @param[in] aRadiationPressureCoefficient Radiation pressure efficiency coefficient   [-]
     * @param[in] aVectorToSource               Position vector to source of radiation
     *                                          pressure, e.g, the Sun                      [m]
     * @param[in] aRadiationPressureArea        Area subject to radiation pressure          [m^2]
     */
    RadiationPressureSettings( const bool      aStatus,
                               const double    aRadiationPressure,
                               const double    aRadiationPressureCoefficient,
                               const Position& aVectorToSource,
                               const double    aRadiationPressureArea )
        : status( aStatus ),
          radiationPressure( aRadiationPressure ),
          radiationPressureCoefficient( aRadiationPressureCoefficient ),
          vectorToSource( aVectorToSource ),
          radiationPressureArea( aRadiationPressureArea )
    { }

    //! Status.
    const bool status;

    //! Radiation pressure [N m^-2].
    const double radiationPressure;

    //! Radiation pressure coefficient [-].
    const double radiationPressureCoefficient;

    //! Position vector to source of radiation pressure [m].
    const Position vectorToSource;

    //! Radiation pressure area [m^2].
    const double radiationPressureArea;

protected:

private:
};

} // namespace scarab

#endif // SCARAB_RADIATION_PRESSURE_SETTINGS_HPP
