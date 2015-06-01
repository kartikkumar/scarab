/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef SCARAB_CENTRAL_GRAVITY_SETTINGS_HPP
#define SCARAB_CENTRAL_GRAVITY_SETTINGS_HPP

namespace scarab
{

//! Central gravity model settings.
/*!
 * Data struct containing all valid input parameters for the central gravity model. This struct is
 * populated by the checkSimulatorSettings() function.
 *
 * @sa checkSimulatorSettings, executeSimulator
 */
struct CentralGravitySettings
{
public:

    //! Construct data struct.
    /*!
     * Constructs data struct based on verified input parameters.
     *
     * @sa checkSimulatorSettings, executeSimulator
     * @param[in] aStatus                     Flag indicating if model is on or off
     * @param[in] aGravitationalParameter     Gravitational parameter of central body [km^3 m^-2]
     */
    CentralGravitySettings( const bool aStatus,
                            const double aGravitationalParameter )
        : status( aStatus ),
          gravitationalParameter( aGravitationalParameter )
    { }

    //! Status.
    const bool status;

    //! Gravitational parameter [km^3 m^-2].
    const double gravitationalParameter;

protected:

private:
};

} // namespace scarab

#endif // SCARAB_CENTRAL_GRAVITY_SETTINGS_HPP
