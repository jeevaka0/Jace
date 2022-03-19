/* Created by Jeevaka Dassanayake on 4/1/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

namespace StdPlus {
}


template<typename Enum> struct EnableBitMaskOperators {
	static const bool enable = false;
};


template<typename Enum> typename enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type operator&( Enum lhs, Enum rhs ) {
	using Underlying = typename underlying_type<Enum>::type;
	return (Enum) ( (Underlying)lhs & (Underlying)rhs );
}


template<typename Enum> typename enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type operator|( Enum lhs, Enum rhs ) {
	using Underlying = typename underlying_type<Enum>::type;
	return (Enum) ( (Underlying)lhs | (Underlying)rhs );
}


template<typename Enum> typename enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type operator^( Enum lhs, Enum rhs ) {
	using Underlying = typename underlying_type<Enum>::type;
	return (Enum) ( (Underlying)lhs ^ (Underlying)rhs );
}


template<typename Enum> typename enable_if<EnableBitMaskOperators<Enum>::enable, Enum>::type operator~( Enum v ) {
	using Underlying = typename underlying_type<Enum>::type;
	return (Enum) ( ~(Underlying)v );
}
