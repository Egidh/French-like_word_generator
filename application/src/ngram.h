#pragma once

#include "graph/graph.h"

#include "utils/map_ptr.h"


char *generateWord(Graph *graph, char **symbols);
void ngramGenerator(char *path, int n);
