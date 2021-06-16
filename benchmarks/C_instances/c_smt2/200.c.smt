(set-logic LIA)

( declare-const a Int )
( declare-const a! Int )
( declare-const b Int )
( declare-const b! Int )
( declare-const i Int )
( declare-const i! Int )
( declare-const r Int )
( declare-const r! Int )
( declare-const x Int )
( declare-const x! Int )
( declare-const y Int )
( declare-const y! Int )

( declare-const a_0 Int )
( declare-const b_0 Int )
( declare-const b_1 Int )
( declare-const b_2 Int )
( declare-const i_0 Int )
( declare-const i_1 Int )
( declare-const i_2 Int )
( declare-const i_3 Int )
( declare-const r_0 Int )
( declare-const r_1 Int )
( declare-const r_2 Int )
( declare-const r_3 Int )
( declare-const x_0 Int )
( declare-const x_1 Int )
( declare-const y_0 Int )
( declare-const y_1 Int )

( define-fun inv-f( ( a Int )( b Int )( i Int )( r Int )( x Int )( y Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( a Int )( b Int )( i Int )( r Int )( x Int )( y Int )( a_0 Int )( b_0 Int )( b_1 Int )( b_2 Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( r_0 Int )( r_1 Int )( r_2 Int )( r_3 Int )( x_0 Int )( x_1 Int )( y_0 Int )( y_1 Int ) ) Bool
	( and
		( = a a_0 )
		( = b b_0 )
		( = i i_1 )
		( = r r_1 )
		( = x x_1 )
		( = y y_1 )
		( >= a_0 0 )
		( >= b_0 0 )
		( = x_1 a_0 )
		( = y_1 b_0 )
		( = r_1 0 )
		( = i_1 0 )
	)
)

( define-fun trans-f ( ( a Int )( b Int )( i Int )( r Int )( x Int )( y Int )( a! Int )( b! Int )( i! Int )( r! Int )( x! Int )( y! Int )( a_0 Int )( b_0 Int )( b_1 Int )( b_2 Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( r_0 Int )( r_1 Int )( r_2 Int )( r_3 Int )( x_0 Int )( x_1 Int )( y_0 Int )( y_1 Int ) ) Bool
	( or
		( and
			( = b_1 b )
			( = i_2 i )
			( = r_2 r )
			( = b_1 b! )
			( = i_2 i! )
			( = r_2 r! )
			( = a a! )
			( = i i! )
			( = r r! )
			( = x x! )
			( = y y! )
		)
		( and
			( = b_1 b )
			( = i_2 i )
			( = r_2 r )
			( not ( = b_1 0 ) )
			( = r_3 ( + r_2 a_0 ) )
			( = b_2 ( - b_1 1 ) )
			( = i_3 ( + i_2 1 ) )
			( = b_2 b! )
			( = i_3 i! )
			( = r_3 r! )
			(= a a_0 )
			(= a! a_0 )
			(= x x_1 )
			(= x! x_1 )
			(= y y_1 )
			(= y! y_1 )
		)
	)
)

( define-fun post-f ( ( a Int )( b Int )( i Int )( r Int )( x Int )( y Int )( a_0 Int )( b_0 Int )( b_1 Int )( b_2 Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( r_0 Int )( r_1 Int )( r_2 Int )( r_3 Int )( x_0 Int )( x_1 Int )( y_0 Int )( y_1 Int ) ) Bool
	( or
		( not
			( and
				( = a a_0)
				( = b b_1)
				( = i i_2)
				( = r r_2)
				( = x x_1)
				( = y y_1)
			)
		)
		( not
			( and
				( not ( not ( = b_1 0 ) ) )
				( not ( = r_2 ( * x_1 y_1 ) ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f a b i r x y a_0 b_0 b_1 b_2 i_0 i_1 i_2 i_3 r_0 r_1 r_2 r_3 x_0 x_1 y_0 y_1  )
		( inv-f a b i r x y )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f a b i r x y )
			( trans-f a b i r x y a! b! i! r! x! y! a_0 b_0 b_1 b_2 i_0 i_1 i_2 i_3 r_0 r_1 r_2 r_3 x_0 x_1 y_0 y_1 )
		)
		( inv-f a! b! i! r! x! y! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f a b i r x y  )
		( post-f a b i r x y a_0 b_0 b_1 b_2 i_0 i_1 i_2 i_3 r_0 r_1 r_2 r_3 x_0 x_1 y_0 y_1 )
	)
))

