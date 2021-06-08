(set-logic LIA)

( declare-const k Int )
( declare-const k! Int )
( declare-const n Int )
( declare-const n! Int )
( declare-const p Int )
( declare-const p! Int )
( declare-const r Int )
( declare-const r! Int )

( declare-const k_0 Int )
( declare-const k_1 Int )
( declare-const k_2 Int )
( declare-const k_3 Int )
( declare-const n_0 Int )
( declare-const n_1 Int )
( declare-const p_0 Int )
( declare-const r_0 Int )
( declare-const r_1 Int )
( declare-const r_2 Int )
( declare-const r_3 Int )

( define-fun inv-f( ( k Int )( n Int )( p Int )( r Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( k Int )( n Int )( p Int )( r Int )( k_0 Int )( k_1 Int )( k_2 Int )( k_3 Int )( n_0 Int )( n_1 Int )( p_0 Int )( r_0 Int )( r_1 Int )( r_2 Int )( r_3 Int ) ) Bool
	( and
		( = k k_1 )
		( = n n_1 )
		( = r r_1 )
		( = r_1 1 )
		( = k_1 0 )
		( = n_1 586 )
	)
)

( define-fun trans-f ( ( k Int )( n Int )( p Int )( r Int )( k! Int )( n! Int )( p! Int )( r! Int )( k_0 Int )( k_1 Int )( k_2 Int )( k_3 Int )( n_0 Int )( n_1 Int )( p_0 Int )( r_0 Int )( r_1 Int )( r_2 Int )( r_3 Int ) ) Bool
	( or
		( and
			( = k_2 k )
			( = r_2 r )
			( = k_2 k! )
			( = r_2 r! )
			( = n n_1 )
			( = n! n_1 )
			( = p p! )
			( = r r! )
		)
		( and
			( = k_2 k )
			( = r_2 r )
			( not ( = k_2 n_1 ) )
			( = k_3 ( + k_2 1 ) )
			( = r_3 ( mod ( * r_2 k_3 ) p_0 ) )
			( = k_3 k! )
			( = r_3 r! )
			(= n n_1 )
			(= n! n_1 )
			(= p p_0 )
			(= p! p_0 )
		)
	)
)

( define-fun post-f ( ( k Int )( n Int )( p Int )( r Int )( k_0 Int )( k_1 Int )( k_2 Int )( k_3 Int )( n_0 Int )( n_1 Int )( p_0 Int )( r_0 Int )( r_1 Int )( r_2 Int )( r_3 Int ) ) Bool
	( and
		( or
			( not
				( and
					( = k k_2)
					( = n n_1)
					( = p p_0 )
					( = r r_2)
				)
			)
			( not
				( and
					( not ( not ( = k_2 n_1 ) ) )
					( >= n_1 0 )
					( >= k_2 0 )
					( not ( and ( and ( >= n_1 0 ) ( >= k_2 0 ) ) ( = r_2  ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = k k_2)
					( = n n_1)
					( = p p_0 )
					( = r r_2)
				)
			)
			( not
				( and
					( not ( not ( = k_2 n_1 ) ) )
					( >= n_1 0 )
					( not ( >= k_2 0 ) )
					( not ( and ( and ( >= n_1 0 ) ( >= k_2 0 ) ) ( = r_2  ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = k k_2)
					( = n n_1)
					( = p p_0 )
					( = r r_2)
				)
			)
			( not
				( and
					( not ( not ( = k_2 n_1 ) ) )
					( not ( >= n_1 0 ) )
					( not ( and ( and ( >= n_1 0 ) ( >= k_2 0 ) ) ( = r_2  ) ) )
				)
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f k n p r k_0 k_1 k_2 k_3 n_0 n_1 p_0 r_0 r_1 r_2 r_3  )
		( inv-f k n p r )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f k n p r )
			( trans-f k n p r k! n! p! r! k_0 k_1 k_2 k_3 n_0 n_1 p_0 r_0 r_1 r_2 r_3 )
		)
		( inv-f k! n! p! r! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f k n p r  )
		( post-f k n p r k_0 k_1 k_2 k_3 n_0 n_1 p_0 r_0 r_1 r_2 r_3 )
	)
))

