/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef SCARAB_OUTPUT_SETTINGS_HPP
#define SCARAB_OUTPUT_SETTINGS_HPP

#include <string>

namespace scarab
{

//! Output settings.
/*!
 * Data struct containing all valid output settings. This struct is populated by the
 * checkSimulatorSettings() function.
 *
 * @sa checkSimulatorSettings, executeSimulator
 */
struct OutputSettings
{
public:

    //! Construct data struct.
    /*!
     * Constructs data struct based on verified input parameters.
     *
     * @sa checkSimulatorSettings, executeSimulator
     *
     */
    OutputSettings( const std::string& aMetadataFilename,
                    const std::string& aStateHistoryFilename )
        : metadataFilename( aMetadataFilename ),
          stateHistoryFilename( aStateHistoryFilename )
    { }

    //! Metadata filename.
    const std::string metadataFilename;

    //! State history filename.
    const std::string stateHistoryFilename;

protected:

private:
};

} // namespace scarab

#endif // SCARAB_OUTPUT_SETTINGS_HPP
