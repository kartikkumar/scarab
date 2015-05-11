/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef SCARAB_TYPEDEFS_HPP
#define SCARAB_TYPEDEFS_HPP

#include <map>
#include <string>
#include <vector>

#include <boost/array.hpp>

namespace scarab
{

//! Position-type (3-vector).
typedef boost::array< double, 3 > Position;

//! Velocity-type (3-vector).
typedef boost::array< double, 3 > Velocity;

//! Acceleration-type (3-vector).
typedef boost::array< double, 3 > Acceleration;

//! State-type.
typedef boost::array< double, 6 > State;

//! State history.
typedef std::map< double, State > StateHistory;

//! State history iterator.
typedef StateHistory::iterator StateHistoryIt;

//! State history iterator.
typedef StateHistory::const_iterator StateHistoryConstIt;

//! Typedef for list of acceleration model names.
typedef std::vector< std::string > ListOfModelNames;

} // namespace scarab

#endif // SCARAB_TYPEDEFS_HPP
