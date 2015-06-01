/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <map>
#include <string>
#include <typeinfo>
#include <vector>

#include <boost/array.hpp>

#include <catch.hpp>

#include "Scarab/typedefs.hpp"

namespace scarab
{
namespace tests
{

TEST_CASE( "Test definition of typedefs", "[typedefs]" )
{
    REQUIRE( typeid( Position )         == typeid( boost::array< double, 3 > ) );
    REQUIRE( typeid( Velocity )         == typeid( boost::array< double, 3 > ) );
    REQUIRE( typeid( Acceleration )     == typeid( boost::array< double, 3 > ) );
    REQUIRE( typeid( State )            == typeid( boost::array< double, 6 > ) );
    REQUIRE( typeid( StateHistory )     == typeid( std::map< double, State > ) );
    REQUIRE( typeid( ListOfModelNames ) == typeid( std::vector< std::string > ) );
}

} // namespace tests
} // namespace scarab
