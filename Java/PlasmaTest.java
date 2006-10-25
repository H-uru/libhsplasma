import Plasma.CoreLib.*;

public class PlasmaTest {
    public static void main(String[] args) {
        hsTBasicArray<Integer> arr = new hsTBasicArray<Integer>();

        arr.add(3);
        arr.add(5);
        arr.remove(0);
        arr.add(7);
        System.out.printf("%d, %d\n", arr.get(0), arr.get(1));
    }
}

