(set-logic LIA)

( declare-const temp_w Int )
( declare-const temp_w! Int )
( declare-const temp_x Int )
( declare-const temp_x! Int )
( declare-const temp_y Int )
( declare-const temp_y! Int )
( declare-const temp_z Int )
( declare-const temp_z! Int )
( declare-const w Int )
( declare-const w! Int )
( declare-const x Int )
( declare-const x! Int )
( declare-const y Int )
( declare-const y! Int )
( declare-const z Int )
( declare-const z! Int )

( declare-const temp_w_0 Int )
( declare-const temp_w_1 Int )
( declare-const temp_x_0 Int )
( declare-const temp_x_1 Int )
( declare-const temp_y_0 Int )
( declare-const temp_y_1 Int )
( declare-const temp_z_0 Int )
( declare-const temp_z_1 Int )
( declare-const w_0 Int )
( declare-const w_1 Int )
( declare-const w_2 Int )
( declare-const w_3 Int )
( declare-const x_0 Int )
( declare-const y_0 Int )
( declare-const z_0 Int )
( declare-const z_1 Int )
( declare-const z_2 Int )
( declare-const z_3 Int )

( define-fun inv-f( ( temp_w Int )( temp_x Int )( temp_y Int )( temp_z Int )( w Int )( x Int )( y Int )( z Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( temp_w Int )( temp_x Int )( temp_y Int )( temp_z Int )( w Int )( x Int )( y Int )( z Int )( temp_w_0 Int )( temp_w_1 Int )( temp_x_0 Int )( temp_x_1 Int )( temp_y_0 Int )( temp_y_1 Int )( temp_z_0 Int )( temp_z_1 Int )( w_0 Int )( w_1 Int )( w_2 Int )( w_3 Int )( x_0 Int )( y_0 Int )( z_0 Int )( z_1 Int )( z_2 Int )( z_3 Int ) ) Bool
	( or
		( and
			( = w w_1 )
			( = x x_0 )
			( = y y_0 )
			( = z z_1 )
			( >= x_0 0 )
			( and ( >= x_0 0 ) ( >= y_0 x_0 ) )
			( = z_1 0 )
			( = w_1 0 )
		)
		( and
			( = w w_1 )
			( = x x_0 )
			( = y y_0 )
			( = z z_1 )
			( not ( >= x_0 0 ) )
			( and ( >= x_0 0 ) ( >= y_0 x_0 ) )
			( = z_1 0 )
			( = w_1 0 )
		)
	)
)

( define-fun trans-f ( ( temp_w Int )( temp_x Int )( temp_y Int )( temp_z Int )( w Int )( x Int )( y Int )( z Int )( temp_w! Int )( temp_x! Int )( temp_y! Int )( temp_z! Int )( w! Int )( x! Int )( y! Int )( z! Int )( temp_w_0 Int )( temp_w_1 Int )( temp_x_0 Int )( temp_x_1 Int )( temp_y_0 Int )( temp_y_1 Int )( temp_z_0 Int )( temp_z_1 Int )( w_0 Int )( w_1 Int )( w_2 Int )( w_3 Int )( x_0 Int )( y_0 Int )( z_0 Int )( z_1 Int )( z_2 Int )( z_3 Int ) ) Bool
	( or
		( and
			( = temp_w_0 temp_w )
			( = temp_x_0 temp_x )
			( = temp_y_0 temp_y )
			( = temp_z_0 temp_z )
			( = w_2 w )
			( = z_2 z )
			( = temp_w_0 temp_w! )
			( = temp_x_0 temp_x! )
			( = temp_y_0 temp_y! )
			( = temp_z_0 temp_z! )
			( = w_2 w! )
			( = z_2 z! )
			( = y y_0 )
			( = y! y_0 )
			( = temp_w temp_w! )
			( = temp_x temp_x! )
			( = temp_y temp_y! )
			( = temp_z temp_z! )
			( = x x! )
			( = z z! )
		)
		( and
			( not ( < w_2 y_0 ) )
			( not ( = z_2 ( * x_0 y_0 ) ) )
			(= temp_w temp_w_0 )
			(= temp_w! temp_w_0 )
			(= temp_x temp_x_0 )
			(= temp_x! temp_x_0 )
			(= temp_y temp_y_0 )
			(= temp_y! temp_y_0 )
			(= temp_z temp_z_0 )
			(= temp_z! temp_z_0 )
			(= w w_1 )
			(= w! w_1 )
			(= x x_0 )
			(= x! x_0 )
			(= y y_0 )
			(= y! y_0 )
			(= z z_1 )
			(= z! z_1 )
		)
	)
)

( define-fun post-f ( ( temp_w Int )( temp_x Int )( temp_y Int )( temp_z Int )( w Int )( x Int )( y Int )( z Int )( temp_w_0 Int )( temp_w_1 Int )( temp_x_0 Int )( temp_x_1 Int )( temp_y_0 Int )( temp_y_1 Int )( temp_z_0 Int )( temp_z_1 Int )( w_0 Int )( w_1 Int )( w_2 Int )( w_3 Int )( x_0 Int )( y_0 Int )( z_0 Int )( z_1 Int )( z_2 Int )( z_3 Int ) ) Bool
	( or
		( not
			( and
				( = temp_w temp_w_0)
				( = temp_x temp_x_0)
				( = temp_y temp_y_0)
				( = temp_z temp_z_0)
				( = w w_2)
				( = x x_0)
				( = y y_0)
				( = z z_2)
			)
		)
		( not
			( and
				( not ( < w_2 y_0 ) )
				( = temp_x_1 x_0 )
				( = temp_y_1 y_0 )
				( = temp_z_1 z_2 )
				( = temp_w_1 w_2 )
				( = z_3  )
				( = w_3  )
				( = temp_w_0 temp_w_1 )
				( = temp_x_0 temp_x_1 )
				( = temp_y_0 temp_y_1 )
				( = temp_z_0 temp_z_1 )
				( = w_2 w_3 )
				( = z_2 z_3 )
				( not ( < w_2 y_0 ) )
				( not ( = z_2 ( * x_0 y_0 ) ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f temp_w temp_x temp_y temp_z w x y z temp_w_0 temp_w_1 temp_x_0 temp_x_1 temp_y_0 temp_y_1 temp_z_0 temp_z_1 w_0 w_1 w_2 w_3 x_0 y_0 z_0 z_1 z_2 z_3  )
		( inv-f temp_w temp_x temp_y temp_z w x y z )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f temp_w temp_x temp_y temp_z w x y z )
			( trans-f temp_w temp_x temp_y temp_z w x y z temp_w! temp_x! temp_y! temp_z! w! x! y! z! temp_w_0 temp_w_1 temp_x_0 temp_x_1 temp_y_0 temp_y_1 temp_z_0 temp_z_1 w_0 w_1 w_2 w_3 x_0 y_0 z_0 z_1 z_2 z_3 )
		)
		( inv-f temp_w! temp_x! temp_y! temp_z! w! x! y! z! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f temp_w temp_x temp_y temp_z w x y z  )
		( post-f temp_w temp_x temp_y temp_z w x y z temp_w_0 temp_w_1 temp_x_0 temp_x_1 temp_y_0 temp_y_1 temp_z_0 temp_z_1 w_0 w_1 w_2 w_3 x_0 y_0 z_0 z_1 z_2 z_3 )
	)
))

