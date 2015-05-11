/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef SCARAB_SIMULATIOR_HPP
#define SCARAB_SIMULATIOR_HPP

#include <rapidjson/document.h>

#include "Scarab/typedefs.hpp"

namespace scarab
{

//! Execute simulator.
/*!
 * Executes simulator using paameters specified by user in JSON input file.
 *
 * @param[in] config User-defined configuration options (extracted from JSON input file)
 */
void executeSimulator( const rapidjson::Document& config );

//! Simulator input.
/*!
 * Data struct containing all valid input parameters for the simulator. This struct is populated
 * by the checkSimulatorInput() function.
 *
 * @sa checkSimulatorInput, executeSimulator
 */
struct SimulatorInput
{
public:

    //! Construct data struct.
    /*!
     * Constructs data struct based on verified input parameters.
     *
     * @sa checkSimulatorInput, executeSimulator
     * @param[in] aGravitationalParameter Gravitational parameter of central body  [km^3 2^-2]
     * @param[in] anInitialState          Initial state                            [km; km/s]
     * @param[in] aStartTime              Simulation start time                    [s]
     * @param[in] anEndTime               Simulation end time                      [s]
     * @param[in] anInitialStep           Simulation initial time step             [s]
     * @param[in] aListOfModelNames       List of names of models to include
     * @param[in] aMetadataFilename       Simulation metadata filename
     * @param[in] aStateHistoryFilename   State history filename
     */
    SimulatorInput( const double            aGravitationalParameter,
                    const State&            anInitialState,
                    const double            aStartTime,
                    const double            anEndTime,
                    const double            anInitialStep,
                    const ListOfModelNames& aListOfModelNames,
                    const std::string       aMetadataFilename,
                    const std::string       aStateHistoryFilename )
        : gravitationalParameter( aGravitationalParameter ),
          initialState( anInitialState ),
          startTime( aStartTime ),
          endTime( anEndTime ),
          initialStep( anInitialStep ),
          listOfModelNames( aListOfModelNames ),
          metadataFilename( aMetadataFilename ),
          outputFilename( aStateHistoryFilename )
    { }

    //! Gravitational parameter of central body [km^3 2^-2].
    const double gravitationalParameter;

    //! Initial state [km; km/s].
    const State initialState;

    //! Start time for numerical integration.
    const double startTime;

    //! End time for numerical integration.
    const double endTime;

    //! Initial step for numerical integration.
    const double initialStep;

    //! A list of names of models.
    const ListOfModelNames listOfModelNames;

    //! Simulation metadata filename.
    const std::string metadataFilename;

    //! State history filename.
    const std::string outputFilename;

protected:

private:
};

//! Check simulator input parameters.
/*!
 * Checks that all inputs for the simulator are valid. If not, an error is thrown with a short
 * description of the problem.
 *
 * If all inputs are valid, a data struct containing all the inputs is returned, which is
 * subsequently used to execute the simulator and related functions.
 *
 * @sa executeSimulator, SimulatorInput
 * @param[in] config User-defined configuration options (extracted from JSON input file)
 * @return           Struct containing all valid input
 */
SimulatorInput checkSimulatorInput( const rapidjson::Document& config );

} // namespace scarab

#endif // SCARAB_SIMULATIOR_HPP
