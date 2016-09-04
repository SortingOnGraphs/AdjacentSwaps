/*
 * AdjacentSwaps is a C++ implementation for adjacent swap-based sorting algorithms
 * for a graph with a line, ring, star, or complete topology by using minimum generator
 * sequence procedures involving the symmetric group S_n and its several generating sets.
 *
 * Copyright (C) 2016 Dohan Kim <dkim@airesearch.kr>
 * Author : Dohan Kim < dkim@airesearch.kr >
 *
 * File Name : MGS.cpp
 * Description : Main modules for AdjacentSwaps 
 *
 */

#include "MGS.h"
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <math.h>

using namespace std;

MGS::MGS( MGSIO *mgsIO, PGroup *pgroup )
{
	this->mgsIO = mgsIO;
	this->pgroup = pgroup;
}

vector<int> MGS::perm_bubble_sorting( int *perm, int length )
{
    vector<int> generator_sequence;
	int *temp = new int[length];

	for( int k = 0; k < length; k++ )
	{
		temp[k] = perm[k];
	}

	for( int i = length - 1; i > 0; i-- )
	{
		for( int j = 0; j < i; j++ )
		{
			if( temp[j] > temp[j + 1] )
			{
				generator_sequence.push_back( j );
				swap(temp[j], temp[j+1]);
			}
		}
	}

    return generator_sequence;
}

int MGS::mgs_print_result( vector<transposition> &minimum_length_sequence, int upper_bound )
{
	cout<<endl<<"The minimum number of adjacent swaps needed is ";
	cout<<minimum_length_sequence.size();
	cout<<"."<<endl;
/*
	cout<<"Source permutation: ";

	for( int n = 0; n < mgsIO->number_of_elements; n++ )
	{
		cout<<mgsIO->source_permutation[n];
		cout<<" ";
	}
*/
//	cout<<endl;


	cout<<"<A permutation decomposition for the inverse of source permutation>"<<endl;

	int *tempi = pgroup->inverse( mgsIO->source_permutation, mgsIO->number_of_elements );

    	for( int i = 0; i < mgsIO->number_of_elements; i++ )
    	{
		cout<<tempi[i]<<" ";
	}
	
	cout << " = ";

	for( int j = 0; j < (int)minimum_length_sequence.size() ; j++ )
	{
		if( j != (int)minimum_length_sequence.size() - 1 )
		{
			cout<<"("<<minimum_length_sequence[j].first<<" "<<minimum_length_sequence[j].second<<")";

			//if( j % 50 == 0 && j != 0 )
			//{
			//	cout<<endl;
			//}

		}
		else
		{
			cout<<"("<<minimum_length_sequence[j].first<<" "<<minimum_length_sequence[j].second<<")";
		}
	}
	cout<<endl;

#ifdef _DEBUG
	int *src_permutation = new int[mgsIO->number_of_elements];
	int *dst_permutation = new int[mgsIO->number_of_elements];

	for( int n = 0; n < mgsIO->number_of_elements; n++ )
	{
		src_permutation[n] = mgsIO->source_permutation[n];
		dst_permutation[n] = mgsIO->target_permutation[n];
	}
	cout<<"Source Permutation: ";
	for( int s = 0 ; s < mgsIO->number_of_elements ; s++ )
	{
		cout<<src_permutation[s]<<" ";
	}
	cout<<endl;


	for( int k = 0; k < (int)minimum_length_sequence.size() ; k++ )
	{
		cout<<k+1<<". "<<"After swapping objects between vertex "<<minimum_length_sequence[k].first<<" and vertex "<<minimum_length_sequence[k].second<<" : ";
		swap( src_permutation[minimum_length_sequence[k].first - 1], src_permutation[minimum_length_sequence[k].second - 1] );

		for( int v = 0 ; v < mgsIO->number_of_elements ; v++ )
		{
			cout<<src_permutation[v]<<" ";
		}
		cout<<endl;
	}
		
	cout<<"Target Permutation: ";
	for( int t = 0 ; t < mgsIO->number_of_elements ; t++ )
	{
		cout<<dst_permutation[t]<<" ";
	}
	cout<<endl;

	bool compare_assignments = true;

	for( int u = 0 ; u < mgsIO->number_of_elements ; u++ )
	{
		if( src_permutation[u] != dst_permutation[u] )
		{
			compare_assignments = false;
			break;
		}
	}

	cout<<"Upper Bound: "<<upper_bound<<endl;

	if( compare_assignments )
	{
		cout<<"Reached the target permutation successfully"<<" ("<<(int)minimum_length_sequence.size()<<" adjacent swaps)."<<endl;
	}
	else
	{
		cout<<"Not reached the target permutation."<<endl;
	}
#endif

	return 1;
}

