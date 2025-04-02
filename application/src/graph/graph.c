/*
    Copyright (c) Arnaud BANNIER, Nicolas BODIN and Matthieu LE BERRE.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#include "graph.h"

Graph *Graph_create(int size)
{
    Graph *graph = (Graph *)calloc(1, sizeof(Graph));
    graph->nodeList = (GraphNode *)calloc(size, sizeof(GraphNode));
    graph->size = size;

    return graph;
}

void Graph_destroy(Graph *graph)
{
    if (!graph)
        return;

    for (int i = 0; i < graph->size; i++)
    {
        free(graph->nodeList[i].arcList);
    }

    free(graph->nodeList);
    free(graph);
}

void Graph_setArc(Graph *graph, int u, int v, float weight)
{
    assert(graph && "The Graph must be created");
    assert(0 <= u && u < graph->size && "The node ID is invalid");
    assert(0 <= v && v < graph->size && "The node ID is invalid");

    ArcList *prev = graph->nodeList[u].arcList;

    if (!prev)
    {
        prev = (ArcList *)calloc(1, sizeof(ArcList));
        prev->target = v;
        prev->weight = weight;

        graph->nodeList[u].arcList = prev;
        graph->nodeList[u].arcCount++;
    }
    else
    {
        for (ArcList *arc = Graph_getArcList(graph, u); arc != NULL; arc = arc->next)
        {
            if (arc->target == v)
            {
                arc->weight = weight;
                return;
            }

            else if (arc->target > v)
            {
                ArcList *newArc = (ArcList *)calloc(1, sizeof(ArcList));
                newArc->target = v;
                newArc->weight = weight;
                newArc->next = arc;

                if (arc != graph->nodeList[u].arcList)
                    prev->next = newArc;
                else
                    graph->nodeList[u].arcList = newArc;

                graph->nodeList[u].arcCount++;
                return;
            }

            prev = arc;
        }

        ArcList *newArc = (ArcList *)calloc(1, sizeof(ArcList));
        newArc->target = v;
        newArc->weight = weight;
        newArc->next = NULL;

        if (prev)
            prev->next = newArc;
        else
            graph->nodeList[u].arcList = newArc;

        graph->nodeList[u].arcCount++;
        return;
    }
}

void Graph_removeArc(Graph *graph, int u, int v)
{
    assert(graph && "The Graph must be created");
    assert(0 <= u && u < graph->size && "The node ID is invalid");
    assert(0 <= v && v < graph->size && "The node ID is invalid");

    ArcList *current = graph->nodeList[u].arcList;
    if (!current)
        return;
    if (current->target == v)
    {
        ArcList *next = current->next;
        free(current);
        graph->nodeList[u].arcCount--;
        graph->nodeList[u].arcList = next;
    }
    else
    {
        while (current->next)
        {
            if (current->next->target == v)
            {
                ArcList *next = current->next->next;
                free(current->next);
                graph->nodeList[u].arcCount--;
                current->next = next;
                break;
            }
            current = current->next;
        }
    }
}

float *Graph_getArc(Graph *graph, int u, int v)
{
    assert(graph && "The Graph must be created");
    assert(0 <= u && u < graph->size && "The node ID is invalid");
    assert(0 <= v && v < graph->size && "The node ID is invalid");

    ArcList *current = graph->nodeList[u].arcList;
    while (current)
    {
        if (current->target == v)
            return &current->weight;
        current = current->next;
    }

    return NULL;
}

Graph *Graph_load(char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        assert(false && "The file name is incorrect");
        return NULL;
    }

    Graph *newGraph = (Graph *)calloc(1, sizeof(Graph));
    int arcCount;
    fscanf(file, "%d %d\n", &newGraph->size, &arcCount);

    int prevNode = -1;
    if (newGraph->size)
        newGraph->nodeList = (GraphNode *)calloc(newGraph->size, sizeof(GraphNode));

    for (int i = 0; i < arcCount; i++)
    {
        int currNode, targetNode;
        float currWeight;
        fscanf(file, "%d %d %f\n", &currNode, &targetNode, &currWeight);
        newGraph->nodeList[currNode].arcCount++;

        ArcList *iter = newGraph->nodeList[currNode].arcList;
        if (!iter)
        {
            newGraph->nodeList[currNode].arcList = (ArcList *)calloc(1, sizeof(ArcList));
            iter = newGraph->nodeList[currNode].arcList;
            iter->target = targetNode;
            iter->weight = currWeight;
        }
        else
        {
            while (iter->next)
            {
                iter = iter->next;
            }
            iter->next = (ArcList *)calloc(1, sizeof(ArcList));
            iter = iter->next;
            iter->target = targetNode;
            iter->weight = currWeight;
        }
    }

    fclose(file);

    return newGraph;
}

void Graph_print(Graph *graph, char **ngrams)
{
    assert(graph && "The Graph must be created");

    // TODO

    // Astuce :
    // Pour parcourir tous les arcs sortant d'un noeud currID
    // Vous pouvez utiliser la boucle suivante :

    printf("Nombre de noeuds : %d\n", graph->size);
    int count = 0;
    for (int i = 0; i < graph->size; i++)
    {
        // printf("Noeud %d :\n", i);
        for (ArcList *arc = Graph_getArcList(graph, i);
             arc != NULL; arc = arc->next)
        {
            int target = arc->target;
            float weight = arc->weight;

            printf("\t%3d %3d %.2f", i, target, weight);
            printf(" %s %s\n", ngrams[i], ngrams[target]);
            count++;
        }
    }
    printf("Arc count : %d\n", count);
}
