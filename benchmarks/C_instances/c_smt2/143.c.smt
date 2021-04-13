(set-logic LIA)

( declare-const d Int )
( declare-const d! Int )
( declare-const n Int )
( declare-const n! Int )
( declare-const q Int )
( declare-const q! Int )
( declare-const r Int )
( declare-const r! Int )

( declare-const d_0 Int )
( declare-const n_0 Int )
( declare-const q_0 Int )
( declare-const q_1 Int )
( declare-const q_2 Int )
( declare-const q_3 Int )
( declare-const r_0 Int )
( declare-const r_1 Int )
( declare-const r_2 Int )
( declare-const r_3 Int )

( define-fun inv-f( ( d Int )( n Int )( q Int )( r Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( d Int )( n Int )( q Int )( r Int )( d_0 Int )( n_0 Int )( q_0 Int )( q_1 Int )( q_2 Int )( q_3 Int )( r_0 Int )( r_1 Int )( r_2 Int )( r_3 Int ) ) Bool
	( and
		( = n n_0 )
		( = q q_1 )
		( = r r_1 )
		( = q_0 0 )
		( = r_0 n_0 )
		( = q_1 0 )
		( = r_1 n_0 )
	)
)

( define-fun trans-f ( ( d Int )( n Int )( q Int )( r Int )( d! Int )( n! Int )( q! Int )( r! Int )( d_0 Int )( n_0 Int )( q_0 Int )( q_1 Int )( q_2 Int )( q_3 Int )( r_0 Int )( r_1 Int )( r_2 Int )( r_3 Int ) ) Bool
	( or
		( and
			( = q_2 q )
			( = r_2 r )
			( = q_2 q! )
			( = r_2 r! )
			( = d d_0 )
			( = d! d_0 )
			( = n n! )
			( = q q! )
		)
		( and
			( = q_2 q )
			( = r_2 r )
			( >= r_2 d_0 )
			( = r_3 ( - r_2 d_0 ) )
			( = q_3 ( + q_2 1 ) )
			( = q_3 q! )
			( = r_3 r! )
			(= d d_0 )
			(= d! d_0 )
			(= n n_0 )
			(= n! n_0 )
		)
	)
)

( define-fun post-f ( ( d Int )( n Int )( q Int )( r Int )( d_0 Int )( n_0 Int )( q_0 Int )( q_1 Int )( q_2 Int )( q_3 Int )( r_0 Int )( r_1 Int )( r_2 Int )( r_3 Int ) ) Bool
	( and
		( or
			( not
				( and
					( = d d_0 )
					( = n n_0)
					( = q q_2)
					( = r r_2)
				)
			)
			( not
				( and
					( not ( >= r_2 d_0 ) )
					( >= n_0 0 )
					( < r_2 d_0 )
					( not ( and ( < r_2 d_0 ) ( = n_0 ( + ( * q_2 d_0 ) r_2 ) ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = d d_0 )
					( = n n_0)
					( = q q_2)
					( = r r_2)
				)
			)
			( not
				( and
					( not ( >= r_2 d_0 ) )
					( >= n_0 0 )
					( not ( < r_2 d_0 ) )
					( not ( and ( < r_2 d_0 ) ( = n_0 ( + ( * q_2 d_0 ) r_2 ) ) ) )
				)
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f d n q r d_0 n_0 q_0 q_1 q_2 q_3 r_0 r_1 r_2 r_3  )
		( inv-f d n q r )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f d n q r )
			( trans-f d n q r d! n! q! r! d_0 n_0 q_0 q_1 q_2 q_3 r_0 r_1 r_2 r_3 )
		)
		( inv-f d! n! q! r! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f d n q r  )
		( post-f d n q r d_0 n_0 q_0 q_1 q_2 q_3 r_0 r_1 r_2 r_3 )
	)
))

