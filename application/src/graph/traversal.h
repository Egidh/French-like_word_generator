/*
    Copyright (c) Arnaud BANNIER, Nicolas BODIN and Matthieu LE BERRE.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#pragma once

#include "settings.h"
#include "graph.h"
#include "utils/tree_int.h"

/// @brief Affiche le parcours en profondeur d'un graphe.
/// @param graph le graphe.
/// @param start sommet de départ pour l'exploration du graphe.
void Graph_dfsPrint(Graph *graph, int start);

/// @brief Affiche le parcours en largeur d'un graphe.
/// @param graph le graphe.
/// @param start sommet de départ pour l'exploration du graphe.
void Graph_bfsPrint(Graph *graph, int start);

/// @brief Construit un arbre couvrant à partir d'un graphe.
/// @param graph le graphe.
/// @param start sommet de départ (racine de l'arbre à créer).
TreeInt *Graph_spanningTree(Graph *graph, int start);
