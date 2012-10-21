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

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include "ResManager/plResManager.h"
#include "Debug/hsExceptions.hpp"
#include "Debug/plDebug.h"
#include "Util/plString.h"

#include "PRP/Object/plSceneObject.h"
#include "PRP/Object/plDrawInterface.h"
#include "PRP/Object/plCoordinateInterface.h"
#include "PRP/Geometry/plDrawableSpans.h"
#include "PRP/Surface/plLayer.h"

void doHelp(const char* myname) {
    printf("Usage: %s filename.prp [options] [objectname ...]\n\n", myname);
    printf("Options:\n");
    printf("    -o file  Write the output to `file`\n");
    printf("    -m file  Write the material definition file to `file`\n");
    printf("    --help   Display this message\n\n");
    printf("If no object is specified, all objects in the file will be dumped.\n\n");
}

plString filenameConvert(const char* filename, const char* ext) {
    plString basename = plString(filename).beforeFirst('.');
    return basename + ext;
}

void WriteObj(plSceneObject* obj, hsStream* S, bool doXform);
void WriteMat(hsGMaterial* mat, hsStream* S);

int main(int argc, char** argv) {
    if (argc < 2) {
        doHelp(argv[0]);
        return 0;
    }
    plDebug::Init(plDebug::kDLAll);

    const char* filename = argv[1];
    plString outfile = filenameConvert(filename, ".obj");
    plString mtlfile = filenameConvert(filename, ".mtl");
    std::vector<plString> objects;

    for (int i=2; i<argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-o") == 0) {
                if (i+1 >= argc) {
                    printf("No output filename supplied\n");
                    return 0;
                } else {
                    outfile = argv[++i];
                }
            } else if (strcmp(argv[i], "-m") == 0) {
                if (i+1 >= argc) {
                    printf("No material filename supplied\n");
                    return 0;
                } else {
                    mtlfile = argv[++i];
                }
            } else if (strcmp(argv[i], "--help") == 0) {
                doHelp(argv[0]);
                return 0;
            } else {
                printf("Unrecognized option: %s\n", argv[i]);
            }
        } else {
            objects.push_back(argv[i]);
        }
    }

    plResManager rm;
    plPageInfo* page;
    try {
        page = rm.ReadPage(filename);
    } catch (const hsException& e) {
        plDebug::Error("%s:%lu: %s", e.File(), e.Line(), e.what());
        return 1;
    } catch (const std::exception& e) {
        plDebug::Error("%s", e.what());
        return 1;
    } catch (...) {
        plDebug::Error("Undefined error!");
        return 1;
    }

    hsFileStream OS;

    if (!OS.open(mtlfile, fmCreate)) {
        fprintf(stderr, "Error opening %s for writing!\n", mtlfile.cstr());
        return 1;
    }
    OS.writeStr("#Generated by Prp2Obj\n");

    try {
        std::vector<plKey> MObjs = rm.getKeys(page->getLocation(), kGMaterial);
        for (size_t i = 0; i < MObjs.size(); i++) {
            hsGMaterial* mat = hsGMaterial::Convert(rm.getObject(MObjs[i]));
            WriteMat(mat, &OS);
        }
    } catch (const hsException& e) {
        plDebug::Error("%s:%lu: %s", e.File(), e.Line(), e.what());
        return 1;
    }
    OS.close();

    if (!OS.open(outfile, fmCreate)) {
        fprintf(stderr, "Error opening %s for writing!\n", outfile.cstr());
        return 1;
    }
    OS.writeStr("#Generated by Prp2Obj\n");
    OS.writeStr(plString::Format("mtllib %s\n", mtlfile.cstr()));

    size_t nObjects = 0;
    try {
        std::vector<plKey> SObjs = rm.getKeys(page->getLocation(), kSceneObject);
        for (size_t i = 0; i < SObjs.size(); i++) {
            auto obj_f = std::find(objects.begin(), objects.end(), SObjs[i]->getName());
            if (obj_f != objects.end()) {
                plSceneObject* obj = plSceneObject::Convert(rm.getObject(SObjs[i]));
                if (obj->getDrawInterface().Exists())
                    WriteObj(obj, &OS, objects.empty());
                nObjects++;
            }
        }
    } catch (const hsException& e) {
        plDebug::Error("%s:%lu: %s", e.File(), e.Line(), e.what());
        return 1;
    }
    OS.close();

    printf("Successfully wrote %u objects\n", (unsigned int)nObjects);
    return 0;
}

static size_t s_BaseIndex = 1;
static size_t s_TexBaseIndex = 1;