int MGS::mgs_line()
{
	int line_upper_bound = 0;

	vector<transposition> line_sequence;

	int *temp = 
		pgroup->multiplication( pgroup->inverse( mgsIO->target_permutation, mgsIO->number_of_elements ), 
		mgsIO->source_permutation, mgsIO->number_of_elements );

	vector<int> l_sequence =
		perm_bubble_sorting( temp, mgsIO->number_of_elements );

	for( int i = 0; i < (int)l_sequence.size(); i++ )
	{
		line_sequence.push_back( transposition( l_sequence[i] + 1, l_sequence[i] + 2 ) );
	}

#ifdef _DEBUG
	line_upper_bound = ( mgsIO->number_of_elements * ( mgsIO->number_of_elements - 1 ) ) / 2;
	cout<<"Upper Bound (the diameter of bubble sort Cayley graph BS_n for n="<<mgsIO->number_of_elements<<") : ";
	cout<<line_upper_bound<<" (i.e.,";
	cout<<"nx(n-1)/2 for n="<<mgsIO->number_of_elements <<")."<<endl;
#endif
	this->mgs_print_result( line_sequence, line_upper_bound );

	return 1;
}

int MGS::mgs_star()
{
	int star_upper_bound = 0;

	vector<transposition> star_sequence;

	int *temp =
		pgroup->multiplication( pgroup->inverse( mgsIO->source_permutation, mgsIO->number_of_elements ),
		mgsIO->target_permutation, mgsIO->number_of_elements );

    vector<int> s_sequence;
	vector< vector<int> > d_cycle = pgroup->disjoint_cycles( temp, mgsIO->number_of_elements );

	for( int i = 0; i < (int) d_cycle.size(); i++ )
	{
		if( d_cycle[i].size() > 1 )
		{
			if( d_cycle[i][0] == 1 )
			{
				for( int j = d_cycle[i].size() - 1; j > 0; j-- )
				{
					s_sequence.push_back( d_cycle[i][j] );
				}
			}
			else
			{
				s_sequence.push_back( d_cycle[i][0] );

				for( int k = d_cycle[i].size() - 1; k >= 0; k-- )
				{
					s_sequence.push_back( d_cycle[i][k] );
				}
			}
		}
	}

	for( int m = 0; m < (int)s_sequence.size(); m++ )
	{
		star_sequence.push_back( transposition( 1, s_sequence[m] ) );
	}

#ifdef _DEBUG
	star_upper_bound = (int)floor(  3 * ( mgsIO->number_of_elements - 1 ) / 2 );
	cout<<"Upper Bound (the diameter of star Cayley graph ST_n for n="<<mgsIO->number_of_elements<<") : ";
	cout<<star_upper_bound;
	/*(i.e.,"; cout<<"floor(3*(n-1)/2) for n="<<mgsIO->number_of_elements <<")."<<endl;*/
#endif

	this->mgs_print_result( star_sequence, star_upper_bound );
	
	return 1;
}

