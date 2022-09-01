/* Generated from orogen/lib/orogen/templates/typekit/Opaques.cpp */

#include <mars/typekit/OpaqueTypes.hpp>
#include <mars/typekit/Opaques.hpp>

    /** Returns the intermediate value that is contained in \c real_type */
    /** Stores \c intermediate into \c real_type. \c intermediate is owned by \c
     * real_type afterwards. */
    /** Release ownership of \c real_type on the corresponding intermediate
     * pointer.
     */

void orogen_typekits::toIntermediate(::mars::opaques::Vector3d& intermediate, ::mars::utils::Vector const& real_type)
{
    intermediate.x = real_type.x();
    intermediate.y = real_type.y();
    intermediate.z = real_type.z();
}

void orogen_typekits::fromIntermediate(::mars::utils::Vector& real_type, ::mars::opaques::Vector3d const& intermediate)
{
    real_type.x() = intermediate.x;
    real_type.y() = intermediate.y;
    real_type.z() = intermediate.z;
}
