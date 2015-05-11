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
#include <sstream>
#include <stdexcept>

#include <boost/make_shared.hpp>
#include <boost/numeric/odeint.hpp>
#include <boost/progress.hpp>

#include "Scarab/accelerationModelListGenerator.hpp"
#include "Scarab/centralGravityModel.hpp"
#include "Scarab/dataStore.hpp"
#include "Scarab/eventManager.hpp"
#include "Scarab/simulator.hpp"
#include "Scarab/stateDerivativeModel.hpp"
#include "Scarab/tools.hpp"

namespace scarab
{

//! Execute simulator.
void executeSimulator( const rapidjson::Document& config )
{
    // Verify config parameters. Exception is thrown if any of the parameters are missing.
    const SimulatorInput input = checkSimulatorInput( config );

    std::cout << std::endl;
    std::cout << "******************************************************************" << std::endl;
    std::cout << "                             Simulator                            " << std::endl;
    std::cout << "******************************************************************" << std::endl;
    std::cout << std::endl;

    // Create data store with all simulation data.
    std::cout << "Creating data store with simulation data ..." << std::endl;
    ListOfAccelerationModels listOfAccelerationModels;
    DataStore data( input.gravitationalParameter, input.initialState, listOfAccelerationModels );
    std::cout << "Created data store successfully!" << std::endl;

    // Create and populate list of models.
    std::cout << "Creating and populating list of models ..." << std::endl;
    data.listOfAccelerationModels = generateAccelerationModelList( input.listOfModelNames, data );
    std::cout << "Created list of models successfully!" << std::endl;

    // Create state derivative model.
    std::cout << "Creating state derivative model ..." << std::endl;
    StateDerivativeModel stateDerivativeModel( data );
    std::cout << "Created state derivative model successfully!" << std::endl;

    // Set up numerical integrator and execute integration.
    std::cout << "Set up and execute numerical integrator ..." << std::endl;
    State initialState = input.initialState; // @todo Fails to compile without this.
    StateHistory stateHistory;
    stateHistory[ input.startTime ] = initialState;
    boost::progress_display showProgress( );
    boost::numeric::odeint::integrate( stateDerivativeModel,
                                       initialState,
                                       input.startTime,
                                       input.endTime,
                                       input.initialStep,
                                       EventManager( stateHistory ) );
    std::cout << "Executed numerical integrator successfully!" << std::endl;

    std::cout << std::endl;
    std::cout << "******************************************************************" << std::endl;
    std::cout << "                               Output                             " << std::endl;
    std::cout << "******************************************************************" << std::endl;
    std::cout << std::endl;

    // Write simulation metadata to file.
    std::cout << "Writing simulation metadata to file ..." << std::endl;
    std::ofstream metadataFile( input.metadataFilename.c_str( ) );
    print( metadataFile, "gravitational_parameter", data.gravitationalParameter, "km^3 s^-2" );
    print( metadataFile, "initial_x",               initialState[ 0 ], "km" );
    print( metadataFile, "initial_y",               initialState[ 1 ], "km" );
    print( metadataFile, "initial_z",               initialState[ 2 ], "km" );
    print( metadataFile, "initial_vx",              initialState[ 3 ], "km s^-1" );
    print( metadataFile, "initial_vy",              initialState[ 4 ], "km s^-1" );
    print( metadataFile, "initial_vz",              initialState[ 5 ], "km s^-1" );
    print( metadataFile, "start_time",              input.startTime,   "s" );
    print( metadataFile, "end_time",                input.endTime,     "s" );
    print( metadataFile, "initial_step",            input.initialStep, "s" );
    metadataFile.close( );
    std::cout << "Simulation metadata written to file successfully!" << std::endl;

    // Write simulation data to file.
    std::cout << "Writing state history to file ..." << std::endl;
    std::string outputFileHeader = "t,x,y,z,vx,vy,vz";
    std::ofstream outputFile( input.outputFilename.c_str( ) );
    print( outputFile, stateHistory, outputFileHeader );
    outputFile.close( );
    std::cout << "State history written to file successfully!" << std::endl;
}

//! Check simulator input parameters.
SimulatorInput checkSimulatorInput( const rapidjson::Document& config )
{
    // Search for and store gravitational parameter in config.
    const double gravitationalParameter
        = find( config, "gravitational_parameter" )->value.GetDouble( );
    std::cout << "Gravitational parameter                   " << gravitationalParameter << " "
              << "km^3 s^-2" << std::endl;

    // Search for and store initial state in config.
    State initialState;
    for ( unsigned int i = 0; i < initialState.size( ); i++ )
    {
        initialState[ i ] = find( config, "initial_state" )->value[ i ].GetDouble( );
    }
    std::cout << "Initial state                             [ ";
    for ( unsigned int i = 0; i < initialState.size( ) - 1; i++ )
    {
        std::cout << initialState[ i ] << "; ";
    }
    std::cout << initialState[ initialState.size( ) - 1 ] << " ]" << std::endl;

    // Search for and store start time, end time, and initial step for numerical integrator.
    const double startTime      = find( config, "start_time" )->value.GetDouble( );
    std::cout << "Start time                                " << startTime << " s" << std::endl;
    const double endTime        = find( config, "end_time" )->value.GetDouble( );
    std::cout << "End time                                  " << endTime << " s" << std::endl;
    const double initialStep    = find( config, "initial_step" )->value.GetDouble( );
    std::cout << "Initial step                              " << initialStep << " s" << std::endl;

    // Search for and store list of names of models to include in simulator.
    ListOfModelNames listOfModelNames;
    ConfigIterator modelsIterator = find( config, "models" );
    for ( unsigned int i = 0; i < modelsIterator->value.Size( ); i++ )
    {
        listOfModelNames.push_back( modelsIterator->value[ i ].GetString( ) );
    }
    std::cout << "Models                                    [ ";
    for ( unsigned int i = 0; i < listOfModelNames.size( ) - 1; i++ )
    {
        std::cout << listOfModelNames[ i ] << "; ";
    }
    std::cout << listOfModelNames[ listOfModelNames.size( ) - 1 ] << " ]" << std::endl;

    // Search for and store output file names.
    const std::string metadataFilename     = find( config, "metadata_file" )->value.GetString( );
    std::cout << "Simulation metadata file                  " << metadataFilename << std::endl;
    const std::string stateHistoryFilename
        = find( config, "state_history_file" )->value.GetString( );
    std::cout << "State history file                        " << stateHistoryFilename << std::endl;

    return SimulatorInput( gravitationalParameter,
                           initialState,
                           startTime,
                           endTime,
                           initialStep,
                           listOfModelNames,
                           metadataFilename,
                           stateHistoryFilename );
}

} // namespace scarab