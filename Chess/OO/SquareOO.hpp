/* Created by Jeevaka Dassanayake on 4/2/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

namespace Chess {

	class SquareOO : public Square {
	public :
		SquareOO();
		SquareOO( unsigned r, unsigned c );
		SquareOO( const Square& other );
		SquareOO& operator= ( const Square& other );

		virtual unsigned int getRow() const override;
		virtual unsigned int getColumn() const override;


	protected :
		// Typedefs


		// Methods
		virtual void setRow( unsigned r ) override;
		virtual void setColumn( unsigned c ) override;


		// Data
		unsigned row;
		unsigned column;
	};
}
