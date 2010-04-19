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

#ifndef _PLRESMANAGER_H
#define _PLRESMANAGER_H

#include "PlasmaDefs.h"
#include "Util/PlasmaVersions.h"
#include "PRP/KeyedObject/plLocation.h"
#include "pdUnifiedTypeMap.h"
#include "Stream/plEncryptedStream.h"
#include "Util/hsTArray.hpp"
#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"
#include "plKeyCollector.h"
#include "PRP/plPageInfo.h"
#include "plAgeInfo.h"

/** Callback to indicate the progress of the current operation, range [0,1] */
typedef void (*ProgressCallback)(float progress);

/**
 * \brief Manages the entire library's resources, including keys, creatables,
 *        age info and page info.
 *
 * You will need to create at least one ResManager if you plan to use
 * any creatables or keys in your application.  You can also use it to
 * handle PRC data and store Age or PRP information.  Most of the
 * top-level file-based operations you'll do will start from here.
 */
DllClass plResManager {
private:
    static unsigned int fNumResMgrs;

protected:
    PlasmaVer fPlasmaVer;
    plKeyCollector keys;
    std::vector<plPageInfo*> pages;
    std::vector<plAgeInfo*> ages;
    ProgressCallback progressFunc;

private:
    void ReadKeyring(hsStream* S, const plLocation& loc);
    unsigned int ReadObjects(hsStream* S, const plLocation& loc);
    void WriteKeyring(hsStream* S, const plLocation& loc);
    unsigned int WriteObjects(hsStream* S, const plLocation& loc);

public:
    /**
     * Constructs a ResManager.
     *
     * If the version is left unspecified,
     * it will be determined automatically when you call either
     * ReadPage() or ReadAge()
     * \sa setVer(), getVer()
     */
    plResManager(PlasmaVer pv = pvUnknown);

    /**
     * Destroy the ResManager.
     *
     * This will delete all keys, Creatables, Ages and Pages that are
     * registered with the ResManager.
     */
    virtual ~plResManager();

    /**
     * Set the version of data files this ResManager expects to deal
     * with.  This is used when reading or writing data to files, but
     * doesn't have any affect on data already loaded.
     * \param force Change the version even if one is already set
     * \sa getVer()
     */
    void setVer(PlasmaVer pv, bool force = false);

    /**
     * Return the version of data files this ResManager expects to
     * deal with.  Used for reading or writing data to files only.
     * \sa setVer()
     */
    PlasmaVer getVer() { return fPlasmaVer; }

    /** Read a plKey and register it with the ResManager */
    plKey readKey(hsStream* S);

    /** Read a raw plKey from a stream (no "exists" bool for Uru streams) */
    plKey readUoid(hsStream* S);

    /** Write a plKey to a stream */
    void writeKey(hsStream* S, plKey key);

    /** Write the plKey that describes the specified hsKeyedObject to a stream */
    void writeKey(hsStream* S, hsKeyedObject* ko);

    /** Write a raw plKey to a stream (no "exists" bool for Uru streams) */
    void writeUoid(hsStream* S, plKey key);

    /** Write the raw plKey that describes the hsKeyedObject to a stream */
    void writeUoid(hsStream* S, hsKeyedObject* ko);

    /** Parse the PRC tag as a plKey and register it with the ResManager */
    plKey prcParseKey(const pfPrcTag* tag);

    /**
     * Find and return the object referenced by key, or NULL if the key
     * either doesn't exist or isn't loaded.  This uses the ResManager's
     * internal list of keys, unlike plKeyData::getObj() which just returns
     * the key's internal object pointer.
     * \sa plKeyData::getObj()
     */
    class hsKeyedObject* getObject(plKey key);

    /** Returns the total number of keys registered for the specified plLocation */
    unsigned int countKeys(const plLocation& loc) { return keys.countKeys(loc); }

    /**
     * Read a Page (PRP File) and register it with the ResManager.
     * \return a pointer to the plPageInfo describing the page.
     * \sa ReadPagePrc(), ReadAge(), ReadAgePrc()
     */
    plPageInfo* ReadPage(const char* filename);

    /**
     * Parse a page from a PRC data source, and register it with the ResManager.
     * \return a pointer to the plPageInfo describing the page.
     * \sa ReadPage(), ReadAge(), ReadAgePrc()
     */
    plPageInfo* ReadPagePrc(const pfPrcTag* root);

    /**
     * Write the specified page to a PRP file
     * \sa WritePagePrc(), WriteAge(), WriteAgePrc()
     */
    void WritePage(const char* filename, plPageInfo* page);

    /**
     * Write the specified page to a PRC document
     * \sa WritePage(), WriteAge(), WriteAgePrc()
     */
    void WritePagePrc(pfPrcHelper* prc, plPageInfo* page);

    /**
     * Find a registered page whose location is specified by loc.
     * \return the plPageInfo describing the page, or NULL if it is not found.
     * \sa FindAge()
     */
    plPageInfo* FindPage(const plLocation& loc);

    /**
     * Unloads and frees memory for all registered data for the page
     * whose location is specified by loc.
     * \sa UnloadAge(), DelPage()
     */
    void UnloadPage(const plLocation& loc);

    /**
     * Read an AGE file and register it with the ResManager.
     * \param readPages Specifies whether to also load and register all of
     *        the pages referenced by the AGE file.
     * \return a pointer to the plAgeInfo describing the AGE file.
     * \sa ReadAgePrc(), ReadPage(), ReadPagePrc()
     */
    plAgeInfo* ReadAge(const char* filename, bool readPages);

    /**
     * Read age file data from a PRC block and register it with the ResManager.
     * \return a pointer to the plAgeInfo describing the age.
     * \sa ReadAge(), ReadPage(), ReadPagePrc()
     */
    plAgeInfo* ReadAgePrc(const pfPrcTag* root);

    /**
     * Create/overwrite an age file for the specified age info structure
     * \sa WriteAgePrc(), WritePage(), WritePagePrc()
     */
    void WriteAge(const char* filename, plAgeInfo* age);

    /**
     * Write a PRC chunk for the specified age info structure
     * \sa WriteAge(), WritePage, WritePagePrc()
     */
    void WriteAgePrc(pfPrcHelper* prc, plAgeInfo* age);

    /**
     * Finds a registered age info structure by name.
     * \param name The filename of the age to be found
     * \return the age info structure, or NULL if it can't be found
     * \sa FindPage()
     */
    plAgeInfo* FindAge(const plString& name);

    /**
     * Unload an age info structure by name.  Frees all memory associated
     * with the age, and also unloads all pages that are described by this
     * age info.
     * \sa UnloadPage(), DelAge()
     */
    void UnloadAge(const plString& name);

    /**
     * Read a plCreatable from the stream.  This should be converted
     * to a compatible subclass in order to make use of its members.
     * \param canStub Specifies whether an unsupported ClassIndex can be
     *        made into a plCreatableStub without disrupting the stream.
     * \param stubLen Specifies the size of the plCreatable for stubs
     *        This only makes sense if canStub is true, and it MUST be
     *        specified if canStub is true.
     * \return The plCreatable object.
     * \sa WriteCreatable(), prcParseCreatable()
     */
    class plCreatable* ReadCreatable(hsStream* S, bool canStub = false, int stubLen = 0);

    /**
     * Writes a plCreatable to the stream.
     * \sa ReadCreatable(), prcParseCreatable()
     */
    void WriteCreatable(hsStream* S, class plCreatable* pCre);

    /**
     * Parse a plCreatable contained in the PRC tag.
     * \return a parsed plCreatable, or NULL if parsing failed.
     * \sa ReadCreatable(), WriteCreatable(), plCreatable::prcParse(), plCreatable::prcWrite()
     */
    class plCreatable* prcParseCreatable(const pfPrcTag* tag);

    /**
     * Finds the plSceneNode associated with the page at loc.  If there is
     * more than one Scene Node in the page, returns only the first one.
     * \return a plSceneNode for the page, or NULL if one wasn't found
     */
    class plSceneNode* getSceneNode(const plLocation& loc);

    /**
     * Return an array of all page locations registered by the ResManager.
     * Note that this might include locations that are not currently loaded,
     * since it's possible to load keys for external pages.
     */
    std::vector<plLocation> getLocations();

    /**
     * Return an array of all of the Creatable Class types that have one or
     * more keys loaded into the ResManager for this location.
     * \param checkKeys if set to true, the ResManager will clean out
     *        any invalid keys while building the type list.
     */
    std::vector<short> getTypes(const plLocation& loc, bool checkKeys = false);

    /**
     * Return an array of all the plKeys of the specified Creatable Class
     * for the specified location.
     * \param checkKeys if set to true, the ResManager will clean out
     *        any invalid keys while building the type list.
     */
    std::vector<plKey> getKeys(const plLocation& loc, short type,
                               bool checkKeys = false);
    
    /**
     * Return an array of all the plKeys of the specified Creatable Class
     * for all locations.
     * \param checkKeys if set to true, the ResManager will clean out
     *        any invalid keys while building the type list.
     */
    std::vector<plKey> getKeys(short type, bool checkKeys = false);

    /**
     * Manually register a plKey with the ResManager.
     *
     * Note: You should do this if you are creating a NEW hsKeyedObject
     * (after initializing the key with hsKeyedObject::init() ).
     * You should NOT use this for keys or KeyedObjects that are loaded
     * into the ResManager through other sources, like parsing from a
     * file or PRC tag.
     *
     * Unlike AddObject(), this function WILL check to see if the key
     * is already registered, and returns a copy of the registered key
     * instead of the new one, if it is found in the ResManager.
     * \return a copy of the key stored in the ResManager
     * \sa hsKeyedObject::init(), MoveKey(), AddObject()
     */
    plKey AddKey(plKey key);

    /**
     * Change a plKey's location to the one specified.  This is probably
     * a good idea to call after importing a key or KeyedObject from a
     * file or PRC data, to ensure the key and object get put into the
     * correct place.  Since plKeys share a single datum, any objects in
     * any pages that hold reference to this key will also use the
     * updated location.
     * \sa AddKey(), AddObject()
     */
    void MoveKey(plKey key, const plLocation& to);

    /**
     * Manually register an hsKeyedObject with the ResManager.
     *
     * Like AddKey, this registers the object and its key into the ResManager,
     * but this function also changes the location of the associated plKey
     * to match the location we're adding it to.  However, unlike AddKey(),
     * this function performs no check to see whether the key is already
     * loaded.  You should only use this function for NEW hsKeyedObjects
     * and never for ones that are already loaded from a file or PRC tag.
     * \sa AddKey(), MoveKey(), hsKeyedObject::init()
     */
    void AddObject(const plLocation& loc, hsKeyedObject* obj);

    /**
     * Manually register a plPageInfo with the ResManager.
     *
     * Note: You should only use this for NEW pages created by the
     * application, never for pages read from files or PRC tags.
     */
    void AddPage(plPageInfo* page);

    /**
     * Manually register a plAgeInfo with the ResManager.
     *
     * Note: You should only use this for NEW ages created by the
     * application, never for ages read from files or PRC tags.
     */
    void AddAge(plAgeInfo* age);

    /**
     * Removes the plKey and its associated hsKeyedObject from the
     * ResManager, and frees the memory associated with both.
     * This will allow you to delete an object from a page.
     */
    void DelObject(plKey obj);

    /**
     * Removes the page specified by loc from the ResManager, and
     * frees any memory associated with it.  Unlike UnloadPage(),
     * this function does NOT remove any keys or objects referenced
     * by the page.
     * \sa UnloadPage()
     */
    void DelPage(const plLocation& loc);

    /**
     * Removes the age specified by filename from the ResManager, and
     * frees any memory associated with it.  Unlike UnloadAge(),
     * this function does NOT remove any pages referenced by the age,
     * nor any objects referenced by those pages.
     */
    void DelAge(const plString& name);

    /**
     * This function can completely change a location identifier for
     * all loaded data.  Any plKeys or plPageInfos that are registered
     * whose location matches \a from will be updated to the location
     * \a to, and when the files are written back to disk, they will be
     * stored with the new location info.
     */
    void ChangeLocation(plLocation from, plLocation to);

    /**
     * This function is currently unsupported.
     */
    ProgressCallback SetProgressFunc(ProgressCallback newFunc);
};

#endif
