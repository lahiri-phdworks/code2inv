(set-logic LIA)

( declare-const arr Int )
( declare-const arr! Int )
( declare-const high Int )
( declare-const high! Int )
( declare-const i Int )
( declare-const i! Int )
( declare-const j Int )
( declare-const j! Int )
( declare-const pivot Int )
( declare-const pivot! Int )

( declare-const arr_0 Int )
( declare-const high_0 Int )
( declare-const high_1 Int )
( declare-const i_0 Int )
( declare-const i_1 Int )
( declare-const i_2 Int )
( declare-const i_3 Int )
( declare-const i_4 Int )
( declare-const j_0 Int )
( declare-const j_1 Int )
( declare-const j_2 Int )
( declare-const j_3 Int )
( declare-const pivot_0 Int )
( declare-const pivot_1 Int )

( define-fun inv-f( ( arr Int )( high Int )( i Int )( j Int )( pivot Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( arr Int )( high Int )( i Int )( j Int )( pivot Int )( arr_0 Int )( high_0 Int )( high_1 Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( i_4 Int )( j_0 Int )( j_1 Int )( j_2 Int )( j_3 Int )( pivot_0 Int )( pivot_1 Int ) ) Bool
	( and
		( = arr arr_0 )
		( = high high_1 )
		( = i i_1 )
		( = j j_1 )
		( = pivot pivot_1 )
		( = arr_0  )
		( = high_1 ( - ( /   ) 1 ) )
		( = pivot_1  )
		( = i_1 0 )
		( = j_1 0 )
	)
)

( define-fun trans-f ( ( arr Int )( high Int )( i Int )( j Int )( pivot Int )( arr! Int )( high! Int )( i! Int )( j! Int )( pivot! Int )( arr_0 Int )( high_0 Int )( high_1 Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( i_4 Int )( j_0 Int )( j_1 Int )( j_2 Int )( j_3 Int )( pivot_0 Int )( pivot_1 Int ) ) Bool
	( or
		( and
			( = i_2 i )
			( = j_2 j )
			( = i_2 i! )
			( = j_2 j! )
			( = high high_1 )
			( = high! high_1 )
			( = arr arr! )
			( = i i! )
			( = pivot pivot! )
		)
		( and
			( = i_2 i )
			( = j_2 j )
			( <= j_2 ( - high_1 1 ) )
			( <  pivot_1 )
			( = i_3 ( + i_2 1 ) )
			( = i_4 i_3 )
			( = j_3 ( + j_2 1 ) )
			( = i_4 i! )
			( = j_3 j! )
			(= arr arr_0 )
			(= arr! arr_0 )
			(= high high_1 )
			(= high! high_1 )
			(= pivot pivot_1 )
			(= pivot! pivot_1 )
		)
		( and
			( = i_2 i )
			( = j_2 j )
			( <= j_2 ( - high_1 1 ) )
			( not ( <  pivot_1 ) )
			( = i_4 i_2 )
			( = j_3 ( + j_2 1 ) )
			( = i_4 i! )
			( = j_3 j! )
			(= arr arr_0 )
			(= arr! arr_0 )
			(= high high_1 )
			(= high! high_1 )
			(= pivot pivot_1 )
			(= pivot! pivot_1 )
		)
	)
)

( define-fun post-f ( ( arr Int )( high Int )( i Int )( j Int )( pivot Int )( arr_0 Int )( high_0 Int )( high_1 Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( i_4 Int )( j_0 Int )( j_1 Int )( j_2 Int )( j_3 Int )( pivot_0 Int )( pivot_1 Int ) ) Bool
	( and
		( or
			( not
				( and
					( = arr arr_0)
					( = high high_1)
					( = i i_2)
					( = j j_2)
					( = pivot pivot_1)
				)
			)
			( not
				( and
					( not ( <= j_2 ( - high_1 1 ) ) )
					( <= ( <= 0 i_2 ) high_1 )
					( <  pivot_1 )
					( =  pivot_1 )
					( not ( and ( and ( and ( <= ( <= 0 i_2 ) high_1 ) ( <  pivot_1 ) ) ( =  pivot_1 ) ) ( >  pivot_1 ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = arr arr_0)
					( = high high_1)
					( = i i_2)
					( = j j_2)
					( = pivot pivot_1)
				)
			)
			( not
				( and
					( not ( <= j_2 ( - high_1 1 ) ) )
					( <= ( <= 0 i_2 ) high_1 )
					( <  pivot_1 )
					( not ( =  pivot_1 ) )
					( not ( and ( and ( and ( <= ( <= 0 i_2 ) high_1 ) ( <  pivot_1 ) ) ( =  pivot_1 ) ) ( >  pivot_1 ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = arr arr_0)
					( = high high_1)
					( = i i_2)
					( = j j_2)
					( = pivot pivot_1)
				)
			)
			( not
				( and
					( not ( <= j_2 ( - high_1 1 ) ) )
					( <= ( <= 0 i_2 ) high_1 )
					( not ( <  pivot_1 ) )
					( not ( and ( and ( and ( <= ( <= 0 i_2 ) high_1 ) ( <  pivot_1 ) ) ( =  pivot_1 ) ) ( >  pivot_1 ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = arr arr_0)
					( = high high_1)
					( = i i_2)
					( = j j_2)
					( = pivot pivot_1)
				)
			)
			( not
				( and
					( not ( <= j_2 ( - high_1 1 ) ) )
					( not ( <= ( <= 0 i_2 ) high_1 ) )
					( not ( and ( and ( and ( <= ( <= 0 i_2 ) high_1 ) ( <  pivot_1 ) ) ( =  pivot_1 ) ) ( >  pivot_1 ) ) )
				)
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f arr high i j pivot arr_0 high_0 high_1 i_0 i_1 i_2 i_3 i_4 j_0 j_1 j_2 j_3 pivot_0 pivot_1  )
		( inv-f arr high i j pivot )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f arr high i j pivot )
			( trans-f arr high i j pivot arr! high! i! j! pivot! arr_0 high_0 high_1 i_0 i_1 i_2 i_3 i_4 j_0 j_1 j_2 j_3 pivot_0 pivot_1 )
		)
		( inv-f arr! high! i! j! pivot! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f arr high i j pivot  )
		( post-f arr high i j pivot arr_0 high_0 high_1 i_0 i_1 i_2 i_3 i_4 j_0 j_1 j_2 j_3 pivot_0 pivot_1 )
	)
))

