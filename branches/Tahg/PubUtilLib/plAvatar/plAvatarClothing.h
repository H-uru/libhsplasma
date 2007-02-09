#ifndef PLAVATARCLOTHING_H
#define PLAVATARCLOTHING_H

#include "../../NucleusLib/pnNetCommon/plSynchedObject.h"
//#include "../../hsTArray.h"
//#include "hsColorRGBA.h"
//#include "hsBitVector.h"
#include "../plgImage/plMipmap.h"
#include "plClothingLayout.h"
#include "../plSDL/plSDL.h"

class plClothingItemOptions {
  struct hsColorRGBA fTint1; //this+0x0
  struct hsColorRGBA fTint2; //this+0x10

public:
  plClothingItemOptions::plClothingItemOptions(){}
  int plClothingItemOptions::IsMatch(class plClothingItemOptions *){}
};

class plClothingItem : public hsKeyedObject {
  char * fName; //this+0x10
  class plSharedMesh * fMeshes[3]; //this+0x14
  hsTArray<plMipmap * *> fTextures; //this+0x20
  hsTArray<char *> fElementNames; //this+0x28
  hsTArray<plClothingElement *> fElements; //this+0x30
  unsigned char fGroup; //this+0x38
  unsigned char fType; //this+0x39
  unsigned char fTileset; //this+0x3a
  unsigned char fSortOrder; //this+0x3b
  char * fDescription; //this+0x3c
  char * fCustomText; //this+0x40
  class plMipmap * fThumbnail; //this+0x44
  class plClothingItem * fAccessory; //this+0x48
  unsigned char fDefaultTint1[3]; //this+0x4c
  unsigned char fDefaultTint2[3]; //this+0x4f
  char * fAccessoryName; //this+0x54

public:
  plClothingItem(const class plClothingItem &){}
  plClothingItem::plClothingItem(){}
  plClothingItem::~plClothingItem(){}
  const char * plClothingItem::ClassName(){}
  unsigned short plClothingItem::ClassIndex(){}
  static unsigned short plClothingItem::Index(){}
  static class plClothingItem * Create(){}
  static const class plClothingItem * ConvertNoRef(const class plCreatable *){}
  static class plClothingItem * plClothingItem::ConvertNoRef(class plCreatable *){}
  static class plClothingItem * Convert(class plCreatable *){}
  static int HasDerivedClass(unsigned short){}
  static int plClothingItem::HasBaseClass(unsigned short){}
  class plCreatable * plClothingItem::GetInterface(unsigned short){}
  const class plCreatable * plClothingItem::GetConstInterface(unsigned short){}
  void SetName(char *){}
  const char * plClothingItem::GetName(){}
  int plClothingItem::CanWearWith(class plClothingItem *){}
  int plClothingItem::WearBefore(class plClothingItem *){}
  int plClothingItem::HasBaseAlpha(){}
  int plClothingItem::HasSameMeshes(class plClothingItem *){}
  void plClothingItem::Read(class hsStream *, class hsResMgr *){}
  void plClothingItem::Write(class hsStream *, class hsResMgr *){}
  int plClothingItem::MsgReceive(class plMessage *){}

private:
  static void plClothingItem::SetClassIndex(unsigned short){}
};

