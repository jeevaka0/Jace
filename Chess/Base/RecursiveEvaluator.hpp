/* Created by Jeevaka Dassanayake on 3/6/22.
   Copyright (c) 2022 Jeevaka Dassanayake.*/

namespace Chess {

	class RecursiveEvaluator : public MoveEvaluator {
	public :
		RecursiveEvaluator( Position& p );

		virtual Move& findBestMove() = 0;

		virtual void setMaxPlies( unsigned mp );
		virtual unsigned long getPlyCount();

	protected:

		// Typedefs


		// Methods
		virtual void initializeSearch();
		virtual void bumpPlyCount();


		// Data
		unsigned maxPlies;
		unsigned long plyCount;
	};
}