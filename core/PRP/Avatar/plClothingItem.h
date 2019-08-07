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

#ifndef _PLCLOTHINGITEM_H
#define _PLCLOTHINGITEM_H

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

class PLASMA_DLL plClothingItem : public hsKeyedObject
{
    CREATABLE(plClothingItem, kClothingItem, hsKeyedObject)

public:
    enum LODLevels { kLODHigh, kLODMedium, kLODLow, kNumLODLevels };

    enum ClothingLayers
    {
        kLayerBase, kLayerSkin, kLayerSkinBlend1, kLayerSkinBlend2,
        kLayerSkinBlend3, kLayerSkinBlend4, kLayerSkinBlend5, kLayerSkinBlend6,
        kLayerTint1, kLayerTint2, kLayerMax
    };

    enum Tilesets
    {
        kSetShirt, kSetFace, kSetShoe, kSetPants, kSetHand, kSetPlayerBook,
        kSetGlasses, kSetKI, kSetEye, kSetBackpack, kMaxTileset
    };

    enum Types
    {
        kTypePants, kTypeShirt, kTypeLeftHand, kTypeRightHand, kTypeFace,
        kTypeHair, kTypeLeftFoot, kTypeRightFoot, kTypeAccessory, kMaxType
    };

    enum Groups
    {
        kClothingBaseMale, kClothingBaseFemale, kClothingBaseNoOptions,
        kMaxGroup
    };

private:
    ST::string fItemName, fDescription, fCustomText;
    unsigned char fGroup, fType, fTileset, fSortOrder;

    std::vector<ST::string> fElementNames;
    std::vector<plKey*> fTextures;
    plKey fIcon, fAccessory;
    plKey fMeshes[kNumLODLevels];

    unsigned char fDefaultTint1[3];
    unsigned char fDefaultTint2[3];

public:
    plClothingItem();
    ~plClothingItem();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    /** Returns the name of the clothing item. */
    ST::string getItemName() const { return fItemName; }

    /** Returns the properties description for the clothing item. */
    ST::string getDescription() const { return fDescription; }

    /** Returns the customization text for the clothing item. */
    ST::string getCustomText() const { return  fCustomText; }

    /**
     * Returns the group this item belongs to.
     * \sa Groups
     */
    unsigned char getGroup() const { return fGroup; }

    /**
     * Returns the clothing item's item type.
     * \sa Types
     */
    unsigned char getType() const { return fType; }

    /**
     * Returns the clothing item's tileset for AvatarCustomization.
     * \sa Tilesets
     */
    unsigned char getTileset() const { return fTileset; }

    /** Returns the sorting order for the item in AvatarCustomization. */
    unsigned char getSortOrder() const { return fSortOrder; }

    /** Returns the icon to display this clothing item in AvatarCustomization. */
    plKey getIcon() const { return fIcon; }

    /** Returns this item's accessory link. */
    plKey getAccessory() const { return fAccessory; }

    /**
     * Returns a key for the plSharedMesh that stores this items geometry
     * at LOD of \a lodLevel.
     * \sa LODLevels
     */
    plKey getMesh(int lodLevel) const { return fMeshes[lodLevel]; }

    /** Returns the default first tint color for the item. */
    hsColorRGBA getDefaultTint1() const
    {
        return hsColorRGBA(fDefaultTint1[0] / 255.0f, fDefaultTint1[1] / 255.0f,
                           fDefaultTint1[2] / 255.0f, 1.0f);
    }

    /** Returns the default second tint color for the item. */
    hsColorRGBA getDefaultTint2() const
    {
        return hsColorRGBA(fDefaultTint2[0] / 255.0f, fDefaultTint2[1] / 255.0f,
                           fDefaultTint2[2] / 255.0f, 1.0f);
    }

    /** Set the name of the clothing item. */
    void setItemName(const ST::string& name) { fItemName = name; }

    /** Set the property description string for this item. */
    void setDescription(const ST::string& desc) { fDescription = desc; }

    /** Set the customization text for this clothing item. */
    void setCustomText(const ST::string& text) { fCustomText = text; }

    /**
     * Set the group this item belongs to.
     * \sa Groups
     */
    void setGroup(unsigned char group) { fGroup = group; }

    /**
     * Set the clothing item's type.
     * \sa Types
     */
    void setType(unsigned char type) { fType = type; }

    /**
     * Set the tileset to assign this item in AvatarCustomization.
     * \sa Tilesets
     */
    void setTileset(unsigned char set) { fTileset = set; }

    /** Set the sort order for listing in AvatarCustomization. */
    void setSortOrder(unsigned char order) { fSortOrder = order; }

    /** Set the clothing item's icon for AvatarCustomization. */
    void setIcon(plKey icon) { fIcon = std::move(icon); }

    /** Set the accessory key for this item. */
    void setAccessory(plKey acc) { fAccessory = std::move(acc); }

    /**
     * Set the key for the plSharedMesh that contains this item's geometry
     * at LOD level \a lodLevel.
     * \sa LODLevels
     */
    void setMesh(int lodLevel, plKey mesh) { fMeshes[lodLevel] = std::move(mesh); }

    /** Set the default first tint color for this item. */
    void setDefaultTint1(const hsColorRGBA& tint);

    /** Set the default second tint color for this item. */
    void setDefaultTint2(const hsColorRGBA& tint);

    /** Remove all elements from the clothing item. */
    void clearElements();

    /** Add a named element to the clothing item. */
    void addElement(const ST::string& elementName);

    /**
     * Sets the texture for element number \a element, at layer \a layer
     * to \a texture.
     * \sa ClothingLayers
     */
    void setElementTexture(int element, int layer, plKey texture)
    {
        fTextures[element][layer] = std::move(texture);
    }

    /**
     * Sets the element name for element number \a element to \a elementName.
     */
    void setElementName(int element, const ST::string& elementName)
    {
        fElementNames[element] = elementName;
    }

    /**
     * Returns the element texture for element number \a element, at layer
     * \a layer.
     * \sa ClothingLayers
     */
    plKey getElementTexture(int element, int layer) const
    {
        return fTextures[element][layer];
    }

    /**
     * Returns the element name for element number \a element.
     */
    ST::string getElementName(int element) const
    {
        return fElementNames[element];
    }

    /** Remove the specified element from the clothing item. */
    void delElement(int element);
};

#endif
