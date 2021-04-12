(set-logic LIA)

( declare-const i Int )
( declare-const i! Int )
( declare-const n Int )
( declare-const n! Int )
( declare-const out Int )
( declare-const out! Int )

( declare-const i_0 Int )
( declare-const i_1 Int )
( declare-const i_2 Int )
( declare-const i_3 Int )
( declare-const n_0 Int )
( declare-const out_0 Int )
( declare-const out_1 Int )
( declare-const out_2 Int )
( declare-const out_3 Int )
( declare-const out_4 Int )
( declare-const out_5 Int )

( define-fun inv-f( ( i Int )( n Int )( out Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( i Int )( n Int )( out Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( n_0 Int )( out_0 Int )( out_1 Int )( out_2 Int )( out_3 Int )( out_4 Int )( out_5 Int ) ) Bool
	( and
		( = i i_1 )
		( = n n_0 )
		( = out out_1 )
		( > n_0 2 )
		( = i_1 0 )
		( = out_1 0 )
	)
)

( define-fun trans-f ( ( i Int )( n Int )( out Int )( i! Int )( n! Int )( out! Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( n_0 Int )( out_0 Int )( out_1 Int )( out_2 Int )( out_3 Int )( out_4 Int )( out_5 Int ) ) Bool
	( or
		( and
			( = i_2 i )
			( = out_2 out )
			( = i_2 i! )
			( = out_2 out! )
			( = n n_0 )
			( = n! n_0 )
			( = out out! )
		)
		( and
			( = i_2 i )
			( = out_2 out )
			( < i_2 n_0 )
			( = i_3 ( + i_2 1 ) )
			( = out_3 ( + out_2 1 ) )
			( = out_4 out_3 )
			( = i_3 i! )
			( = out_4 out! )
			(= n n_0 )
			(= n! n_0 )
		)
		( and
			( = i_2 i )
			( = out_2 out )
			( < i_2 n_0 )
			( = i_3 ( + i_2 1 ) )
			( = out_5 ( + out_2 i_3 ) )
			( = out_4 out_5 )
			( = i_3 i! )
			( = out_4 out! )
			(= n n_0 )
			(= n! n_0 )
		)
	)
)

( define-fun post-f ( ( i Int )( n Int )( out Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( n_0 Int )( out_0 Int )( out_1 Int )( out_2 Int )( out_3 Int )( out_4 Int )( out_5 Int ) ) Bool
	( and
		( or
			( not
				( and
					( = i i_2)
					( = n n_0)
					( = out out_2)
				)
			)
			( not
				( and
					( not ( < i_2 n_0 ) )
					( = ( mod i_2 2 ) 0 )
					( = i_2 5 )
					( = ( mod i_2 2 ) 0 )
					( > out_2 ( / ( * n_0 n_0 ) 2 ) )
					( not ( or ( and ( = ( mod i_2 2 ) 0 ) ( > out_2 ( / ( * n_0 n_0 ) 2 ) ) ) ( and ( = i_2 5 ) ( = out_2 5 ) ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = i i_2)
					( = n n_0)
					( = out out_2)
				)
			)
			( not
				( and
					( not ( < i_2 n_0 ) )
					( = ( mod i_2 2 ) 0 )
					( = i_2 5 )
					( = ( mod i_2 2 ) 0 )
					( not ( > out_2 ( / ( * n_0 n_0 ) 2 ) ) )
					( = i_2 5 )
					( not ( or ( and ( = ( mod i_2 2 ) 0 ) ( > out_2 ( / ( * n_0 n_0 ) 2 ) ) ) ( and ( = i_2 5 ) ( = out_2 5 ) ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = i i_2)
					( = n n_0)
					( = out out_2)
				)
			)
			( not
				( and
					( not ( < i_2 n_0 ) )
					( = ( mod i_2 2 ) 0 )
					( = i_2 5 )
					( = ( mod i_2 2 ) 0 )
					( not ( > out_2 ( / ( * n_0 n_0 ) 2 ) ) )
					( not ( = i_2 5 ) )
					( not ( or ( and ( = ( mod i_2 2 ) 0 ) ( > out_2 ( / ( * n_0 n_0 ) 2 ) ) ) ( and ( = i_2 5 ) ( = out_2 5 ) ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = i i_2)
					( = n n_0)
					( = out out_2)
				)
			)
			( not
				( and
					( not ( < i_2 n_0 ) )
					( = ( mod i_2 2 ) 0 )
					( = i_2 5 )
					( not ( = ( mod i_2 2 ) 0 ) )
					( = i_2 5 )
					( not ( or ( and ( = ( mod i_2 2 ) 0 ) ( > out_2 ( / ( * n_0 n_0 ) 2 ) ) ) ( and ( = i_2 5 ) ( = out_2 5 ) ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = i i_2)
					( = n n_0)
					( = out out_2)
				)
			)
			( not
				( and
					( not ( < i_2 n_0 ) )
					( = ( mod i_2 2 ) 0 )
					( = i_2 5 )
					( not ( = ( mod i_2 2 ) 0 ) )
					( not ( = i_2 5 ) )
					( not ( or ( and ( = ( mod i_2 2 ) 0 ) ( > out_2 ( / ( * n_0 n_0 ) 2 ) ) ) ( and ( = i_2 5 ) ( = out_2 5 ) ) ) )
				)
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f i n out i_0 i_1 i_2 i_3 n_0 out_0 out_1 out_2 out_3 out_4 out_5  )
		( inv-f i n out )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f i n out )
			( trans-f i n out i! n! out! i_0 i_1 i_2 i_3 n_0 out_0 out_1 out_2 out_3 out_4 out_5 )
		)
		( inv-f i! n! out! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f i n out  )
		( post-f i n out i_0 i_1 i_2 i_3 n_0 out_0 out_1 out_2 out_3 out_4 out_5 )
	)
))

