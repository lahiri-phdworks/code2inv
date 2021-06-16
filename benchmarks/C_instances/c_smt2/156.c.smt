(set-logic LIA)

( declare-const a Int )
( declare-const a! Int )
( declare-const b Int )
( declare-const b! Int )
( declare-const r Int )
( declare-const r! Int )

( declare-const a_0 Int )
( declare-const a_1 Int )
( declare-const a_2 Int )
( declare-const a_3 Int )
( declare-const b_0 Int )
( declare-const b_1 Int )
( declare-const b_2 Int )
( declare-const b_3 Int )
( declare-const r_0 Int )
( declare-const r_1 Int )

( define-fun inv-f( ( a Int )( b Int )( r Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( a Int )( b Int )( r Int )( a_0 Int )( a_1 Int )( a_2 Int )( a_3 Int )( b_0 Int )( b_1 Int )( b_2 Int )( b_3 Int )( r_0 Int )( r_1 Int ) ) Bool
	( and
		( = a a_0 )
		( = b b_0 )
		( = r r_0 )
		( > a_0 0 )
		( > b_0 0 )
		( > r_0 0 )
		( = ( mod a_0 r_0 ) 0 )
		( = ( mod b_0 r_0 ) 0 )
	)
)

( define-fun trans-f ( ( a Int )( b Int )( r Int )( a! Int )( b! Int )( r! Int )( a_0 Int )( a_1 Int )( a_2 Int )( a_3 Int )( b_0 Int )( b_1 Int )( b_2 Int )( b_3 Int )( r_0 Int )( r_1 Int ) ) Bool
	( or
		( and
			( = a_1 a )
			( = b_1 b )
			( = a_1 a! )
			( = b_1 b! )
			( = a a! )
			( = r r! )
		)
		( and
			( = a_1 a )
			( = b_1 b )
			( not ( = b_1 0 ) )
			( > a_1 b_1 )
			( = a_2 ( - a_1 b_1 ) )
			( = a_3 a_2 )
			( = b_2 b_1 )
			( = a_3 a! )
			( = b_2 b! )
			(= r r_0 )
			(= r! r_0 )
		)
		( and
			( = a_1 a )
			( = b_1 b )
			( not ( = b_1 0 ) )
			( not ( > a_1 b_1 ) )
			( = b_3 ( - b_1 a_1 ) )
			( = a_3 a_1 )
			( = b_2 b_3 )
			( = a_3 a! )
			( = b_2 b! )
			(= r r_0 )
			(= r! r_0 )
		)
	)
)

( define-fun post-f ( ( a Int )( b Int )( r Int )( a_0 Int )( a_1 Int )( a_2 Int )( a_3 Int )( b_0 Int )( b_1 Int )( b_2 Int )( b_3 Int )( r_0 Int )( r_1 Int ) ) Bool
	( and
		( or
			( not
				( and
					( = a a_1)
					( = b b_1)
					( = r r_0)
				)
			)
			( not
				( and
					( not ( not ( = b_1 0 ) ) )
					( = r_1 a_1 )
					( = ( mod a_1 r_1 ) 0 )
					( not ( and ( = ( mod a_1 r_1 ) 0 ) ( > r_1 0 ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = a a_1)
					( = b b_1)
					( = r r_0)
				)
			)
			( not
				( and
					( not ( not ( = b_1 0 ) ) )
					( = r_1 a_1 )
					( not ( = ( mod a_1 r_1 ) 0 ) )
					( not ( and ( = ( mod a_1 r_1 ) 0 ) ( > r_1 0 ) ) )
				)
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f a b r a_0 a_1 a_2 a_3 b_0 b_1 b_2 b_3 r_0 r_1  )
		( inv-f a b r )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f a b r )
			( trans-f a b r a! b! r! a_0 a_1 a_2 a_3 b_0 b_1 b_2 b_3 r_0 r_1 )
		)
		( inv-f a! b! r! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f a b r  )
		( post-f a b r a_0 a_1 a_2 a_3 b_0 b_1 b_2 b_3 r_0 r_1 )
	)
))

