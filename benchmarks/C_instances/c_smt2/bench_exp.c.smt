(set-logic LIA)

( declare-const a Int )
( declare-const a! Int )
( declare-const b Int )
( declare-const b! Int )
( declare-const res Int )
( declare-const res! Int )
( declare-const x Int )
( declare-const x! Int )
( declare-const y Int )
( declare-const y! Int )

( declare-const a_0 Int )
( declare-const a_1 Int )
( declare-const a_2 Int )
( declare-const a_3 Int )
( declare-const b_0 Int )
( declare-const b_1 Int )
( declare-const b_2 Int )
( declare-const res_0 Int )
( declare-const res_1 Int )
( declare-const res_2 Int )
( declare-const res_3 Int )
( declare-const res_4 Int )
( declare-const x_0 Int )
( declare-const x_1 Int )
( declare-const y_0 Int )
( declare-const y_1 Int )

( define-fun inv-f( ( a Int )( b Int )( res Int )( x Int )( y Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( a Int )( b Int )( res Int )( x Int )( y Int )( a_0 Int )( a_1 Int )( a_2 Int )( a_3 Int )( b_0 Int )( b_1 Int )( b_2 Int )( res_0 Int )( res_1 Int )( res_2 Int )( res_3 Int )( res_4 Int )( x_0 Int )( x_1 Int )( y_0 Int )( y_1 Int ) ) Bool
	( and
		( = a a_1 )
		( = b b_1 )
		( = res res_1 )
		( = x x_1 )
		( = y y_1 )
		( = a_1 5 )
		( = b_1 3 )
		( = x_1 a_1 )
		( = y_1 b_1 )
		( = res_1 1 )
	)
)

( define-fun trans-f ( ( a Int )( b Int )( res Int )( x Int )( y Int )( a! Int )( b! Int )( res! Int )( x! Int )( y! Int )( a_0 Int )( a_1 Int )( a_2 Int )( a_3 Int )( b_0 Int )( b_1 Int )( b_2 Int )( res_0 Int )( res_1 Int )( res_2 Int )( res_3 Int )( res_4 Int )( x_0 Int )( x_1 Int )( y_0 Int )( y_1 Int ) ) Bool
	( or
		( and
			( = a_2 a )
			( = res_2 res )
			( = a_2 a! )
			( = res_2 res! )
			( = b b_1 )
			( = b! b_1 )
			( = a a! )
			( = res res! )
			( = x x! )
			( = y y! )
		)
		( and
			( = a_2 a )
			( = res_2 res )
			( > b_1 0 )
			( & b_1 1 )
			( = res_3 ( * res_2 a_2 ) )
			( = res_4 res_3 )
			( = a_3 ( * a_2 a_2 ) )
			( = a_3 a! )
			( = res_4 res! )
			(= b b_1 )
			(= b! b_1 )
			(= x x_1 )
			(= x! x_1 )
			(= y y_1 )
			(= y! y_1 )
		)
		( and
			( = a_2 a )
			( = res_2 res )
			( > b_1 0 )
			( not ( & b_1 1 ) )
			( = res_4 res_2 )
			( = a_3 ( * a_2 a_2 ) )
			( = a_3 a! )
			( = res_4 res! )
			(= b b_1 )
			(= b! b_1 )
			(= x x_1 )
			(= x! x_1 )
			(= y y_1 )
			(= y! y_1 )
		)
	)
)

( define-fun post-f ( ( a Int )( b Int )( res Int )( x Int )( y Int )( a_0 Int )( a_1 Int )( a_2 Int )( a_3 Int )( b_0 Int )( b_1 Int )( b_2 Int )( res_0 Int )( res_1 Int )( res_2 Int )( res_3 Int )( res_4 Int )( x_0 Int )( x_1 Int )( y_0 Int )( y_1 Int ) ) Bool
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f a b res x y a_0 a_1 a_2 a_3 b_0 b_1 b_2 res_0 res_1 res_2 res_3 res_4 x_0 x_1 y_0 y_1  )
		( inv-f a b res x y )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f a b res x y )
			( trans-f a b res x y a! b! res! x! y! a_0 a_1 a_2 a_3 b_0 b_1 b_2 res_0 res_1 res_2 res_3 res_4 x_0 x_1 y_0 y_1 )
		)
		( inv-f a! b! res! x! y! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f a b res x y  )
		( post-f a b res x y a_0 a_1 a_2 a_3 b_0 b_1 b_2 res_0 res_1 res_2 res_3 res_4 x_0 x_1 y_0 y_1 )
	)
))

