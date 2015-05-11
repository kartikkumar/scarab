/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <sstream>
#include <stdexcept>

#include "Scarab/tools.hpp"

namespace scarab
{

//! Find parameter.
ConfigIterator find( const rapidjson::Document& config, const std::string& parameterName )
{
    const ConfigIterator iterator = config.FindMember( parameterName.c_str( ) );
    if ( iterator == config.MemberEnd( ) )
    {
        std::ostringstream error;
        error << "ERROR: \"" << parameterName << "\" missing from config file!";
        throw std::runtime_error( error.str( ) );
    }
    return iterator;
}

//! Print state history to stream.
void print( std::ostream& stream,
            const StateHistory stateHistory,
            const std::string& streamHeader,
            const int precision )
{
    stream << streamHeader << std::endl;

    for ( StateHistoryConstIt it = stateHistory.begin( ); it != stateHistory.end( ); it++ )
    {
        stream << std::setprecision( precision )
               << it->first       << ",";

        for ( unsigned int i = 0; i < it->second.size( ) - 1; i++ )
        {
            stream << it->second[ i ] << ",";
        }
        stream << it->second[ it->second.size( ) - 1 ] << std::endl;
    }
}

} // namespace scarab
