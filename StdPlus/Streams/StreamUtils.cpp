/* Created by Jeevaka Dassanayake on 4/21/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

#include "../../Shared/BaseIncludes.hpp"

#include "StreamUtils.hpp"


using namespace StdPlus;


// Q&D reader.
unsigned StreamUtils::readParams( istream& iss ) { return 0; }


void StreamUtils::dumpHex( ostream& os, char *pBuffer, unsigned length ) {
	char* pNext = pBuffer;
	char* pEnd = pBuffer + length;
	int count = 0;

	while ( pNext < pEnd ) {
		unsigned char c = (unsigned char)*pNext++;
		os << hex << setw( 2 ) << setfill( '0' ) << (unsigned short)c << ' ';
		if ( ++count % 16 == 0 ) {
			os << endl;
		} else if ( count % 4 == 0 ) {
			os << "  ";
		}
	}
}
