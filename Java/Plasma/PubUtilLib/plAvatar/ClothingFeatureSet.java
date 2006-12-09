package Plasma.PubUtilLib.plAvatar;

import java.io.IOException;
import Plasma.CoreLib.hsStream;
import Plasma.plCreatable;
import Plasma.NucleusLib.pnKeyedObject.*;

public class ClothingFeatureSet extends plCreatable {
    public class ClothingTexture {
        public byte TexID;
        public plKey Texture;
    }

    protected String FeatureName;
    public ClothingTexture[] Textures = new ClothingTexture[0];

    public void read(hsStream S) throws IOException {
        FeatureName = S.readSafeString();
        Textures = new ClothingTexture[S.readByte()];
        for (int i=0; i<Textures.length; i++) {
            Textures[i].TexID = S.readByte();
            Textures[i].Texture.read(S);
        }
    }

    public void write(hsStream S) throws IOException {
        S.writeSafeString(FeatureName);
        S.writeByte((byte)Textures.length);
        for (int i=0; i<Textures.length; i++) {
            S.writeByte(Textures[i].TexID);
            Textures[i].Texture.write(S);
        }
    }
    
    public String getTypeName() { return ""; }
    public int getTypeNum() { return -1; }
}

