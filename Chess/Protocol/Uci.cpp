/* Created by Jeevaka Dassanayake on 4/21/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

#include "../../Shared/BaseIncludes.hpp"
#include "../../StdPlus/StdPlus.hpp"

#include "../Base/ChessConst.hpp"
#include "../Base/PieceEnum.hpp"
#include "../Base/Square.hpp"
#include "../Base/Move.hpp"
#include "../Base/Position.hpp"

#include "../Base/MoveEvaluator.hpp"
#include "../Base/RecursiveEvaluator.hpp"
#include "../Base/Engine.hpp"
#include "Protocol.hpp"

#include "Uci.hpp"
#include "../Base/Notation.hpp"

#include "../OO/SquareOO.hpp"


using namespace Chess;

Uci::CommandHandlers Uci::commandHandlers = {
		{ "//", &Uci::handleComment }
		, { "uci", &Uci::handleUci }
		, { "isready", &Uci::handleIsReady }
		, { "ucinewgame", &Uci::handleNewGame }
		, { "position", &Uci::handlePosition }
		, { "go", &Uci::handleGo }
		, { "quit", &Uci::handleQuit }
/*
		, { "", &Uci:: }
*/
};


Uci::CommandHandlers Uci::goOptionHandlers = {
		  { "//", &Uci::handleComment }
		, { "depth", &Uci::handleGoDepth }
/*
		, { "", &Uci:: }
*/
};


Uci::Uci( ostream& o ) : Protocol(), os( o ){

}


int Uci::process( istream& is ) {
	int result = 0;
	string line;
	while( 0 == result && getline( is, line ) ) {
		if ( !line.empty() ) {
			istringstream iss( line );
			string command;
			if ( StreamUtils::readParams( iss, command ) ) {				// Ignore empty lines.
				commandHandlersCit cit = commandHandlers.find( command );
				if ( commandHandlers.end() != cit ) {						// Ignore unknown commands.
					result = (this->*cit->second)( iss );
				} else {
					os << "info string Unhandled command: " << command << endl;
				}
			}
		}
	}
	return result;
}


int Uci::handleComment( istream& is ) {
	string line;
	getline( is, line );
	return 0;
}


int Uci::handleUci( istream& is ) {
	os << "id name Jace 0.1" << endl;
	os << "id author Jeevaka D." << endl;

	os << "uciok" << endl;
	return 0;
}


int Uci::handleIsReady( istream& is ) {
	os << "readyok" << endl;
	return 0;
}


int Uci::handleNewGame( istream& is ) {
	pEngine->reset();
	return 0;
}


int Uci::handlePosition( istream& is ) {
	int result = 0;
	if ( pEngine->canSetup() ) {
		string option;
		if ( StreamUtils::readParams( is, option ) ) {                // Ignore empty lines.
			if ( option == "startpos" ) {
				Notation::setInitialPosition( pEngine->getPosition() );
				appendMoves( is );
			} else if ( option == "fen" ) {
				Notation::setPosition( pEngine->getPosition(), is );		// Needs to be valid.
				appendMoves( is );
			} else {
				os << "info string Incomplete 'position' command." << endl;
				result = -1;
			}
			if ( 0 == result ) {
				pEngine->initialize();
			}
		}
	} else {		// This happens when continuing a game. "position fen ff f f moves m1 .. mn" comes in.
		applyLastMove( is );
	}
	return result;
}


void Uci::appendMoves( istream& is ) {
	if ( !is.eof() ) {
		string option;
		StreamUtils::readParams( is, option );
		if( "moves" == option ) {
			string nextMove;
			while ( !is.eof() ) {
				StreamUtils::readParams( is, nextMove );
				applyMove( nextMove );
				//pEngine->getPosition().print( cout ) << endl;
			}
		} else {
			cerr << "Unknown option " << option << endl;
		}
	}
}


int Uci::applyLastMove( istream& is ) {
	string line;
	getline( is, line );
	string lastMove = line.substr( line.rfind(' ') + 1 );

	applyMove( lastMove );
	return 0;
}


void Uci::applyMove( const string& move ) {
	SquareOO start, end;
	Notation::getSquare( start, move );
	Notation::getSquare( end, move.substr( 2 ) );

	PieceEnum promoted = PieceEnum::EMPTY;
	if( move.length() == 5 ) {
		char pieceChar = move[ 4 ];
		if( pEngine->getPosition().getTurn() ) {
			pieceChar = (char)toupper( pieceChar );
		}
		promoted = Notation::charToPiece( pieceChar );
	}
	pEngine->applyMove( start, end, promoted );
}


int Uci::handleGo( istream& is ) {
	int result = -1;
	if( !pEngine->canSetup() ) {		// Engine currently has a valid setup.
		result = 0;
		string goOption;
		while ( 0 == result && StreamUtils::readParams( is, goOption ) ) {
			commandHandlersCit cit = goOptionHandlers.find( goOption );
			if ( commandHandlers.end() != cit ) {						// Ignore unknown commands.
				result = (this->*cit->second)( is );
			} else {
				os << "info string Unhandled go option: " << goOption << endl;
			}
		}

		if ( -1 != result ) {
			stopWatch.reset();
			stopWatch.start();

			const Move& best( pEngine->getBestMove() );

			stopWatch.stop();
			os << "info string Evaluated " << pEngine->getPlyCount() << " plies in ";
			stopWatch.printTotal( os, seconds(1), 3 );
			os << " seconds." << endl;

			pEngine->applyMove( best );
			os << "bestmove ";
			Notation::printMove( best, os );
			os << endl;
		}
	}
	return result;
}


int Uci::handleGoDepth( istream& is ) {
	int result = -1;
	unsigned maxDepth;
	if ( StreamUtils::readParams( is, maxDepth ) ) {
		pEngine->setMaxDepth( maxDepth );
		result = 0;
	}
	return result;
}


int Uci::handleQuit( istream& is ) {
	return 1;
}
