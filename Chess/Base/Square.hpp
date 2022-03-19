/* Created by Jeevaka Dassanayake on 4/2/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

namespace Chess {

	class Square {
	public :
		virtual unsigned getRow() const = 0;
		virtual unsigned getColumn() const = 0;

	protected :
		// Typedefs


		// Methods
		virtual void setRow( unsigned r ) = 0;
		virtual void setColumn( unsigned c ) = 0;


		// Data

		friend class Notation;
		friend class Position;
	};
}
