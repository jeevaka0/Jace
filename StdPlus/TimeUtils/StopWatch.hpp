/* Created by Jeevaka Dassanayake on 3/22/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

namespace StdPlus {

	class StopWatch {
	public :
		typedef unsigned long (*GetNanos)();
		StopWatch( GetNanos gn );
		~StopWatch();

		void start();
		void stop();
		void reset();

		void printTotal( ostream& os, nanoseconds unit, unsigned decimals  );


	protected :
		// Typedefs


		// Methods
		void printInterval( ostream& os, unsigned long interval, nanoseconds unit, unsigned decimals );

		// Data
		const GetNanos getNanos;
		unsigned long started;
		unsigned long total;
//		unsigned long count;
//		unsigned long minElapsed;
//		unsigned long maxElapsed;
	};
}
