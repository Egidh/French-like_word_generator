#include "ngram.h"

int randomInt(float *p, int n)
{
    float u = rand() / (float)RAND_MAX;
    float s = 0;

    int i;
    for (i = 0; i < n; i++)
    {
        s += p[i];
        if (u < s)
            break;
    }

    return i;
}

char *generateWord(Graph *graph, char **symbols)
{
    int i = 0, index = 0;
    int position = 0;
    char *word = (char *)calloc(64, sizeof(char));

    while (index != 1)
    {
        int n = graph->nodeList[index].arcCount;
        float *p = (float *)calloc(n, sizeof(float));
        ArcList **arcTab = (ArcList **)calloc(n, sizeof(ArcList *));

        int j = 0;
        for (ArcList *arc = Graph_getArcList(graph, index); arc != NULL; arc = arc->next)
        {
            p[j] = arc->weight;
            arcTab[j] = arc;
            j++;
        }

        i = randomInt(p, n);
        index = arcTab[i]->target;

        free(p);

        if (index != 1)
            strcpy(&word[position++], symbols[index]);
    }

    return word;
}

void ngramGenerator(char *path, int n)
{
    FILE *dictionary = fopen(path, "r");
    assert(dictionary && "ERROR while loading dictionary");

    MapPtr *map = MapPtr_create();

    char *buffer = (char *)calloc(64, sizeof(char));
    while (fscanf(dictionary, "%s\n", buffer) == 1)
    {
        int len = strlen(buffer);
        if (len < n)
            continue;

        for (int i = 0; i <= len - n; i++)
        {
            char *key = (char *)calloc(n, sizeof(char));
            strncpy(key, &buffer[i], n);
            MapPtr_insert(map, key, NULL);
        }
    }

    char **ngramTab = (char **)calloc(map->size + 2, sizeof(char *));

    MapPtrIter *iter = MapPtrIter_create(map);
    Graph *graph = Graph_create(map->size + 2);

    char ngramPath[64];
    sprintf(ngramPath, "../data/word_generator/%d-grams.txt", n);

    FILE *file = fopen(ngramPath, "w");
    assert(file && "ERROR while creating n-gram file");

    fprintf(file, "%d %d\n%s\n%s\n", n, graph->size, "_START_", "__END__");

    int i = 2;
    while (MapPtrIter_isValid(iter))
    {
        ngramTab[i] = (char *)calloc(n, sizeof(char));
        char *key = MapPtrIter_getKey(iter);
        strncpy(ngramTab[i], key, n);

        int *value = (int *)calloc(1, sizeof(int));
        *value = i;

        MapPtr_insert(map, key, value);
        // int *test = MapPtr_get(map, key); //debug

        fprintf(file, "%s\n", ngramTab[i]);

        MapPtrIter_next(iter);
        i++;
    }

    fclose(file);
    file = NULL;

    rewind(dictionary);
    int arcCount = 0;

    while (fscanf(dictionary, "%s\n", buffer) == 1)
    {
        int len = strlen(buffer);
        if (len < n)
            continue;

        char *key = (char *)calloc(n, sizeof(char));
        strncpy(key, buffer, n);
        int *target = (int *)MapPtr_get(map, key);

        float *weight = Graph_getArc(graph, 0, *target);
        if (!weight)
            arcCount++;

        Graph_setArc(graph, 0, *target, (weight) ? *(weight) + 1 : 1);

        char *next = (char *)calloc(n, sizeof(char));
        for (int i = 0; i < len - n; i++)
        {
            strncpy(key, &buffer[i], n);
            int *actual = (int *)MapPtr_get(map, key);

            strncpy(next, &buffer[i + 1], n);

            target = (int *)MapPtr_get(map, next);

            weight = Graph_getArc(graph, *actual, *target);
            if (!weight)
                arcCount++;

            Graph_setArc(graph, *actual, *target, (weight) ? *(weight) + 1 : 1);
        }

        strncpy(key, &buffer[len - n], n);
        target = (int *)MapPtr_get(map, key);

        weight = Graph_getArc(graph, *target, 1);
        if(!weight)
            arcCount++;

        Graph_setArc(graph, *target, 1, (weight) ? *(weight) + 1 : 1);
        //Graph_print(graph, ngramTab);

        free(key);
        free(next);
    }
    fclose(dictionary);
    dictionary = NULL;

    char graphPath[64];
    sprintf(graphPath, "../data/word_generator/graph_%d-grams.txt", n);

    file = fopen(graphPath, "w");
    assert(file && "ERROR while creating graph file");

    fprintf(file, "%d %d\n", graph->size, arcCount);
    for (int i = 0; i < graph->size; i++)
    {
        int totalWeight = 0;
        for (ArcList *arc = Graph_getArcList(graph, i); arc != NULL; arc = arc->next)
        {
            totalWeight += arc->weight;
        }
        for (ArcList *arc = Graph_getArcList(graph, i); arc != NULL; arc = arc->next)
        {
            arc->weight /= (float)totalWeight;
            fprintf(file, "%d %d %f\n", i, arc->target, arc->weight);
        }
    }

    fclose(file);
    file = NULL;
}