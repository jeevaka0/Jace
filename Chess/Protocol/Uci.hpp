/* Created by Jeevaka Dassanayake on 4/21/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

// We can move stream related processing to a base class and derive fom it.

namespace Chess {

	class Uci : public Protocol {
	public :
		Uci( ostream& o );

		virtual int process( istream& is ) override;

	protected :
		// Typedefs
		typedef int ( Uci::*HandleCommand )( istream& is );
		typedef map<string, HandleCommand> CommandHandlers;
		typedef CommandHandlers::iterator commandHandlersIt;
		typedef CommandHandlers::const_iterator commandHandlersCit;

		// Methods
		int handleComment( istream& is );
		int handleUci( istream& is );
		int handleIsReady( istream& is );
		int handleNewGame( istream& is );
		int handlePosition( istream& is );
		int handleGo( istream& is );
		int handleQuit( istream& is );

		// go options
		int handleGoDepth( istream& is );

		void applyMove( const string& move );
		int applyLastMove( istream& is );

		// Data
		ostream& os;

		static CommandHandlers commandHandlers;
		static CommandHandlers goOptionHandlers;
		void appendMoves( istream& is );
	};
}