void WriteObj(plSceneObject* obj, hsStream* S, bool doXform) {
    if (!obj->getDrawInterface().isLoaded()) {
        plDebug::Warning("Cannot get draw interface for %s", obj->getKey()->getName().cstr());
        return;
    }
    plDrawInterface* draw = plDrawInterface::Convert(obj->getDrawInterface()->getObj());
    plCoordinateInterface* coord = NULL;
    if (obj->getCoordInterface().Exists())
        coord = plCoordinateInterface::Convert(obj->getCoordInterface()->getObj());

    S->writeStr(plString::Format("\ng %s\n", obj->getKey()->getName().cstr()));
    for (size_t i=0; i<draw->getNumDrawables(); i++) {
        if (draw->getDrawableKey(i) == -1)
            continue;

        plDrawableSpans* span = plDrawableSpans::Convert(draw->getDrawable(i)->getObj());
        plDISpanIndex di = span->getDIIndex(draw->getDrawableKey(i));
        if ((di.fFlags & plDISpanIndex::kMatrixOnly) != 0)
            continue;

        for (size_t idx=0; idx<di.fIndices.size(); idx++) {
            plIcicle* ice = (plIcicle*)span->getSpan(di.fIndices[idx]);
            std::vector<plGBufferVertex> verts = span->getVerts(ice);
            std::vector<unsigned short> indices = span->getIndices(ice);

            unsigned int uvwSrc = 0;
            hsMatrix44 uvwXform;
            plKey matKey = span->getMaterials()[ice->getMaterialIdx()];
            if (matKey.Exists()) {
                hsGMaterial* mat = hsGMaterial::Convert(matKey->getObj(), false);
                if (mat != NULL && mat->getLayers().size() > 0) {
                    plLayerInterface* lay = plLayerInterface::Convert(mat->getLayers()[0]->getObj(), false);
                    while (lay != NULL && lay->getUnderLay().Exists())
                        lay = plLayerInterface::Convert(lay->getUnderLay()->getObj(), false);
                    uvwSrc = lay->getUVWSrc();
                    uvwXform = lay->getTransform();
                }
            }

            for (size_t j = 0; j < verts.size(); j++) {
                hsVector3 pos;
                if (doXform) {
                    if (coord != NULL)
                        pos = coord->getLocalToWorld().multPoint(verts[j].fPos) * 10.0f;
                    else
                        pos = ice->getLocalToWorld().multPoint(verts[j].fPos) * 10.0f;
                } else {
                    pos = verts[j].fPos * 10.0f;
                }
                S->writeStr(plString::Format("v %f %f %f\n", pos.X, pos.Z, -pos.Y));
            }

            if (span->getBuffer(ice->getGroupIdx())->getNumUVs() > uvwSrc) {
                for (size_t j = 0; j < verts.size(); j++) {
                    hsVector3 txUvw = uvwXform.multPoint(verts[j].fUVWs[uvwSrc]);
                    S->writeStr(plString::Format("vt %f %f %f\n",
                                txUvw.X, txUvw.Y, txUvw.Z));
                }
            }

            for (size_t j = 0; j < verts.size(); j++) {
                S->writeStr(plString::Format("vn %f %f %f\n",
                            verts[j].fNormal.X,
                            verts[j].fNormal.Z,
                            -verts[j].fNormal.Y));
            }

            if (span->getBuffer(ice->getGroupIdx())->getNumUVs() > uvwSrc) {
                for (size_t j = 0; j < indices.size(); j += 3) {
                    S->writeStr(plString::Format("f %u/%u/%u %u/%u/%u %u/%u/%u\n",
                                indices[j+0] + s_BaseIndex,
                                indices[j+0] + s_TexBaseIndex,
                                indices[j+0] + s_BaseIndex,
                                indices[j+1] + s_BaseIndex,
                                indices[j+1] + s_TexBaseIndex,
                                indices[j+1] + s_BaseIndex,
                                indices[j+2] + s_BaseIndex,
                                indices[j+2] + s_TexBaseIndex,
                                indices[j+2] + s_BaseIndex));
                }
                s_BaseIndex += ice->getVLength();
                s_TexBaseIndex += ice->getVLength();
            } else {
                for (size_t j = 0; j < indices.size(); j += 3) {
                    S->writeStr(plString::Format("f %u//%u %u//%u %u//%u\n",
                                indices[j+0] + s_BaseIndex,
                                indices[j+0] + s_BaseIndex,
                                indices[j+1] + s_BaseIndex,
                                indices[j+1] + s_BaseIndex,
                                indices[j+2] + s_BaseIndex,
                                indices[j+2] + s_BaseIndex));
                }
                s_BaseIndex += ice->getVLength();
            }
        }
    }
}

void WriteMat(hsGMaterial* mat, hsStream* S) {
    if (mat->getLayers().empty())
        return;

    // Obj doesn't support multiple textures, so we just get the texture
    // on the base of the first layer in each material...
    plLayerInterface* lay = plLayerInterface::Convert(mat->getLayers()[0]->getObj(), false);
    while (lay != NULL && lay->getUnderLay().Exists())
        lay = plLayerInterface::Convert(lay->getUnderLay()->getObj(), false);
    if (lay == NULL) {
        plDebug::Warning("Cannot get layer for %s", mat->getKey()->getName().cstr());
        return;
    }

    S->writeStr(plString::Format("\nnewmtl %s\n", mat->getKey()->getName().cstr()));

    if ((lay->getState().fShadeFlags & hsGMatState::kShadeWhite) != 0)
        S->writeStr("Ka 1.0 1.0 1.0\n");
    S->writeStr(plString::Format("Kd %f %f %f\n",
                lay->getRuntime().r, lay->getRuntime().g, lay->getRuntime().b));
    if ((lay->getState().fShadeFlags & hsGMatState::kShadeSpecular) != 0) {
        S->writeStr(plString::Format("Ks %f %f %f\n",
                    lay->getSpecular().r, lay->getSpecular().g, lay->getSpecular().b));
        S->writeStr(plString::Format("Ns %f\n", lay->getSpecularPower()));
    }
    S->writeStr(plString::Format("d %f\n", lay->getOpacity()));
}
