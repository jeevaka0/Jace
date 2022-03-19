/* Created by Jeevaka Dassanayake on 4/21/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

namespace StdPlus {

	class StreamUtils {
	public :
		template <class T, class ... Args> static unsigned readParams( istream& iss, T& t, Args& ... args );
		static void dumpHex( ostream& os, char* pBuffer, unsigned length );

	protected :
		// Typedefs


		// Methods
		static unsigned readParams( istream& iss );


		// Data
	};

	template <class T, class ... Args> unsigned StreamUtils::readParams( istream& iss, T& t, Args& ... args ) {
		unsigned count = 0;
		int c;
		while ( ( c = iss.peek() ) && !iss.eof() && isspace( c ) ) {
			iss.get();
		}
		if ( !iss.eof() ) {
			iss >> t;
			count = 1 + readParams( iss, args ... );
		}
		return count;
	}


	struct _SetFixed {
		inline _SetFixed( int d ) { digits = d; }
		int digits;
	};


	inline _SetFixed setfixed( unsigned digits ) { return _SetFixed( (int)digits ); }

	inline ostream& operator<<( ostream& os, _SetFixed d ) {
		os << fixed << setprecision( d.digits );
		return os;
	}
}
