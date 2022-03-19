/* Created by Jeevaka Dassanayake on 3/20/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

#include "../Shared/BaseIncludes.hpp"
#include "../StdPlus/StdPlus.hpp"
#include "../Chess/Chess.hpp"
#include "../ChessAlgos/ChessAlgos.hpp"

#include "Jace.hpp"


Jace::Jace() : protocol( *new Uci( cout ) ), engine( *new BourdonnaisEngine( protocol ) ) {
	protocol.setEngine( &engine );
}


int Jace::live( const string& input ) {
	int result = 0;
	if ( !input.empty() ) {
		ifstream ifs( input );
		if ( ifs.is_open() ) {
			result = protocol.process( ifs );
		} else {
			cerr << "Failed to open: " << input << endl;
		}
	}
	if( 0 == result ) {				// If there was no error continue processing commands from cin.
		protocol.process( cin );
	}
	return result;
}


int main( int argc, char *argv[] ) {
	Jace jace;
	if ( 1 == argc ) {
		jace.live( "" );
	} else if ( 2 == argc ) {
		jace.live( argv[ 1 ] );
	} else {
		cout << "jace {uci file}" << endl;
	}
	return 0;
}
