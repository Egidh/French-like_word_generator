/*
    Copyright (c) Arnaud BANNIER, Nicolas BODIN and Matthieu LE BERRE.
    Licensed under the MIT License.
    See LICENSE.md in the project root for license information.
*/

#pragma once

#include "settings.h"

/// @brief Structure représentant un arbre d'entiers.
/// Chaque noeud peut avec un nombre quelconque d'enfants.
typedef struct TreeInt
{
    /// @brief Pointeur vers le premier enfant du noeud.
    struct TreeInt *firstChild;

    /// @brief Pointeur vers le noeud frère suivant.
    struct TreeInt *nextSibling;

    /// @brief Valeur du noeud.
    int value;
} TreeInt;

/// @brief Crée un arbre avec uniquement un noeud.
/// @param value la valeur du noeud (la racine de l'arbre).
/// @return L'arbre créé.
TreeInt* TreeInt_create(int value);

/// @brief Détruit récursivement tous les noeuds d'un arbre donné par sa racine.
/// @param tree la racine de l'arbre.
void TreeInt_destroy(TreeInt* tree);

/// @brief Ajoute un enfant à un noeud d'un arbre.
/// @param node le noeud.
/// @param child l'enfant à ajouter. Il peut s'agir de la racine d'un arbre.
void TreeInt_addChild(TreeInt* node, TreeInt* child);

/// @brief Recherche un noeud dans un arbre.
/// @param tree la racine de l'arbre.
/// @param value la valeur recherchée.
/// @return Un noeud ayant la valeur recherchée ou NULL si aucun noeud ne
/// possède cette valeur.
TreeInt* TreeInt_get(TreeInt* tree, int value);

/// @brief Affiche un arbre.
/// @param tree la racine de l'arbre.
void TreeInt_print(TreeInt* tree);
