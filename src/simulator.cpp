/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <fstream>
#include <iostream>
#include <limits>
#include <string>

#include <boost/numeric/odeint.hpp>
#include <boost/progress.hpp>

#include "Scarab/accelerationModelId.hpp"
#include "Scarab/accelerationModelListGenerator.hpp"
#include "Scarab/chaserSettings.hpp"
#include "Scarab/dataStore.hpp"
#include "Scarab/eventManager.hpp"
#include "Scarab/integratorSettings.hpp"
#include "Scarab/outputSettings.hpp"
#include "Scarab/radiationPressureSettings.hpp"
#include "Scarab/simulator.hpp"
#include "Scarab/stateDerivativeModel.hpp"
#include "Scarab/targetSettings.hpp"
#include "Scarab/tools.hpp"
#include "Scarab/typedefs.hpp"

namespace scarab
{

//! Execute simulator.
void executeSimulator( const rapidjson::Document& config )
{
    // Verify simulator settings. Exception is thrown if any of the parameters are missing.
    const SimulatorSettings settings = checkSimulatorSettings( config );

    std::cout << std::endl;
    std::cout << "******************************************************************" << std::endl;
    std::cout << "                             Simulator                            " << std::endl;
    std::cout << "******************************************************************" << std::endl;
    std::cout << std::endl;

    // Create data store with all simulation data.
    std::cout << "Creating data store with simulation data ..." << std::endl;
    // @TODO: Need to figure out a way to remove this line.
    ListOfAccelerationModels listOfAccelerationModels;
    DataStore data( settings.integratorSettings.initialState,
                    settings.integratorSettings.startTime,
                    settings.centralGravitySettings.gravitationalParameter,
                    listOfAccelerationModels );
    std::cout << "Created data store successfully!" << std::endl;

    // Create and populate list of models.
    std::cout << "Creating and populating list of models ..." << std::endl;
    generateAccelerationModelList( data );
    std::cout << "Created limitsst of models successfully!" << std::endl;

    // Create state derivative model.
    std::cout << "Creating state derivative model ..." << std::endl;
    StateDerivativeModel stateDerivativeModel( data );
    std::cout << "Created state derivative model successfully!" << std::endl;

    // Set up numerical integrator and execute integration.
    std::cout << "Set up and execute numerical integrator ..." << std::endl;
    State initialState = settings.integratorSettings.initialState; // @todo Fails to compile
                                                                   // without this.
    StateHistory stateHistory;
    stateHistory[ settings.integratorSettings.startTime ] = initialState;
    boost::progress_display showProgress( );
    boost::numeric::odeint::integrate( stateDerivativeModel,
                                       initialState,
                                       settings.integratorSettings.startTime,
                                       settings.integratorSettings.endTime,
                                       settings.integratorSettings.initialStep,
                                       EventManager( stateHistory ) );
    std::cout << "Executed numerical integrator successfully!" << std::endl;

    std::cout << std::endl;
    std::cout << "******************************************************************" << std::endl;
    std::cout << "                              Output                              " << std::endl;
    std::cout << "******************************************************************" << std::endl;
    std::cout << std::endl;

    // Write simulation metadata to file.
    std::cout << "Writing simulation metadata to file ..." << std::endl;
    std::ofstream metadataFile( settings.outputSettings.metadataFilename.c_str( ) );
    print( metadataFile, "gravitational_parameter", data.gravitationalParameter, "km^3 s^-2" );
    print( metadataFile, "initial_x",               initialState[ 0 ], "km" );
    print( metadataFile, "initial_y",               initialState[ 1 ], "km" );
    print( metadataFile, "initial_z",               initialState[ 2 ], "km" );
    print( metadataFile, "initial_vx",              initialState[ 3 ], "km s^-1" );
    print( metadataFile, "initial_vy",              initialState[ 4 ], "km s^-1" );
    print( metadataFile, "initial_vz",              initialState[ 5 ], "km s^-1" );
    print( metadataFile, "start_time",              settings.integratorSettings.startTime,   "s" );
    print( metadataFile, "end_time",                settings.integratorSettings.endTime,     "s" );
    print( metadataFile, "initial_step",            settings.integratorSettings.initialStep, "s" );
    metadataFile.close( );
    std::cout << "Simulation metadata written to file successfully!" << std::endl;

    // Write simulation data to file.
    std::cout << "Writing state history to file ..." << std::endl;
    const std::string outputFileHeader = "t,x,y,z,vx,vy,vz";
    std::ofstream outputFile( settings.outputSettings.stateHistoryFilename.c_str( ) );
    print( outputFile, stateHistory, outputFileHeader );
    outputFile.close( );
    std::cout << "State history written to file successfully!" << std::endl;
}

//! Check simulator settings.
SimulatorSettings checkSimulatorSettings( const rapidjson::Document& config )
{
    // Search for and store numerical integrator settings.
    std::cout << std::endl;
    std::cout << "Numerical integration settings" << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    State initialState;
    for ( unsigned int i = 0; i < initialState.size( ); i++ )
    {
        initialState[ i ] = find( config, "initial_state" )->value[ i ].GetDouble( );
    }
    std::cout << "Initial state                             [";
    for ( unsigned int i = 0; i < initialState.size( ) - 1; i++ )
    {
        std::cout << initialState[ i ] << "; ";
    }
    std::cout << initialState[ initialState.size( ) - 1 ] << "]" << std::endl;

    const double startTime      = find( config, "start_time" )->value.GetDouble( );
    std::cout << "Start time                                " << startTime << " s" << std::endl;
    const double endTime        = find( config, "end_time" )->value.GetDouble( );
    std::cout << "End time                                  " << endTime << " s" << std::endl;
    const double initialStep    = find( config, "initial_step" )->value.GetDouble( );
    std::cout << "Initial step                              " << initialStep << " s" << std::endl;

    const IntegratorSettings integratorSettings( initialState, startTime, endTime, initialStep );

    // Search for and store chaser settings.
    std::cout << std::endl;
    std::cout << "Chaser settings" << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    const double chaserMass     = find( config, "chaser" )->value[ "mass" ].GetDouble( );
    std::cout << "Mass                                      " << chaserMass << " kg" << std::endl;

    const ChaserSettings chaserSettings( chaserMass );

    // Search for and store target properties.
    std::cout << std::endl;
    std::cout << "Target settings" << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    const double targetMass     = find( config, "target" )->value[ "mass" ].GetDouble( );
    std::cout << "Mass                                      " << targetMass << " kg" << std::endl;

    const TargetSettings targetSettings( targetMass );

    // Search for and store central gravity model settings.
    std::cout << std::endl;
    std::cout << "Central gravity settings" << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    std::cout << "Status                                    ON" << std::endl;
    const double gravitationalParameter
        = find( config, "gravitational_parameter" )->value.GetDouble( );
    std::cout << "Gravitational parameter                   "
              << gravitationalParameter << " km^3 s^-2" << std::endl;

    const CentralGravitySettings centralGravitySettings( true, gravitationalParameter );

    // Search for and store radiation pressure model settings.
    std::cout << std::endl;
    std::cout << "Radiation pressure settings" << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    ConfigIterator radiationPressureIterator = find( config, "radiation_pressure" );
    const bool radiationPressureStatus   = radiationPressureIterator->value[ "status" ].GetBool( );
    double  radiationPressure            = std::numeric_limits< double >::signaling_NaN( );
    double  radiationPressureCoefficient = std::numeric_limits< double >::signaling_NaN( );
    double  radiationPressureArea        = std::numeric_limits< double >::signaling_NaN( );
    Position vectorToSource;
    vectorToSource[ 0 ] = std::numeric_limits< double >::signaling_NaN( );
    vectorToSource[ 1 ] = std::numeric_limits< double >::signaling_NaN( );
    vectorToSource[ 2 ] = std::numeric_limits< double >::signaling_NaN( );

    std::cout << "Status                                    ";
    if ( radiationPressureStatus == true )
    {
        std::cout << "ON" << std::endl;
        radiationPressure = radiationPressureIterator->value[ "radiation_pressure" ].GetDouble( );
        std::cout << "Radiation pressure                        "
                  << radiationPressure << " N m^-2" << std::endl;
        radiationPressureCoefficient
            = radiationPressureIterator->value[ "radiation_pressure_coefficient" ].GetDouble( );
        std::cout << "Radiation pressure coefficient            "
                  << radiationPressureCoefficient << std::endl;
        radiationPressureArea
            = radiationPressureIterator->value[ "radiation_pressure_area" ].GetDouble( );
        std::cout << "Radiation pressure area                   "
                  << radiationPressureArea << " m^2" << std::endl;

        for ( unsigned int i = 0; i < vectorToSource.size( ); i++ )
        {
            vectorToSource[ i ]
                = radiationPressureIterator->value[ "vector_to_source" ][ i ].GetDouble( );
        }
        std::cout << "Vector to source                          [";
        for ( unsigned int i = 0; i < vectorToSource.size( ) - 1; i++ )
        {
            std::cout << vectorToSource[ i ] << "; ";
        }
        std::cout << vectorToSource[ vectorToSource.size( ) - 1 ] << "]" << std::endl;
    }
    else
    {
        std::cout << "OFF" << std::endl;
    }

    const RadiationPressureSettings radiationPressureSettings( radiationPressureStatus,
                                                               radiationPressure,
                                                               radiationPressureCoefficient,
                                                               vectorToSource,
                                                               radiationPressureArea );

    // Search for and store output file names.
    std::cout << std::endl;
    std::cout << "Output settings" << std::endl;
    std::cout << "------------------------------------------" << std::endl;

    ConfigIterator outputIterator = find( config, "output" );
    const std::string metadataFilename = outputIterator->value[ "metadata_file" ].GetString( );
    std::cout << "Simulation metadata file                  " << metadataFilename << std::endl;
    const std::string stateHistoryFilename
        = outputIterator->value[ "state_history_file" ].GetString( );
    std::cout << "State history file                        " << stateHistoryFilename << std::endl;

    const OutputSettings outputSettings( metadataFilename, stateHistoryFilename );

    return SimulatorSettings( integratorSettings,
                              chaserSettings,
                              targetSettings,
                              centralGravitySettings,
                              radiationPressureSettings,
                              outputSettings );
}

} // namespace scarab