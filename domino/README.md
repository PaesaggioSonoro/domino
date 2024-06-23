# Domino
## Introduzione
Componenti del gruppo:
- [Francesco Zanus-Fortes](https://moodle.unive.it/user/view.php?id=110996&course=15113)
- [Niccolò Busetto](https://moodle.unive.it/user/view.php?id=110413&course=15112)
- [Luca Colussi](https://moodle.unive.it/user/view.php?id=110176&course=15112)
- [Nicola Alberti](https://moodle.unive.it/user/view.php?id=110412&course=15112)

## Divisione dei ruoli nel gruppo
- Francesco Zanus-Fortes: implementazione della logica di gioco generale e dell'IA, gestione teorica della grafica, makefile, testing e debugging
- Niccolò Busetto: implementazione della grafica high level e delle funzioni di input, testing e debugging
- Luca Colussi e Nicola Alberti: implementazione delle funzioni di inizializzazione e disegno low level, font, immagini e animazioni, testing e debugging

Il progetto è stato realizzato utilizzando la libreria grafica [SDL2](https://www.libsdl.org/) e il compilatore [MinGW](https://www.mingw-w64.org/). In questa versione del gioco è possibile giocare in due modalità:
- **Single Player**: il giocatore piazza le tessere fino a quando sono disponibili combinazioni valide. Non è prevista vittoria o sconfitta e viene comunicato il punteggio finale.
- **With AI**: il giocatore si scontrerà contro il computer fino a quando uno dei due giocatori non potrà piazzare più tessere. Verrà comunicato il vincitore e il punteggio finale.

Il campo di gioco viene sempre visualizzato orizzontalmente e non sono previste tessere in verticale.

## Controlli
Il software non supporta l'utilizzo del mouse per via della complessità nella gestione delle coordinate, viene utilizzata solo la tastiera. I controlli sono i seguenti:
### Menu
- **Freccia su/giù**: navigare tra le opzioni
### Gioco
#### Selezione della carta
- **Freccia destra/sinistra**: navigare tra le carte
- **Invio**: selezionare la carta
#### Piazzamento della carta
- **Freccia destra/sinistra**: navigare tra la posizione a sinistra o a destra rispetto al campo di gioco
- **Freccia su/giù**: ruotare la carta
- **Invio**: piazzare la carta
- **Esc**: tornare indietro

Alla fine di ogni partita sarà possibile tramite il tasto **Invio** tornare al menu principale e effettuarne una nuova.

## Struttura del progetto
Il progetto è stato diviso in più file per una maggiore leggibilità e manutenibilità del codice. La struttura del progetto è la seguente:
- **main.c**: file principale del progetto, effettua le chiamate alle funzioni per l'inizializzazione del gioco (tra cui caricamento di asset esterni) e il game loop.
- **init.c**: contiene le funzioni per l'inizializzazione del gioco, come la creazione della finestra e del renderer, il caricamento delle immagini e l'inizializzazione di SDL.
- **game.c**: contiene le funzioni per la gestione del gioco, come la creazione del campo di gioco, la gestione delle tessere e la logica di gioco. In particolare la funzione `GameLoop` gestisce ogni frame in base allo stato del gioco e agli input ricevuti.
- **draw.c**: contiene le funzioni per la gestione della grafica, come il disegno delle tessere e del campo di gioco. In particolare la funzione `DrawGame` disegna ogni frame in base allo stato del gioco comunicato tramite strutture contenute in `structs.h` aggiornate da parte della funzione `GameLoop`.
- **input.c**: contiene le funzioni per la gestione degli input tramite le apposite API, aggiornando di conseguenza le strutture contenute in `structs.h` che verranno poi utilizzate da `GameLoop`.
- **structs.h**: contiene le strutture dati utilizzate per la comunicazione tra le funzioni, tra cui `Card`, `Game` e `Control`.
- **defs.h**: contiene le definizioni di costanti utilizzate in tutto il progetto, come le dimensioni della finestra e alcune regole del gioco.
- Altri file:
    - **tessera.c**: contiene le funzioni per il rendering delle tessere
    - **font.c**: contiene le funzioni per il rendering del testo

## Algoritmo di IA
L'algoritmo di IA sceglie tra tutte le tessere posizionabili quella che massimizza il punteggio. Il punteggio di una tessera è calcolato come la somma dei punteggi delle combinazioni che la tessera forma con le tessere già posizionate. 

## Compilazione
Il gioco può essere compilato e eseguito solo su piattaforma Windows a causa della complessità nella compilazione
della libreria grafica SDL che al suo interno presenta file binari precompilati per Windows. Per poter gestire la compilazione per 
altri sistemi operativi sarebbe stato necessario gestire separate librerie con file binari precompilati per 
ogni sistema operativo. La libreria inoltre è stata unita a SDL_image e SDL_ttf per poter gestire immagini e testo, tali espansioni
presentano limitate documentazioni rendendo difficile la compilazione per altri sistemi.

## Risorse esterne
- Font: [Arcade Ya](https://www.dafont.com/it/arcade-ya.font) di Gaut Fonts
- Immagini (testo menu): [Arcade Font Writer](https://arcade.photonstorm.com/)
- Librerie: 
    - [Simple DirectMedia Layer](https://www.libsdl.org/)
    - Immagini SDL: [SDL_image](https://www.libsdl.org/projects/SDL_image/)
    - Testo SDL: [SDL_ttf](https://www.libsdl.org/projects/SDL_ttf/)