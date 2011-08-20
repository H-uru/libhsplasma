#include "plBtMotionState.h"

#include <PRP/Object/plCoordinateInterface.h>
#include <PRP/Object/plSceneObject.h>
#include <PRP/Object/plSimulationInterface.h>
#include <PRP/Physics/plGenericPhysical.h>

namespace {
    inline btVector3 toBullet(const hsVector3& plvec)
    {
        btVector3 btvec;
        btvec.setX(plvec.X);
        btvec.setY(plvec.Y);
        btvec.setZ(plvec.Z);
        return btvec;
    }

    inline hsVector3 toPlasma(const btVector3& btvec)
    {
        hsVector3 plvec;
        plvec.X = btvec.getX();
        plvec.Y = btvec.getY();
        plvec.Z = btvec.getZ();
        return plvec;
    }

    inline btQuaternion toBullet(const hsQuat& plquat)
    {
        btQuaternion btquat;
        btquat.setX(plquat.X);
        btquat.setY(plquat.Y);
        btquat.setZ(plquat.Z);
        btquat.setW(plquat.W);
        return btquat;
    }

    inline hsQuat toPlasma(const btQuaternion& btquat)
    {
        hsQuat plquat;
        plquat.X = btquat.getX();
        plquat.Y = btquat.getY();
        plquat.Z = btquat.getZ();
        plquat.W = btquat.getW();
        return plquat;
    }

    void updateCiChildren(plCoordinateInterface* ci)
    {
        const hsTArray<plKey>& kids = ci->getChildren();
        for (size_t i = 0; i < kids.getSize(); i++) {
            plSceneObject *obj = plSceneObject::Convert(kids[i]->getObj());
            plCoordinateInterface *child = plCoordinateInterface::Convert(obj->getCoordInterface()->getObj());
            child->setLocalToWorld(child->getLocalToParent() * ci->getLocalToWorld());
            child->setWorldToLocal(child->getLocalToWorld().inverse());
            updateCiChildren(child);
        }
    }
}

plBtMotionState::plBtMotionState(const plKey& key)
{
    obj = key;
}

void plBtMotionState::getWorldTransform(btTransform& worldTrans) const
{
    plSceneObject *object = plSceneObject::Convert(obj->getObj());
    if (object->getCoordInterface().Exists()) {
        plCoordinateInterface *iface = plCoordinateInterface::Convert(object->getCoordInterface()->getObj());
        worldTrans.setFromOpenGLMatrix(iface->getLocalToWorld().glMatrix());
    } else {
        plSimulationInterface *sim = plSimulationInterface::Convert(object->getSimInterface()->getObj());
        plGenericPhysical *phys = plGenericPhysical::Convert(sim->getPhysical()->getObj());
        worldTrans.setOrigin(toBullet(phys->getPos()));
        worldTrans.setRotation(toBullet(phys->getRot()));
    }
}

void plBtMotionState::setWorldTransform(const btTransform& worldTrans)
{
    plSceneObject *object = plSceneObject::Convert(obj->getObj());
    if (object->getCoordInterface().Exists()) {
        plCoordinateInterface *iface = plCoordinateInterface::Convert(object->getCoordInterface()->getObj());
        btMatrix3x3 mat(worldTrans.getRotation());
        hsMatrix44 worldmat;
        worldmat(0,0) = mat.getRow(0).x();
        worldmat(0,1) = mat.getRow(0).y();
        worldmat(0,2) = mat.getRow(0).z();
        worldmat(1,0) = mat.getRow(1).x();
        worldmat(1,1) = mat.getRow(1).y();
        worldmat(1,2) = mat.getRow(1).z();
        worldmat(2,0) = mat.getRow(2).x();
        worldmat(2,1) = mat.getRow(2).y();
        worldmat(2,2) = mat.getRow(2).z();
        worldmat.setTranslate(toPlasma(worldTrans.getOrigin()));
        iface->setWorldToLocal(worldmat);
        iface->setParentToLocal(worldmat);
        iface->setLocalToWorld(worldmat.inverse());
        iface->setLocalToParent(worldmat.inverse());
        updateCiChildren(iface);
    } else {
        plSimulationInterface *sim = plSimulationInterface::Convert(object->getSimInterface()->getObj());
        plGenericPhysical *phys = plGenericPhysical::Convert(sim->getPhysical()->getObj());
        phys->setPos(toPlasma(worldTrans.getOrigin()));
        phys->setRot(toPlasma(worldTrans.getRotation()));
    }
}