class plClothingOutfit : public plSynchedObject {
  class plArmatureMod * fAvatar; //this+0x5c
  class plRenderTarget * fTargetTexture; //this+0x60
  class hsGMaterial * fMaterial; //this+0x64
  hsTArray<plClothingItem *> fItems; //this+0x68
  hsTArray<plClothingItemOptions *> fOptions; //this+0x70
  class plClothingBase * fBase; //this+0x78
  unsigned char fGroup; //this+0x7c
  bool fSynchClients; //this+0x7d
  struct hsColorRGBA fSkinTint; //this+0x80
  float fSkinBlends[6]; //this+0x90
  class hsBitVector fDirtyItems; //this+0xa8
  int fVaultSaveEnabled; //this+0xb4
  bool fMorphsInitDone; //this+0xb8

public:
  plClothingOutfit(const class plClothingOutfit &){}
  plClothingOutfit::plClothingOutfit(){}
  plClothingOutfit::~plClothingOutfit(){}
  const char * plClothingOutfit::ClassName(){}
  unsigned short plClothingOutfit::ClassIndex(){}
  static unsigned short Index(){}
  static class plClothingOutfit * Create(){}
  static const class plClothingOutfit * plClothingOutfit::ConvertNoRef(const class plCreatable *){}
  static class plClothingOutfit * plClothingOutfit::ConvertNoRef(class plCreatable *){}
  static class plClothingOutfit * Convert(class plCreatable *){}
  static int HasDerivedClass(unsigned short){}
  static int HasBaseClass(unsigned short){}
  class plCreatable * plClothingOutfit::GetInterface(unsigned short){}
  const class plCreatable * plClothingOutfit::GetConstInterface(unsigned short){}
  void plClothingOutfit::SaveCustomizations(int){}
  void plClothingOutfit::AddItem(class plClothingItem *, int, int, int){}
  void plClothingOutfit::RemoveItem(class plClothingItem *, int, int){}
  void plClothingOutfit::TintItem(class plClothingItem *, float, float, float, int, int, int, int, unsigned char){}
  void plClothingOutfit::TintSkin(float, float, float, int, int){}
  void plClothingOutfit::MorphItem(class plClothingItem *, unsigned char, unsigned char, float, int){}
  void plClothingOutfit::SetAge(float, int, int){}
  void plClothingOutfit::SetSkinBlend(float, unsigned char, int, int){}
  float plClothingOutfit::GetSkinBlend(unsigned char){}
  struct hsColorRGBA plClothingOutfit::GetItemTint(class plClothingItem *, unsigned char){}
  float GetAge(){}
  hsTArray<plClothingItem *> & plClothingOutfit::GetItemList(){}
  hsTArray<plClothingItemOptions *> & plClothingOutfit::GetOptionList(){}
  void plClothingOutfit::Read(class hsStream *, class hsResMgr *){}
  void plClothingOutfit::Write(class hsStream *, class hsResMgr *){}
  bool plClothingOutfit::DirtySynchState(const char *, unsigned long){}
  void plClothingOutfit::StripAccessories(){}
  void plClothingOutfit::WearDefaultClothing(){}
  void plClothingOutfit::WearDefaultClothingType(unsigned long){}
  void plClothingOutfit::WearMaintainerOutfit(){}
  void plClothingOutfit::WearRandomOutfit(){}
  void plClothingOutfit::RemoveMaintainerOutfit(){}
  int plClothingOutfit::ReadItems(class hsStream *, class hsResMgr *, int){}
  void plClothingOutfit::WriteItems(class hsStream *, class hsResMgr *){}
  void plClothingOutfit::ForceUpdate(bool){}
  int plClothingOutfit::MsgReceive(class plMessage *){}
  void plClothingOutfit::IInstanceSharedMeshes(class plClothingItem *){}
  void plClothingOutfit::IRemoveSharedMeshes(class plClothingItem *){}
  void plClothingOutfit::ReadFromVault(){}
  //void plClothingOutfit::WriteToVault(const TArray<plStateDataRecord *,TArrayCopyBits<plStateDataRecord *> > &){}
  void plClothingOutfit::WriteToVault(){}
  void plClothingOutfit::SetupMorphSDL(){}
  void plClothingOutfit::DirtyTileset(int){}

private:
  static void plClothingOutfit::SetClassIndex(unsigned short){}

protected:
  void plClothingOutfit::IAddItem(class plClothingItem *){}
  void plClothingOutfit::IRemoveItem(class plClothingItem *){}
  int plClothingOutfit::ITintItem(class plClothingItem *, struct hsColorRGBA, unsigned char){}
  int plClothingOutfit::IMorphItem(class plClothingItem *, unsigned char, unsigned char, float){}
  void plClothingOutfit::IHandleMorphSDR(class plStateDataRecord *){}
  void plClothingOutfit::IUpdate(){}
};

#endif

