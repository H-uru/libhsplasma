#ifndef _PLCLOTHINGITEM_H
#define _PLCLOTHINGITEM_H

#include "Util/hsTArray.hpp"
#include "Sys/hsColor.h"
#include "PRP/KeyedObject/hsKeyedObject.h"

/**
 * \brief Describes a wearable Clothing Item for avatars.
 *
 * Clothing in Plasma is made up of several elements, all linked back to a
 * named plClothingItem.  The Clothing Manager within Uru keeps a list of
 * loaded Clothing Items and can assign them to avatars by item name.
 * The plClothingItem is the top level object to describe an item for the
 * clothing manager.
 */

DllClass plClothingItem : public hsKeyedObject {
public:
    enum LODLevels { kLODHigh, kLODMedium, kLODLow, kNumLODLevels };

    enum ClothingLayers {
        kLayerBase, kLayerSkin, kLayerSkinBlend1, kLayerSkinBlend2,
        kLayerSkinBlend3, kLayerSkinBlend4, kLayerSkinBlend5, kLayerSkinBlend6,
        kLayerTint1, kLayerTint2, kLayerMax
    };

    enum Tilesets {
        kSetShirt, kSetFace, kSetShoe, kSetPants, kSetHand, kSetPlayerBook,
        kSetGlasses, kSetKI, kSetEye, kSetBackpack, kMaxTileset
    };

    enum Types {
        kTypePants, kTypeShirt, kTypeLeftHand, kTypeRightHand, kTypeFace,
        kTypeHair, kTypeLeftFoot, kTypeRightFoot, kTypeAccessory, kMaxType
    };

    enum Groups {
        kClothingBaseMale, kClothingBaseFemale, kClothingBaseNoOptions,
        kMaxGroup
    };

private:
    plString fItemName, fDescription, fCustomText;
    unsigned char fGroup, fType, fTileset, fSortOrder;

    hsTArray<plString> fElementNames;
    hsTArray<plKey*> fTextures;
    plKey fIcon, fAccessory;
    plKey fMeshes[kNumLODLevels];

    unsigned char fDefaultTint1[3];
    unsigned char fDefaultTint2[3];

public:
    plClothingItem();
    virtual ~plClothingItem();

    DECLARE_CREATABLE(plClothingItem)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    /** Returns the name of the clothing item. */
    plString getItemName() const;

    /** Returns the properties description for the clothing item. */
    plString getDescription() const;

    /** Returns the custom text for the clothing item. */
    plString getCustomText() const;

    /**
     * Returns the group this item belongs to.
     * \sa Groups
     */
    unsigned char getGroup() const;

    /**
     * Returns the clothing item's item type.
     * \sa Types
     */
    unsigned char getType() const;

    /**
     * Returns the clothing item's tileset for AvatarCustomization.
     * \sa Tilesets
     */
    unsigned char getTileset() const;

    /** Returns the sorting order for the item in AvatarCustomization. */
    unsigned char getSortOrder() const;

    /** Returns the icon to display this clothing item in AvatarCustomization. */
    plKey getIcon() const;

    /** Returns this item's accessory link. */
    plKey getAccessory() const;

    /**
     * Returns a key for the plSharedMesh that stores this items geometry
     * at LOD of \a lodLevel.
     * \sa LODLevels
     */
    plKey getMesh(int lodLevel) const;

    /** Returns the default first tint color for the item. */
    hsColorRGBA getDefaultTint1() const;

    /** Returns the default second tint color for the item. */
    hsColorRGBA getDefaultTint2() const;

    /** Set the name of the clothing item. */
    void setItemName(const plString& name);

    /** Set the property description string for this item. */
    void setDescription(const plString& desc);

    /** Set the custom text for this clothing item. */
    void setCustomText(const plString& text);

    /**
     * Set the group this item belongs to.
     * \sa Groups
     */
    void setGroup(unsigned char group);

    /**
     * Set the clothing item's type.
     * \sa Types
     */
    void setType(unsigned char type);

    /**
     * Set the tileset to assign this item in AvatarCustomization.
     * \sa Tilesets
     */
    void setTileset(unsigned char set);

    /** Set the sort order for listing in AvatarCustomization. */
    void setSortOrder(unsigned char order);

    /** Set the clothing item's icon for AvatarCustomization. */
    void setIcon(plKey icon);

    /** Set the accessory key for this item. */
    void setAccessory(plKey acc);

    /**
     * Set the key for the plSharedMesh that contains this item's geometry
     * at LOD level \a lodLevel.
     * \sa LODLevels
     */
    void setMesh(int lodLevel, plKey mesh);

    /** Set the default first tint color for this item. */
    void setDefaultTint1(const hsColorRGBA& tint);

    /** Set the default second tint color for this item. */
    void setDefaultTint2(const hsColorRGBA& tint);

    /** Remove all elements from the clothing item. */
    void clearElements();

    /** Add a named element to the clothing item. */
    void addElement(const plString& elementName);

    /**
     * Sets the texture for element number \a element, at layer \a layer
     * to \a texture.
     * \sa ClothingLayers
     */
    void setElementTexture(int element, int layer, plKey texture);

    /**
     * Sets the element name for element number \a element to \a elementName.
     */
    void setElementName(int element, const plString& elementName);

    /**
     * Returns the element texture for element number \a element, at layer
     * \a layer.
     * \sa ClothingLayers
     */
    plKey getElementTexture(int element, int layer) const;

    /**
     * Returns the element name for element number \a element.
     */
    plString getElementName(int element) const;

    /** Remove the specified element from the clothing item. */
    void delElement(int element);
};

#endif
