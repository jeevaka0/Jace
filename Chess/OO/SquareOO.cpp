/* Created by Jeevaka Dassanayake on 4/2/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

#include "../../Shared/BaseIncludes.hpp"

#include "../Base/Square.hpp"
#include "SquareOO.hpp"


using namespace Chess;


SquareOO::SquareOO() {
}


SquareOO::SquareOO( const Square& other ) {
	*this = other;
}


SquareOO::SquareOO( unsigned r, unsigned c ) {
	row = r;
	column = c;
}


SquareOO& SquareOO::operator=( const Square& other ) {
	row = other.getRow();
	column = other.getColumn();
	return *this;
}


unsigned int SquareOO::getRow() const {
	return row;
}


unsigned int SquareOO::getColumn() const {
	return column;
}


void SquareOO::setRow( unsigned r ) {
	row = r;
}

void SquareOO::setColumn( unsigned c ) {
	column = c;
}
