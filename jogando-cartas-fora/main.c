#include <stdio.h>

int main(void) {
  int number_of_cards;

  while(1) {
    scanf("%d", &number_of_cards);
    if(number_of_cards == 0) break;
    int cards[1000000];
    int discardedCards[1000000];
    int first_card_indice = 0, last_card_indice = number_of_cards - 1, discardedCount = 0;

    for (int i = 0; i < number_of_cards; i++) {
      cards[i] = i + 1;
    }

    while (first_card_indice < last_card_indice) {
      discardedCards[discardedCount++] = cards[first_card_indice++];
      cards[++last_card_indice] = cards[first_card_indice++];
    }

    printf("Discarded cards:");
    for (int i = 0; i < discardedCount; i++) {
      printf(" %d", discardedCards[i]);
      if (i < discardedCount - 1) printf(",");
    }
    printf("\nRemaining card: %d\n", cards[first_card_indice]);
  }

  return 0;
}
