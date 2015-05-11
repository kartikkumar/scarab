/*
 * Copyright (c) 2014-2015 Kartik Kumar, Dinamica Srl
 * Copyright (c) 2014-2015 Marko Jankovic, DFKI GmbH
 * Copyright (c) 2014-2015 Natalia Ortiz, University of Southampton
 * Copyright (c) 2014-2015 Juan Romero, University of Strathclyde
 * Distributed under the MIT License.
 * See accompanying file LICENSE.md or copy at http://opensource.org/licenses/MIT
 */

#ifndef SCARAB_ACCELERATION_MODEL_HPP
#define SCARAB_ACCELERATION_MODEL_HPP

#include <boost/shared_ptr.hpp>

#include "Scarab/typedefs.hpp"

namespace scarab
{

//! Acceleration model.
/*!
 * Acceleration model base class.
 *
 * @tparam Acceleration Definition of type used to store computed acceleration.
 */
template < typename Acceleration >
class AccelerationModel
{
public:

    //! Compute acceleration.
    /*!
     * Computes acceleration by overloading ()-operator. This if a pure virtual function, hence it
     * must be implemented by any derived classes.
     *
     * @param[in] state Current state
     * @param[in] time  Current time
     * @return          Computed acceleration
     */
    virtual Acceleration operator( )( const State& state, const double time ) = 0;

    //! Default destructor.
    /*!
     * Default (virtual) destructor.
     */
    virtual ~AccelerationModel( ) { }

protected:

private:
};

//! 3D acceleration model.
typedef AccelerationModel< Acceleration >               AccelerationModel3d;
//! Pointer to 3D acceleration model.
typedef boost::shared_ptr< AccelerationModel3d >        AccelerationModel3dPtr;

} // namespace scarab

#endif // SCARAB_ACCELERATION_MODEL_HPP
