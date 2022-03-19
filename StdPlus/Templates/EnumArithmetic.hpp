/* Created by Jeevaka Dassanayake on 5/14/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

namespace StdPlus {
}


template<typename Enum> struct EnableArithmeticOperators {
	static const bool enable = false;
};

// Pre-increment
template<typename Enum> typename enable_if<EnableArithmeticOperators<Enum>::enable, Enum>::type& operator++( Enum& e ) {
	using Underlying = typename underlying_type<Enum>::type;
	e = (Enum)( (Underlying)e + 1 );
	return e;
}


// Pre-decrement
template<typename Enum> typename enable_if<EnableArithmeticOperators<Enum>::enable, Enum>::type& operator--( Enum& e ) {
	using Underlying = typename underlying_type<Enum>::type;
	e = (Enum)( (Underlying)e - 1 );
	return e;
}


// Post-increment
template<typename Enum> typename enable_if<EnableArithmeticOperators<Enum>::enable, Enum>::type operator++( Enum& e, int ) {
	Enum old = e;
	++e;
	return old;
}


// Pre-decrement
template<typename Enum> typename enable_if<EnableArithmeticOperators<Enum>::enable, Enum>::type operator--( Enum& e, int ) {
	Enum old = e;
	--e;
	return old;
}

