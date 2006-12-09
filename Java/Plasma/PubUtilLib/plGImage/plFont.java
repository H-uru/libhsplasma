package Plasma.PubUtilLib.plGImage;

import java.io.IOException;
import java.io.FileNotFoundException;
import Plasma.CoreLib.hsStream;
import Plasma.NucleusLib.pnKeyedObject.*;

public class plFont extends hsKeyedObject {
    class FontLetterDef {
        public int offset;
        public int lHeight;
        public int stHeight;
        public float lPadding;
        public float rPadding;
    }

    protected String fontName;
    protected byte fontSize = -1;
    protected int fontFlags;
    protected int imgWidth;
    protected int imgHeight;
    protected int maxHeight;
    protected byte bpp;

    protected byte[] bmpData;
    protected short unknown;

    public FontLetterDef[] Letters = new FontLetterDef[256];
    
    public plFont() { }
    public plFont(String fileName) throws FileNotFoundException, IOException {
        hsStream FS = new hsStream(fileName, hsStream.MODE_READ);
        readP2F(FS);
    }

    public void read(hsStream S) throws IOException {
        super.read(S);
        readP2F(S);
    }

    public void write(hsStream S) throws IOException {
        super.write(S);
        writeP2F(S);
    }

    public void readP2F(hsStream S) throws IOException {
        fontName = S.readString(256);
        fontSize = S.readByte();
        fontFlags = S.readInt();
        imgWidth = S.readInt();
        imgHeight = S.readInt();
        maxHeight = S.readInt();
        bpp = S.readByte();

        bmpData = S.readString(imgWidth * imgHeight).getBytes();
        unknown = S.readShort();

        Letters = new FontLetterDef[S.readInt()];
        for (int i=0; i<Letters.length; i++) {
            Letters[i].offset = S.readInt();
            Letters[i].lHeight = S.readInt();
            Letters[i].stHeight = S.readInt();
            Letters[i].lPadding = S.readFloat();
            Letters[i].rPadding = S.readFloat();
        }
    }

    public void writeP2F(hsStream S) throws IOException {
        byte[] fName = new byte[256];
        System.arraycopy(fontName.getBytes(), 0, fName, 0, fontName.length());
        S.writeString(new String(fName));
        S.writeByte(fontSize);
        S.writeInt(fontFlags);
        S.writeInt(imgWidth);
        S.writeInt(imgHeight);
        S.writeInt(maxHeight);
        S.writeByte(bpp);

        S.writeString(new String(bmpData));
        S.writeShort(unknown);

        for (int i=0; i<Letters.length; i++) {
            S.writeInt(Letters[i].offset);
            S.writeInt(Letters[i].lHeight);
            S.writeInt(Letters[i].stHeight);
            S.writeFloat(Letters[i].lPadding);
            S.writeFloat(Letters[i].rPadding);
        }
    }
}

