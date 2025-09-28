package pcd.rle.sequencial;

import java.util.concurrent.TimeUnit;

public class RLESequential {
    public static String compressRLE(String input) {
        StringBuilder output = new StringBuilder();
        int count, i = 0;

        while (i < input.length()) {
            char currentChar = input.charAt(i);
            count = 1;
            while (i + 1 < input.length() && input.charAt(i) == input.charAt(i + 1)) {
                count++;
                i++;
            }
            output.append(currentChar).append(count);
            i++;
        }

        return output.toString();
    }

    public static void main(String[] args) {
        String input = "aaabbccccddddeeeeeff";

        long start = System.nanoTime();
        String compressed = compressRLE(input);
        long end = System.nanoTime();

        long duration = end - start;

        System.out.println("String comprimida: " + compressed);
        System.out.println("Tempo de execução (sequencial): " +
                TimeUnit.NANOSECONDS.toMicros(duration) + " microssegundos");
    }
}
