/* Created by Jeevaka Dassanayake on 3/20/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

namespace Chess {
	class MoveEvaluator;

	class Position {
	public :
		Position();

		ostream& print( ostream& os ) const;
		istream& read( istream& is );

		virtual void applyMove( const Move& move );
		virtual void applyMove( const Square& start, const Square& end, PieceEnum promoted );
		virtual void revertMove( const Move& move );
		virtual bool isCheck() const;

		virtual PieceEnum getPiece( unsigned row, unsigned column ) const = 0;
		virtual PieceEnum getPiece( const Square& square ) const = 0;
		virtual PieceEnum getPieceType( const Square& square );
		virtual bool isEmpty( unsigned row, unsigned column ) const = 0;
		virtual bool isEmpty( const Square& square ) const = 0;

		virtual bool getTurn() const = 0;
		virtual bool getCastlingPermission( bool isWhite, bool isKingSide ) const = 0;
		virtual bool hasEnpassant() const = 0;
		virtual const Square& getEnPassantSquare() const = 0;
		virtual unsigned getHalfMoveCount() const = 0;
		virtual unsigned getFullMoveCount() const = 0;

		virtual void doAllMoves( MoveEvaluator& moveEvaluator );

		virtual void setTurn( bool isWhite ) = 0;		// Use with care.
		virtual void flipTurn() = 0;

	protected:
		// Typedefs
		typedef void (Position::*DoPieceMoves)( unsigned, unsigned, MoveEvaluator& );

		// Methods
		virtual void setPiece( unsigned row, unsigned column, PieceEnum piece ) = 0;
		virtual void setCastlingPermission( bool isWhite, bool isKingSide, bool allowed ) = 0;
		virtual void setEnPassant( const Square& square, bool yes ) = 0;
		virtual void resetEnPassant() = 0;
		virtual void setHalfMoveCount( unsigned count ) = 0;        // From last pawn move or capture. 100 => draw.
		virtual void setFullMoveCount( unsigned count ) = 0;        // From Start. Starts at 1.
		virtual void bumpCounters() = 0;
		virtual void revertCounters() = 0;

		void resetCastlingPermissions();
		virtual Square& getEnPassantSquare() = 0;

		virtual void applyMove( unsigned rStart, unsigned cStart, unsigned rDest, unsigned cDest, PieceEnum promoted
				, bool enPassant );
		virtual void attemptPromotions( unsigned rStart, unsigned cStart, unsigned rDest, unsigned cDest, PieceEnum captured
				, MoveEvaluator& evaluator );
		virtual void attemptOneMove( unsigned rStart, unsigned cStart, unsigned rDest, unsigned cDest, PieceEnum captured
				, PieceEnum promoted, bool enPassant, MoveEvaluator& evaluator ) = 0;  // Move, confirm check, emit, revert.
		virtual bool attemptDirectionalMove( unsigned rStart, unsigned cStart, unsigned rDest, unsigned cDest
				, MoveEvaluator& evaluator );
		virtual void doDirectionalMoves( unsigned row, unsigned column, int rOffset, int cOffset, MoveEvaluator& evaluator );

		virtual void doPawnMoves( unsigned row, unsigned column, MoveEvaluator& evaluator );
		virtual void doKnightMoves( unsigned row, unsigned column, MoveEvaluator& evaluator );
		virtual void doBishopMoves( unsigned row, unsigned column, MoveEvaluator& evaluator );
		virtual void doRookMoves( unsigned row, unsigned column, MoveEvaluator& evaluator );
		virtual void doQueenMoves( unsigned row, unsigned column, MoveEvaluator& evaluator );
		virtual void doKingMoves( unsigned row, unsigned column, MoveEvaluator& evaluator );
		virtual void attemptCastling( bool isKingSide, MoveEvaluator& evaluator );

		virtual bool isAttacked( unsigned row, unsigned column ) const;    // By a piece of the color opposite to getTurn()
		virtual bool containsPiece( unsigned row, unsigned column, PieceEnum piece ) const;
		virtual bool containsPieceInDirection( unsigned row, unsigned column, int rOffset, int cOffset, PieceEnum piece
				, PieceEnum queen ) const;

		virtual unsigned firstRow() const;
		virtual unsigned secondRow() const;
		virtual unsigned lastRow() const;

		friend class Notation;

		constexpr static DoPieceMoves movers[ChessConst::NumPieces]
				= { &Position::doPawnMoves, &Position::doKnightMoves, &Position::doBishopMoves, &Position::doRookMoves
						, &Position::doQueenMoves, &Position::doKingMoves };
	};
}
