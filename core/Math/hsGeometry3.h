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
struct PLASMA_DLL hsVector3
{
    float X, Y, Z;

    /** Construct a vector at the origin [0,0,0] */
    hsVector3() : X(), Y(), Z() { }

    /** Construct a vector at [x,y,z] */
    hsVector3(float _x, float _y, float _z) : X(_x), Y(_y), Z(_z) { }

    /** Zeros the vector; that is, put it at the origin [0,0,0] */
    void Zero() { X = Y = Z = 0.0f; }

    /** Returns the magnitude of the vector: \f$\sqrt{x^2+y^2+z^2}\f$ */
    float magnitude() const;

    /** Returns true if the values of the vectors are identical */
    bool operator==(const hsVector3& other) const
    {
        return (X == other.X) && (Y == other.Y) && (Z == other.Z);
    }

    /** Returns true if the values of the vectors are non-identical */
    bool operator!=(const hsVector3& other) const
    {
        return (X != other.X) || (Y != other.Y) || (Z != other.Z);
    }

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
    hsVector3 operator+(const hsVector3& other) const
    {
        return hsVector3(X + other.X, Y + other.Y, Z + other.Z);
    }

    /**
     * Adds the vectors in place using vector addition:
     * \f$[x_1,y_1,z_1] + [x_2,y_2,z_2] = [x_1+x_2,y_1+y_2,z_1+z_2]\f$
     */
    hsVector3& operator+=(const hsVector3& other)
    {
        X += other.X;
        Y += other.Y;
        Z += other.Z;
        return *this;
    }

    /**
     * Subtracts the vectors using vector addition:
     * \f$[x_1,y_1,z_1] - [x_2,y_2,z_2] = [x_1-x_2,y_1-y_2,z_1-z_2]\f$
     */
    hsVector3 operator-(const hsVector3& other) const
    {
        return hsVector3(X - other.X, Y - other.Y, Z - other.Z);
    }

    /**
     * Multiplies the vector by the scalar factor \a mult:
     * \f$[x,y,z] * mult = [x*mult,y*mult,z*mult]\f$
     */
    hsVector3 operator*(const float mult) const
    {
        return hsVector3(X * mult, Y * mult, Z * mult);
    }

    /**
     * Multiplies two vectors using the Dot Product:
     * \f$dot = x_1*x_2 + y_1*y_2 + z_1*z_2\f$
     */
    float dotP(const hsVector3& other) const
    {
        return (X * other.X) + (Y * other.Y) + (Z * other.Z);
    }

    /**
     * Multiplies two vectors using the Cross Product:
     * \f$[x,y,z] = [(y_1*z_2) - (z_1*y_2),(z_1*x_2) - (x_1*z_2),(x_1*y_2) - (y_1*x_2)]\f$
     */
    hsVector3 crossP(const hsVector3& other) const
    {
        return hsVector3((Y * other.Z) - (Z * other.Y),
                         (Z * other.X) - (X * other.Z),
                         (X * other.Y) - (Y * other.X));
    }

    /** Converts this vector a unit vector such that its magnitude is 1 */
    void normalize();
};


/**
 * \brief Describes an infinite plane in 3D space.
 */
struct PLASMA_DLL hsPlane3
{
    /** The Normal direction of the plane (should be a unit vector). */
    hsVector3 N;

    /** The distance this plane is from the origin, with respect to N. */
    float W;

    /** Constructs a plane at the origin aligned to the X-Y axis plane. */
    hsPlane3() : N(0.0f, 0.0f, 1.0f), W() { }

    /** Constructs a plane at \a w with a normal of \a n. */
    hsPlane3(const hsVector3& n, float w) : N(n), W(w) { }

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
struct PLASMA_DLL hsFloatPoint2
{
    float X, Y;

    /** Constructs a point at the origin [0,0] */
    hsFloatPoint2() : X(), Y() { }
};

#endif
