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

    Tessera tesseraScelta = tessere[scelta];

    // Se la tessera scelta è [11|11], è sempre una scelta valida
    if (tesseraScelta.lato1 == 11 && tesseraScelta.lato2 == 11) {
        return scelta;
    }

    if (tesseraScelta.lato1 == 12 && tesseraScelta.lato2 == 21) {
        return scelta;
    }

    // Controlla la validità per le altre tessere
    if (direzione == 0 && latoDisponibileSinistra != -1 &&
        tesseraScelta.lato1 != latoDisponibileSinistra && tesseraScelta.lato2 != latoDisponibileSinistra) {
        printf("Scelta non valida. Riprova.\n");
        return -1;
    }

    if (direzione == 1 && latoDisponibileDestra != -1 &&
        tesseraScelta.lato1 != latoDisponibileDestra && tesseraScelta.lato2 != latoDisponibileDestra) {
        printf("Scelta non valida. Riprova.\n");
        return -1;
    }

    return scelta;
}


int chiediRuotaTessera() {
    int scelta;
    do {
        printf("Vuoi ruotare la tessera? (0: no, 1: si'): ");
        scanf("%d", &scelta);
        if (scelta != 0 && scelta != 1) {
            printf("Errore: inserire solo 0 o 1.\n");
        }
    } while (scelta != 0 && scelta != 1);
    return scelta;
}

void aggiornaPianoDiGioco(Tessera *piano, int lunghezzaPiano) { //funzione richiamata quando 11 11
    for (int i = 0; i < lunghezzaPiano; i++) {
        piano[i].lato1 = (piano[i].lato1 == 6) ? 1 : piano[i].lato1 + 1;
        piano[i].lato2 = (piano[i].lato2 == 6) ? 1 : piano[i].lato2 + 1;
    }
}

void aggiungiTesseraPiano(Tessera *piano, int *lunghezzaPiano, Tessera tessera, int latoAggiunta, int *latoDisponibileSinistra, int *latoDisponibileDestra, int ruotaTessera) {
    int isTesseraSpeciale = (tessera.lato1 == 0 && tessera.lato2 == 0);
    int isPianoSpecialeSinistra = (*lunghezzaPiano > 0 && piano[0].lato1 == 0 && piano[0].lato2 == 0);
    int isPianoSpecialeDestra = (*lunghezzaPiano > 0 && piano[*lunghezzaPiano - 1].lato1 == 0 && piano[*lunghezzaPiano - 1].lato2 == 0);

    if (tessera.lato1 == 11 && tessera.lato2 == 11) {   //codice 11 11 
        aggiornaPianoDiGioco(piano, *lunghezzaPiano);
        tessera.lato1 = tessera.lato2 = (latoAggiunta == 0) ? piano[0].lato1 : piano[*lunghezzaPiano - 1].lato2;
    }
    
    if (tessera.lato1 == 12 && tessera.lato2 == 21) {   //codice 12 21
        // Copia a specchio la tessera adiacente
        if (latoAggiunta == 0 && *lunghezzaPiano > 0) { // Sinistra
            tessera.lato1 = piano[0].lato2;
            tessera.lato2 = piano[0].lato1;
        } else if (latoAggiunta == 1 && *lunghezzaPiano > 0) { // Destra
            tessera.lato1 = piano[*lunghezzaPiano - 1].lato2;
            tessera.lato2 = piano[*lunghezzaPiano - 1].lato1;
        }
    }
    if (ruotaTessera) {
        int temp = tessera.lato1;
        tessera.lato1 = tessera.lato2;
        tessera.lato2 = temp;
    }

    if (latoAggiunta == 0) {
        if (!isTesseraSpeciale && !isPianoSpecialeSinistra && *latoDisponibileSinistra != -1 && tessera.lato2 != *latoDisponibileSinistra) {
            int temp = tessera.lato1;
            tessera.lato1 = tessera.lato2;
            tessera.lato2 = temp;
        }

        for (int i = *lunghezzaPiano; i > 0; i--) {
            piano[i] = piano[i - 1];
        }
        piano[0] = tessera;

        *latoDisponibileSinistra = isTesseraSpeciale ? -1 : tessera.lato1;
        if (*lunghezzaPiano == 0) {
            *latoDisponibileDestra = isTesseraSpeciale ? -1 : tessera.lato2;
        }
    } else {
        if (!isTesseraSpeciale && !isPianoSpecialeDestra && *latoDisponibileDestra != -1 && tessera.lato1 != *latoDisponibileDestra) {
            int temp = tessera.lato1;
            tessera.lato1 = tessera.lato2;
            tessera.lato2 = temp;
        }

        piano[*lunghezzaPiano] = tessera;

        *latoDisponibileDestra = isTesseraSpeciale ? -1 : tessera.lato2;
        if (*lunghezzaPiano == 0) {
            *latoDisponibileSinistra = isTesseraSpeciale ? -1 : tessera.lato1;
        }
    }

    (*lunghezzaPiano)++;
}

