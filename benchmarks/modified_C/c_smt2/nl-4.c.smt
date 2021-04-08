(set-logic LIA)

( declare-const temp_x Int )
( declare-const temp_x! Int )
( declare-const temp_y Int )
( declare-const temp_y! Int )
( declare-const temp_z Int )
( declare-const temp_z! Int )
( declare-const x Int )
( declare-const x! Int )
( declare-const y Int )
( declare-const y! Int )
( declare-const z Int )
( declare-const z! Int )

( declare-const temp_x_0 Int )
( declare-const temp_x_1 Int )
( declare-const temp_y_0 Int )
( declare-const temp_y_1 Int )
( declare-const temp_z_0 Int )
( declare-const temp_z_1 Int )
( declare-const x_0 Int )
( declare-const x_1 Int )
( declare-const x_2 Int )
( declare-const y_0 Int )
( declare-const z_0 Int )
( declare-const z_1 Int )
( declare-const z_2 Int )
( declare-const z_3 Int )

( define-fun inv-f( ( temp_x Int )( temp_y Int )( temp_z Int )( x Int )( y Int )( z Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( temp_x Int )( temp_y Int )( temp_z Int )( x Int )( y Int )( z Int )( temp_x_0 Int )( temp_x_1 Int )( temp_y_0 Int )( temp_y_1 Int )( temp_z_0 Int )( temp_z_1 Int )( x_0 Int )( x_1 Int )( x_2 Int )( y_0 Int )( z_0 Int )( z_1 Int )( z_2 Int )( z_3 Int ) ) Bool
	( or
		( and
			( = x x_0 )
			( = y y_0 )
			( = z z_1 )
			( >= x_0 0 )
			( and ( >= x_0 0 ) ( >= y_0 0 ) )
			( = z_1 ( * x_0 y_0 ) )
		)
		( and
			( = x x_0 )
			( = y y_0 )
			( = z z_1 )
			( not ( >= x_0 0 ) )
			( and ( >= x_0 0 ) ( >= y_0 0 ) )
			( = z_1 ( * x_0 y_0 ) )
		)
	)
)

( define-fun trans-f ( ( temp_x Int )( temp_y Int )( temp_z Int )( x Int )( y Int )( z Int )( temp_x! Int )( temp_y! Int )( temp_z! Int )( x! Int )( y! Int )( z! Int )( temp_x_0 Int )( temp_x_1 Int )( temp_y_0 Int )( temp_y_1 Int )( temp_z_0 Int )( temp_z_1 Int )( x_0 Int )( x_1 Int )( x_2 Int )( y_0 Int )( z_0 Int )( z_1 Int )( z_2 Int )( z_3 Int ) ) Bool
	( or
		( and
			( = temp_x_0 temp_x )
			( = temp_y_0 temp_y )
			( = temp_z_0 temp_z )
			( = x_1 x )
			( = z_2 z )
			( = temp_x_0 temp_x! )
			( = temp_y_0 temp_y! )
			( = temp_z_0 temp_z! )
			( = x_1 x! )
			( = z_2 z! )
			( = temp_x temp_x! )
			( = temp_y temp_y! )
			( = temp_z temp_z! )
			( = y y! )
			( = z z! )
		)
		( and
			( = temp_x_0 temp_x )
			( = temp_y_0 temp_y )
			( = temp_z_0 temp_z )
			( = x_1 x )
			( = z_2 z )
			( > x_1 0 )
			( = temp_x_1 x_1 )
			( = temp_y_1 y_0 )
			( = temp_z_1 z_2 )
			( = x_2  )
			( = z_3  )
			( = temp_x_1 temp_x! )
			( = temp_y_1 temp_y! )
			( = temp_z_1 temp_z! )
			( = x_2 x! )
			( = z_3 z! )
			(= y y_0 )
			(= y! y_0 )
		)
	)
)

( define-fun post-f ( ( temp_x Int )( temp_y Int )( temp_z Int )( x Int )( y Int )( z Int )( temp_x_0 Int )( temp_x_1 Int )( temp_y_0 Int )( temp_y_1 Int )( temp_z_0 Int )( temp_z_1 Int )( x_0 Int )( x_1 Int )( x_2 Int )( y_0 Int )( z_0 Int )( z_1 Int )( z_2 Int )( z_3 Int ) ) Bool
	( or
		( not
			( and
				( = temp_x temp_x_0)
				( = temp_y temp_y_0)
				( = temp_z temp_z_0)
				( = x x_1)
				( = y y_0)
				( = z z_2)
			)
		)
		( not
			( and
				( not ( > x_1 0 ) )
				( not ( = z_2 0 ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f temp_x temp_y temp_z x y z temp_x_0 temp_x_1 temp_y_0 temp_y_1 temp_z_0 temp_z_1 x_0 x_1 x_2 y_0 z_0 z_1 z_2 z_3  )
		( inv-f temp_x temp_y temp_z x y z )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f temp_x temp_y temp_z x y z )
			( trans-f temp_x temp_y temp_z x y z temp_x! temp_y! temp_z! x! y! z! temp_x_0 temp_x_1 temp_y_0 temp_y_1 temp_z_0 temp_z_1 x_0 x_1 x_2 y_0 z_0 z_1 z_2 z_3 )
		)
		( inv-f temp_x! temp_y! temp_z! x! y! z! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f temp_x temp_y temp_z x y z  )
		( post-f temp_x temp_y temp_z x y z temp_x_0 temp_x_1 temp_y_0 temp_y_1 temp_z_0 temp_z_1 x_0 x_1 x_2 y_0 z_0 z_1 z_2 z_3 )
	)
))

