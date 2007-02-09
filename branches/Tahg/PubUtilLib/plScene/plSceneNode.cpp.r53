#include "plSceneNode.h"
#include "../plResMgr/plResManager.h"

plSceneNode::plSceneNode(PlasmaVer pv) { }
plSceneNode::~plSceneNode() { }

short plSceneNode::ClassIndex() { return 0x0000; }

void plSceneNode::read(hsStream *S) {
    hsKeyedObject::read(S);

    SceneObjects.setSize(S->readInt());
	int i;
    for (i=0; i<SceneObjects.getSize(); i++) {
        SceneObjects[i] = plResManager::inst->readKey(S);
        SceneObjects[i]->Ref();
    }
    OtherObjects.setSize(S->readInt());
    for (i=0; i<OtherObjects.getSize(); i++) {
        OtherObjects[i] = plResManager::inst->readKey(S);
        OtherObjects[i]->Ref();
    }
}

void plSceneNode::write(hsStream *S) {
    hsKeyedObject::write(S);

    S->writeInt(SceneObjects.getSize());
	int i;
    for (i=0; i<SceneObjects.getSize(); i++)
        plResManager::inst->writeKey(S, SceneObjects[i]);
    S->writeInt(OtherObjects.getSize());
    for (i=0; i<OtherObjects.getSize(); i++)
        plResManager::inst->writeKey(S, OtherObjects[i]);
}

#ifdef Tahg //line 34(ideally) Don't touch vvvv
            //  Fine, I'll leave it for now in this file, but it's stupid to try
            //  to align everything to the same lines as Cyan does -- espeically
            //  since this *isn't* Cyan's library.
plSceneNode::plSceneNode() {
}


plSceneNode::~plSceneNode() {
	plgDispatch::Dispatch()->UnRegisterForExactType(plNodeCleanupMsg::plNodeCleanupMsgClassIndex, fpKey);

	if(fSpaceTree != 0) delete fSpaceTree;
}





void plSceneNode::Init() //49
{
	plgDispatch::Dispatch()->RegisterForExactType(plNodeCleanupMsg::plNodeCleanupMsgClassIndex, fpKey);
}


void plSceneNode::Read(class hsStream * s, class hsResMgr * mgr) { //55
	hsKeyedObject::Read(s, mgr);

	unsigned long n;
	plKey key;

	n = s->ReadSwap32();
	fSceneObjects.Reset();
	for(int i = 0; i < n; i++)
	{
		plNodeRefMsg * msg = new plNodeRefMsg(fpKey, 1, 3, i);
		mgr->ReadKeyNotifyMe(s, msg, plRefFlags::Type::None);		
	}

	n = s->ReadSwap32();
	fGenericPool.Reset();
	for( ; n > 0; n--)
	{
		plNodeRefMsg * msg = new plNodeRefMsg(fpKey, 1, 7, -1);
		mgr->ReadKeyNotifyMe(s, msg, plRefFlags::Type::None);
	}
}


void plSceneNode::Write(class hsStream * s, class hsResMgr * mgr) { //79
	hsKeyedObject::Write(s, mgr);

	int i;

	s->WriteSwap32(fSceneObjects.getSize());
	for(i = 0; i < fSceneObjects.getSize(); i++) {
		mgr->WriteKey(s, fSceneObjects[i], 0);
	}
	s->WriteSwap32(fGenericPool.getSize());
	for(i = 0; i < fGenericPool.getSize(); i++) {
		mgr->WriteKey(s, fGenericPool[i], 0);
	}
}












































void plSceneNode::SubmitOccluders(class plPageTreeMgr * pageMgr)const { //137
	pageMgr->AddOccluderList(hsTArray<plOccluder *>(fOccluders));
}


plSpaceTree * plSceneNode::IBuildSpaceTree(void) { //142
	plSpaceTreeMaker maker;
	maker.Reset();

	hsBounds3Ext bnd;
	bnd.Reset(new hsPoint3(0,0,0));


	for(int i = 0; i < fDrawPool.getSize(); i++)

		if(fDrawPool[i])
			maker.AddLeaf(fDrawPool[i]->GetSpaceTree()->GetWorldBounds(), 0);
		
		else maker.AddLeaf(bnd, 1);


		fSpaceTree = maker.MakeTree();
		fSpaceTree->MakeDirty();

		return fSpaceTree;
}


