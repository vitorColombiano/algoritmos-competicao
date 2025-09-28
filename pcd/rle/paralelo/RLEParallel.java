package pcd.rle.paralelo;
import java.util.*;
import java.util.stream.*;

public class RLEParallel {
  public static String compressRLE(String input) {
    StringBuilder output = new StringBuilder();
    int i = 0;
    while (i < input.length()) {
      char c = input.charAt(i);
      int count = 1;
      while (i + 1 < input.length() && input.charAt(i + 1) == c) {
        count++;
        i++;
      }
      output.append(c).append(count);
      i++;
    }
    return output.toString();
  }

  // Versão paralela dividindo a string em blocos
  public static String compressRLEParallel(String input, int numChunks) {
    int len = input.length();
    int chunkSize = (len + numChunks - 1) / numChunks;

    List<String> parts = IntStream.range(0, numChunks).parallel()
      .mapToObj(chunk -> {
        int start = chunk * chunkSize;
        int end = Math.min(start + chunkSize, len);
        if (start >= end) return "";
        return compressRLE(input.substring(start, end));
      }).collect(Collectors.toList());

    return String.join("", parts);
  }

  public static void main(String[] args) {
    String input = "aaabbccccddddeeeeeff";

    long startSeq = System.nanoTime();
    String outputSeq = compressRLE(input);
    long endSeq = System.nanoTime();
    System.out.println("Sequencial: " + outputSeq);
    System.out.println("Tempo seq: " + (endSeq - startSeq) / 1e6 + " ms");

    long startPar = System.nanoTime();
    String outputPar = compressRLEParallel(input, 4);
    long endPar = System.nanoTime();
    System.out.println("Paralelo: " + outputPar);
    System.out.println("Tempo par: " + (endPar - startPar) / 1e6 + " ms");
  }
}
