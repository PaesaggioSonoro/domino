#include <stdio.h>
#include <stdlib.h>
#include <time.h>



typedef struct {
    int lato1;
    int lato2;
    int utilizzata;
} Tessera;

void stampaTessera(Tessera t) {
    printf("[%d|%d] ", t.lato1, t.lato2);
}

void stampaMano(Tessera *tessere, int n) {
    printf("\n");
    printf("Le tue tessere:\n");
    for (int i = 0; i < n; i++) {
        if (!tessere[i].utilizzata) {
            printf("%d: ", i);
            stampaTessera(tessere[i]);
        }
    }
    printf("\n");
}

void stampaPianoDiGioco(Tessera *piano, int lunghezzaPiano) {
    printf("Piano di gioco: ");
    for (int i = 0; i < lunghezzaPiano; i++) {
        stampaTessera(piano[i]);
    }
    printf("\n");
}

int scegliTessera(Tessera *tessere, int n, int latoDisponibileSinistra, int latoDisponibileDestra, int direzione) {
    int scelta;
    printf("Scegli una tessera (numero) o -1 per terminare: ");
    scanf("%d", &scelta);

    if (scelta == -1) {
        return -2; // Termina il gioco
    }

    if (scelta < 0 || scelta >= n || tessere[scelta].utilizzata) {
        printf("Scelta non valida. Riprova.\n");
        return -1;
    }

    // Verifica la validità della tessera per tessera [0|0]
    if (tessere[scelta].lato1 == 0 && tessere[scelta].lato2 == 0) {
        return scelta; // La tessera [0|0] è sempre valida
    }

    // Verifica la validità della tessera in base alla direzione di aggiunta
    if (direzione == 0 && latoDisponibileSinistra != -1 &&
        tessere[scelta].lato1 != latoDisponibileSinistra && tessere[scelta].lato2 != latoDisponibileSinistra) {
        printf("Scelta non valida. Riprova.\n");
        return -1;
    }

    if (direzione == 1 && latoDisponibileDestra != -1 &&
        tessere[scelta].lato1 != latoDisponibileDestra && tessere[scelta].lato2 != latoDisponibileDestra) {
        printf("Scelta non valida. Riprova.\n");
        return -1;
    }

    return scelta;
}


void ruotaTesseraSeNecessario(Tessera *tessera, int latoDisponibile) {
    if (latoDisponibile != -1 && tessera->lato1 != latoDisponibile && tessera->lato2 == latoDisponibile) {
        int temp = tessera->lato1;
        tessera->lato1 = tessera->lato2;
        tessera->lato2 = temp;
    }
}
void aggiungiTesseraPiano(Tessera *piano, int *lunghezzaPiano, Tessera tessera, int latoAggiunta, int *latoDisponibileSinistra, int *latoDisponibileDestra);
int ciSonoTessereGiocabili(Tessera *tessere, int n, int latoDisponibileSinistra, int latoDisponibileDestra);

void giocaDomino(Tessera *tessere, int n) {
    int punteggio = 0, scelta, latoAggiunta;
    int latoDisponibileSinistra = -1, latoDisponibileDestra = -1;
    Tessera pianoDiGioco[100];
    int lunghezzaPiano = 0;

while (1) {
        stampaMano(tessere, n);

        // Controllo se è la prima tessera da posizionare
        if (lunghezzaPiano == 0) {
            latoAggiunta = 1; // Scegli automaticamente di aggiungere a destra
            printf("Posizionando la prima tessera nel piano di gioco...\n");
        } else {
            printf("Dove vuoi aggiungere la tessera? (0: sinistra, 1: destra): ");
            scanf("%d", &latoAggiunta);
        }

        scelta = scegliTessera(tessere, n, latoDisponibileSinistra, latoDisponibileDestra, latoAggiunta);

        if (scelta == -1) continue; // Scelta non valida, riprova
        if (scelta == -2) break; // Termina il gioco

       
        Tessera tesseraScelta = tessere[scelta];
        tessere[scelta].utilizzata = 1;

        printf("Hai giocato: ");
        stampaTessera(tesseraScelta);
        printf("\n");

        punteggio += tesseraScelta.lato1 + tesseraScelta.lato2;

        aggiungiTesseraPiano(pianoDiGioco, &lunghezzaPiano, tesseraScelta, latoAggiunta, &latoDisponibileSinistra, &latoDisponibileDestra);

        stampaPianoDiGioco(pianoDiGioco, lunghezzaPiano);
        printf("Punteggio corrente: %d\n", punteggio);

         if (!ciSonoTessereGiocabili(tessere, n, latoDisponibileSinistra, latoDisponibileDestra)) {
            printf("Gioco finito: nessuna tessera giocabile.\n");
            break; // Termina il gioco
        }
    }

    printf("\nPunteggio finale: %d\n", punteggio);
}

