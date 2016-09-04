/*
 * AdjacentSwaps is a C++ implementation for adjacent swap-based sorting algorithms
 * for a graph with a line, ring, star, or complete topology by using minimum generator
 * sequence procedures involving the symmetric group S_n and its several generating sets.
 *
 * Copyright (C) 2016 Dohan Kim <dkim@airesearch.kr>
 * Author : Dohan Kim < dkim@airesearch.kr >
 *
 * File Name : PGroup.h
 * Description : Header file of PGroup.cpp
 *
 */

#ifndef _PGROUP_H
#define _PGROUP_H

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

typedef pair<int, int> transposition;

class PGroup
{
  private:
  public:
	PGroup();
	~PGroup();
	int *inverse( int *perm, int length );
	int *multiplication( int *perm1, int *perm2, int length );
	int *stable_displacement_vector( int *perm, int length );
	int perm_element_find( int *perm, int length, int k );
	int line_inversion_number( int *perm, int length );
	int ring_inversion_number( int *dvec, int length );
	vector< vector<int> > disjoint_cycles( int *perm, int length );
};

#endif /* _PGROUP_H */
