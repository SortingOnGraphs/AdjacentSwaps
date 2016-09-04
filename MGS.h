/*
 * AdjacentSwaps is a C++ implementation for adjacent swap-based sorting algorithms
 * for a graph with a line, ring, star, or complete topology by using minimum generator
 * sequence procedures involving the symmetric group S_n and its several generating sets.
 *
 * Copyright (C) 2016 Dohan Kim <dkim@airesearch.kr>
 * Author : Dohan Kim < dkim@airesearch.kr >
 
 * File Name : MGS.h
 * Description : Header file of MGS.cpp 
 *
 */

#ifndef _MGS_H
#define _MGS_H

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

#include <math.h>

#include "PGroup.h"

using namespace std;

typedef struct
{
	char *input_file;
	char generator_type;
	int number_of_elements;
	int bipartite_index;
	bool random_permutation;
	int *source_permutation;
	int *target_permutation;
} MGSIO;

class MGS
{
  private:
	MGSIO *mgsIO;
	PGroup *pgroup;
  public:
	MGS( MGSIO *mgsIO, PGroup *pgroup );
	~MGS(){};
	int print(); 
	int mgs_line(); 
	int mgs_star();
	int mgs_complete();
	int mgs_ring();
	int mgs_print_result( vector<transposition> &minimum_length_sequence, int upper_bound );
	int perm_ring_sorting( int *perm_for_sorting, int *d_vec, int number_of_tasks, vector<int> &ring_sequence );
	vector<int> perm_bubble_sorting( int *perm, int length );
};

extern MGSIO mgsIO;
extern int mgs_print( MGSIO *mgsIO );
extern int mgs_initialize( MGSIO *mgsIO );
#endif /* _MGS_H */
