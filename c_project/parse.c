#include "parse.h"
#include "00-init.h"
#include <libxml2/libxml/parser.h>
#include <libxml2/libxml/tree.h>

/**
 * parse:
 *  @filename: a filename or an URL
 *
 * Parse the resource and free the resulting tree
 */
xmlDocPtr parse(char *filename)
{
    xmlDocPtr doc; /* the resulting document tree */

    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    doc = xmlReadFile(filename, NULL, 0);
    if (doc == NULL)
        fprintf(stderr, "Failed to parse %s\n", filename), exit(-1);

    /*xmlFreeDoc(doc);
      printf("parse succeded!\n");//JUST FOR TESTING
      */

    /*
     * Cleanup function for the XML library.
     */
    xmlCleanupParser();
    /*
     * this is to debug memory for regression tests
     */
    xmlMemoryDump();

    return doc;
}

/**\ Faz parse de multiplos ficheiros através da xmlLib para um array da Glib.
  @param array    Array onde será guardado as árvores do parsing.
  @param N        Número de ficheiros a carregar.
  @param filename Nomes dos ficheiros a carregar.
  @return         Array de xmlDocPtr.
  */
xmlArray parseMult(xmlArray array, int N, char *filename[N])
{
    int i;

    if(array != NULL) {
        #pragma omp parallel for
        for(i = 0 ; i < N ; i++)
            g_ptr_array_add(array, parse(filename[i]));
        g_ptr_array_set_size (array, N);
    }
    return array;
}
