(set-logic LIA)

( declare-const temp_x Int )
( declare-const temp_x! Int )
( declare-const temp_y Int )
( declare-const temp_y! Int )
( declare-const x Int )
( declare-const x! Int )
( declare-const y Int )
( declare-const y! Int )

( declare-const temp_x_0 Int )
( declare-const temp_x_1 Int )
( declare-const temp_y_0 Int )
( declare-const temp_y_1 Int )
( declare-const x_0 Int )
( declare-const x_1 Int )
( declare-const x_2 Int )
( declare-const y_0 Int )
( declare-const y_1 Int )
( declare-const y_2 Int )
( declare-const y_3 Int )

( define-fun inv-f( ( temp_x Int )( temp_y Int )( x Int )( y Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( temp_x Int )( temp_y Int )( x Int )( y Int )( temp_x_0 Int )( temp_x_1 Int )( temp_y_0 Int )( temp_y_1 Int )( x_0 Int )( x_1 Int )( x_2 Int )( y_0 Int )( y_1 Int )( y_2 Int )( y_3 Int ) ) Bool
	( or
		( and
			( = x x_0 )
			( = y y_1 )
			( >= x_0 0 )
			( and ( >= x_0 0 ) ( <= x_0 10 ) )
			( = y_1 ( * x_0 x_0 ) )
		)
		( and
			( = x x_0 )
			( = y y_1 )
			( not ( >= x_0 0 ) )
			( and ( >= x_0 0 ) ( <= x_0 10 ) )
			( = y_1 ( * x_0 x_0 ) )
		)
	)
)

( define-fun trans-f ( ( temp_x Int )( temp_y Int )( x Int )( y Int )( temp_x! Int )( temp_y! Int )( x! Int )( y! Int )( temp_x_0 Int )( temp_x_1 Int )( temp_y_0 Int )( temp_y_1 Int )( x_0 Int )( x_1 Int )( x_2 Int )( y_0 Int )( y_1 Int )( y_2 Int )( y_3 Int ) ) Bool
	( or
		( and
			( = temp_x_0 temp_x )
			( = temp_y_0 temp_y )
			( = x_1 x )
			( = y_2 y )
			( = temp_x_0 temp_x! )
			( = temp_y_0 temp_y! )
			( = x_1 x! )
			( = y_2 y! )
			( = temp_x temp_x! )
			( = temp_y temp_y! )
			( = y y! )
		)
		( and
			( = temp_x_0 temp_x )
			( = temp_y_0 temp_y )
			( = x_1 x )
			( = y_2 y )
			( <= ( * x_1 x_1 ) 1000 )
			( = temp_x_1 x_1 )
			( = temp_y_1 y_2 )
			( = x_2 ( + x_1 1 ) )
			( = y_3 ( + y_2 1 ) )
			( = temp_x_1 temp_x! )
			( = temp_y_1 temp_y! )
			( = x_2 x! )
			( = y_3 y! )
		)
	)
)

( define-fun post-f ( ( temp_x Int )( temp_y Int )( x Int )( y Int )( temp_x_0 Int )( temp_x_1 Int )( temp_y_0 Int )( temp_y_1 Int )( x_0 Int )( x_1 Int )( x_2 Int )( y_0 Int )( y_1 Int )( y_2 Int )( y_3 Int ) ) Bool
	( or
		( not
			( and
				( = temp_x temp_x_0)
				( = temp_y temp_y_0)
				( = x x_1)
				( = y y_2)
			)
		)
		( not
			( and
				( not ( <= ( * x_1 x_1 ) 1000 ) )
				( not ( <= y_2 1000 ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f temp_x temp_y x y temp_x_0 temp_x_1 temp_y_0 temp_y_1 x_0 x_1 x_2 y_0 y_1 y_2 y_3  )
		( inv-f temp_x temp_y x y )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f temp_x temp_y x y )
			( trans-f temp_x temp_y x y temp_x! temp_y! x! y! temp_x_0 temp_x_1 temp_y_0 temp_y_1 x_0 x_1 x_2 y_0 y_1 y_2 y_3 )
		)
		( inv-f temp_x! temp_y! x! y! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f temp_x temp_y x y  )
		( post-f temp_x temp_y x y temp_x_0 temp_x_1 temp_y_0 temp_y_1 x_0 x_1 x_2 y_0 y_1 y_2 y_3 )
	)
))

