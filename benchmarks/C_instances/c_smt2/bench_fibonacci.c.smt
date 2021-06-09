(set-logic LIA)

( declare-const i Int )
( declare-const i! Int )
( declare-const n Int )
( declare-const n! Int )
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
( declare-const x_0 Int )
( declare-const x_1 Int )
( declare-const x_2 Int )
( declare-const x_3 Int )
( declare-const y_0 Int )
( declare-const y_1 Int )

( define-fun inv-f( ( i Int )( n Int )( x Int )( y Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( i Int )( n Int )( x Int )( y Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( n_0 Int )( n_1 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int )( y_0 Int )( y_1 Int ) ) Bool
	( and
		( = i i_1 )
		( = n n_1 )
		( = x x_1 )
		( = y y_1 )
		( = x_1 0 )
		( = y_1 1 )
		( = n_1 10 )
		( = i_1 0 )
	)
)

( define-fun trans-f ( ( i Int )( n Int )( x Int )( y Int )( i! Int )( n! Int )( x! Int )( y! Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( n_0 Int )( n_1 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int )( y_0 Int )( y_1 Int ) ) Bool
	( or
		( and
			( = i_2 i )
			( = x_2 x )
			( = i_2 i! )
			( = x_2 x! )
			( = n n_1 )
			( = n! n_1 )
			( = x x! )
			( = y y! )
		)
		( and
			( = i_2 i )
			( = x_2 x )
			( < i_2 n_1 )
			( = x_3 ( - y_1 x_2 ) )
			( = i_3 ( + i_2 1 ) )
			( = i_3 i! )
			( = x_3 x! )
			(= n n_1 )
			(= n! n_1 )
			(= y y_1 )
			(= y! y_1 )
		)
	)
)

( define-fun post-f ( ( i Int )( n Int )( x Int )( y Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( n_0 Int )( n_1 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int )( y_0 Int )( y_1 Int ) ) Bool
	( and
		( or
			( not
				( and
					( = i i_2)
					( = n n_1)
					( = x x_2)
					( = y y_1)
				)
			)
			( not
				( and
					( not ( < i_2 n_1 ) )
					( <= 0 i_2 )
					( <= i_2 n_1 )
					( >= n_1 0 )
					( = x_2  )
					( not ( and ( and ( and ( and ( <= 0 i_2 ) ( <= i_2 n_1 ) ) ( >= n_1 0 ) ) ( = x_2  ) ) ( = y_1  ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = i i_2)
					( = n n_1)
					( = x x_2)
					( = y y_1)
				)
			)
			( not
				( and
					( not ( < i_2 n_1 ) )
					( <= 0 i_2 )
					( <= i_2 n_1 )
					( >= n_1 0 )
					( not ( = x_2  ) )
					( not ( and ( and ( and ( and ( <= 0 i_2 ) ( <= i_2 n_1 ) ) ( >= n_1 0 ) ) ( = x_2  ) ) ( = y_1  ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = i i_2)
					( = n n_1)
					( = x x_2)
					( = y y_1)
				)
			)
			( not
				( and
					( not ( < i_2 n_1 ) )
					( <= 0 i_2 )
					( <= i_2 n_1 )
					( not ( >= n_1 0 ) )
					( not ( and ( and ( and ( and ( <= 0 i_2 ) ( <= i_2 n_1 ) ) ( >= n_1 0 ) ) ( = x_2  ) ) ( = y_1  ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = i i_2)
					( = n n_1)
					( = x x_2)
					( = y y_1)
				)
			)
			( not
				( and
					( not ( < i_2 n_1 ) )
					( <= 0 i_2 )
					( not ( <= i_2 n_1 ) )
					( not ( and ( and ( and ( and ( <= 0 i_2 ) ( <= i_2 n_1 ) ) ( >= n_1 0 ) ) ( = x_2  ) ) ( = y_1  ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = i i_2)
					( = n n_1)
					( = x x_2)
					( = y y_1)
				)
			)
			( not
				( and
					( not ( < i_2 n_1 ) )
					( not ( <= 0 i_2 ) )
					( not ( and ( and ( and ( and ( <= 0 i_2 ) ( <= i_2 n_1 ) ) ( >= n_1 0 ) ) ( = x_2  ) ) ( = y_1  ) ) )
				)
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f i n x y i_0 i_1 i_2 i_3 n_0 n_1 x_0 x_1 x_2 x_3 y_0 y_1  )
		( inv-f i n x y )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f i n x y )
			( trans-f i n x y i! n! x! y! i_0 i_1 i_2 i_3 n_0 n_1 x_0 x_1 x_2 x_3 y_0 y_1 )
		)
		( inv-f i! n! x! y! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f i n x y  )
		( post-f i n x y i_0 i_1 i_2 i_3 n_0 n_1 x_0 x_1 x_2 x_3 y_0 y_1 )
	)
))

