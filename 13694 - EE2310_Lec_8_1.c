#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char suit;
    char face;
} card_t;
/*
 * face's values are 'A', '2',..., 'T', 'J', 'Q', 'K',
 * in which 'T' stands for 10.
 * suit's values are 'S', 'H', 'D', 'C'
 */

void input_card_t(card_t *ptr_card1){
	scanf("%c%c\n",&ptr_card1->suit,&ptr_card1->face);
}
void output_card_t(card_t *ptr_card1){
	if(ptr_card1->face=='T') printf("%c10", ptr_card1->suit);
  else printf("%c%c",ptr_card1->suit,ptr_card1->face);    
}

int main(){
    card_t card_arr[10];
    for(int i=0; i<10; ++i){
        input_card_t(card_arr + i);
    }
    
    for(int i=0; i<9; ++i){
        output_card_t(card_arr + i);
        printf(" ");
    }
    output_card_t(card_arr + 9);
    printf("\n");

    
    
    return 0;
}

