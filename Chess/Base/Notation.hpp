/* Created by Jeevaka Dassanayake on 3/31/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

namespace Chess {

	class Notation {
	public :
		static istream& setPosition( Position& position, istream& fen );
		static void setInitialPosition( Position& position );
		static ostream& print( const Position& position, ostream& os );

		static ostream& printSquare( const Square& square, ostream& os );
		static ostream& printMove( const Move& move, ostream& os );				// start end notation.

		static PieceEnum charToPiece( char c );
		static char pieceToChar( PieceEnum p );
		static bool isWhite( char c );
		static char colorToChar( bool isWhite );
		static void getSquare( Square& square, const string& s );

	protected :
		// Typedefs


		// Methods


		// Data
		const static string initialFen;
		const static map<char, PieceEnum> cTP;
		const static map<PieceEnum, char> pTC;
	};
}


