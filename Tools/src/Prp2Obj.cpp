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
#include <string_theory/stdio>
#include "ResManager/plResManager.h"
#include "Debug/hsExceptions.hpp"
#include "Debug/plDebug.h"

#include "PRP/Object/plSceneObject.h"
#include "PRP/Object/plDrawInterface.h"
#include "PRP/Object/plCoordinateInterface.h"
#include "PRP/Geometry/plDrawableSpans.h"
#include "PRP/Surface/plLayer.h"

static void doHelp(const char* myname)
{
    ST::printf("Usage: {} filename.prp [options] [objectname ...]\n", myname);
    puts("");
    puts("Options:");
    puts("    -o file  Write the output to `file`");
    puts("    -m file  Write the material definition file to `file`");
    puts("    --help   Display this message");
    puts("");
    puts("If no object is specified, all objects in the file will be dumped.");
    puts("");
}

static ST::string filenameConvert(const ST::string& filename, const char* ext)
{
    ST::string basename = filename.before_first('.');
    return basename + ext;
}

static void WriteObj(plSceneObject* obj, hsStream* S, bool doXform);
static void WriteMat(hsGMaterial* mat, hsStream* S);

int main(int argc, char* argv[])
{
    if (argc < 2) {
        doHelp(argv[0]);
        return 0;
    }
    plDebug::Init(plDebug::kDLAll);

    const char* filename = argv[1];
    ST::string outfile = filenameConvert(filename, ".obj");
    ST::string mtlfile = filenameConvert(filename, ".mtl");
    std::vector<ST::string> objects;

    for (int i=2; i<argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-o") == 0) {
                if (i+1 >= argc) {
                    fputs("No output filename supplied\n", stderr);
                    return 0;
                } else {
                    outfile = argv[++i];
                }
            } else if (strcmp(argv[i], "-m") == 0) {
                if (i+1 >= argc) {
                    fputs("No material filename supplied\n", stderr);
                    return 0;
                } else {
                    mtlfile = argv[++i];
                }
            } else if (strcmp(argv[i], "--help") == 0) {
                doHelp(argv[0]);
                return 0;
            } else {
                ST::printf(stderr, "Unrecognized option: {}\n", argv[i]);
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
        plDebug::Error("{}:{}: {}", e.File(), e.Line(), e.what());
        return 1;
    } catch (const std::exception& e) {
        plDebug::Error("{}", e.what());
        return 1;
    } catch (...) {
        plDebug::Error("Undefined error!");
        return 1;
    }

    hsFileStream OS;

    if (!OS.open(mtlfile, fmCreate)) {
        ST::printf(stderr, "Error opening {} for writing!\n", mtlfile);
        return 1;
    }
    OS.writeStr("#Generated by Prp2Obj\n");

    try {
        std::vector<plKey> MObjs = rm.getKeys(page->getLocation(), kGMaterial);
        for (size_t i = 0; i < MObjs.size(); i++) {
            hsGMaterial* mat = rm.getObject<hsGMaterial>(MObjs[i]);
            WriteMat(mat, &OS);
        }
    } catch (const hsException& e) {
        plDebug::Error("{}:{}: {}", e.File(), e.Line(), e.what());
        return 1;
    }
    OS.close();

    if (!OS.open(outfile, fmCreate)) {
        ST::printf(stderr, "Error opening {} for writing!\n", outfile);
        return 1;
    }
    OS.writeStr("#Generated by Prp2Obj\n");
    OS.writeStr(ST::format("mtllib {}\n", mtlfile));

    size_t nObjects = 0;
    try {
        std::vector<plKey> SObjs = rm.getKeys(page->getLocation(), kSceneObject);
        for (size_t i = 0; i < SObjs.size(); i++) {
            auto obj_f = std::find(objects.begin(), objects.end(), SObjs[i]->getName());
            if (obj_f != objects.end() || objects.size() == 0) {
                plSceneObject* obj = rm.getObject<plSceneObject>(SObjs[i]);
                if (obj->getDrawInterface().Exists())
                    WriteObj(obj, &OS, objects.empty());
                nObjects++;
            }
        }
    } catch (const hsException& e) {
        plDebug::Error("{}:{}: {}", e.File(), e.Line(), e.what());
        return 1;
    }
    OS.close();

    ST::printf("Successfully wrote {} objects\n", nObjects);
    return 0;
}

static size_t s_BaseIndex = 1;
static size_t s_TexBaseIndex = 1;