int MGS::mgs_complete()
{
	int complete_upper_bound = 0;

	vector<transposition> complete_sequence;

	int *temp =
		pgroup->multiplication( pgroup->inverse( mgsIO->source_permutation, mgsIO->number_of_elements ),
		mgsIO->target_permutation, mgsIO->number_of_elements );

	vector< vector<int> > c_sequence;
	vector< vector<int> > d_cycle = pgroup->disjoint_cycles( temp, mgsIO->number_of_elements );

	for( int i = 0; i < (int) d_cycle.size(); i++ )
	{
		if( d_cycle[i].size() > 1 )
		{
			vector<int> temp;
			temp.push_back( d_cycle[i][0] );

			for( int j = d_cycle[i].size() - 1; j > 0; j-- )
			{
				temp.push_back( d_cycle[i][j] );
			}
			c_sequence.push_back( temp );
			temp.clear();
		}
	}

	for( int m = 0; m < (int)c_sequence.size(); m++)
	{
		for( int n = 1; n < (int)c_sequence[m].size(); n++ )
		{
			complete_sequence.push_back( transposition( c_sequence[m][0], c_sequence[m][n] ) );
		}
		cout<<endl;
	}

#ifdef _DEBUG
	complete_upper_bound =  mgsIO->number_of_elements - 1;
	cout<<"Upper Bound (the diameter of complete transposition graph CT_n for n="<<mgsIO->number_of_elements<<") : ";
	cout<<complete_upper_bound<<" (i.e.,";
	cout<<"n-1 for n="<<mgsIO->number_of_elements <<")."<<endl;
#endif

	this->mgs_print_result( complete_sequence, complete_upper_bound );

	return 1;
}

int MGS::mgs_ring()
{
	int ring_upper_bound = 0;

	int *perm_for_sorting =
		pgroup->multiplication( pgroup->inverse( mgsIO->target_permutation, mgsIO->number_of_elements ),
		mgsIO->source_permutation, mgsIO->number_of_elements );

	int *d_vec = pgroup->stable_displacement_vector( perm_for_sorting, mgsIO->number_of_elements ); 

	vector<int> r_sequence;
	vector<transposition> ring_sequence;

#ifdef _VERBOSE
	cout<<"Stable displacement vector : ";

	for( int i = 0; i < mgsIO->number_of_elements; i++)
	{
		cout<<d_vec[i]<<" ";
	}
	cout<<endl;
#endif

	int i_number = pgroup->ring_inversion_number( d_vec, mgsIO->number_of_elements );

#ifdef _VERBOSE
	int	temp = i_number;
#endif

#ifdef _DEBUG
	cout<<endl<<"Inversion number (for p_2^{-1}p_1, where p_1, p_2 denote source and target permutation, respectively): "<<i_number<<endl;
#endif

	for( int j = i_number; j > 0 ; j-- ) 
	{
		perm_ring_sorting( perm_for_sorting, d_vec, mgsIO->number_of_elements, r_sequence );
		d_vec = pgroup->stable_displacement_vector( perm_for_sorting, mgsIO->number_of_elements );

#ifdef _VERBOSE
		cout<<temp - j + 1<<"." "Stable displacement vector "<<"(inversion #:"<<i_number<<")  ";
		for( int i = 0; i < mgsIO->number_of_elements; i++)
    	{
			cout<<d_vec[i]<<" ";
		}
		cout<<endl;
#endif
		i_number = pgroup->ring_inversion_number( d_vec, mgsIO->number_of_elements );

#ifdef _VERBOSE
	cout<<<<endl<<"Inversion number (Ring Topology): "<<i_number<<endl;
#endif
	}		

#ifdef _VERBOSE
	for( int m = 0; m < (int)r_sequence.size(); m++)
	{
		cout<<r_sequence[m]<<" ";
	}

	cout<<"Perm for sorting:";

	for( int n = 0; n < mgsIO->number_of_elements; n++)
	{
		cout<<perm_for_sorting[n]<<" ";
	}
#endif

	for( int v = 0; v < (int)r_sequence.size(); v++ )
	{
		if( r_sequence[v] == mgsIO->number_of_elements )
		{
			ring_sequence.push_back( transposition( 1, r_sequence[v] ) );
		}
		else
		{
			ring_sequence.push_back( transposition( r_sequence[v], r_sequence[v] + 1  ) );
		}
	}

#ifdef _DEBUG
	ring_upper_bound = ( mgsIO->number_of_elements *  mgsIO->number_of_elements ) / 4;
	cout<<endl<<"Upper bound (the diameter of modified bubble sort Cayley graph MBS_n for n="<<mgsIO->number_of_elements<<") : ";
	cout<<ring_upper_bound<<" (i.e.,";
	cout<<"|_ n^2/4 _| for n="<<mgsIO->number_of_elements <<")."<<endl;
#endif

	this->mgs_print_result( ring_sequence, ring_upper_bound );

	cout<<endl<<endl;

	return 1;
}

