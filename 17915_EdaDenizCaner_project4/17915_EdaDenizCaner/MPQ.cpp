#include "MPQ.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename Comparable>
void MPQ<Comparable>::percolateDown( int hole )
{
	int child;
	Comparable tmp = std::move( heapArray[ hole ] );

	for( ; hole * 2 <= currentSize; hole = child )
	{
		child = hole * 2;
		if( child != currentSize && heapArray[ child + 1 ] < heapArray[ child ] )
			++child;
		if( heapArray[ child ] < tmp )
			heapArray[ hole ] = std::move( heapArray[ child ] );
		else
			break;
	}
	heapArray[ hole ] = std::move( tmp );
}

template <typename Comparable>
void MPQ<Comparable>::buildHeap( )
{
	for( int i = currentSize / 2; i > 0; --i )
		percolateDown( i );
}

template <typename Comparable>
MPQ<Comparable>::MPQ( const vector<Comparable> & items )
	: heapArray(items.size( ) +10), currentSize( items.size() ) 
{
	for( unsigned int i = 0; i < items.size( ); ++i )
		heapArray[ i + 1 ] = items[ i ];
	buildHeap( );
}

template <typename Comparable>
MPQ<Comparable>::~MPQ()
{
	if(isEmpty()) {
		cout << "> Heap is empty" << endl;
	}
	else{
		
	}
}

template <typename Comparable>
bool MPQ<Comparable>::isEmpty( ) const
{
	return currentSize == 0;
}

template <typename Comparable>
void MPQ<Comparable>::deleteMin( )
{
	if( isEmpty( ) )
		throw UnderflowException{ };

	heapArray[ 1 ] = std::move( heapArray[ currentSize-- ] );
	percolateDown( 1 );
}

template <typename Comparable>
void MPQ<Comparable>::deleteMin( Comparable & minItem )
{
	if( isEmpty( ) )
		throw UnderflowException{ };

	minItem = std::move( heapArray[ 1 ] );
	heapArray[ 1 ] = std::move( heapArray[ currentSize-- ] );
	percolateDown( 1 );
}

/**
* Insert item x, allowing duplicates.
*/
template <typename Comparable>
void MPQ<Comparable>::insert( const Comparable & x )
{
	if( currentSize == heapArray.size( ) - 1 )
		heapArray.resize( heapArray.size( ) * 2 );

	// Percolate up
	int hole = ++currentSize;
	Comparable copy = x;

	heapArray[ 0 ] = std::move( copy );
	for( ; x < heapArray[ hole / 2 ]; hole /= 2 )
		heapArray[ hole ] = std::move( heapArray[ hole / 2 ] );
	heapArray[ hole ] = std::move( heapArray[ 0 ] );
}
