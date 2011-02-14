/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _HSGEOMETRY3_H
#define _HSGEOMETRY3_H

#include "Stream/hsStream.h"
#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

/**
 * \brief Stores a vector in 3D space.
 */
struct PLASMA_DLL hsVector3 {
    float X, Y, Z;

    /** Construct a vector at the origin [0,0,0] */
    hsVector3();

    /** Construct a vector at [x,y,z] */
    hsVector3(float x, float y, float z);

    /** Copy constructor, copies the value of vector \a src */
    hsVector3(const hsVector3& src);

    /** Copies the value of vector \a other to this vector */
    hsVector3& operator=(const hsVector3& other);

    /** Zeros the vector; that is, put it at the origin [0,0,0] */
    void Zero();

    /** Returns the magnitude of the vector: \f$\sqrt{x^2+y^2+z^2}\f$ */
    float magnitude() const;

    /** Returns true if the values of the vectors are identical */
    bool operator==(const hsVector3& other) const;

    /** Returns true if the values of the vectors are non-identical */
    bool operator!=(const hsVector3& other) const;

    /** Reads the vector from a stream */
    void read(hsStream* S);

    /** Writes the vector to a stream */
    void write(hsStream* S);

    /** Write the vector to PRC source */
    void prcWrite(pfPrcHelper* prc);

    /** Parse a vector from PRC source */
    void prcParse(const pfPrcTag* tag);

    /**
     * Adds the vectors using vector addition:
     * \f$[x_1,y_1,z_1] + [x_2,y_2,z_2] = [x_1+x_2,y_1+y_2,z_1+z_2]\f$
     */
    hsVector3 operator+(const hsVector3& other) const;

    /**
     * Subtracts the vectors using vector addition:
     * \f$[x_1,y_1,z_1] - [x_2,y_2,z_2] = [x_1-x_2,y_1-y_2,z_1-z_2]\f$
     */
    hsVector3 operator-(const hsVector3& other) const;

    /**
     * Multiplies the vector by the scalar factor \a mult:
     * \f$[x,y,z] * mult = [x*mult,y*mult,z*mult]\f$
     */
    hsVector3 operator*(const float mult) const;

    /**
     * Multiplies two vectors using the Dot Product:
     * \f$dot = x_1*x_2 + y_1*y_2 + z_1*z_2\f$
     */
    float dotP(const hsVector3& other) const;

    /**
     * Multiplies two vectors using the Cross Product:
     * \f$[x,y,z] = [(y_1*z_2) - (z_1*y_2),(z_1*x_2) - (x_1*z_2),(x_1*y_2) - (y_1*x_2)]\f$
     */
    hsVector3 crossP(const hsVector3& other) const;
};


/**
 * \brief Describes an infinite plane in 3D space.
 */
struct PLASMA_DLL hsPlane3 {
    /** The Normal direction of the plane (should be a unit vector). */
    hsVector3 N;

    /** The distance this plane is from the origin, with respect to N. */
    float W;

    /** Constructs a plane at the origin aligned to the X-Y axis plane. */
    hsPlane3();

    /** Constructs a plane at \a w with a normal of \a n. */
    hsPlane3(const hsVector3& n, float w);

    /** Copy constructor; copies the value of \a src to this plane. */
    hsPlane3(const hsPlane3& src);

    /** Copy the value of \a other to this plane. */
    hsPlane3& operator=(const hsPlane3& other);

    /** Read this plane from a stream */
    void read(hsStream* S);

    /** Write this plane to a stream */
    void write(hsStream* S);

    /** Write this plane as PRC source */
    void prcWrite(pfPrcHelper* prc);

    /** Parse PRC source into this plane */
    void prcParse(const pfPrcTag* tag);
};


/**
 * \brief Stores a point in 2D space.
 */
struct PLASMA_DLL hsFloatPoint2 {
    float X, Y;

    /** Constructs a point at the origin [0,0] */
    hsFloatPoint2();
};

#endif
