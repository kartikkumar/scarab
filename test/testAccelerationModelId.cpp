/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <map>
#include <typeinfo>

#include <catch.hpp>

#include "Scarab/accelerationModelId.hpp"

namespace scarab
{
namespace tests
{

TEST_CASE( "Test definition acceleration model IDs", "[acceleration_models]" )
{
    REQUIRE( centralGravityModelId        == 0 );
    REQUIRE( radiationPressureModelId     == 1 );
}

TEST_CASE( "Test definition of acceleration model list typedef",
           "[typedefs], [acceleration_models]" )
{
    REQUIRE( typeid( ListOfAccelerationModels )
             == typeid( std::map< AccelerationModelId, AccelerationModel3dPtr > ) );
}

} // namespace tests
} // namespace scarab
