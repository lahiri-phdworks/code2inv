(set-logic LIA)

( declare-const temp_w Int )
( declare-const temp_w! Int )
( declare-const temp_x Int )
( declare-const temp_x! Int )
( declare-const temp_z Int )
( declare-const temp_z! Int )
( declare-const w Int )
( declare-const w! Int )
( declare-const x Int )
( declare-const x! Int )
( declare-const z Int )
( declare-const z! Int )
( declare-const tmp Int )
( declare-const tmp! Int )

( declare-const temp_w_0 Int )
( declare-const temp_w_1 Int )
( declare-const temp_x_0 Int )
( declare-const temp_x_1 Int )
( declare-const temp_z_0 Int )
( declare-const temp_z_1 Int )
( declare-const w_0 Int )
( declare-const w_1 Int )
( declare-const w_2 Int )
( declare-const x_0 Int )
( declare-const z_0 Int )
( declare-const z_1 Int )
( declare-const z_2 Int )
( declare-const z_3 Int )

( define-fun inv-f( ( temp_w Int )( temp_x Int )( temp_z Int )( w Int )( x Int )( z Int )( tmp Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( temp_w Int )( temp_x Int )( temp_z Int )( w Int )( x Int )( z Int )( tmp Int )( temp_w_0 Int )( temp_w_1 Int )( temp_x_0 Int )( temp_x_1 Int )( temp_z_0 Int )( temp_z_1 Int )( w_0 Int )( w_1 Int )( w_2 Int )( x_0 Int )( z_0 Int )( z_1 Int )( z_2 Int )( z_3 Int ) ) Bool
	( and
		( = w w_0 )
		( = x x_0 )
		( = z z_1 )
		( = z_1 ( * w_0 x_0 ) )
	)
)

( define-fun trans-f ( ( temp_w Int )( temp_x Int )( temp_z Int )( w Int )( x Int )( z Int )( tmp Int )( temp_w! Int )( temp_x! Int )( temp_z! Int )( w! Int )( x! Int )( z! Int )( tmp! Int )( temp_w_0 Int )( temp_w_1 Int )( temp_x_0 Int )( temp_x_1 Int )( temp_z_0 Int )( temp_z_1 Int )( w_0 Int )( w_1 Int )( w_2 Int )( x_0 Int )( z_0 Int )( z_1 Int )( z_2 Int )( z_3 Int ) ) Bool
	( or
		( and
			( = temp_w_0 temp_w )
			( = temp_x_0 temp_x )
			( = temp_z_0 temp_z )
			( = w_1 w )
			( = z_2 z )
			( = temp_w_0 temp_w! )
			( = temp_x_0 temp_x! )
			( = temp_z_0 temp_z! )
			( = w_1 w! )
			( = z_2 z! )
			( = temp_w temp_w! )
			( = temp_x temp_x! )
			( = temp_z temp_z! )
			( = w w! )
			( = x x! )
			( = z z! )
			(= tmp tmp! )
		)
		( and
			( not ( = z_2 ( * w_1 x_0 ) ) )
			(= temp_w temp_w_0 )
			(= temp_w! temp_w_0 )
			(= temp_x temp_x_0 )
			(= temp_x! temp_x_0 )
			(= temp_z temp_z_0 )
			(= temp_z! temp_z_0 )
			(= w w_0 )
			(= w! w_0 )
			(= x x_0 )
			(= x! x_0 )
			(= z z_1 )
			(= z! z_1 )
			(= tmp tmp! )
		)
	)
)

( define-fun post-f ( ( temp_w Int )( temp_x Int )( temp_z Int )( w Int )( x Int )( z Int )( tmp Int )( temp_w_0 Int )( temp_w_1 Int )( temp_x_0 Int )( temp_x_1 Int )( temp_z_0 Int )( temp_z_1 Int )( w_0 Int )( w_1 Int )( w_2 Int )( x_0 Int )( z_0 Int )( z_1 Int )( z_2 Int )( z_3 Int ) ) Bool
	( or
		( not
			( and
				( = temp_w temp_w_0)
				( = temp_x temp_x_0)
				( = temp_z temp_z_0)
				( = w w_1)
				( = x x_0)
				( = z z_2)
			)
		)
		( not
			( and
				( = temp_w_1 w_1 )
				( = temp_x_1 x_0 )
				( = temp_z_1 z_2 )
				( = w_2  )
				( = z_3  )
				( = temp_w_0 temp_w_1 )
				( = temp_x_0 temp_x_1 )
				( = temp_z_0 temp_z_1 )
				( = w_1 w_2 )
				( = z_2 z_3 )
				( not ( = z_2 ( * w_1 x_0 ) ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f temp_w temp_x temp_z w x z tmp temp_w_0 temp_w_1 temp_x_0 temp_x_1 temp_z_0 temp_z_1 w_0 w_1 w_2 x_0 z_0 z_1 z_2 z_3  )
		( inv-f temp_w temp_x temp_z w x z tmp )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f temp_w temp_x temp_z w x z tmp )
			( trans-f temp_w temp_x temp_z w x z tmp temp_w! temp_x! temp_z! w! x! z! tmp! temp_w_0 temp_w_1 temp_x_0 temp_x_1 temp_z_0 temp_z_1 w_0 w_1 w_2 x_0 z_0 z_1 z_2 z_3 )
		)
		( inv-f temp_w! temp_x! temp_z! w! x! z! tmp! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f temp_w temp_x temp_z w x z tmp  )
		( post-f temp_w temp_x temp_z w x z tmp temp_w_0 temp_w_1 temp_x_0 temp_x_1 temp_z_0 temp_z_1 w_0 w_1 w_2 x_0 z_0 z_1 z_2 z_3 )
	)
))

