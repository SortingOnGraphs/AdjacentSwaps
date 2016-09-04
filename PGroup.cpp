/*
 * AdjacentSwaps is a C++ implementation for adjacent swap-based sorting algorithms
 * for a graph with a line, ring, star, or complete topology by using minimum generator
 * sequence procedures involving the symmetric group S_n and its several generating sets.
 *
 * Copyright (C) 2016 Dohan Kim <dkim@airesearch.kr>
 * Author : Dohan Kim < dkim@airesearch.kr >
 *
 * File Name : PGroup.cpp
 * Description : Permutation group related modules for AdjacentSwaps
 */

#include "PGroup.h"
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;

PGroup::PGroup()
{
}

PGroup::~PGroup()
{
}

int *PGroup::inverse( int *perm, int length )
{
	int *inverse_perm = new int[length];

	for( int i = 0; i < length; i++ )
	{
		inverse_perm[perm[i] - 1] = i + 1;		
	}

	return inverse_perm;
}

int *PGroup::multiplication( int *perm1, int *perm2, int length )
{
	int *return_perm = new int[length];

	for( int i = 0; i < length; i++ )
	{
		return_perm[i] = perm1[perm2[i] - 1];
	}

	return return_perm;
}

vector< vector<int> > PGroup::disjoint_cycles( int *perm, int length )
{
	vector< vector<int> > d_cycle;
	vector<bool> mark;
	int start = 0;

	mark.resize( length );

	for( int k = 0; k < length; k++ )
	{
		mark[k] = false;
	}

	for( int i = 0; i < length; i++ )
	{
		if( mark[i] == true )
			continue;

		vector<int> temp;

		if( perm[i] == i + 1 )
		{
			mark[i] = true;
			temp.push_back( i + 1 );
			d_cycle.push_back( temp );
		}

		else
		{
			start = i;

			do {
				mark[start] = true;
				temp.push_back( start + 1 );
				start = perm[start] - 1;
			} while ( !mark[start]);

			d_cycle.push_back( temp );
		}

		temp.clear();
	}


	return d_cycle;
}

int PGroup::line_inversion_number( int *perm, int length )
{
	int inv_number = 0;

	for( int i = 0; i < length; i++ )
	{
		for( int j = i + 1; j < length; j++ )
		{
			if( perm[i] > perm[j] )
			{
				inv_number++;
			}
		}
	}

	return inv_number;
}

int PGroup::ring_inversion_number( int *dvec, int length )	
{
	int inv_number = 0;

	for( int i = 0; i < length; i++ )
	{
		for( int j = i + 1; j < length; j++ )
		{
			if( i + 1 + dvec[i] > j + 1 + dvec[j] ||  i + 1 + dvec[i] + length < j + 1 + dvec[j] )
			{
				inv_number++;
			}
		}
	}

	return inv_number;
}

bool compare( int i, int j ) 
{ 
	return i<j; 
}

int *PGroup::stable_displacement_vector( int *perm, int length )
{
	int *dvec = new int[length];
	int *max, *min = NULL;

	for( int i = 0; i < length; i++ )
	{
		dvec[i] = perm_element_find( perm, length, i + 1 ) - ( i + 1 ); 
	}

	max = max_element( dvec, dvec + length, compare );
	min = min_element( dvec, dvec + length, compare );

	while( *max - *min > length )
	{
		*max = *max - length;
		*min = *min + length;

		max = max_element( dvec, dvec + length, compare );
		min = min_element( dvec, dvec + length, compare );
	}
	
	return dvec;
}

int PGroup::perm_element_find( int *perm, int length, int k )
{
	for( int i = 0; i < length; i++ )
	{
		if( perm[i] == k )
		{
			return i + 1;
		}
	}

	return 1;
}
