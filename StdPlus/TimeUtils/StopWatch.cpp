/* Created by Jeevaka Dassanayake on 3/22/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

#include "../../Shared/BaseIncludes.hpp"

#include "../Streams/StreamUtils.hpp"
#include "StopWatch.hpp"


using namespace StdPlus;


StopWatch::StopWatch( StopWatch::GetNanos gn ) : getNanos( gn ) {
	reset();
}


void StopWatch::reset() {
	total = 0;
}


StopWatch::~StopWatch() {
}


void StopWatch::start() {
	started = getNanos();
}


void StopWatch::stop() {
	total += getNanos() - started;
}


void StopWatch::printTotal( ostream& os, nanoseconds unit, unsigned decimals ) {
	printInterval( os, total, unit, decimals );
}


void StopWatch::printInterval( ostream& os, unsigned long interval, nanoseconds unit, unsigned decimals ) {
	os << setfixed( decimals ) << (double)interval / (double)unit.count();
}
