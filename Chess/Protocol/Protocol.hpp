/* Created by Jeevaka Dassanayake on 4/21/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

namespace Chess {

	// We could decouple main thread from engine via queues. Keep single threaded for now.
	class Protocol {
	public :
		Protocol();
		void setEngine( Engine* pE );
		virtual int process( istream& is ) = 0;

	protected :
		// Typedefs


		// Methods


		// Data
		Engine* pEngine;
		StopWatch stopWatch;
	};
}