plSpaceTree * plSceneNode::ITrashSpaceTree() { //165
	if (fSpaceTree != 0) delete fSpaceTree;
	return fSpaceTree = 0;
}


void  plSceneNode::IDirtySpaceTree(void) { //171

	for (int i = 0; i < fDrawPool.getSize(); i++)
	{
		if(fDrawPool[i] && fDrawPool[i]->GetSpaceTree()->HasLeafFlag(
			fDrawPool[i]->GetSpaceTree()->GetRoot(), 2)) {
			fDrawPool[i]->GetSpaceTree()->Refresh();
			fDrawPool[i]->GetSpaceTree()->MoveLeaf(i, fDrawPool[i]->GetSpaceTree()->GetWorldBounds());

		}
	}
}

plSpaceTree * plSceneNode::GetSpaceTree(void) { //184
	if(!fSpaceTree)
		;
	return 0;
}
=======


void plSceneNode::Read(class hsStream * s, class hsResMgr * mgr) { //55
	hsKeyedObject::Read(s, mgr);

	unsigned long n;
	plKey key;

	n = s->ReadSwap32();
	fSceneObjects.Reset();
	for(int i = 0; i < n; i++)
	{
		plNodeRefMsg * msg = new plNodeRefMsg(fpKey, 1, 3, i);
		mgr->ReadKeyNotifyMe(s, msg, plRefFlags::Type::None);		
	}

	n = s->ReadSwap32();
	fGenericPool.Reset();
	for( ; n > 0; n--)
	{
		plNodeRefMsg * msg = new plNodeRefMsg(fpKey, 1, 7, -1);
		mgr->ReadKeyNotifyMe(s, msg, plRefFlags::Type::None);
	}
}


void plSceneNode::Write(class hsStream * s, class hsResMgr * mgr) { //79
	hsKeyedObject::Write(s, mgr);

	int i;

	s->WriteSwap32(fSceneObjects.getSize());
	for(i = 0; i < fSceneObjects.getSize(); i++) {
		mgr->WriteKey(s, fSceneObjects[i], 0);
	}
	s->WriteSwap32(fGenericPool.getSize());
	for(i = 0; i < fGenericPool.getSize(); i++) {
		mgr->WriteKey(s, fGenericPool[i], 0);
	}
}












































void plSceneNode::SubmitOccluders(class plPageTreeMgr * pageMgr)const { //137
	pageMgr->AddOccluderList(hsTArray<plOccluder *>(fOccluders));
}


plSpaceTree * plSceneNode::IBuildSpaceTree(void) { //142
	plSpaceTreeMaker maker;
	maker.Reset();

	hsBounds3Ext bnd;
	bnd.Reset(new hsPoint3(0,0,0));


	for(int i = 0; i < fDrawPool.getSize(); i++)

		if(fDrawPool[i])
			maker.AddLeaf(fDrawPool[i]->GetSpaceTree()->GetWorldBounds(), 0);
		
		else maker.AddLeaf(bnd, 1);


		fSpaceTree = maker.MakeTree();
		fSpaceTree->MakeDirty();

		return fSpaceTree;
}


plSpaceTree * plSceneNode::ITrashSpaceTree() { //165
	if (fSpaceTree != 0) delete fSpaceTree;
	return fSpaceTree = 0;
}


void  plSceneNode::IDirtySpaceTree(void) { //171

	for (int i = 0; i < fDrawPool.getSize(); i++)
	{
		if(fDrawPool[i] && fDrawPool[i]->GetSpaceTree()->HasLeafFlag(
			fDrawPool[i]->GetSpaceTree()->GetRoot(), 2)) {
			fDrawPool[i]->GetSpaceTree()->Refresh();
			fDrawPool[i]->GetSpaceTree()->MoveLeaf(i, fDrawPool[i]->GetSpaceTree()->GetWorldBounds());

		}
	}
}

plSpaceTree * plSceneNode::GetSpaceTree(void) { //184
	if(!fSpaceTree)
		;
	return 0;
}
>>>>>>> .r49
#endif //Don't touch ^^^^
