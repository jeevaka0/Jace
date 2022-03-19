/* Created by Jeevaka Dassanayake on 4/23/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

namespace Chess {

	class MoveOO : public Move {
	public :
		MoveOO();
		MoveOO( const Square& s, const Square& e, PieceEnum p, bool ep, PieceEnum c, bool wep, const Square& o
				, const bool (&cp)[2][2] );

		virtual const Square& getStart() const override;
		virtual const Square& getEnd() const override;
		virtual bool isEnPassant() const override;
		virtual PieceEnum promotedPiece() const override;

		virtual Move& operator=( const Move& other ) override;

		virtual PieceEnum capturedPiece() const override;
		virtual bool hadEnPassant() const override;
		virtual const Square& enPassantSquare() const override;
		virtual bool getOldCastlingPermission( bool isWhite, bool isKingSide ) const override;

	protected :
		// Typedefs


		// Methods


		// Data
		SquareOO start;
		SquareOO end;
		PieceEnum promoted;
		bool enPassant;

		PieceEnum captured;
		bool wasEnPassant;
		SquareOO oldEnPassantSquare;
		bool castlingPermission[2][2];
	};
}
