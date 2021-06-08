(set-logic LIA)

( declare-const left Int )
( declare-const left! Int )
( declare-const mid Int )
( declare-const mid! Int )
( declare-const n Int )
( declare-const n! Int )
( declare-const right Int )
( declare-const right! Int )

( declare-const left_0 Int )
( declare-const left_1 Int )
( declare-const left_2 Int )
( declare-const left_3 Int )
( declare-const left_4 Int )
( declare-const mid_0 Int )
( declare-const mid_1 Int )
( declare-const mid_2 Int )
( declare-const n_0 Int )
( declare-const n_1 Int )
( declare-const right_0 Int )
( declare-const right_1 Int )
( declare-const right_2 Int )
( declare-const right_3 Int )
( declare-const right_4 Int )

( define-fun inv-f( ( left Int )( mid Int )( n Int )( right Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( left Int )( mid Int )( n Int )( right Int )( left_0 Int )( left_1 Int )( left_2 Int )( left_3 Int )( left_4 Int )( mid_0 Int )( mid_1 Int )( mid_2 Int )( n_0 Int )( n_1 Int )( right_0 Int )( right_1 Int )( right_2 Int )( right_3 Int )( right_4 Int ) ) Bool
	( and
		( = left left_1 )
		( = n n_1 )
		( = right right_1 )
		( = n_1 154 )
		( = left_1 0 )
		( = right_1 n_1 )
	)
)

( define-fun trans-f ( ( left Int )( mid Int )( n Int )( right Int )( left! Int )( mid! Int )( n! Int )( right! Int )( left_0 Int )( left_1 Int )( left_2 Int )( left_3 Int )( left_4 Int )( mid_0 Int )( mid_1 Int )( mid_2 Int )( n_0 Int )( n_1 Int )( right_0 Int )( right_1 Int )( right_2 Int )( right_3 Int )( right_4 Int ) ) Bool
	( or
		( and
			( = left_2 left )
			( = mid_1 mid )
			( = right_2 right )
			( = left_2 left! )
			( = mid_1 mid! )
			( = right_2 right! )
			( = mid mid! )
			( = n n! )
		)
		( and
			( = left_2 left )
			( = mid_1 mid )
			( = right_2 right )
			( <= left_2 right_2 )
			( = mid_2 ( / ( + left_2 right_2 ) 2 ) )
			( <= ( * mid_2 mid_2 ) n_1 )
			( = left_3 ( + mid_2 1 ) )
			( = left_4 left_3 )
			( = right_3 right_2 )
			( = left_4 left! )
			( = mid_2 mid! )
			( = right_3 right! )
			(= n n_1 )
			(= n! n_1 )
		)
		( and
			( = left_2 left )
			( = mid_1 mid )
			( = right_2 right )
			( <= left_2 right_2 )
			( = mid_2 ( / ( + left_2 right_2 ) 2 ) )
			( not ( <= ( * mid_2 mid_2 ) n_1 ) )
			( = right_4 ( - mid_2 1 ) )
			( = left_4 left_2 )
			( = right_3 right_4 )
			( = left_4 left! )
			( = mid_2 mid! )
			( = right_3 right! )
			(= n n_1 )
			(= n! n_1 )
		)
	)
)

( define-fun post-f ( ( left Int )( mid Int )( n Int )( right Int )( left_0 Int )( left_1 Int )( left_2 Int )( left_3 Int )( left_4 Int )( mid_0 Int )( mid_1 Int )( mid_2 Int )( n_0 Int )( n_1 Int )( right_0 Int )( right_1 Int )( right_2 Int )( right_3 Int )( right_4 Int ) ) Bool
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f left mid n right left_0 left_1 left_2 left_3 left_4 mid_0 mid_1 mid_2 n_0 n_1 right_0 right_1 right_2 right_3 right_4  )
		( inv-f left mid n right )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f left mid n right )
			( trans-f left mid n right left! mid! n! right! left_0 left_1 left_2 left_3 left_4 mid_0 mid_1 mid_2 n_0 n_1 right_0 right_1 right_2 right_3 right_4 )
		)
		( inv-f left! mid! n! right! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f left mid n right  )
		( post-f left mid n right left_0 left_1 left_2 left_3 left_4 mid_0 mid_1 mid_2 n_0 n_1 right_0 right_1 right_2 right_3 right_4 )
	)
))

