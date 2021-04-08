(set-logic LIA)

( declare-const c Int )
( declare-const c! Int )
( declare-const temp_c Int )
( declare-const temp_c! Int )
( declare-const temp_y Int )
( declare-const temp_y! Int )
( declare-const temp_z Int )
( declare-const temp_z! Int )
( declare-const y Int )
( declare-const y! Int )
( declare-const z Int )
( declare-const z! Int )
( declare-const tmp Int )
( declare-const tmp! Int )

( declare-const c_0 Int )
( declare-const c_1 Int )
( declare-const c_2 Int )
( declare-const c_3 Int )
( declare-const c_4 Int )
( declare-const temp_c_0 Int )
( declare-const temp_c_1 Int )
( declare-const temp_y_0 Int )
( declare-const temp_y_1 Int )
( declare-const temp_z_0 Int )
( declare-const temp_z_1 Int )
( declare-const y_0 Int )
( declare-const z_0 Int )
( declare-const z_1 Int )
( declare-const z_2 Int )
( declare-const z_3 Int )
( declare-const z_4 Int )

( define-fun inv-f( ( c Int )( temp_c Int )( temp_y Int )( temp_z Int )( y Int )( z Int )( tmp Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( c Int )( temp_c Int )( temp_y Int )( temp_z Int )( y Int )( z Int )( tmp Int )( c_0 Int )( c_1 Int )( c_2 Int )( c_3 Int )( c_4 Int )( temp_c_0 Int )( temp_c_1 Int )( temp_y_0 Int )( temp_y_1 Int )( temp_z_0 Int )( temp_z_1 Int )( y_0 Int )( z_0 Int )( z_1 Int )( z_2 Int )( z_3 Int )( z_4 Int ) ) Bool
	( and
		( = c c_1 )
		( = y y_0 )
		( = z z_1 )
		( = c_1 0 )
		( >= y_0 0 )
		( >= y_0 127 )
		( = z_1 ( * 36 y_0 ) )
	)
)

( define-fun trans-f ( ( c Int )( temp_c Int )( temp_y Int )( temp_z Int )( y Int )( z Int )( tmp Int )( c! Int )( temp_c! Int )( temp_y! Int )( temp_z! Int )( y! Int )( z! Int )( tmp! Int )( c_0 Int )( c_1 Int )( c_2 Int )( c_3 Int )( c_4 Int )( temp_c_0 Int )( temp_c_1 Int )( temp_y_0 Int )( temp_y_1 Int )( temp_z_0 Int )( temp_z_1 Int )( y_0 Int )( z_0 Int )( z_1 Int )( z_2 Int )( z_3 Int )( z_4 Int ) ) Bool
	( or
		( and
			( = c_2 c )
			( = temp_c_0 temp_c )
			( = temp_y_0 temp_y )
			( = temp_z_0 temp_z )
			( = z_2 z )
			( = c_2 c! )
			( = temp_c_0 temp_c! )
			( = temp_y_0 temp_y! )
			( = temp_z_0 temp_z! )
			( = z_2 z! )
			( = c c! )
			( = temp_c temp_c! )
			( = temp_y temp_y! )
			( = temp_z temp_z! )
			( = y y! )
			( = z z! )
			(= tmp tmp! )
		)
		( and
			( < c_2 36 )
			( not ( >= z_2 0 ) )
			(= c c_1 )
			(= c! c_1 )
			(= temp_c temp_c_0 )
			(= temp_c! temp_c_0 )
			(= temp_y temp_y_0 )
			(= temp_y! temp_y_0 )
			(= temp_z temp_z_0 )
			(= temp_z! temp_z_0 )
			(= y y_0 )
			(= y! y_0 )
			(= z z_1 )
			(= z! z_1 )
			(= tmp tmp! )
		)
		( and
			( not ( < c_2 36 ) )
			(= c c_1 )
			(= c! c_1 )
			(= temp_c temp_c_0 )
			(= temp_c! temp_c_0 )
			(= temp_y temp_y_0 )
			(= temp_y! temp_y_0 )
			(= temp_z temp_z_0 )
			(= temp_z! temp_z_0 )
			(= y y_0 )
			(= y! y_0 )
			(= z z_1 )
			(= z! z_1 )
			(= tmp tmp! )
		)
	)
)

( define-fun post-f ( ( c Int )( temp_c Int )( temp_y Int )( temp_z Int )( y Int )( z Int )( tmp Int )( c_0 Int )( c_1 Int )( c_2 Int )( c_3 Int )( c_4 Int )( temp_c_0 Int )( temp_c_1 Int )( temp_y_0 Int )( temp_y_1 Int )( temp_z_0 Int )( temp_z_1 Int )( y_0 Int )( z_0 Int )( z_1 Int )( z_2 Int )( z_3 Int )( z_4 Int ) ) Bool
	( and
		( or
			( not
				( and
					( = c c_2)
					( = temp_c temp_c_0)
					( = temp_y temp_y_0)
					( = temp_z temp_z_0)
					( = y y_0)
					( = z z_2)
				)
			)
			( not
				( and
					( = temp_c_1 c_2 )
					( = temp_y_1 y_0 )
					( = temp_z_1 z_2 )
					( < c_2 36 )
					( = z_3  )
					( = c_3  )
					( = c_4 c_3 )
					( = z_4 z_3 )
					( = c_2 c_4 )
					( = temp_c_0 temp_c_1 )
					( = temp_y_0 temp_y_1 )
					( = temp_z_0 temp_z_1 )
					( = z_2 z_4 )
					( < c_2 36 )
					( not ( >= z_2 0 ) )
				)
			)
		)
		( or
			( not
				( and
					( = c c_2)
					( = temp_c temp_c_0)
					( = temp_y temp_y_0)
					( = temp_z temp_z_0)
					( = y y_0)
					( = z z_2)
				)
			)
			( not
				( and
					( = temp_c_1 c_2 )
					( = temp_y_1 y_0 )
					( = temp_z_1 z_2 )
					( not ( < c_2 36 ) )
					( = c_4 c_2 )
					( = z_4 z_2 )
					( = c_2 c_4 )
					( = temp_c_0 temp_c_1 )
					( = temp_y_0 temp_y_1 )
					( = temp_z_0 temp_z_1 )
					( = z_2 z_4 )
					( < c_2 36 )
					( not ( >= z_2 0 ) )
				)
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f c temp_c temp_y temp_z y z tmp c_0 c_1 c_2 c_3 c_4 temp_c_0 temp_c_1 temp_y_0 temp_y_1 temp_z_0 temp_z_1 y_0 z_0 z_1 z_2 z_3 z_4  )
		( inv-f c temp_c temp_y temp_z y z tmp )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f c temp_c temp_y temp_z y z tmp )
			( trans-f c temp_c temp_y temp_z y z tmp c! temp_c! temp_y! temp_z! y! z! tmp! c_0 c_1 c_2 c_3 c_4 temp_c_0 temp_c_1 temp_y_0 temp_y_1 temp_z_0 temp_z_1 y_0 z_0 z_1 z_2 z_3 z_4 )
		)
		( inv-f c! temp_c! temp_y! temp_z! y! z! tmp! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f c temp_c temp_y temp_z y z tmp  )
		( post-f c temp_c temp_y temp_z y z tmp c_0 c_1 c_2 c_3 c_4 temp_c_0 temp_c_1 temp_y_0 temp_y_1 temp_z_0 temp_z_1 y_0 z_0 z_1 z_2 z_3 z_4 )
	)
))