static void WriteObj(plSceneObject* obj, hsStream* S, bool doXform)
{
    if (!obj->getDrawInterface().isLoaded()) {
        plDebug::Warning("Cannot get draw interface for {}", obj->getKey()->getName());
        return;
    }
    plDrawInterface* draw = obj->getDrawInterface()->getObj<plDrawInterface>();
    plCoordinateInterface* coord = nullptr;
    if (obj->getCoordInterface().Exists())
        coord = obj->getCoordInterface()->getObj<plCoordinateInterface>();

    S->writeStr(ST::format("\ng {}\n", obj->getKey()->getName()));
    for (size_t i=0; i<draw->getNumDrawables(); i++) {
        if (draw->getDrawableKey(i) == -1)
            continue;

        plDrawableSpans* span = draw->getDrawable(i)->getObj<plDrawableSpans>();
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
                hsGMaterial* mat = matKey->getObj<hsGMaterial>(false);
                if (mat && mat->getLayers().size() > 0) {
                    plLayerInterface* lay = mat->getLayers()[0]->getObj<plLayerInterface>(false);
                    while (lay && lay->getUnderLay().Exists())
                        lay = lay->getUnderLay()->getObj<plLayerInterface>(false);
                    uvwSrc = lay->getUVWSrc();
                    uvwXform = lay->getTransform();
                }
            }

            for (size_t j = 0; j < verts.size(); j++) {
                hsVector3 pos;
                if (doXform) {
                    if (coord)
                        pos = coord->getLocalToWorld().multPoint(verts[j].fPos) * 10.0f;
                    else
                        pos = ice->getLocalToWorld().multPoint(verts[j].fPos) * 10.0f;
                } else {
                    pos = verts[j].fPos * 10.0f;
                }
                S->writeStr(ST::format("v {f} {f} {f}\n", pos.X, pos.Z, -pos.Y));
            }

            if (span->getBuffer(ice->getGroupIdx())->getNumUVs() > uvwSrc) {
                for (size_t j = 0; j < verts.size(); j++) {
                    hsVector3 txUvw = uvwXform.multPoint(verts[j].fUVWs[uvwSrc]);
                    S->writeStr(ST::format("vt {f} {f} {f}\n",
                                txUvw.X, txUvw.Y, txUvw.Z));
                }
            }

            for (size_t j = 0; j < verts.size(); j++) {
                S->writeStr(ST::format("vn {f} {f} {f}\n",
                            verts[j].fNormal.X,
                            verts[j].fNormal.Z,
                            -verts[j].fNormal.Y));
            }

            if (span->getBuffer(ice->getGroupIdx())->getNumUVs() > uvwSrc) {
                for (size_t j = 0; j < indices.size(); j += 3) {
                    S->writeStr(ST::format("f {}/{}/{} {}/{}/{} {}/{}/{}\n",
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
                    S->writeStr(ST::format("f {}//{} {}//{} {}//{}\n",
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

static void WriteMat(hsGMaterial* mat, hsStream* S)
{
    if (mat->getLayers().empty())
        return;

    // Obj doesn't support multiple textures, so we just get the texture
    // on the base of the first layer in each material...
    plLayerInterface* lay = mat->getLayers()[0]->getObj<plLayerInterface>(false);
    while (lay && lay->getUnderLay().Exists())
        lay = lay->getUnderLay()->getObj<plLayerInterface>(false);
    if (lay == nullptr) {
        plDebug::Warning("Cannot get layer for {}", mat->getKey()->getName());
        return;
    }

    S->writeStr(ST::format("\nnewmtl {}\n", mat->getKey()->getName()));

    if ((lay->getState().fShadeFlags & hsGMatState::kShadeWhite) != 0)
        S->writeStr("Ka 1.0 1.0 1.0\n");
    S->writeStr(ST::format("Kd {f} {f} {f}\n",
                lay->getRuntime().r, lay->getRuntime().g, lay->getRuntime().b));
    if ((lay->getState().fShadeFlags & hsGMatState::kShadeSpecular) != 0) {
        S->writeStr(ST::format("Ks {f} {f} {f}\n",
                    lay->getSpecular().r, lay->getSpecular().g, lay->getSpecular().b));
        S->writeStr(ST::format("Ns {f}\n", lay->getSpecularPower()));
    }
    S->writeStr(ST::format("d {f}\n", lay->getOpacity()));
}
