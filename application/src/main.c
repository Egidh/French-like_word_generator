/*
    Copyright (c) Arnaud BANNIER, Nicolas BODIN and Matthieu LE BERRE.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#include "settings.h"
#include "ngram.h"

#include "graph/graph.h"
#include "graph/traversal.h"

#include "utils/list_int.h"
#include "utils/tree_int.h"
#include "utils/map_ptr.h"

MapPtr *Map_fromDictionnary(char *path)
{
    MapPtr *map = MapPtr_create();

    FILE *file = fopen(path, "r");
    assert(file);

    char buffer[64];
    while (fscanf(file, "%s\n", buffer) == 1)
    {
        MapPtr_insert(map, buffer, NULL);
    }

    return map;
}

int main()
{
    srand(time(NULL));

    int c = 6;
#if 0
    ngramGenerator("../data/word_generator/dictionnary.txt", c);
#endif

    MapPtr *map = Map_fromDictionnary("../data/word_generator/dictionnary.txt");

    char graphPath[64];
    sprintf(graphPath, "../data/word_generator/graph_%d-grams.txt", c);

    Graph *graph = Graph_load(graphPath);
    assert(graph && "Error while loading the graph");

    char ngramPath[64];
    sprintf(ngramPath, "../data/word_generator/%d-grams.txt", c);

    FILE *file = fopen(ngramPath, "r");
    int size = -1, n = -1;
    fscanf(file, "%d %d\n", &n, &size);
    char **symbols = (char **)calloc(size + 2, sizeof(char *));
    for (int i = 0; i < size + 2; i++)
    {
        symbols[i] = (char *)calloc((i > 1) ? n : 8, sizeof(char));
        fscanf(file, "%s\n", symbols[i]);
    }
    fclose(file);

    int prevSize = map->size;
    for (int i = 0; i < 10; i++)
    {
        char *word = generateWord(graph, symbols);
        if (MapPtr_containsKey(map, word))
            i--;
        else
            printf("%s\n", word);
    }

    MapPtr_destroy(map);
    Graph_destroy(graph);

    return EXIT_SUCCESS;
}
