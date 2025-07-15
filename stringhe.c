#include <stdio.h>
#include <string.h>
#define MAX_LENGTH 6

/*  
 * Funzione per pulire il buffer di input
 * Rimuove i caratteri in eccesso fino a newline o EOF
 * Utilizzata per evitare problemi di overflow del buffer
 * quando si legge una stringa con fgets o scanf
 */
void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

/*
 * Funzione per leggere una stringa con messaggio personalizzato 
 * restituisce il numero di caratteri letti  (-1 in caso di errore)
 * Il buffer deve essere allocato con una dimensione sufficiente
 * per contenere la stringa e il carattere di terminazione null.
 */
ssize_t read_string(char *msg, char *buffer, int max_length) {
    printf("%s", msg);
    size_t len = 0;
    if (fgets(buffer, max_length, stdin) != NULL) {
        // Rimuovo il carattere di nuova linea se presente
        len = strlen(buffer);
       
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[--len] = '\0';
        } else {    
            buffer[max_length - 1] = '\0'; // Trunca la stringa
            len = max_length - 1; // Aggiorna la lunghezza
            clear_buffer(); // Pulisce il buffer se la stringa è più lunga di max_length

        }
    } else{
        // Errore nella lettura
        buffer[0] = '\0'; // Imposto la stringa vuota
        return -1;
    }
    // Restituisco il numero di caratteri letti
    return len;
}

/**
 * Funzione per leggere una riga di lunghezza variabile.
 * Alloca dinamicamente il buffer.
 * Restituisce il numero di caratteri letti (senza il newline),
 * oppure -1 in caso di errore.
 *
 * L'utente deve poi fare free() sulla stringa ritornata.
 */
ssize_t read_string_dynamic(const char *msg, char **out_string) {
    char *line = NULL;
    size_t bufsize = 0;
    
    printf("%s", msg);
    fflush(stdout);

    ssize_t nread = getline(&line, &bufsize, stdin);
    if (nread == -1) {
        // Errore o EOF
        *out_string = NULL;
        return -1;
    }

    // Rimuove newline
    if (nread > 0 && line[nread - 1] == '\n') {
        line[nread - 1] = '\0';
        nread--;
    }

    *out_string = line;
    return nread;
}


int main() {
    char str[MAX_LENGTH];
    ssize_t len;
    // Chiamata alla funzione per leggere una stringa
    len = read_string("Inserisci una stringa: ", str, MAX_LENGTH);
    printf("Hai inserito: %s  - e ne sono felice\n", str);
    if (len >= 0) {
        printf("Hai inserito (%zd caratteri): %s\n", len, str);
       
    } else {
        printf("Errore nella lettura.\n");
    }

    char *input = NULL;
    len = read_string_dynamic("Inserisci una stringa: ", &input);

    if (len >= 0) {
        printf("Hai inserito (%zd caratteri): %s\n", len, input);
        //free(input);
    } else {
        printf("Errore nella lettura.\n");
    }
    if (input) {
        free(input); // Libero la memoria allocata dinamicamente
    }
    return 0;
}
