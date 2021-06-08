(set-logic LIA)

( declare-const i Int )
( declare-const i! Int )
( declare-const n Int )
( declare-const n! Int )
( declare-const temp Int )
( declare-const temp! Int )
( declare-const x Int )
( declare-const x! Int )
( declare-const y Int )
( declare-const y! Int )

( declare-const i_0 Int )
( declare-const i_1 Int )
( declare-const i_2 Int )
( declare-const i_3 Int )
( declare-const n_0 Int )
( declare-const n_1 Int )
( declare-const temp_0 Int )
( declare-const temp_1 Int )
( declare-const x_0 Int )
( declare-const x_1 Int )
( declare-const x_2 Int )
( declare-const x_3 Int )
( declare-const y_0 Int )
( declare-const y_1 Int )
( declare-const y_2 Int )
( declare-const y_3 Int )

( define-fun inv-f( ( i Int )( n Int )( temp Int )( x Int )( y Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( i Int )( n Int )( temp Int )( x Int )( y Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( n_0 Int )( n_1 Int )( temp_0 Int )( temp_1 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int )( y_0 Int )( y_1 Int )( y_2 Int )( y_3 Int ) ) Bool
	( and
		( = i i_1 )
		( = n n_1 )
		( = x x_1 )
		( = y y_1 )
		( = x_1 0 )
		( = y_1 1 )
		( = n_1 20 )
		( = i_1 0 )
	)
)

( define-fun trans-f ( ( i Int )( n Int )( temp Int )( x Int )( y Int )( i! Int )( n! Int )( temp! Int )( x! Int )( y! Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( n_0 Int )( n_1 Int )( temp_0 Int )( temp_1 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int )( y_0 Int )( y_1 Int )( y_2 Int )( y_3 Int ) ) Bool
	( or
		( and
			( = i_2 i )
			( = temp_0 temp )
			( = x_2 x )
			( = y_2 y )
			( = i_2 i! )
			( = temp_0 temp! )
			( = x_2 x! )
			( = y_2 y! )
			( = n n_1 )
			( = n! n_1 )
			( = temp temp! )
			( = x x! )
			( = y y! )
		)
		( and
			( = i_2 i )
			( = temp_0 temp )
			( = x_2 x )
			( = y_2 y )
			( < i_2 n_1 )
			( = temp_1 ( + x_2 y_2 ) )
			( = x_3 y_2 )
			( = y_3 temp_1 )
			( = i_3 ( + i_2 1 ) )
			( = i_3 i! )
			( = temp_1 temp! )
			( = x_3 x! )
			( = y_3 y! )
			(= n n_1 )
			(= n! n_1 )
		)
	)
)

( define-fun post-f ( ( i Int )( n Int )( temp Int )( x Int )( y Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( n_0 Int )( n_1 Int )( temp_0 Int )( temp_1 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int )( y_0 Int )( y_1 Int )( y_2 Int )( y_3 Int ) ) Bool
	( and
		( or
			( not
				( and
					( = i i_2)
					( = n n_1)
					( = temp temp_0)
					( = x x_2)
					( = y y_2)
				)
			)
			( not
				( and
					( not ( < i_2 n_1 ) )
					( < ( <= 0 i_2 ) n_1 )
					( = x_2  )
					( not ( and ( and ( < ( <= 0 i_2 ) n_1 ) ( = x_2  ) ) ( = y_2  ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = i i_2)
					( = n n_1)
					( = temp temp_0)
					( = x x_2)
					( = y y_2)
				)
			)
			( not
				( and
					( not ( < i_2 n_1 ) )
					( < ( <= 0 i_2 ) n_1 )
					( not ( = x_2  ) )
					( not ( and ( and ( < ( <= 0 i_2 ) n_1 ) ( = x_2  ) ) ( = y_2  ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = i i_2)
					( = n n_1)
					( = temp temp_0)
					( = x x_2)
					( = y y_2)
				)
			)
			( not
				( and
					( not ( < i_2 n_1 ) )
					( not ( < ( <= 0 i_2 ) n_1 ) )
					( not ( and ( and ( < ( <= 0 i_2 ) n_1 ) ( = x_2  ) ) ( = y_2  ) ) )
				)
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f i n temp x y i_0 i_1 i_2 i_3 n_0 n_1 temp_0 temp_1 x_0 x_1 x_2 x_3 y_0 y_1 y_2 y_3  )
		( inv-f i n temp x y )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f i n temp x y )
			( trans-f i n temp x y i! n! temp! x! y! i_0 i_1 i_2 i_3 n_0 n_1 temp_0 temp_1 x_0 x_1 x_2 x_3 y_0 y_1 y_2 y_3 )
		)
		( inv-f i! n! temp! x! y! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f i n temp x y  )
		( post-f i n temp x y i_0 i_1 i_2 i_3 n_0 n_1 temp_0 temp_1 x_0 x_1 x_2 x_3 y_0 y_1 y_2 y_3 )
	)
))

