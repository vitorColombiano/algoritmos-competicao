#include <stdio.h>

int main(void) {
  char str[1001];

  while(scanf("%s", str) != EOF) {
    int freq[26] = {0};
    int oddCountImpar = 0;

    //Conta a frequência de cada letra
    for (int i = 0; str[i] != '\0'; i++) {
      freq[str[i] - 'a']++;
    }

    // contar quantas letras tem frequência ímpar
    for (int i=0; i<26; i++) {
      if (freq[i] % 2 != 0) {
        oddCountImpar++;
      }
    }

    int minToAdd = (oddCountImpar > 1) ? (oddCountImpar - 1) : 0;
    printf("%d\n", minToAdd);
  }
  return 0;
}