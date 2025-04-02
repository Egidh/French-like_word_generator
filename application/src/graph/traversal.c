/*
    Copyright (c) Arnaud BANNIER, Nicolas BODIN and Matthieu LE BERRE.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#include "traversal.h"
#include "utils/list_int.h"

/// @brief Sous-fonction de Graph_dfsPrint() pour les appels r�cursifs.
/// @param graph le graphe.
/// @param currID l'identifiant du noeud courant.
/// @param explored tableau de bool�ens indiquant pour chaque identifiant de
/// noeud s'il a �t� marqu� comme ateint.
static void Graph_dfsPrintRec(Graph *graph, int currID, bool *explored);

/// @brief Sous-fonction de Graph_spanningTree() pour les appels r�cursifs.
/// @param graph le graphe.
/// @param currID sommet en cours de traitement.
/// @param explored tableau de bool�ens indiquant pour chaque identifiant de
/// noeud s'il a �t� marqu� comme ateint.
static TreeInt *Graph_spanningTreeRec(Graph *graph, int currID, bool *explored);

void Graph_dfsPrint(Graph *graph, int start)
{
    assert(graph && "The Graph must be created");
    assert(0 <= start && start < graph->size && "The node ID is invalid");

    bool *explored = (bool *)calloc(graph->size, sizeof(bool));
    Graph_dfsPrintRec(graph, 0, explored);
    free(explored);
}

static void Graph_dfsPrintRec(Graph *graph, int currID, bool *explored)
{
    explored[currID] = true;
    printf("%d\n", currID);

    // TODO
    // Astuce :
    // Pour parcourir tous les arcs sortant d'un noeud currID
    // Vous pouvez utiliser la boucle suivante :
    for (ArcList *arc = Graph_getArcList(graph, currID);
         arc != NULL; arc = arc->next)
    {
        int target = arc->target;
        if (!explored[arc->target])
            Graph_dfsPrintRec(graph, arc->target, explored);
    }
}

void Graph_bfsPrint(Graph *graph, int start)
{
    assert(graph && "The Graph must be created");
    assert(0 <= start && start < graph->size && "The node ID is invalid");

    ListInt *list = ListInt_create();
    ListInt_insertLast(list, start);

    bool *explored = (bool *)calloc(graph->size, sizeof(bool));
    explored[start] = true;

    while (!ListInt_isEmpty(list))
    {
        int currID = ListInt_popFirst(list);
        printf("%d\n", currID);

        for (ArcList *arc = Graph_getArcList(graph, currID); arc != NULL; arc = arc->next)
        {
            int target = arc->target;

            if (!explored[target])
                ListInt_insertLast(list, target);
            explored[target] = true;
        }
    }
    free(explored);
}

TreeInt *Graph_spanningTree(Graph *graph, int start)
{
    bool *explored = (bool *)calloc(graph->size, sizeof(bool));
    TreeInt *tree = Graph_spanningTreeRec(graph, start, explored);
    free(explored);

    return tree;
}

static TreeInt *Graph_spanningTreeRec(Graph *graph, int currID, bool *explored)
{
    explored[currID] = true;
    TreeInt *tree = TreeInt_create(currID);

    for (ArcList *arc = Graph_getArcList(graph, currID); arc != NULL; arc = arc->next)
    {
        int target = arc->target;

        if (!explored[target])
            TreeInt_addChild(tree, Graph_spanningTreeRec(graph, target, explored));
        explored[target] = true;
    }
    return tree;
}
