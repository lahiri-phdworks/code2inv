(set-logic LIA)

( declare-const i Int )
( declare-const i! Int )
( declare-const k Int )
( declare-const k! Int )
( declare-const n Int )
( declare-const n! Int )
( declare-const p Int )
( declare-const p! Int )
( declare-const r Int )
( declare-const r! Int )

( declare-const i_0 Int )
( declare-const i_1 Int )
( declare-const i_2 Int )
( declare-const k_0 Int )
( declare-const k_1 Int )
( declare-const k_2 Int )
( declare-const k_3 Int )
( declare-const n_0 Int )
( declare-const n_1 Int )
( declare-const p_0 Int )
( declare-const p_1 Int )
( declare-const r_0 Int )
( declare-const r_1 Int )
( declare-const r_2 Int )
( declare-const r_3 Int )

( define-fun inv-f( ( i Int )( k Int )( n Int )( p Int )( r Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( i Int )( k Int )( n Int )( p Int )( r Int )( i_0 Int )( i_1 Int )( i_2 Int )( k_0 Int )( k_1 Int )( k_2 Int )( k_3 Int )( n_0 Int )( n_1 Int )( p_0 Int )( p_1 Int )( r_0 Int )( r_1 Int )( r_2 Int )( r_3 Int ) ) Bool
	( and
		( = i i_0 )
		( = k k_1 )
		( = n n_1 )
		( = p p_1 )
		( = r r_1 )
		( = r_1 1 )
		( = k_1 0 )
		( = n_1 586 )
		( = p_1 100003 )
		( =  1 )
		( = i_0 1 )
	)
)

( define-fun trans-f ( ( i Int )( k Int )( n Int )( p Int )( r Int )( i! Int )( k! Int )( n! Int )( p! Int )( r! Int )( i_0 Int )( i_1 Int )( i_2 Int )( k_0 Int )( k_1 Int )( k_2 Int )( k_3 Int )( n_0 Int )( n_1 Int )( p_0 Int )( p_1 Int )( r_0 Int )( r_1 Int )( r_2 Int )( r_3 Int ) ) Bool
	( or
		( and
			( = i_1 i )
			( = i_1 i! )
			( = p p_1 )
			( = p! p_1 )
			( = k k! )
			( = n n! )
			( = r r! )
		)
		( and
			( = i_1 i )
			( < i_1 p_1 )
			( =  ( mod ( *  i_1 ) p_1 ) )
			( = i_2 ( + i_1 1 ) )
			( = i_2 i! )
			(= k k_1 )
			(= k! k_1 )
			(= n n_1 )
			(= n! n_1 )
			(= p p_1 )
			(= p! p_1 )
			(= r r_1 )
			(= r! r_1 )
		)
	)
)

( define-fun post-f ( ( i Int )( k Int )( n Int )( p Int )( r Int )( i_0 Int )( i_1 Int )( i_2 Int )( k_0 Int )( k_1 Int )( k_2 Int )( k_3 Int )( n_0 Int )( n_1 Int )( p_0 Int )( p_1 Int )( r_0 Int )( r_1 Int )( r_2 Int )( r_3 Int ) ) Bool
	( and
		( or
			( not
				( and
					( = i i_1)
					( = k k_1)
					( = n n_1)
					( = p p_1)
					( = r r_1)
				)
			)
			( not
				( and
					( not ( < i_1 p_1 ) )
					( = k_2 k_0 )
					( = r_2 r_0 )
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
					( = i i_1)
					( = k k_1)
					( = n n_1)
					( = p p_1)
					( = r r_1)
				)
			)
			( not
				( and
					( not ( < i_1 p_1 ) )
					( = k_2 k_0 )
					( = r_2 r_0 )
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
					( = i i_1)
					( = k k_1)
					( = n n_1)
					( = p p_1)
					( = r r_1)
				)
			)
			( not
				( and
					( not ( < i_1 p_1 ) )
					( = k_2 k_0 )
					( = r_2 r_0 )
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
		( pre-f i k n p r i_0 i_1 i_2 k_0 k_1 k_2 k_3 n_0 n_1 p_0 p_1 r_0 r_1 r_2 r_3  )
		( inv-f i k n p r )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f i k n p r )
			( trans-f i k n p r i! k! n! p! r! i_0 i_1 i_2 k_0 k_1 k_2 k_3 n_0 n_1 p_0 p_1 r_0 r_1 r_2 r_3 )
		)
		( inv-f i! k! n! p! r! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f i k n p r  )
		( post-f i k n p r i_0 i_1 i_2 k_0 k_1 k_2 k_3 n_0 n_1 p_0 p_1 r_0 r_1 r_2 r_3 )
	)
))

