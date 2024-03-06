#include "structs.h"

Game game;
extern void draw(void);
extern void init(char *);
extern void cleanup(void);
extern TTF_Font *loadFont(char *, int);
extern void delay(unsigned int);
extern void getInput(void);
extern void GameLoop(void);
extern void DistributeCards();


char * getAbsolutePath(char *relativePath);