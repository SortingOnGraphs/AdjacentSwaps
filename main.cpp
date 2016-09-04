/*
 * AdjacentSwaps is a C++ implementation for adjacent swap-based sorting algorithms 
 * for a graph with a line, ring, star, or complete topology by	using minimum generator
 * sequence procedures involving the symmetric group S_n and its several generating sets.
 *
 * Copyright (C) 2016 Dohan Kim <dkim@airesearch.kr>
 * Author : Dohan Kim < dkim@airesearch.kr >
 *
 * File Name : main.cpp 
 * Description : The main file for AdjacentSwaps
 *
 */

#include "MGS.h"
#include "PGroup.h"

#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <fstream>
#include <iostream>

using namespace std;
MGSIO mgsIO;

int mgs_initialize( MGSIO *mgsIO )
{
	char line[1024];
	char buf[1024];
	vector<string> temp_list;
	FILE *fptr1 = NULL;

	if( ( fptr1 = fopen( mgsIO->input_file, "r" ) ) == NULL )
	{
		cout << "FILE OPEN ERROR: "<<__FILE__<<","<<__LINE__<<endl;
		exit( 1 );
	}
	else
	{
		while( fgets( line, sizeof( line ), fptr1 ) != NULL )
		{
			size_t i = strspn( line, " \t\n\v" );

			if ( line[i] == '#' )
			{
				continue;
			}
			else if( !strncmp( line, "GeneratorType", 13 ) )
			{
				memset( buf, '\0' , sizeof( buf) );
				sscanf( line,"%*s %s", buf );
				mgsIO->generator_type = buf[0];
			}
			else if( !strncmp( line, "NumberOfElements", 16 ) )
			{
				memset( buf, '\0' , sizeof( buf) );
				sscanf( line,"%*s %s", buf );
				mgsIO->number_of_elements = atoi( buf );

				mgsIO->source_permutation =
					( int * )malloc( sizeof( int ) * mgsIO->number_of_elements );
				mgsIO->target_permutation =
					( int * )malloc( sizeof( int ) * mgsIO->number_of_elements );
			}
			else if( !strncmp( line, "RandomPermutation", 17 ) )
			{
				memset( buf, '\0' , sizeof( buf) );
				sscanf( line,"%*s %s", buf );

				if( buf[0] == 'Y' )
				{
					mgsIO->random_permutation = true;
				}
				else
				{
					mgsIO->random_permutation = false;
				}
			}
			else if( !strncmp( line, "SourcePermutation", 17 ) )
			{
				if( mgsIO->random_permutation )
				{
					break;
				}

				char *temp_ptr = NULL;
				int index = 0;
				memset( buf, '\0' , sizeof( buf ) );
				strncpy( buf, line, strlen( line ) );

				temp_ptr = strtok( buf, "\t ");

				while( temp_ptr != NULL && index < mgsIO->number_of_elements )
				{
					temp_ptr = strtok( NULL, "\t " );
					mgsIO->source_permutation[index++] = atoi( temp_ptr );
				}
			}
			else
			{
				continue;

			}
		}
	}

	fclose( fptr1 );

	return 1;
}

int mgs_print( MGSIO *mgsIO )
{
	cout<<"************************************************"<<endl;
	cout<<"Graph Network Topology: ";

	if( mgsIO->generator_type == 'L' )
	{
		cout<<"Line Topology";
	} else if( mgsIO->generator_type == 'S' )
	{
		cout<<"Star Topology";
	}
	else if( mgsIO->generator_type == 'C' )
	{
		cout<<"Complete Topology";
	}
	else if( mgsIO->generator_type == 'B' )
	{
		cout<<"Complete Bipartite Topology";
	}
	else if( mgsIO->generator_type == 'R' )
	{
		cout<<"Ring Topology";
	}
	else
	{
		//cannot be reached here
		exit(-1);
	}

	cout<<endl;

	cout<<"Number of Objects: "<<mgsIO->number_of_elements<<endl;

	if( mgsIO->random_permutation == true )
	{
		cout<<"Random Initial Source Permutation: Yes"<<endl; 
	}
	else
	{
		cout<<"Random Initial Source Permutation: No"<<endl;
	}

	cout<<"Source Permutation (Initial Assignment): ";
	for( int i = 0 ; i < mgsIO->number_of_elements ; i++ )
	{
		cout<<mgsIO->source_permutation[i]<<" ";
	}
	cout<<endl;

	cout<<"Target Permutation: ";
	for( int j = 0 ; j < mgsIO->number_of_elements ; j++ )
	{
		cout<<mgsIO->target_permutation[j]<<" "; 
	}
	cout<<endl;

	fflush( stdout );
	return 1;
}

int main( int argc, char **argv )
{
	if( argc < 2 )
	{
		cout<<"Usage: ./mgs input_file"<<endl;
		exit( 1 );
	}

	srand ( unsigned ( time (NULL) ) );

	PGroup pgroup;
	mgsIO.input_file = argv[1];
	mgs_initialize( &mgsIO );

	for( int i = 0; i < mgsIO.number_of_elements; i++ )
	{
		mgsIO.target_permutation[i] = i + 1;
	}

	if( mgsIO.random_permutation )
	{
		for( int i = 0; i < mgsIO.number_of_elements; i++ )
		{
			mgsIO.source_permutation[i] = i + 1;
		}

		random_shuffle( mgsIO.source_permutation, mgsIO.source_permutation + mgsIO.number_of_elements );
	}

	MGS mgs( &mgsIO, &pgroup );
	mgs_print( &mgsIO );

	if( mgsIO.generator_type == 'L' )
	{
		mgs.mgs_line();
	}
	else if( mgsIO.generator_type == 'S' )
	{
		mgs.mgs_star();
	}
	else if( mgsIO.generator_type == 'C' )
	{
		mgs.mgs_complete();
	} 
	else if( mgsIO.generator_type == 'R' )
	{
		mgs.mgs_ring();
	}

	mgs.print();

	return 1;
}
