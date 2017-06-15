#include "program.h"

TAD_istruct clean(TAD_istruct qs);

gboolean freeArt(ART r1, ART r2, void* null);

ArtTree freeArtTree(ArtTree r, void*null);

gboolean freeRev(REVISION r);

gboolean freeCont(CONT r1, CONT r2, void* null);

Heap freeHeap(Heap r);

char ** freePref(char **r);