int ciSonoTessereGiocabili(Tessera *tessere, int n, int latoDisponibileSinistra, int latoDisponibileDestra, int lunghezzaPiano, Tessera *pianoDiGioco) {
    for (int i = 0; i < n; i++) {
        if (tessere[i].utilizzata) continue;

        // La tessera speciale [11|11] è sempre giocabile
        if (tessere[i].lato1 == 11 && tessere[i].lato2 == 11) {
            return 1;
        }
        // Uguale per la 12 21
        if (tessere[i].lato1 == 12 && tessere[i].lato2 == 21) {
            return 1;
        }

        // Verifica se la tessera può essere giocata a sinistra o a destra
        if ((tessere[i].lato1 == latoDisponibileSinistra || tessere[i].lato2 == latoDisponibileSinistra) ||
            (tessere[i].lato1 == latoDisponibileDestra || tessere[i].lato2 == latoDisponibileDestra)) {
            return 1;
        }
    }

    return 0; // Non ci sono tessere giocabili
}

void giocaDomino(Tessera *tessere, int n) {
    int punteggio = 0, scelta, latoAggiunta;
    int latoDisponibileSinistra = -1, latoDisponibileDestra = -1;
    Tessera pianoDiGioco[100];
    int lunghezzaPiano = 0;

    while (1) {
        stampaMano(tessere, n);
        stampaPianoDiGioco(pianoDiGioco, lunghezzaPiano);

        // Controlla se tutte le tessere del giocatore sono state utilizzate
        int tessereRimanenti = 0;
        for (int i = 0; i < n; i++) {
            if (!tessere[i].utilizzata) {
                tessereRimanenti++;
            }
        }

        if (tessereRimanenti == 0) {
            printf("Hai terminato tutte le tue tessere! Gioco terminato.\n");
            break;
        }

         if (lunghezzaPiano > 0 && !ciSonoTessereGiocabili(tessere, n, latoDisponibileSinistra, latoDisponibileDestra, lunghezzaPiano, pianoDiGioco)) {
        printf("Non ci sono piu' mosse disponibili. Gioco terminato.\n");
        break;
    }

        if (lunghezzaPiano == 0) {
            latoAggiunta = 1;
            printf("Posizionando la prima tessera nel piano di gioco...\n");
        } else {
    do {
        printf("Dove vuoi aggiungere la tessera? (0: sinistra, 1: destra): ");
        scanf("%d", &latoAggiunta);
        if (latoAggiunta != 0 && latoAggiunta != 1) {
            printf("Errore: inserire solo 0 o 1.\n");
        }
    } while (latoAggiunta != 0 && latoAggiunta != 1);
}

        scelta = scegliTessera(tessere, n, latoDisponibileSinistra, latoDisponibileDestra, latoAggiunta);

        if (scelta == -1) continue;
        if (scelta == -2) break;

        Tessera tesseraScelta = tessere[scelta];
        tessere[scelta].utilizzata = 1;

        int ruotaTessera = 0;
        if (lunghezzaPiano == 0 || (latoAggiunta == 0 && pianoDiGioco[0].lato1 == 0) || (latoAggiunta == 1 && pianoDiGioco[lunghezzaPiano - 1].lato2 == 0)) {
            ruotaTessera = chiediRuotaTessera();
        }

        printf("Hai giocato: ");
        stampaTessera(tesseraScelta);
        printf("\n");

        punteggio += tesseraScelta.lato1 + tesseraScelta.lato2;

        aggiungiTesseraPiano(pianoDiGioco, &lunghezzaPiano, tesseraScelta, latoAggiunta, &latoDisponibileSinistra, &latoDisponibileDestra, ruotaTessera);

        printf("Punteggio corrente: %d\n", punteggio);
    }

    printf("\nPunteggio finale: %d\n", punteggio);
}


void generaSetTessere(Tessera *set, int *size) {
    int k = 0;
    // Aggiungi la tessera speciale [0|0] e [11|11] e [12|21]
    set[k++] = (Tessera){0, 0, 0};
    set[k++] = (Tessera){11, 11, 0};
    set[k++] = (Tessera){12, 21, 0};


    for (int i = 1; i <= 6; i++) {
        for (int j = i; j <= 6; j++) {
            set[k++] = (Tessera){i, j, 0};
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

int main() {
    srand(time(NULL));
    Tessera setTessere[28];
    int setSize;

    generaSetTessere(setTessere, &setSize);

    int nGiocatore = generaNumeroCasuale(6); // Numero di tessere per il giocatore

    Tessera tessereGiocatore[nGiocatore];
    assegnaTessereGiocatore(tessereGiocatore, nGiocatore, setTessere, setSize);

    giocaDomino(tessereGiocatore, nGiocatore);

    return 0;
}