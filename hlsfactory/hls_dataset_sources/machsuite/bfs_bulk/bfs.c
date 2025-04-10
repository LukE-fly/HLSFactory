/*
Implementations based on:
Harish and Narayanan. "Accelerating large graph algorithms on the GPU using CUDA." HiPC, 2007.
Hong, Oguntebi, Olukotun. "Efficient Parallel Graph Exploration on Multi-Core CPU and GPU." PACT, 2011.
*/

#include "bfs.h"
#define MAX_N_EDGES 158

void bfs(node_t nodes[N_NODES], edge_t edges[N_EDGES], node_index_t starting_node, level_t level[N_NODES], edge_index_t level_counts[N_LEVELS])
{
  node_index_t n;
  int count;
  int i;
  level_t horizon;
  edge_index_t cnt;

  level[starting_node] = 0;
  level_counts[0] = 1;

  loop_horizons: for( horizon=0; horizon<N_LEVELS; horizon++ ) {
    cnt = 0;
    // Add unmarked neighbors of the current horizon to the next horizon
    loop_nodes: for( n=0; n<N_NODES; n++ ) {
      if( level[n]==horizon ) {
        edge_index_t e = nodes[n].edge_begin;
        edge_index_t tmp_end = nodes[n].edge_end;
        loop_neighbors: for(i=0; i<MAX_N_EDGES; i++ ) {
          if(e < tmp_end){
            count++;
            node_index_t tmp_dst = edges[e].dst;
            level_t tmp_level = level[tmp_dst];

            if( tmp_level ==MAX_LEVEL ) { // Unmarked
              level[tmp_dst] = horizon+1;
              ++cnt;
            }
          }
          e++;
        }
      }
    }
    if( (level_counts[horizon+1]=cnt)==0 )
      break;
  }
}
