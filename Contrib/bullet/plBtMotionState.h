#include <LinearMath/btMotionState.h>

#include <PRP/KeyedObject/plKey.h>

class plBtMotionState : public btMotionState {
public:
    plBtMotionState(const plKey&);

    virtual void getWorldTransform(btTransform& worldTrans) const;
    virtual void setWorldTransform(const btTransform& worldTrans);

private:
    plKey obj;
};
