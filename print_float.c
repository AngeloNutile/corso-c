/* print_float.c */
/* Scopo didattico:
   1) Stampare un numero float nella sua rappresentazione binaria (IEEE 754)
   2) Mostrare come si può accedere alla rappresentazione interna di un dato in C
*/

#include <stdio.h>
#include <stdint.h>
/*
 * Funzione per stampare un numero senza segno (uint32_t) in binario.
 * Parametri:
 * - numero: il valore da stampare
 * - bits: numero di bit da visualizzare (se 0, viene usata la dimensione standard: 32 bit)
 */
void print_bits(uint32_t numero, int bits) {
    if (bits == 0) bits = sizeof(uint32_t)*8; // comportamento standard
    // stampiamo dalla cifra più significativa
    for (int i = bits - 1; i >= 0; i--) {
        // facciamo & tra 1 (costante senza segno) e la cifra 
        printf("%c", (numero & (1U << i)) ? '1' : '0');
    }
}

int main(void){
     // Utilizziamo una union per accedere allo stesso valore come float o come uint32_t
    union {
        float f;        // numero float (32 bit, formato IEEE 754)
        uint32_t i;     // stessa area di memoria interpretata come intero senza segno
    } u;

    float x;  // il numero da analizzare
    printf("** Rappresentazione interna float IEEE 754 **\n");
    printf("Utilizzo della union con float (%lu bit) e uint32_t (%lu bit)\n\n", sizeof(float), sizeof(uint32_t));
   
    while(1){
        printf("Immetti un float (0 per terminare): ");
        int esito = scanf("%f", &x);
        while (getchar() != '\n');  // ← pulizia buffer SEMPRE

        if (esito != 1) {
            printf("Input non valido. Riprova.\n");
            continue;  // ripeti il ciclo
        }

        if (x == 0) break; // esce dal ciclo e termina
        
        u.f = x; // assegno il valore alla union e quindi sia a f che a i (stessa dimensione)
        printf("\tFloat %f IEEE 754: %X in binario: ", u.f, u.i);
        print_bits(u.i,0);
         
        uint32_t sign = (u.i >> 31) & 0x1;
        uint32_t exponent = (u.i >> 23) & 0xFF;
        uint32_t mantissa = u.i & 0x7FFFFF;

        printf("\n\tSegno (1 bit): ");
        print_bits(sign, 1);
    
        printf("\n\tEsponente (8 bit): ");
        print_bits(exponent, 8);
        printf(" (decimale: %u, normalizzato: %d)", exponent, (int)exponent - 127);


        printf("\n\tMantissa (23 bit): ");
        print_bits(mantissa, 23);
        printf("\n");
    
    };
     
             
    printf("Bye\n");
    return 0;
}