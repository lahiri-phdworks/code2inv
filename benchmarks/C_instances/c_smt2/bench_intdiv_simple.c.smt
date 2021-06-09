(set-logic LIA)

( declare-const a Int )
( declare-const a! Int )
( declare-const d Int )
( declare-const d! Int )
( declare-const q Int )
( declare-const q! Int )
( declare-const r Int )
( declare-const r! Int )

( declare-const a_0 Int )
( declare-const a_1 Int )
( declare-const d_0 Int )
( declare-const d_1 Int )
( declare-const q_0 Int )
( declare-const q_1 Int )
( declare-const q_2 Int )
( declare-const q_3 Int )
( declare-const r_0 Int )
( declare-const r_1 Int )
( declare-const r_2 Int )
( declare-const r_3 Int )

( define-fun inv-f( ( a Int )( d Int )( q Int )( r Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( a Int )( d Int )( q Int )( r Int )( a_0 Int )( a_1 Int )( d_0 Int )( d_1 Int )( q_0 Int )( q_1 Int )( q_2 Int )( q_3 Int )( r_0 Int )( r_1 Int )( r_2 Int )( r_3 Int ) ) Bool
	( and
		( = a a_1 )
		( = d d_1 )
		( = q q_1 )
		( = r r_1 )
		( = a_1 7454 )
		( = d_1 13 )
		( = r_1 a_1 )
		( = q_1 0 )
		( >= a_1 0 )
		( > d_1 0 )
	)
)

( define-fun trans-f ( ( a Int )( d Int )( q Int )( r Int )( a! Int )( d! Int )( q! Int )( r! Int )( a_0 Int )( a_1 Int )( d_0 Int )( d_1 Int )( q_0 Int )( q_1 Int )( q_2 Int )( q_3 Int )( r_0 Int )( r_1 Int )( r_2 Int )( r_3 Int ) ) Bool
	( or
		( and
			( = q_2 q )
			( = r_2 r )
			( = q_2 q! )
			( = r_2 r! )
			( = d d_1 )
			( = d! d_1 )
			( = a a! )
			( = q q! )
		)
		( and
			( = q_2 q )
			( = r_2 r )
			( >= r_2 d_1 )
			( = q_3 ( + q_2 1 ) )
			( = r_3 ( - r_2 d_1 ) )
			( = q_3 q! )
			( = r_3 r! )
			(= a a_1 )
			(= a! a_1 )
			(= d d_1 )
			(= d! d_1 )
		)
	)
)

( define-fun post-f ( ( a Int )( d Int )( q Int )( r Int )( a_0 Int )( a_1 Int )( d_0 Int )( d_1 Int )( q_0 Int )( q_1 Int )( q_2 Int )( q_3 Int )( r_0 Int )( r_1 Int )( r_2 Int )( r_3 Int ) ) Bool
	( and
		( or
			( not
				( and
					( = a a_1)
					( = d d_1)
					( = q q_2)
					( = r r_2)
				)
			)
			( not
				( and
					( not ( >= r_2 d_1 ) )
					( <= ( <= 0 r_2 ) d_1 )
					( = ( / a_1 d_1 ) q_2 )
					( not ( and ( and ( <= ( <= 0 r_2 ) d_1 ) ( = ( / a_1 d_1 ) q_2 ) ) ( = r_2  ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = a a_1)
					( = d d_1)
					( = q q_2)
					( = r r_2)
				)
			)
			( not
				( and
					( not ( >= r_2 d_1 ) )
					( <= ( <= 0 r_2 ) d_1 )
					( not ( = ( / a_1 d_1 ) q_2 ) )
					( not ( and ( and ( <= ( <= 0 r_2 ) d_1 ) ( = ( / a_1 d_1 ) q_2 ) ) ( = r_2  ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = a a_1)
					( = d d_1)
					( = q q_2)
					( = r r_2)
				)
			)
			( not
				( and
					( not ( >= r_2 d_1 ) )
					( not ( <= ( <= 0 r_2 ) d_1 ) )
					( not ( and ( and ( <= ( <= 0 r_2 ) d_1 ) ( = ( / a_1 d_1 ) q_2 ) ) ( = r_2  ) ) )
				)
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f a d q r a_0 a_1 d_0 d_1 q_0 q_1 q_2 q_3 r_0 r_1 r_2 r_3  )
		( inv-f a d q r )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f a d q r )
			( trans-f a d q r a! d! q! r! a_0 a_1 d_0 d_1 q_0 q_1 q_2 q_3 r_0 r_1 r_2 r_3 )
		)
		( inv-f a! d! q! r! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f a d q r  )
		( post-f a d q r a_0 a_1 d_0 d_1 q_0 q_1 q_2 q_3 r_0 r_1 r_2 r_3 )
	)
))

