/* Created by Jeevaka Dassanayake on 3/31/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

#include "../../Shared/BaseIncludes.hpp"
#include "../../StdPlus/StdPlus.hpp"

#include "ChessConst.hpp"
#include "PieceEnum.hpp"
#include "PieceOps.hpp"
#include "Square.hpp"
#include "Move.hpp"
#include "Position.hpp"
#include "Notation.hpp"


using namespace Chess;


istream& Notation::setPosition( Position& position, istream& fen ) {
	string board, castling, enPassant;
	char turn;
	unsigned halfMoveClock, fullMoveNumber;
	fen >> board >> turn >> castling >> enPassant >> halfMoveClock >> fullMoveNumber;

	// Setup the board.
	unsigned row = ChessConst::RowCount - 1, column = 0;
	for( char c : board ) {
		if( 0 != isalpha( c ) ) {
			position.setPiece( row, column, charToPiece( c ) );
			column++;
		} else if ( '/' == c ) {
			row--; column = 0;
		} else {
			for ( unsigned i = 0; i < (unsigned)( c - '0' ); i++ ) {
				position.setPiece( row, column++, PieceEnum::EMPTY );
			}
		}
	}

	position.setTurn( Notation::isWhite( turn ) );

	position.resetCastlingPermissions();
	if ( '-' != castling[0] ) {
		for ( char c : castling ) {
			PieceEnum piece = charToPiece( c );
			bool white = PieceOps::splitColor( piece );
			position.setCastlingPermission( white, PieceEnum::KING == piece, true );
		}
	}

	if ( '-' == enPassant[0] ) {
		position.resetEnPassant();
	} else {
		Square& square( position.getEnPassantSquare() );
		getSquare( square, enPassant );
	}

	position.setHalfMoveCount( halfMoveClock );
	position.setFullMoveCount( fullMoveNumber );

	return fen;
}


void Notation::setInitialPosition( Position& position ) {
	istringstream iss( initialFen );
	setPosition( position, iss );
}


ostream& Notation::print( const Position& position, ostream& os ) {
	for( unsigned row = ChessConst::RowCount - 1; row < ChessConst::RowCount; row-- ) {
		unsigned blanks = 0;
		for ( unsigned column = 0; column < ChessConst::ColumnCount; column++ ) {
			PieceEnum piece = position.getPiece( row, column );
			if ( PieceEnum::EMPTY == piece ) {
				blanks++;
			} else {
				if ( blanks ) {
					os << blanks;
					blanks = 0;
				}
				os << pieceToChar( piece );
			}
		}
		if ( blanks ) os << blanks;
		if ( row ) os << '/';
	}

	os << ' ' << colorToChar( position.getTurn() ) << ' ';

	bool cantCastle = true;
	for( bool isWhite : { true, false } ) {
		for( bool isKingSide : { true, false } ) {
			if ( position.getCastlingPermission( isWhite, isKingSide ) ) {
				os << pieceToChar( PieceOps::setColor( isKingSide ? PieceEnum::KING : PieceEnum::QUEEN, isWhite ) );
				cantCastle = false;
			}
		}
	}
	if ( cantCastle ) os << '-';

	os << ' ';
	if ( position.hasEnpassant() ) {
		printSquare( position.getEnPassantSquare(), os );
	} else {
		os << '-';
	}

	os << ' ' << position.getHalfMoveCount() << ' ' << position.getFullMoveCount();

	return os;
}


ostream& Notation::printMove( const Move& move, ostream& os ) {
	printSquare( move.getStart(), os );
	printSquare( move.getEnd(), os );
	return os;
}


ostream& Notation::printSquare( const Square& square, ostream& os ) {
	os << (char)( 'a' + square.getColumn() ) << (char)( '1' + square.getRow() );
	return os;
}


PieceEnum Notation::charToPiece( char c ) {
	bool isWhite = isupper( c );
	if ( isWhite ) {
		c = (char)( 'a' - 'A' + c);
	}
	PieceEnum piece = cTP.find( c )->second;
	piece = PieceOps::setColor( piece, isWhite );
	return piece;
}


char Notation::pieceToChar( PieceEnum p ) {
	bool isWhite = PieceOps::splitColor( p );
	char c = pTC.find( p )->second;
	if ( isWhite ) {
		c = (char)toupper( c );
	}
	return c;
}


bool Notation::isWhite( char c ) {
	return 'w' == c;
}


char Notation::colorToChar( bool isWhite ) {
	return isWhite ? 'w' : 'b';
}


void Notation::getSquare( Square& square, const string& s ) {
	square.setRow( (unsigned)( s[1] - '1' ) );
	square.setColumn( (unsigned)( s[0] - 'a' ) );
}


const string Notation::initialFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";


const map<char, PieceEnum> Notation::cTP = { { 'b', PieceEnum::BISHOP }, { 'k', PieceEnum::KING }
		, { 'n', PieceEnum::KNIGHT }, { 'p', PieceEnum::PAWN }, { 'q', PieceEnum::QUEEN }, { 'r', PieceEnum::ROOK } };


const map<PieceEnum, char> Notation::pTC = { { PieceEnum::BISHOP, 'b' }, { PieceEnum::KING, 'k' }
		, { PieceEnum::KNIGHT, 'n' }, { PieceEnum::PAWN, 'p' }, { PieceEnum::QUEEN, 'q' }, { PieceEnum::ROOK, 'r' } };

