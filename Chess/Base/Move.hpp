/* Created by Jeevaka Dassanayake on 4/23/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

namespace Chess {

	class Move {
	public :
		virtual Move& operator=( const Move& other ) = 0;

		virtual const Square& getStart() const = 0;
		virtual const Square& getEnd() const = 0;
		virtual bool isEnPassant() const = 0;
		virtual PieceEnum promotedPiece() const = 0;

		// Info needed to revert a move.
		virtual PieceEnum capturedPiece() const = 0;
		virtual bool hadEnPassant() const = 0;
		virtual const Square& enPassantSquare() const = 0;
		virtual bool getOldCastlingPermission( bool isWhite, bool isKingSide ) const = 0;

	protected :
		// Typedefs


		// Methods


		// Data
	};
}
