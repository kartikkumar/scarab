/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#include <Spot/spot.hpp>

#include "Scarab/helloWorld.hpp"

namespace scarab
{

//! Execute "Hello World!" function.
std::string executeHelloWorld( )
{
    spot::executeDummy( );
    return "Hello World!";
}

} // namespace scarab
