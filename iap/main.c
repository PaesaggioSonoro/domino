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

    // Verifica se la tessera scelta o il piano di gioco hanno la tessera speciale
    int isTesseraSpeciale = (tesseraScelta.lato1 == 0 && tesseraScelta.lato2 == 0);
    int isPianoSpecialeSinistra = (latoDisponibileSinistra == 0);
    int isPianoSpecialeDestra = (latoDisponibileDestra == 0);

    if (!isTesseraSpeciale && !isPianoSpecialeSinistra && !isPianoSpecialeDestra) {
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
int ciSonoTessereGiocabili(Tessera *tessere, int n, int latoDisponibileSinistra, int latoDisponibileDestra, int lunghezzaPiano, Tessera *pianoDiGioco);


void giocaDomino(Tessera *tessere, int n) {
    int punteggio = 0, scelta, latoAggiunta;
    int latoDisponibileSinistra = -1, latoDisponibileDestra = -1;
    Tessera pianoDiGioco[100];
    int lunghezzaPiano = 0;

    while (1) {
        stampaMano(tessere, n);
        stampaPianoDiGioco(pianoDiGioco, lunghezzaPiano);

        // Se il piano di gioco è vuoto, salta il controllo delle mosse disponibili
        if (lunghezzaPiano > 0 && !ciSonoTessereGiocabili(tessere, n, latoDisponibileSinistra, latoDisponibileDestra, lunghezzaPiano, pianoDiGioco)) {
            printf("Non ci sono più mosse disponibili. Gioco terminato.\n");
            break;
        }

        if (lunghezzaPiano == 0) {
            latoAggiunta = 1; // Scegli automaticamente di aggiungere a destra per la prima tessera
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

        printf("Punteggio corrente: %d\n", punteggio);
    }

    printf("\nPunteggio finale: %d\n", punteggio);
}


void generaSetTessere(Tessera *set, int *size) {
    int k = 0;
    // Aggiungi la tessera speciale [0|0]
    set[k].lato1 = 0;
    set[k].lato2 = 0;
    set[k].utilizzata = 0;
    k++;

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
    int isTesseraSpeciale = (tessera.lato1 == 0 && tessera.lato2 == 0);
    int isPianoSpecialeSinistra = (*lunghezzaPiano > 0 && piano[0].lato1 == 0 && piano[0].lato2 == 0);
    int isPianoSpecialeDestra = (*lunghezzaPiano > 0 && piano[*lunghezzaPiano - 1].lato1 == 0 && piano[*lunghezzaPiano - 1].lato2 == 0);

    // Controllo se la tessera richiede la rotazione
    int ruotaTessera = 0;
    if (!isTesseraSpeciale && !isPianoSpecialeSinistra && *latoDisponibileSinistra != -1 && tessera.lato2 != *latoDisponibileSinistra) {
        ruotaTessera = chiediRuotaTessera();
    }

    // Ruota la tessera se richiesto
    if (ruotaTessera) {
        int temp = tessera.lato1;
        tessera.lato1 = tessera.lato2;
        tessera.lato2 = temp;
    }

    // Aggiunta a sinistra
    if (latoAggiunta == 0) {
        if (!isTesseraSpeciale && !isPianoSpecialeSinistra && *latoDisponibileSinistra != -1 && tessera.lato2 != *latoDisponibileSinistra) {
            int temp = tessera.lato1;
            tessera.lato1 = tessera.lato2;
            tessera.lato2 = temp;
        }

        // Sposta le tessere esistenti a destra e inserisce la nuova a sinistra
        for (int i = *lunghezzaPiano; i > 0; i--) {
            piano[i] = piano[i - 1];
        }
        piano[0] = tessera;

        // Aggiorna il lato disponibile sinistro
        *latoDisponibileSinistra = isTesseraSpeciale ? -1 : tessera.lato1;
        if (*lunghezzaPiano == 0) {
            *latoDisponibileDestra = isTesseraSpeciale ? -1 : tessera.lato2;
        }
    } else { // Aggiunta a destra
        if (!isTesseraSpeciale && !isPianoSpecialeDestra && *latoDisponibileDestra != -1 && tessera.lato1 != *latoDisponibileDestra) {
            int temp = tessera.lato1;
            tessera.lato1 = tessera.lato2;
            tessera.lato2 = temp;
        }

        // Aggiunge la tessera al lato destro del piano
        piano[*lunghezzaPiano] = tessera;

        // Aggiorna il lato disponibile destro
        *latoDisponibileDestra = isTesseraSpeciale ? -1 : tessera.lato2;
        if (*lunghezzaPiano == 0) {
            *latoDisponibileSinistra = isTesseraSpeciale ? -1 : tessera.lato1;
        }
    }

    // Incrementa la lunghezza del piano di gioco
    (*lunghezzaPiano)++;
}


int ciSonoTessereGiocabili(Tessera *tessere, int n, int latoDisponibileSinistra, int latoDisponibileDestra, int lunghezzaPiano, Tessera *pianoDiGioco) {
    int tesseraSpecialeInMano = 0;
    int tesseraSpecialeUltimaGiocata = 0;

    // Controlla se l'ultima tessera giocata è la [0|0]
    if (lunghezzaPiano > 0 && pianoDiGioco[lunghezzaPiano - 1].lato1 == 0 && pianoDiGioco[lunghezzaPiano - 1].lato2 == 0) {
        tesseraSpecialeUltimaGiocata = 1;
    }

    for (int i = 0; i < n; i++) {
        if (tessere[i].utilizzata) continue;

        // Controlla se la tessera speciale [0|0] è ancora in mano
        if (tessere[i].lato1 == 0 && tessere[i].lato2 == 0) {
            tesseraSpecialeInMano = 1;
            break;
        }

        if (tessere[i].lato1 == latoDisponibileSinistra ||
            tessere[i].lato2 == latoDisponibileSinistra ||
            tessere[i].lato1 == latoDisponibileDestra ||
            tessere[i].lato2 == latoDisponibileDestra) {
            return 1; // Ci sono ancora tessere giocabili
        }
    }

    return tesseraSpecialeInMano || tesseraSpecialeUltimaGiocata; // Restituisce 1 se si verifica una delle condizioni
}

int chiediRuotaTessera() {
    int scelta;
    printf("Vuoi ruotare la tessera? (0: no, 1: sì): ");
    scanf("%d", &scelta);
    return scelta;
}


int main() {
    srand(time(NULL)); // Inizializza il generatore di numeri casuali una volta

    Tessera setTessere[28];
    int setSize;
    generaSetTessere(setTessere, &setSize);

    int nGiocatore = generaNumeroCasuale(6); // Numero di tessere per il giocatore
   
    Tessera tessereGiocatore[nGiocatore];
    assegnaTessereGiocatore(tessereGiocatore, nGiocatore, setTessere, setSize);

    giocaDomino(tessereGiocatore, nGiocatore);
    return 0;
}