#include "plShader.h"

/* plShaderConst */
plShaderConst::plShaderConst() {
    memset(fArray, 0, sizeof(fArray));
}

plShaderConst::plShaderConst(float f1, float f2, float f3, float f4)
             : fX(f1), fY(f2), fZ(f3), fW(f4) { }

plShaderConst::plShaderConst(const plShaderConst& init) {
    memcpy(fArray, init.fArray, sizeof(fArray));
}

plShaderConst& plShaderConst::operator=(const plShaderConst& init) {
    memcpy(fArray, init.fArray, sizeof(fArray));
    return *this;
}

float& plShaderConst::operator[](size_t idx) { return fArray[idx]; }

void plShaderConst::read(hsStream* S) {
    fArray[0] = S->readFloat();
    fArray[1] = S->readFloat();
    fArray[2] = S->readFloat();
    fArray[3] = S->readFloat();
}

void plShaderConst::write(hsStream* S) {
    S->writeFloat(fArray[0]);
    S->writeFloat(fArray[1]);
    S->writeFloat(fArray[2]);
    S->writeFloat(fArray[3]);
}

void plShaderConst::prcWrite(pfPrcHelper* prc) {
    prc->writeTagNoBreak("plShaderConst");
    prc->getStream()->writeStr(plString::Format("%f %f %f %f",
                               fArray[0], fArray[1], fArray[2], fArray[3]));
    prc->closeTagNoBreak();
}

void plShaderConst::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plShaderConst")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    hsTList<plString> data = tag->getContents();
    if (data.getSize() != 4)
        throw pfPrcParseException(__FILE__, __LINE__, "plShaderConst expects 4 floats");
    fArray[0] = data.pop().toFloat();
    fArray[1] = data.pop().toFloat();
    fArray[2] = data.pop().toFloat();
    fArray[3] = data.pop().toFloat();
}


/* plShader */
plShader::plShader() : fID(kUnregistered), fInput(0), fOutput(0) { }
plShader::~plShader() { }

IMPLEMENT_CREATABLE(plShader, kShader, hsKeyedObject)

void plShader::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    fConsts.setSize(S->readInt());
    for (size_t i=0; i<fConsts.getSize(); i++)
        fConsts[i].read(S);
    fID = (plShaderID)S->readInt();

    fInput = S->readByte();
    fOutput = S->readByte();
}

void plShader::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    S->writeInt(fConsts.getSize());
    for (size_t i=0; i<fConsts.getSize(); i++)
        fConsts[i].write(S);
    S->writeInt(fID);

    S->writeByte(fInput);
    S->writeByte(fOutput);
}

void plShader::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);

    prc->writeSimpleTag("Constants");
    for (size_t i=0; i<fConsts.getSize(); i++)
        fConsts[i].prcWrite(prc);
    prc->closeTag();

    prc->startTag("ShaderParams");
    prc->writeParam("ID", fID);
    prc->writeParam("Input", fInput);
    prc->writeParam("Output", fOutput);
    prc->endTag(true);
}

void plShader::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Constants") {
        const pfPrcTag* child = tag->getFirstChild();
        fConsts.setSize(tag->countChildren());
        for (size_t i=0; i<fConsts.getSize(); i++) {
            fConsts[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "ShaderParams") {
        fID = (plShaderID)tag->getParam("ID", "0").toUint();
        fInput = tag->getParam("Input", "0").toUint();
        fOutput = tag->getParam("Output", "0").toUint();
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}

size_t plShader::getNumConsts() const { return fConsts.getSize(); }
plShaderConst plShader::getConst(size_t idx) const { return fConsts[idx]; }
void plShader::clearConsts() { fConsts.clear(); }
void plShader::addConst(const plShaderConst& sc) { fConsts.append(sc); }

plShader::plShaderID plShader::getID() const { return fID; }
unsigned char plShader::getInput() const { return fInput; }
unsigned char plShader::getOutput() const { return fOutput; }
void plShader::setID(plShader::plShaderID id) { fID = id; }
void plShader::setInput(unsigned char input) { fInput = input; }
void plShader::setOutput(unsigned char output) { fOutput = output; }
