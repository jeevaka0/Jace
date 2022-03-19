/* Created by Jeevaka Dassanayake on 6/3/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

namespace StdPlus {

	class TimeUtils {
	public :
		static unsigned long GetSteadyNanos();

		static tm getLocal( const TimePoint& timePoint );
		static tm getUtc( const TimePoint& timePoint );
		static long getNanos( const TimePoint& timePoint );

	protected :
		// Typedefs


		// Methods
		template<class ClockT> static unsigned long GetNanos();

		// Data
	};

	ostream& operator<<( ostream& os, const StdPlus::TimePoint& timePoint );
}
