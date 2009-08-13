#include "plPythonMod.h"

/* plPythonMod */
plPythonMod::plPythonMod() : fPythonCode(NULL), fPythonSize(0) { }
plPythonMod::~plPythonMod() {
	if (fPythonCode != NULL) {
        delete[] fPythonCode;
    }
}

IMPLEMENT_CREATABLE(plPythonMod, kPythonMod, plMultiModifier)

void plPythonMod::read(hsStream* S, plResManager* mgr) {
    plMultiModifier::read(S, mgr);
    
    fPythonSize = S->readInt();
    fPythonCode = new unsigned char[fPythonSize];
    S->read(fPythonSize, fPythonCode);
    
    fReceivers.setSize(S->readInt());
    for (size_t i=0; i<fReceivers.getSize(); i++)
        fReceivers[i] = mgr->readKey(S);
    
    fAnimNotetracks.setSize(S->readInt());
    for (size_t i=0; i<fAnimNotetracks.getSize(); i++) {
    	PY_NOTETRACK note;
        note.objKey = mgr->readKey(S);
        int size = S->readInt();
        if (size != 0) {
            note.note_name = new char[size+1];
            S->read(size+1, (char*)note.note_name);
        } else {
            note.note_name = NULL;
        }
        note.modKey = mgr->readKey(S);
        fAnimNotetracks[i] = note;
    }
    
    fSoundName2Idx.setSize(S->readInt());
    for (size_t i=0; i<fSoundName2Idx.getSize(); i++) {
    	PY_SOUND_IDX sound;
    	int size = S->readInt();
        if (size != 0) {
            sound.sound_name = new char[size+1];
            S->read(size+1, (char*)sound.sound_name);
        } else {
            sound.sound_name = NULL;
        }
        sound.sound_index = S->readInt();
        fSoundName2Idx[i] = sound;
    }
    
    fMaterialAnim.setSize(S->readInt());
    for (size_t i=0; i<fMaterialAnim.getSize(); i++) {
	PY_MATERIAL_ANIM matRec;
	int size = S->readInt();
	if (size != 0) {
	    matRec.material_name = new char[size + 1];
	    S->read(size+1, (char*)matRec.material_name);
	} else {
	    matRec.material_name = NULL;
	}
	size = S->readInt();
	if (size != 0) {
	    matRec.note_name = new char[size+1];
	    S->read(size+1, (char*)matRec.note_name);
	} else {
	    matRec.note_name = NULL;
	}
	matRec.modKey = mgr->readKey(S);
	fMaterialAnim[i] = matRec;
    }
}

void plPythonMod::write(hsStream* S, plResManager* mgr) {
    plMultiModifier::write(S, mgr);
    
    S->writeInt(fPythonSize);
    S->write(fPythonSize, fPythonCode);
    
    S->writeInt(fReceivers.getSize());
    for (size_t i=0; i<fReceivers.getSize(); i++)
        mgr->writeKey(S, fReceivers[i]);
    
    S->writeInt(0);
    
    S->writeInt(0);
    
    S->writeInt(0);
}

void plPythonMod::IPrcWrite(pfPrcHelper* prc) {
    plMultiModifier::IPrcWrite(prc);

    prc->writeSimpleTag("PythonCode");
    prc->writeHexStream(fPythonSize, fPythonCode);
    prc->closeTag();

    size_t i;
    prc->writeSimpleTag("Receivers");
    for (i=0; i<fReceivers.getSize(); i++)
        fReceivers[i]->prcWrite(prc);
    prc->closeTag();
    
    prc->writeSimpleTag("NotetrackRecs");
    for (i=0; i<fAnimNotetracks.getSize(); i++) {
    	prc->startTag("PythonAnimNotetrack");
    	prc->writeParam("NoteName", fAnimNotetracks[i].note_name);
        prc->endTag(false);
        
    	prc->writeSimpleTag("ObjKey");
        fAnimNotetracks[i].objKey->prcWrite(prc);
        prc->closeTag();
        
        prc->writeSimpleTag("ModKey");
        fAnimNotetracks[i].modKey->prcWrite(prc);
        prc->closeTag();
        
        prc->closeTag();
    }
    prc->closeTag();
    
    prc->writeSimpleTag("SoundIdxRecs");
    for (i=0; i<fSoundName2Idx.getSize(); i++) {
    	prc->startTag("PythonSound2Index");
    	prc->writeParam("SoundName", fSoundName2Idx[i].sound_name);
    	prc->writeParam("SoundIndex", fSoundName2Idx[i].sound_index);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->writeSimpleTag("MaterialAnims");
    for(i=0; i<fMaterialAnim.getSize(); i++) {
        prc->startTag("MaterialAnim");
	prc->writeParam("MaterialName", fMaterialAnim[i].material_name);
	prc->writeParam("NoteName", fMaterialAnim[i].note_name);
	prc->endTag(false);

	prc->writeSimpleTag("ModKey");
	fMaterialAnim[i].modKey->prcWrite(prc);
	prc->closeTag();

	prc->closeTag();
    }
    prc->closeTag();
}

void plPythonMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Receivers") {
        fReceivers.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fReceivers.getSize(); i++) {
            fReceivers[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
    	plMultiModifier::IPrcParse(tag, mgr);
    }
}