int MGS::perm_ring_sorting( int *perm_for_sorting, int *d_vec, int number_of_elements, vector<int> &r_sequence )
{
	for( int i = 0; i < number_of_elements; i++ )
	{
		if( i != number_of_elements - 1 )
		{
			if( d_vec[perm_for_sorting[i]-1] < 0 )
			{
				if( d_vec[perm_for_sorting[i+1]-1] > 0 )
				{
					r_sequence.push_back( i + 1 );
#ifdef _VERBOSE
					cout<<"Before: "<<perm_for_sorting[i]<<endl;
					swap( perm_for_sorting[i], perm_for_sorting[i+1] );
					cout<<"After: "<<perm_for_sorting[i]<<endl;
#else
					swap( perm_for_sorting[i], perm_for_sorting[i+1] );
#endif

					break;
				}
			}
			else if( d_vec[perm_for_sorting[i]-1] == 0 )
			{	
				if( d_vec[perm_for_sorting[i+1]-1] > 1 )
				{
					r_sequence.push_back( i + 1 );
					swap( perm_for_sorting[i], perm_for_sorting[i+1] );
					break;
				}
			}
			else
			{
				continue;
			}
		}
		else // compare the first element because it is a ring topology
		{	
			if( d_vec[perm_for_sorting[i]-1] < 0 )
			{
				if( d_vec[perm_for_sorting[0]-1] > 0 )
				{
					r_sequence.push_back( i + 1 );
					swap( perm_for_sorting[i], perm_for_sorting[0] );
					break;
				}
			}
            else if( d_vec[perm_for_sorting[i]-1] == 0 )
            {   
                if( d_vec[perm_for_sorting[0]-1] > 1 )
                {
                    r_sequence.push_back( i + 1 );
                    swap( perm_for_sorting[i], perm_for_sorting[0] );
                    break;
                }
            }
			else
				continue;
		}

#ifdef _VERBOSE
		for( int n = 0; n < mgsIO->number_of_elements; n++)
		{
			cout<<perm_for_sorting[n]<<" ";
		}
		cout<<endl;
#endif
	}

	return 1;
}

int MGS::print()
{
#ifdef _VERBOSE	
	cout<<"Inverse (source): ";
	int *temp1 = pgroup->inverse( mgsIO->source_permutation, mgsIO->number_of_elements );

    for( int i = 0; i < mgsIO->number_of_elements; i++ )
    {
        cout<<temp1[i]<<" ";
    }
	
	cout << endl;

	cout<<"Multiplication (source, target): ";

	int *temp2 = pgroup->multiplication( mgsIO->source_permutation, mgsIO->target_permutation, mgsIO->number_of_elements );

	for( int i = 0; i < mgsIO->number_of_elements; i++ )
	{
		cout<<temp2[i]<<" ";
	}

	cout<<endl<<endl;

	cout<<"Inversion number (source): ";
	int inv = pgroup->line_inversion_number( mgsIO->source_permutation, mgsIO->number_of_elements );

	cout << inv <<endl;

	vector< vector <int> > dcycle = 
		pgroup->disjoint_cycles ( mgsIO->target_permutation, mgsIO->number_of_elements );
	cout<< "Disjoint Cycle(s):"<<endl;

	for( int i = 0; i < (int) dcycle.size(); i++ )
	{
		for( int j = 0; j < (int) dcycle[i].size(); j++ )
		{
			cout<<dcycle[i][j];
		}
		cout<<endl;
	}

	cout<<endl;

	cout<< "Permutation Bubble Sorting:";

	vector<int> bsequence = 
		perm_bubble_sorting( mgsIO->source_permutation, mgsIO->number_of_elements );

	for( int i = 0; i < (int)bsequence.size(); i++)
	{
		cout<<bsequence[i]<<" ";
	}

	cout<<endl;

	int test_vec[8] = {7, 8, 4, 6, 3, 5, 1, 2};

	int *d_vec = pgroup->stable_displacement_vector( test_vec, 8 ); 

	for( int i = 0; i < mgsIO->number_of_elements; i++)
	{
		cout<<d_vec[i]<<" ";
	}

	int i_number = pgroup->ring_inversion_number( d_vec, 8 );

	cout<<"Ring inv number: "<<i_number<<endl;

	cout<<endl;
#endif

	return 1;
	}
