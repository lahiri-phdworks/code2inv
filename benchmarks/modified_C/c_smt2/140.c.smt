(set-logic LIA)

( declare-const i Int )
( declare-const i! Int )
( declare-const i2 Int )
( declare-const i2! Int )
( declare-const n Int )
( declare-const n! Int )
( declare-const sum Int )
( declare-const sum! Int )
( declare-const y Int )
( declare-const y! Int )

( declare-const i_0 Int )
( declare-const i_1 Int )
( declare-const i_2 Int )
( declare-const i_3 Int )
( declare-const i2_0 Int )
( declare-const i2_1 Int )
( declare-const i2_2 Int )
( declare-const i2_3 Int )
( declare-const n_0 Int )
( declare-const sum_0 Int )
( declare-const sum_1 Int )
( declare-const sum_2 Int )
( declare-const sum_3 Int )
( declare-const y_0 Int )
( declare-const y_1 Int )
( declare-const y_2 Int )

( define-fun inv-f( ( i Int )( i2 Int )( n Int )( sum Int )( y Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( i Int )( i2 Int )( n Int )( sum Int )( y Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( i2_0 Int )( i2_1 Int )( i2_2 Int )( i2_3 Int )( n_0 Int )( sum_0 Int )( sum_1 Int )( sum_2 Int )( sum_3 Int )( y_0 Int )( y_1 Int )( y_2 Int ) ) Bool
	( and
		( = i i_1 )
		( = i2 i2_1 )
		( = n n_0 )
		( = sum sum_1 )
		( > n_0 0 )
		( < n_0 500000 )
		( = sum_1 0 )
		( = i_1 1 )
		( = i2_1 0 )
	)
)

( define-fun trans-f ( ( i Int )( i2 Int )( n Int )( sum Int )( y Int )( i! Int )( i2! Int )( n! Int )( sum! Int )( y! Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( i2_0 Int )( i2_1 Int )( i2_2 Int )( i2_3 Int )( n_0 Int )( sum_0 Int )( sum_1 Int )( sum_2 Int )( sum_3 Int )( y_0 Int )( y_1 Int )( y_2 Int ) ) Bool
	( or
		( and
			( = i_2 i )
			( = i2_2 i2 )
			( = sum_2 sum )
			( = y_1 y )
			( = i_2 i! )
			( = i2_2 i2! )
			( = sum_2 sum! )
			( = y_1 y! )
			( = n n_0 )
			( = n! n_0 )
			( = i2 i2! )
			( = sum sum! )
			( = y y! )
		)
		( and
			( = i_2 i )
			( = i2_2 i2 )
			( = sum_2 sum )
			( = y_1 y )
			( <= i_2 n_0 )
			( = i2_3 ( * i_2 i_2 ) )
			( = i_3 ( + i_2 1 ) )
			( = y_2 ( / ( * ( * i_3 ( + i_3 1 ) ) ( + ( * 2 i_3 ) 1 ) ) 6 ) )
			( = sum_3 ( + sum_2 i2_3 ) )
			( = i_3 i! )
			( = i2_3 i2! )
			( = sum_3 sum! )
			( = y_2 y! )
			(= n n_0 )
			(= n! n_0 )
		)
	)
)

( define-fun post-f ( ( i Int )( i2 Int )( n Int )( sum Int )( y Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( i2_0 Int )( i2_1 Int )( i2_2 Int )( i2_3 Int )( n_0 Int )( sum_0 Int )( sum_1 Int )( sum_2 Int )( sum_3 Int )( y_0 Int )( y_1 Int )( y_2 Int ) ) Bool
	( or
		( not
			( and
				( = i i_2)
				( = i2 i2_2)
				( = n n_0)
				( = sum sum_2)
				( = y y_1)
			)
		)
		( not
			( and
				( not ( <= i_2 n_0 ) )
				( not ( = sum_2 ( / ( * ( * n_0 ( + n_0 1 ) ) ( + ( * 2 n_0 ) 1 ) ) 6 ) ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f i i2 n sum y i_0 i_1 i_2 i_3 i2_0 i2_1 i2_2 i2_3 n_0 sum_0 sum_1 sum_2 sum_3 y_0 y_1 y_2  )
		( inv-f i i2 n sum y )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f i i2 n sum y )
			( trans-f i i2 n sum y i! i2! n! sum! y! i_0 i_1 i_2 i_3 i2_0 i2_1 i2_2 i2_3 n_0 sum_0 sum_1 sum_2 sum_3 y_0 y_1 y_2 )
		)
		( inv-f i! i2! n! sum! y! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f i i2 n sum y  )
		( post-f i i2 n sum y i_0 i_1 i_2 i_3 i2_0 i2_1 i2_2 i2_3 n_0 sum_0 sum_1 sum_2 sum_3 y_0 y_1 y_2 )
	)
))