void generaSetTessere(Tessera *set, int *size) {
    set[0].lato1 = 0;
    set[0].lato2 = 0;
    set[0].utilizzata = 0;
    int k = 1; // Inizia da 1 per lasciare spazio alla tessera [0|0]
    for (int i = 1; i <= 6; i++) {
        for (int j = i; j <= 6; j++) {
            set[k].lato1 = i;
            set[k].lato2 = j;
            set[k].utilizzata = 0;
            k++;
        }
    }
    *size = k;
}


void assegnaTessereGiocatore(Tessera *giocatore, int nGiocatore, Tessera *set, int setSize) {
    srand(time(NULL)); // Inizializza il generatore di numeri casuali
    for (int i = 0; i < nGiocatore; i++) {
        int indiceCasuale = rand() % setSize;
        giocatore[i] = set[indiceCasuale];
    }
}

int generaNumeroCasuale(int N) {
    srand(time(NULL));
    int numeroCasuale = rand() % (N - 2) + 3;
    return numeroCasuale;
}

void aggiungiTesseraPiano(Tessera *piano, int *lunghezzaPiano, Tessera tessera, int latoAggiunta, int *latoDisponibileSinistra, int *latoDisponibileDestra) {
    // Se la tessera aggiunta è [0|0], imposta i lati disponibili per accettare qualsiasi tessera
    if (tessera.lato1 == 0 && tessera.lato2 == 0) {
        *latoDisponibileSinistra = -1;
        *latoDisponibileDestra = -1;
    } else {
        // Se la tessera non è [0|0], procedi con le regole normali
        if (latoAggiunta == 0) { // Aggiunta a sinistra
            if (*latoDisponibileSinistra != -1 && tessera.lato2 != *latoDisponibileSinistra) {
                // Girare la tessera se necessario
                int temp = tessera.lato1;
                tessera.lato1 = tessera.lato2;
                tessera.lato2 = temp;
            }
            *latoDisponibileSinistra = tessera.lato1;
        } else { // Aggiunta a destra
            if (*latoDisponibileDestra != -1 && tessera.lato1 != *latoDisponibileDestra) {
                // Girare la tessera se necessario
                int temp = tessera.lato1;
                tessera.lato1 = tessera.lato2;
                tessera.lato2 = temp;
            }
            *latoDisponibileDestra = tessera.lato2;
        }
    }

    // Aggiungere la tessera al piano di gioco
    if (latoAggiunta == 0) { // Aggiunta a sinistra
        for (int i = *lunghezzaPiano; i > 0; i--) {
            piano[i] = piano[i - 1];
        }
        piano[0] = tessera;
    } else { // Aggiunta a destra
        piano[*lunghezzaPiano] = tessera;
    }

    (*lunghezzaPiano)++;
}



int ciSonoTessereGiocabili(Tessera *tessere, int n, int latoDisponibileSinistra, int latoDisponibileDestra) {
    // Se entrambi i lati sono -1, significa che la tessera [0|0] è stata giocata e tutte le tessere sono giocabili
    if (latoDisponibileSinistra == -1 && latoDisponibileDestra == -1) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        if (!tessere[i].utilizzata &&
            (tessere[i].lato1 == latoDisponibileSinistra ||
             tessere[i].lato2 == latoDisponibileSinistra ||
             tessere[i].lato1 == latoDisponibileDestra ||
             tessere[i].lato2 == latoDisponibileDestra)) {
            return 1; // Ci sono ancora tessere giocabili
        }
    }
    return 0; // Nessuna tessera giocabile
}


int main() {
    srand(time(NULL)); // Inizializza il generatore di numeri casuali una volta

    Tessera setTessere[28];
    int setSize;
    generaSetTessere(setTessere, &setSize);

    int nGiocatore = generaNumeroCasuale(10); // Numero di tessere per il giocatore
   
    Tessera tessereGiocatore[nGiocatore];
    assegnaTessereGiocatore(tessereGiocatore, nGiocatore, setTessere, setSize);

    giocaDomino(tessereGiocatore, nGiocatore);
    return 0;
}