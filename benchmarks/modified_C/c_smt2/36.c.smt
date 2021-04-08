(set-logic LIA)

( declare-const c Int )
( declare-const c! Int )
( declare-const temp_c Int )
( declare-const temp_c! Int )
( declare-const tmp Int )
( declare-const tmp! Int )

( declare-const c_0 Int )
( declare-const c_1 Int )
( declare-const c_2 Int )
( declare-const c_3 Int )
( declare-const c_4 Int )
( declare-const c_5 Int )
( declare-const temp_c_0 Int )
( declare-const temp_c_1 Int )

( define-fun inv-f( ( c Int )( temp_c Int )( tmp Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( c Int )( temp_c Int )( tmp Int )( c_0 Int )( c_1 Int )( c_2 Int )( c_3 Int )( c_4 Int )( c_5 Int )( temp_c_0 Int )( temp_c_1 Int ) ) Bool
	( and
		( = c c_1 )
		( = c_1 0 )
	)
)

( define-fun trans-f ( ( c Int )( temp_c Int )( tmp Int )( c! Int )( temp_c! Int )( tmp! Int )( c_0 Int )( c_1 Int )( c_2 Int )( c_3 Int )( c_4 Int )( c_5 Int )( temp_c_0 Int )( temp_c_1 Int ) ) Bool
	( or
		( and
			( = c_2 c )
			( = temp_c_0 temp_c )
			( = c_2 c! )
			( = temp_c_0 temp_c! )
			( = c c! )
			( = temp_c temp_c! )
			(= tmp tmp! )
		)
		( and
			( = c_2 c )
			( = temp_c_0 temp_c )
			( = temp_c_1 c_2 )
			( not ( = c_2 40 ) )
			( = c_3  )
			( = c_4 c_3 )
			( = c_4 c! )
			( = temp_c_1 temp_c! )
			(= tmp tmp! )
		)
		( and
			( = c_2 c )
			( = temp_c_0 temp_c )
			( = temp_c_1 c_2 )
			( not ( not ( = c_2 40 ) ) )
			( = c_4 c_2 )
			( = c_4 c! )
			( = temp_c_1 temp_c! )
			(= tmp tmp! )
		)
		( and
			( = c_2 c )
			( = temp_c_0 temp_c )
			( = temp_c_1 c_2 )
			( = c_2 40 )
			( = c_5 1 )
			( = c_4 c_5 )
			( = c_4 c! )
			( = temp_c_1 temp_c! )
			(= tmp tmp! )
		)
		( and
			( = c_2 c )
			( = temp_c_0 temp_c )
			( = temp_c_1 c_2 )
			( not ( = c_2 40 ) )
			( = c_4 c_2 )
			( = c_4 c! )
			( = temp_c_1 temp_c! )
			(= tmp tmp! )
		)
	)
)

( define-fun post-f ( ( c Int )( temp_c Int )( tmp Int )( c_0 Int )( c_1 Int )( c_2 Int )( c_3 Int )( c_4 Int )( c_5 Int )( temp_c_0 Int )( temp_c_1 Int ) ) Bool
	( or
		( not
			( and
				( = c c_2)
				( = temp_c temp_c_0)
			)
		)
		( not
			( and
				( not ( = c_2 40 ) )
				( not ( <= c_2 40 ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f c temp_c tmp c_0 c_1 c_2 c_3 c_4 c_5 temp_c_0 temp_c_1  )
		( inv-f c temp_c tmp )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f c temp_c tmp )
			( trans-f c temp_c tmp c! temp_c! tmp! c_0 c_1 c_2 c_3 c_4 c_5 temp_c_0 temp_c_1 )
		)
		( inv-f c! temp_c! tmp! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f c temp_c tmp  )
		( post-f c temp_c tmp c_0 c_1 c_2 c_3 c_4 c_5 temp_c_0 temp_c_1 )
	)
))

