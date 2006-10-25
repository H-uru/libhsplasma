package Plasma;

import java.io.IOException;
import Plasma.CoreLib.hsStream;

public class hsMatrix44 {
    private float[][] data = new float[4][4];

    public hsMatrix44() {
        Identity();
    }

    public hsMatrix44(hsMatrix44 init) {
        for (int y=0; y<4; y++)
            for (int x=0; x<4; x++)
                data[y][x] = init.data[y][x];
    }

    public void Identity() {
        for (int y=0; y<4; y++)
            for (int x=0; x<4; x++)
                if (x == y) data[y][x] = 1.0f;
                else data[y][x] = 0.0f;
    }

    public float get(int y, int x) {
        return data[y][x];
    }
    public void set(int y, int x, float val) {
        data[y][x] = val;
    }

    public hsMatrix44 add(hsMatrix44 other) {
        hsMatrix44 result = new hsMatrix44();
        for (int y=0; y<4; y++)
            for (int x=0; x<4; x++)
                result.data[y][x] = this.data[y][x] + other.data[y][x];
        return result;
    }

    public hsMatrix44 mult(float scale) {
        hsMatrix44 result = new hsMatrix44();
        for (int y=0; y<4; y++)
            for (int x=0; x<4; x++)
                result.data[y][x] = data[y][x] * scale;
        return result;
    }

    public hsMatrix44 mult(hsMatrix44 other) {
        hsMatrix44 result = new hsMatrix44();
        for (int y=0; y<4; y++)
            for (int x=0; x<4; x++)
                result.data[y][x] = data[y][0] * other.data[0][x] +
                                    data[y][1] * other.data[1][x] +
                                    data[y][2] * other.data[2][x] +
                                    data[y][3] * other.data[3][x];
        return result;
    }

    public void read(hsStream S) throws IOException {
        for (int y=0; y<4; y++)
            for (int x=0; x<4; x++)
                data[y][x] = S.readFloat();
    }

    public void write(hsStream S) throws IOException {
        for (int y=0; y<4; y++)
            for (int x=0; x<4; x++)
                S.writeFloat(data[y][x]);
    }

    public hsMatrix44 scale(float x, float y, float z) {
        hsMatrix44 scalar = new hsMatrix44();
        scalar.set(0, 0, x);
        scalar.set(1, 1, y);
        scalar.set(2, 2, z);
        return mult(scalar);
    }

    public hsMatrix44 translate(float x, float y, float z) {
        hsMatrix44 xlate = new hsMatrix44();
        xlate.set(0, 3, x);
        xlate.set(1, 3, y);
        xlate.set(2, 3, z);
        return mult(xlate);
    }

    public hsMatrix44 rotate(float x, float y, float z) {
        hsMatrix44 rot = new hsMatrix44();
        hsMatrix44 result;
        rot.set(1, 1, (float)Math.cos(x));
        rot.set(1, 2, (float)Math.sin(x));
        rot.set(2, 1, 0.0f-(float)Math.sin(x));
        rot.set(2, 2, (float)Math.cos(x));
        result = this.mult(rot);
        rot.Identity();
        rot.set(0, 0, (float)Math.cos(y));
        rot.set(0, 2, 0.0f-(float)Math.sin(y));
        rot.set(2, 0, (float)Math.sin(y));
        rot.set(2, 2, (float)Math.cos(y));
        result = result.mult(rot);
        rot.Identity();
        rot.set(0, 0, (float)Math.cos(z));
        rot.set(0, 1, (float)Math.sin(z));
        rot.set(1, 0, 0.0f-(float)Math.sin(z));
        rot.set(1, 1, (float)Math.cos(z));
        return result.mult(rot);
    }

    public String toString() {
        return String.format("[ %8.3f %8.3f %8.3f %8.3f\n  %8.3f %8.3f %8.3f %8.3f\n  %8.3f %8.3f %8.3f %8.3f\n  %8.3f %8.3f %8.3f %8.3f ]",
            data[0][0], data[0][1], data[0][2], data[0][3],
            data[1][0], data[1][1], data[1][2], data[1][3],
            data[2][0], data[2][1], data[2][2], data[2][3],
            data[3][0], data[3][1], data[3][2], data[3][3]);
    }
}

