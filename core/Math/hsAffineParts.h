#ifndef _HSAFFINEPARTS_H
#define _HSAFFINEPARTS_H

#include "hsGeometry3.h"
#include "hsQuat.h"

/**
 * \brief Defines an Affine transformation.
 *
 * This class is used to store the components of an Affine transformation,
 * mostly for use in animations and other movement.
 */

DllClass hsAffineParts {
public:
    /**
     * The meaning of this field is currently unknown...  It might be an
     * unused flag set, or an unused component of Affine transformations.
     * Either way, it was removed in MOUL, and seems to always be 0
     * in the other engines (at least as far as I've seen).
     */
    int fI;

    /** Defines the Translation component */
    hsVector3 fT;

    /** Defines the Rotation component */
    hsQuat fQ;
    
    /** Defines the axis system of the Scaling component */
    hsQuat fU;

    /** Defines the Scaling component */
    hsVector3 fK;

    /** Either 1.0 or -1.0; defines the sign of the determinant */
    float fF;

public:
    /** Constructs a default (identity) Affine Transformation */
    hsAffineParts();

    /** Copy constructor */
    hsAffineParts(const hsAffineParts& init);

    /** Read the affine parts from a versioned stream */
    void read(hsStream* S);

    /** Write the affine parts to a versioned stream */
    void write(hsStream* S);

    /** Write an Affine Transformation tag to the PRC document */
    void prcWrite(pfPrcHelper* prc);

    /** Parse an Affine Transformation tag into the current object */
    void prcParse(const pfPrcTag* tag);

    /** Reset the Affine Transformation to its identity form */
    void reset();
};

#endif
