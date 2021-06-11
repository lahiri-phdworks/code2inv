(set-logic LIA)

( declare-const a Int )
( declare-const a! Int )
( declare-const b Int )
( declare-const b! Int )
( declare-const start Int )
( declare-const start! Int )
( declare-const x Int )
( declare-const x! Int )
( declare-const y Int )
( declare-const y! Int )

( declare-const a_0 Int )
( declare-const a_1 Int )
( declare-const b_0 Int )
( declare-const b_1 Int )
( declare-const start_0 Int )
( declare-const start_1 Int )
( declare-const start_2 Int )
( declare-const start_3 Int )
( declare-const x_0 Int )
( declare-const x_1 Int )
( declare-const y_0 Int )
( declare-const y_1 Int )

( define-fun inv-f( ( a Int )( b Int )( start Int )( x Int )( y Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( a Int )( b Int )( start Int )( x Int )( y Int )( a_0 Int )( a_1 Int )( b_0 Int )( b_1 Int )( start_0 Int )( start_1 Int )( start_2 Int )( start_3 Int )( x_0 Int )( x_1 Int )( y_0 Int )( y_1 Int ) ) Bool
	( and
		( = a a_1 )
		( = b b_1 )
		( = start start_1 )
		( = x x_1 )
		( = y y_1 )
		( = a_1 10 )
		( = b_1 15 )
		( = x_1 a_1 )
		( = y_1 b_1 )
		( = start_1 a_1 )
		( > a_1 0 )
		( > b_1 0 )
	)
)

( define-fun trans-f ( ( a Int )( b Int )( start Int )( x Int )( y Int )( a! Int )( b! Int )( start! Int )( x! Int )( y! Int )( a_0 Int )( a_1 Int )( b_0 Int )( b_1 Int )( start_0 Int )( start_1 Int )( start_2 Int )( start_3 Int )( x_0 Int )( x_1 Int )( y_0 Int )( y_1 Int ) ) Bool
	( or
		( and
			( = start_2 start )
			( = start_2 start! )
			( = b b_1 )
			( = b! b_1 )
			( = a a! )
			( = x x! )
			( = y y! )
		)
		( and
			( = start_2 start )
			( not ( = ( mod start_2 b_1 ) 0 ) )
			( = start_3 ( + start_2 a_1 ) )
			( = start_3 start! )
			(= a a_1 )
			(= a! a_1 )
			(= b b_1 )
			(= b! b_1 )
			(= x x_1 )
			(= x! x_1 )
			(= y y_1 )
			(= y! y_1 )
		)
	)
)

( define-fun post-f ( ( a Int )( b Int )( start Int )( x Int )( y Int )( a_0 Int )( a_1 Int )( b_0 Int )( b_1 Int )( start_0 Int )( start_1 Int )( start_2 Int )( start_3 Int )( x_0 Int )( x_1 Int )( y_0 Int )( y_1 Int ) ) Bool
	( and
		( or
			( not
				( and
					( = a a_1)
					( = b b_1)
					( = start start_2)
					( = x x_1)
					( = y y_1)
				)
			)
			( not
				( and
					( not ( not ( = ( mod start_2 b_1 ) 0 ) ) )
					( >= a_1 0 )
					( >= b_1 0 )
					( not ( and ( and ( >= a_1 0 ) ( >= b_1 0 ) ) ( = start_2  ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = a a_1)
					( = b b_1)
					( = start start_2)
					( = x x_1)
					( = y y_1)
				)
			)
			( not
				( and
					( not ( not ( = ( mod start_2 b_1 ) 0 ) ) )
					( >= a_1 0 )
					( not ( >= b_1 0 ) )
					( not ( and ( and ( >= a_1 0 ) ( >= b_1 0 ) ) ( = start_2  ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = a a_1)
					( = b b_1)
					( = start start_2)
					( = x x_1)
					( = y y_1)
				)
			)
			( not
				( and
					( not ( not ( = ( mod start_2 b_1 ) 0 ) ) )
					( not ( >= a_1 0 ) )
					( not ( and ( and ( >= a_1 0 ) ( >= b_1 0 ) ) ( = start_2  ) ) )
				)
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f a b start x y a_0 a_1 b_0 b_1 start_0 start_1 start_2 start_3 x_0 x_1 y_0 y_1  )
		( inv-f a b start x y )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f a b start x y )
			( trans-f a b start x y a! b! start! x! y! a_0 a_1 b_0 b_1 start_0 start_1 start_2 start_3 x_0 x_1 y_0 y_1 )
		)
		( inv-f a! b! start! x! y! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f a b start x y  )
		( post-f a b start x y a_0 a_1 b_0 b_1 start_0 start_1 start_2 start_3 x_0 x_1 y_0 y_1 )
	)
))

