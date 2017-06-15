#ifndef PARSE_H_
#define PARSE_H_
#include "program.h"
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>

xmlArray parseMult(xmlArray array, int N, char *filename[N]);

xmlDocPtr parse(char *filename) ;

#endif
