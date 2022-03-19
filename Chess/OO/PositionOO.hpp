/* Created by Jeevaka Dassanayake on 3/20/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

namespace Chess {

	class PositionOO : public Position {
	public :
		PositionOO();

		virtual bool getTurn() const override;
		virtual bool getCastlingPermission( bool isWhite, bool isKingSide ) const override;
		virtual bool hasEnpassant() const override;
		virtual const Square& getEnPassantSquare() const override;
		virtual unsigned getHalfMoveCount() const override;
		virtual unsigned getFullMoveCount() const override;
		virtual PieceEnum getPiece( const Square& square ) const override;
		virtual PieceEnum getPiece( unsigned row, unsigned column ) const override;
		virtual bool isEmpty( unsigned row, unsigned column ) const override;
		virtual bool isEmpty( const Square& square ) const override;

		virtual void setTurn( bool isWhite ) override;
		virtual void flipTurn() override;

	protected:
		virtual void setPiece( unsigned row, unsigned column, PieceEnum piece ) override;
		virtual void setCastlingPermission( bool isWhite, bool isKingSide, bool allowed ) override;
		virtual void setEnPassant( const Square& square, bool yes ) override;
		virtual void resetEnPassant() override;
		virtual void setHalfMoveCount( unsigned count ) override;
		virtual void setFullMoveCount( unsigned count ) override;

		virtual Square& getEnPassantSquare() override;

		virtual void attemptOneMove( unsigned rStart, unsigned cStart, unsigned rDest, unsigned cDest, PieceEnum captured,
									 PieceEnum promoted, bool enPassant, MoveEvaluator& evaluator ) override;
		virtual void bumpCounters() override;
		virtual void revertCounters() override;

	protected :
		// Typedefs


		// Methods


		// Data
		PieceEnum squares[ChessConst::RowCount][ChessConst::ColumnCount];
		bool castlingPermission[2][2];
		bool isWhitesTurn;
		bool enPassantPossible;
		SquareOO enPassantSquare;
		unsigned halfMoveCount;
		unsigned fullMoveCount;
	};
}
