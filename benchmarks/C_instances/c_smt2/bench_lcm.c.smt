(set-logic LIA)

( declare-const a Int )
( declare-const a! Int )
( declare-const b Int )
( declare-const b! Int )
( declare-const x Int )
( declare-const x! Int )
( declare-const y Int )
( declare-const y! Int )

( declare-const a_0 Int )
( declare-const a_1 Int )
( declare-const b_0 Int )
( declare-const b_1 Int )
( declare-const b_2 Int )
( declare-const b_3 Int )
( declare-const x_0 Int )
( declare-const x_1 Int )
( declare-const y_0 Int )
( declare-const y_1 Int )

( define-fun inv-f( ( a Int )( b Int )( x Int )( y Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( a Int )( b Int )( x Int )( y Int )( a_0 Int )( a_1 Int )( b_0 Int )( b_1 Int )( b_2 Int )( b_3 Int )( x_0 Int )( x_1 Int )( y_0 Int )( y_1 Int ) ) Bool
	( and
		( = a a_1 )
		( = b b_1 )
		( = x x_1 )
		( = y y_1 )
		( = a_1 5 )
		( = b_1 7 )
		( = x_1 a_1 )
		( = y_1 b_1 )
		( > a_1 0 )
		( > b_1 0 )
	)
)

( define-fun trans-f ( ( a Int )( b Int )( x Int )( y Int )( a! Int )( b! Int )( x! Int )( y! Int )( a_0 Int )( a_1 Int )( b_0 Int )( b_1 Int )( b_2 Int )( b_3 Int )( x_0 Int )( x_1 Int )( y_0 Int )( y_1 Int ) ) Bool
	( or
		( and
			( = b_2 b )
			( = b_2 b! )
			( = a a_1 )
			( = a! a_1 )
			( = x x! )
			( = y y! )
		)
		( and
			( = b_2 b )
			( not ( = a_1 b_2 ) )
			( > a_1 b_2 )
			( = b_3 ( - b_2 a_1 ) )
			( = b_3 b! )
			(= a a_1 )
			(= a! a_1 )
			(= x x_1 )
			(= x! x_1 )
			(= y y_1 )
			(= y! y_1 )
		)
		( and
			( = b_2 b )
			( not ( = a_1 b_2 ) )
			( not ( > a_1 b_2 ) )
			( = b_3 ( - b_2 a_1 ) )
			( = b_3 b! )
			(= a a_1 )
			(= a! a_1 )
			(= x x_1 )
			(= x! x_1 )
			(= y y_1 )
			(= y! y_1 )
		)
	)
)

( define-fun post-f ( ( a Int )( b Int )( x Int )( y Int )( a_0 Int )( a_1 Int )( b_0 Int )( b_1 Int )( b_2 Int )( b_3 Int )( x_0 Int )( x_1 Int )( y_0 Int )( y_1 Int ) ) Bool
	( and
		( or
			( not
				( and
					( = a a_1)
					( = b b_2)
					( = x x_1)
					( = y y_1)
				)
			)
			( not
				( and
					( not ( not ( = a_1 b_2 ) ) )
					( >= a_1 0 )
					( >= b_2 0 )
					( not ( and ( and ( >= a_1 0 ) ( >= b_2 0 ) ) ( = ( * x_1 y_1 ) ( *   ) ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = a a_1)
					( = b b_2)
					( = x x_1)
					( = y y_1)
				)
			)
			( not
				( and
					( not ( not ( = a_1 b_2 ) ) )
					( >= a_1 0 )
					( not ( >= b_2 0 ) )
					( not ( and ( and ( >= a_1 0 ) ( >= b_2 0 ) ) ( = ( * x_1 y_1 ) ( *   ) ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = a a_1)
					( = b b_2)
					( = x x_1)
					( = y y_1)
				)
			)
			( not
				( and
					( not ( not ( = a_1 b_2 ) ) )
					( not ( >= a_1 0 ) )
					( not ( and ( and ( >= a_1 0 ) ( >= b_2 0 ) ) ( = ( * x_1 y_1 ) ( *   ) ) ) )
				)
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f a b x y a_0 a_1 b_0 b_1 b_2 b_3 x_0 x_1 y_0 y_1  )
		( inv-f a b x y )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f a b x y )
			( trans-f a b x y a! b! x! y! a_0 a_1 b_0 b_1 b_2 b_3 x_0 x_1 y_0 y_1 )
		)
		( inv-f a! b! x! y! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f a b x y  )
		( post-f a b x y a_0 a_1 b_0 b_1 b_2 b_3 x_0 x_1 y_0 y_1 )
	)
))

