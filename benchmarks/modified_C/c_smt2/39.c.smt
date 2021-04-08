(set-logic LIA)

( declare-const c Int )
( declare-const c! Int )
( declare-const n Int )
( declare-const n! Int )
( declare-const temp_c Int )
( declare-const temp_c! Int )
( declare-const temp_n Int )
( declare-const temp_n! Int )
( declare-const tmp Int )
( declare-const tmp! Int )

( declare-const c_0 Int )
( declare-const c_1 Int )
( declare-const c_2 Int )
( declare-const c_3 Int )
( declare-const c_4 Int )
( declare-const c_5 Int )
( declare-const n_0 Int )
( declare-const temp_c_0 Int )
( declare-const temp_c_1 Int )
( declare-const temp_n_0 Int )
( declare-const temp_n_1 Int )

( define-fun inv-f( ( c Int )( n Int )( temp_c Int )( temp_n Int )( tmp Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( c Int )( n Int )( temp_c Int )( temp_n Int )( tmp Int )( c_0 Int )( c_1 Int )( c_2 Int )( c_3 Int )( c_4 Int )( c_5 Int )( n_0 Int )( temp_c_0 Int )( temp_c_1 Int )( temp_n_0 Int )( temp_n_1 Int ) ) Bool
	( and
		( = c c_1 )
		( = n n_0 )
		( = c_1 0 )
		( > n_0 0 )
	)
)

( define-fun trans-f ( ( c Int )( n Int )( temp_c Int )( temp_n Int )( tmp Int )( c! Int )( n! Int )( temp_c! Int )( temp_n! Int )( tmp! Int )( c_0 Int )( c_1 Int )( c_2 Int )( c_3 Int )( c_4 Int )( c_5 Int )( n_0 Int )( temp_c_0 Int )( temp_c_1 Int )( temp_n_0 Int )( temp_n_1 Int ) ) Bool
	( or
		( and
			( = c_2 c )
			( = temp_c_0 temp_c )
			( = temp_n_0 temp_n )
			( = c_2 c! )
			( = temp_c_0 temp_c! )
			( = temp_n_0 temp_n! )
			( = c c! )
			( = n n! )
			( = temp_c temp_c! )
			( = temp_n temp_n! )
			(= tmp tmp! )
		)
		( and
			( = c_2 c )
			( = temp_c_0 temp_c )
			( = temp_n_0 temp_n )
			( = temp_c_1 c_2 )
			( = temp_n_1 n_0 )
			( = c_2 n_0 )
			( = c_3 1 )
			( = c_4 c_3 )
			( = c_4 c! )
			( = temp_c_1 temp_c! )
			( = temp_n_1 temp_n! )
			(= n n_0 )
			(= n! n_0 )
			(= tmp tmp! )
		)
		( and
			( = c_2 c )
			( = temp_c_0 temp_c )
			( = temp_n_0 temp_n )
			( = temp_c_1 c_2 )
			( = temp_n_1 n_0 )
			( not ( = c_2 n_0 ) )
			( = c_5  )
			( = c_4 c_5 )
			( = c_4 c! )
			( = temp_c_1 temp_c! )
			( = temp_n_1 temp_n! )
			(= n n_0 )
			(= n! n_0 )
			(= tmp tmp! )
		)
	)
)

( define-fun post-f ( ( c Int )( n Int )( temp_c Int )( temp_n Int )( tmp Int )( c_0 Int )( c_1 Int )( c_2 Int )( c_3 Int )( c_4 Int )( c_5 Int )( n_0 Int )( temp_c_0 Int )( temp_c_1 Int )( temp_n_0 Int )( temp_n_1 Int ) ) Bool
	( or
		( not
			( and
				( = c c_2)
				( = n n_0)
				( = temp_c temp_c_0)
				( = temp_n temp_n_0)
			)
		)
		( not
			( and
				( = c_2 n_0 )
				( not ( <= c_2 n_0 ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f c n temp_c temp_n tmp c_0 c_1 c_2 c_3 c_4 c_5 n_0 temp_c_0 temp_c_1 temp_n_0 temp_n_1  )
		( inv-f c n temp_c temp_n tmp )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f c n temp_c temp_n tmp )
			( trans-f c n temp_c temp_n tmp c! n! temp_c! temp_n! tmp! c_0 c_1 c_2 c_3 c_4 c_5 n_0 temp_c_0 temp_c_1 temp_n_0 temp_n_1 )
		)
		( inv-f c! n! temp_c! temp_n! tmp! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f c n temp_c temp_n tmp  )
		( post-f c n temp_c temp_n tmp c_0 c_1 c_2 c_3 c_4 c_5 n_0 temp_c_0 temp_c_1 temp_n_0 temp_n_1 )
	)
))

