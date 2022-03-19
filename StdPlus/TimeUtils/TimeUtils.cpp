/* Created by Jeevaka Dassanayake on 6/3/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

#include "../../Shared/BaseIncludes.hpp"

#include "TimeTypes.hpp"
#include "TimeUtils.hpp"


using namespace StdPlus;


unsigned long TimeUtils::GetSteadyNanos() {
	return GetNanos<steady_clock>();
}


template<class ClockT> unsigned long TimeUtils::GetNanos() {
	return (unsigned long)duration_cast<nanoseconds>( ClockT::now().time_since_epoch() ).count();
}


tm TimeUtils::getLocal( const TimePoint& timePoint ) {
	time_t tt = high_resolution_clock::to_time_t( timePoint );
	tm ct;
	localtime_r( &tt, &ct );
	return ct;
}


tm TimeUtils::getUtc( const TimePoint& timePoint ) {
	time_t tt = high_resolution_clock::to_time_t( timePoint );
	tm ct;
	gmtime_r( &tt, &ct );
	return ct;
}


long TimeUtils::getNanos( const TimePoint& timePoint ) {
	long nanos = timePoint.time_since_epoch().count() % nano::den;
	return nanos;
}


namespace StdPlus {

	ostream& operator<<( ostream& os, const TimePoint& timePoint ) {
		tm t = TimeUtils::getLocal( timePoint );
		os << put_time( &t, "%F %T." ) << TimeUtils::getNanos( timePoint );
		return os;
	}

}