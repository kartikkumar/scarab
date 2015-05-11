/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef SCARAB_TOOLS_HPP
#define SCARAB_TOOLS_HPP

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

#include <rapidjson/document.h>

#include "Scarab/typedefs.hpp"

namespace scarab
{

//! JSON config iterator.
typedef rapidjson::Value::ConstMemberIterator ConfigIterator;

//! Find parameter.
/*!
 * Finds parameter in config stored in JSON document. An error is thrown if the parameter cannot
 * be found. If the parameter is found, an iterator to the member in the JSON document is returned.
 *
 * @param[in] config        JSON document containing config parameters
 * @param[in] parameterName Name of parameter to find
 * @return                  Iterator to parameter retreived from JSON document
 */
ConfigIterator find( const rapidjson::Document& config, const std::string& parameterName );

//! Print value to stream.
/*!
 * Prints a specified value to stream provided, given a specified width and a filler character.
 *
 * @tparam     DataType  Type for specified value
 * @param[out] stream    Output stream
 * @param[in]  value     Specified value to print
 * @param[in]  width     Width of value printed to stream, in terms of number of characters
 *                       (default = 25)
 * @param[in]  filler    Character used to fill fixed-width (default = ' ')
 */
template< typename DataType >
inline void print( std::ostream& stream,
                   const DataType value,
                   const int width = 25,
                   const char filler = ' ' )
{
    stream << std::left << std::setw( width ) << std::setfill( filler ) << value;
}

//! Print metadata parameter to stream.
/*!
 * Prints metadata parameter to stream provided, given a specified name, value, units, and
 * delimiter.
 *
 * @tparam     DataType      Type for specified value
 * @param[out] stream        Output stream
 * @param[in]  parameterName Name for metadata parameter
 * @param[in]  value         Specified value to print
 * @param[in]  units         Units for value
 * @param[in]  delimiter     Character used to delimiter entries in stream (default = ' ')
 * @param[in]  width         Width of value printed to stream, in terms of number of characters
 *                           (default = 25)
 * @param[in]  filler        Character used to fill fixed-width (default = ' ')
 */
template< typename DataType >
inline void print( std::ostream& stream,
                   const std::string& parameterName,
                   const DataType value,
                   const std::string& units,
                   const char delimiter = ',',
                   const int width = 25,
                   const char filler = ' ' )
{
    print( stream, parameterName, width, filler );
    stream << delimiter;
    print( stream, value, width, filler );
    stream << delimiter;
    print( stream, units, width, filler );
    stream << std::endl;
}

//! Print state history to stream.
/*!
 * Prints state history to stream provided, given a specified state history object, a stream
 * header and a number of digits of precision.
 *
 * @param[out] stream        Output stream
 * @param[in]  stateHistory  State history containing epochs and associated state vectors
 * @param[in]  streamHeader  A header for the output stream (file header if a file stream is
 *                           provided) (default = "")
 * @param[in]  precision     Digits of precision for state history entries printed to stream
 *                           (default = number of digits of precision for a double)
 */
void print( std::ostream& stream,
            const StateHistory stateHistory,
            const std::string& streamHeader = "",
            const int precision = std::numeric_limits< double >::digits10 );

} // namespace scarab

#endif // SCARAB_TOOLS_HPP
