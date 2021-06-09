(set-logic LIA)

( declare-const SIZE Int )
( declare-const SIZE! Int )
( declare-const arr Int )
( declare-const arr! Int )
( declare-const high Int )
( declare-const high! Int )
( declare-const item Int )
( declare-const item! Int )
( declare-const low Int )
( declare-const low! Int )
( declare-const mid Int )
( declare-const mid! Int )

( declare-const SIZE_0 Int )
( declare-const SIZE_1 Int )
( declare-const arr_0 Int )
( declare-const high_0 Int )
( declare-const high_1 Int )
( declare-const high_2 Int )
( declare-const high_3 Int )
( declare-const high_4 Int )
( declare-const item_0 Int )
( declare-const item_1 Int )
( declare-const low_0 Int )
( declare-const low_1 Int )
( declare-const low_2 Int )
( declare-const low_3 Int )
( declare-const low_4 Int )
( declare-const mid_0 Int )
( declare-const mid_1 Int )
( declare-const mid_2 Int )
( declare-const mid_3 Int )
( declare-const mid_4 Int )

( define-fun inv-f( ( SIZE Int )( arr Int )( high Int )( item Int )( low Int )( mid Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( SIZE Int )( arr Int )( high Int )( item Int )( low Int )( mid Int )( SIZE_0 Int )( SIZE_1 Int )( arr_0 Int )( high_0 Int )( high_1 Int )( high_2 Int )( high_3 Int )( high_4 Int )( item_0 Int )( item_1 Int )( low_0 Int )( low_1 Int )( low_2 Int )( low_3 Int )( low_4 Int )( mid_0 Int )( mid_1 Int )( mid_2 Int )( mid_3 Int )( mid_4 Int ) ) Bool
	( and
		( = SIZE SIZE_1 )
		( = arr arr_0 )
		( = high high_1 )
		( = item item_1 )
		( = low low_1 )
		( = mid mid_1 )
		( = arr_0  )
		( = low_1 0 )
		( = mid_1 0 )
		( = item_1 0 )
		( = high_1 ( /   ) )
		( = SIZE_1 ( /   ) )
	)
)

( define-fun trans-f ( ( SIZE Int )( arr Int )( high Int )( item Int )( low Int )( mid Int )( SIZE! Int )( arr! Int )( high! Int )( item! Int )( low! Int )( mid! Int )( SIZE_0 Int )( SIZE_1 Int )( arr_0 Int )( high_0 Int )( high_1 Int )( high_2 Int )( high_3 Int )( high_4 Int )( item_0 Int )( item_1 Int )( low_0 Int )( low_1 Int )( low_2 Int )( low_3 Int )( low_4 Int )( mid_0 Int )( mid_1 Int )( mid_2 Int )( mid_3 Int )( mid_4 Int ) ) Bool
	( or
		( and
			( = high_2 high )
			( = low_2 low )
			( = mid_2 mid )
			( = high_2 high! )
			( = low_2 low! )
			( = mid_2 mid! )
			( = SIZE SIZE! )
			( = arr arr! )
			( = item item! )
			( = mid mid! )
		)
		( and
			( = high_2 high )
			( = low_2 low )
			( = mid_2 mid )
			( < low_2 high_2 )
			( = mid_3 ( >> ( + low_2 high_2 ) 1 ) )
			( < item_1  )
			( = high_3 mid_3 )
			( = high_4 high_3 )
			( = low_3 low_2 )
			( = high_4 high! )
			( = low_3 low! )
			( = mid_3 mid! )
			(= SIZE SIZE_1 )
			(= SIZE! SIZE_1 )
			(= arr arr_0 )
			(= arr! arr_0 )
			(= item item_1 )
			(= item! item_1 )
		)
		( and
			( = high_2 high )
			( = low_2 low )
			( = mid_2 mid )
			( < low_2 high_2 )
			( = mid_3 ( >> ( + low_2 high_2 ) 1 ) )
			( not ( < item_1  ) )
			( <  item_1 )
			( = low_4 ( + mid_3 1 ) )
			( = high_4 high_2 )
			( = low_3 low_4 )
			( = high_4 high! )
			( = low_3 low! )
			( = mid_3 mid! )
			(= SIZE SIZE_1 )
			(= SIZE! SIZE_1 )
			(= arr arr_0 )
			(= arr! arr_0 )
			(= item item_1 )
			(= item! item_1 )
		)
		( and
			( = mid_2 mid )
			( < low_2 high_2 )
			( = mid_3 ( >> ( + low_2 high_2 ) 1 ) )
			( not ( < item_1  ) )
			( not ( <  item_1 ) )
			( = mid_3 mid! )
			(= SIZE SIZE_1 )
			(= SIZE! SIZE_1 )
			(= arr arr_0 )
			(= arr! arr_0 )
			(= high high_1 )
			(= high! high_1 )
			(= item item_1 )
			(= item! item_1 )
			(= low low_1 )
			(= low! low_1 )
		)
	)
)

( define-fun post-f ( ( SIZE Int )( arr Int )( high Int )( item Int )( low Int )( mid Int )( SIZE_0 Int )( SIZE_1 Int )( arr_0 Int )( high_0 Int )( high_1 Int )( high_2 Int )( high_3 Int )( high_4 Int )( item_0 Int )( item_1 Int )( low_0 Int )( low_1 Int )( low_2 Int )( low_3 Int )( low_4 Int )( mid_0 Int )( mid_1 Int )( mid_2 Int )( mid_3 Int )( mid_4 Int ) ) Bool
	( and
		( or
			( not
				( and
					( = SIZE SIZE_1)
					( = arr arr_0)
					( = high high_2)
					( = item item_1)
					( = low low_2)
					( = mid mid_2)
				)
			)
			( not
				( and
					( not ( < low_2 high_2 ) )
					( = mid_4 mid_2 )
					( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 )
					( <= 0 mid_4 )
					( < mid_4 low_2 )
					( not ( =  item_1 ) )
					( not ( and ( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 ) ( or ( or ( and ( and ( <= 0 mid_4 ) ( < mid_4 low_2 ) ) ( not ( =  item_1 ) ) ) ( and ( and ( <= high_2 mid_4 ) ( <= mid_4 SIZE_1 ) ) ( not ( =  item_1 ) ) ) ) ( =  item_1 ) ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = SIZE SIZE_1)
					( = arr arr_0)
					( = high high_2)
					( = item item_1)
					( = low low_2)
					( = mid mid_2)
				)
			)
			( not
				( and
					( not ( < low_2 high_2 ) )
					( = mid_4 mid_2 )
					( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 )
					( <= 0 mid_4 )
					( < mid_4 low_2 )
					( not ( not ( =  item_1 ) ) )
					( <= high_2 mid_4 )
					( <= mid_4 SIZE_1 )
					( not ( =  item_1 ) )
					( not ( and ( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 ) ( or ( or ( and ( and ( <= 0 mid_4 ) ( < mid_4 low_2 ) ) ( not ( =  item_1 ) ) ) ( and ( and ( <= high_2 mid_4 ) ( <= mid_4 SIZE_1 ) ) ( not ( =  item_1 ) ) ) ) ( =  item_1 ) ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = SIZE SIZE_1)
					( = arr arr_0)
					( = high high_2)
					( = item item_1)
					( = low low_2)
					( = mid mid_2)
				)
			)
			( not
				( and
					( not ( < low_2 high_2 ) )
					( = mid_4 mid_2 )
					( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 )
					( <= 0 mid_4 )
					( < mid_4 low_2 )
					( not ( not ( =  item_1 ) ) )
					( <= high_2 mid_4 )
					( <= mid_4 SIZE_1 )
					( not ( not ( =  item_1 ) ) )
					( not ( and ( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 ) ( or ( or ( and ( and ( <= 0 mid_4 ) ( < mid_4 low_2 ) ) ( not ( =  item_1 ) ) ) ( and ( and ( <= high_2 mid_4 ) ( <= mid_4 SIZE_1 ) ) ( not ( =  item_1 ) ) ) ) ( =  item_1 ) ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = SIZE SIZE_1)
					( = arr arr_0)
					( = high high_2)
					( = item item_1)
					( = low low_2)
					( = mid mid_2)
				)
			)
			( not
				( and
					( not ( < low_2 high_2 ) )
					( = mid_4 mid_2 )
					( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 )
					( <= 0 mid_4 )
					( < mid_4 low_2 )
					( not ( not ( =  item_1 ) ) )
					( <= high_2 mid_4 )
					( not ( <= mid_4 SIZE_1 ) )
					( not ( and ( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 ) ( or ( or ( and ( and ( <= 0 mid_4 ) ( < mid_4 low_2 ) ) ( not ( =  item_1 ) ) ) ( and ( and ( <= high_2 mid_4 ) ( <= mid_4 SIZE_1 ) ) ( not ( =  item_1 ) ) ) ) ( =  item_1 ) ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = SIZE SIZE_1)
					( = arr arr_0)
					( = high high_2)
					( = item item_1)
					( = low low_2)
					( = mid mid_2)
				)
			)
			( not
				( and
					( not ( < low_2 high_2 ) )
					( = mid_4 mid_2 )
					( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 )
					( <= 0 mid_4 )
					( < mid_4 low_2 )
					( not ( not ( =  item_1 ) ) )
					( not ( <= high_2 mid_4 ) )
					( not ( and ( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 ) ( or ( or ( and ( and ( <= 0 mid_4 ) ( < mid_4 low_2 ) ) ( not ( =  item_1 ) ) ) ( and ( and ( <= high_2 mid_4 ) ( <= mid_4 SIZE_1 ) ) ( not ( =  item_1 ) ) ) ) ( =  item_1 ) ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = SIZE SIZE_1)
					( = arr arr_0)
					( = high high_2)
					( = item item_1)
					( = low low_2)
					( = mid mid_2)
				)
			)
			( not
				( and
					( not ( < low_2 high_2 ) )
					( = mid_4 mid_2 )
					( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 )
					( <= 0 mid_4 )
					( not ( < mid_4 low_2 ) )
					( <= high_2 mid_4 )
					( <= mid_4 SIZE_1 )
					( not ( =  item_1 ) )
					( not ( and ( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 ) ( or ( or ( and ( and ( <= 0 mid_4 ) ( < mid_4 low_2 ) ) ( not ( =  item_1 ) ) ) ( and ( and ( <= high_2 mid_4 ) ( <= mid_4 SIZE_1 ) ) ( not ( =  item_1 ) ) ) ) ( =  item_1 ) ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = SIZE SIZE_1)
					( = arr arr_0)
					( = high high_2)
					( = item item_1)
					( = low low_2)
					( = mid mid_2)
				)
			)
			( not
				( and
					( not ( < low_2 high_2 ) )
					( = mid_4 mid_2 )
					( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 )
					( <= 0 mid_4 )
					( not ( < mid_4 low_2 ) )
					( <= high_2 mid_4 )
					( <= mid_4 SIZE_1 )
					( not ( not ( =  item_1 ) ) )
					( not ( and ( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 ) ( or ( or ( and ( and ( <= 0 mid_4 ) ( < mid_4 low_2 ) ) ( not ( =  item_1 ) ) ) ( and ( and ( <= high_2 mid_4 ) ( <= mid_4 SIZE_1 ) ) ( not ( =  item_1 ) ) ) ) ( =  item_1 ) ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = SIZE SIZE_1)
					( = arr arr_0)
					( = high high_2)
					( = item item_1)
					( = low low_2)
					( = mid mid_2)
				)
			)
			( not
				( and
					( not ( < low_2 high_2 ) )
					( = mid_4 mid_2 )
					( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 )
					( <= 0 mid_4 )
					( not ( < mid_4 low_2 ) )
					( <= high_2 mid_4 )
					( not ( <= mid_4 SIZE_1 ) )
					( not ( and ( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 ) ( or ( or ( and ( and ( <= 0 mid_4 ) ( < mid_4 low_2 ) ) ( not ( =  item_1 ) ) ) ( and ( and ( <= high_2 mid_4 ) ( <= mid_4 SIZE_1 ) ) ( not ( =  item_1 ) ) ) ) ( =  item_1 ) ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = SIZE SIZE_1)
					( = arr arr_0)
					( = high high_2)
					( = item item_1)
					( = low low_2)
					( = mid mid_2)
				)
			)
			( not
				( and
					( not ( < low_2 high_2 ) )
					( = mid_4 mid_2 )
					( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 )
					( <= 0 mid_4 )
					( not ( < mid_4 low_2 ) )
					( not ( <= high_2 mid_4 ) )
					( not ( and ( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 ) ( or ( or ( and ( and ( <= 0 mid_4 ) ( < mid_4 low_2 ) ) ( not ( =  item_1 ) ) ) ( and ( and ( <= high_2 mid_4 ) ( <= mid_4 SIZE_1 ) ) ( not ( =  item_1 ) ) ) ) ( =  item_1 ) ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = SIZE SIZE_1)
					( = arr arr_0)
					( = high high_2)
					( = item item_1)
					( = low low_2)
					( = mid mid_2)
				)
			)
			( not
				( and
					( not ( < low_2 high_2 ) )
					( = mid_4 mid_2 )
					( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 )
					( not ( <= 0 mid_4 ) )
					( <= high_2 mid_4 )
					( <= mid_4 SIZE_1 )
					( not ( =  item_1 ) )
					( not ( and ( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 ) ( or ( or ( and ( and ( <= 0 mid_4 ) ( < mid_4 low_2 ) ) ( not ( =  item_1 ) ) ) ( and ( and ( <= high_2 mid_4 ) ( <= mid_4 SIZE_1 ) ) ( not ( =  item_1 ) ) ) ) ( =  item_1 ) ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = SIZE SIZE_1)
					( = arr arr_0)
					( = high high_2)
					( = item item_1)
					( = low low_2)
					( = mid mid_2)
				)
			)
			( not
				( and
					( not ( < low_2 high_2 ) )
					( = mid_4 mid_2 )
					( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 )
					( not ( <= 0 mid_4 ) )
					( <= high_2 mid_4 )
					( <= mid_4 SIZE_1 )
					( not ( not ( =  item_1 ) ) )
					( not ( and ( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 ) ( or ( or ( and ( and ( <= 0 mid_4 ) ( < mid_4 low_2 ) ) ( not ( =  item_1 ) ) ) ( and ( and ( <= high_2 mid_4 ) ( <= mid_4 SIZE_1 ) ) ( not ( =  item_1 ) ) ) ) ( =  item_1 ) ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = SIZE SIZE_1)
					( = arr arr_0)
					( = high high_2)
					( = item item_1)
					( = low low_2)
					( = mid mid_2)
				)
			)
			( not
				( and
					( not ( < low_2 high_2 ) )
					( = mid_4 mid_2 )
					( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 )
					( not ( <= 0 mid_4 ) )
					( <= high_2 mid_4 )
					( not ( <= mid_4 SIZE_1 ) )
					( not ( and ( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 ) ( or ( or ( and ( and ( <= 0 mid_4 ) ( < mid_4 low_2 ) ) ( not ( =  item_1 ) ) ) ( and ( and ( <= high_2 mid_4 ) ( <= mid_4 SIZE_1 ) ) ( not ( =  item_1 ) ) ) ) ( =  item_1 ) ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = SIZE SIZE_1)
					( = arr arr_0)
					( = high high_2)
					( = item item_1)
					( = low low_2)
					( = mid mid_2)
				)
			)
			( not
				( and
					( not ( < low_2 high_2 ) )
					( = mid_4 mid_2 )
					( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 )
					( not ( <= 0 mid_4 ) )
					( not ( <= high_2 mid_4 ) )
					( not ( and ( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 ) ( or ( or ( and ( and ( <= 0 mid_4 ) ( < mid_4 low_2 ) ) ( not ( =  item_1 ) ) ) ( and ( and ( <= high_2 mid_4 ) ( <= mid_4 SIZE_1 ) ) ( not ( =  item_1 ) ) ) ) ( =  item_1 ) ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = SIZE SIZE_1)
					( = arr arr_0)
					( = high high_2)
					( = item item_1)
					( = low low_2)
					( = mid mid_2)
				)
			)
			( not
				( and
					( not ( < low_2 high_2 ) )
					( = mid_4 mid_2 )
					( not ( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 ) )
					( not ( and ( <= ( <= ( <= 0 low_2 ) mid_4 ) high_2 ) ( or ( or ( and ( and ( <= 0 mid_4 ) ( < mid_4 low_2 ) ) ( not ( =  item_1 ) ) ) ( and ( and ( <= high_2 mid_4 ) ( <= mid_4 SIZE_1 ) ) ( not ( =  item_1 ) ) ) ) ( =  item_1 ) ) ) )
				)
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f SIZE arr high item low mid SIZE_0 SIZE_1 arr_0 high_0 high_1 high_2 high_3 high_4 item_0 item_1 low_0 low_1 low_2 low_3 low_4 mid_0 mid_1 mid_2 mid_3 mid_4  )
		( inv-f SIZE arr high item low mid )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f SIZE arr high item low mid )
			( trans-f SIZE arr high item low mid SIZE! arr! high! item! low! mid! SIZE_0 SIZE_1 arr_0 high_0 high_1 high_2 high_3 high_4 item_0 item_1 low_0 low_1 low_2 low_3 low_4 mid_0 mid_1 mid_2 mid_3 mid_4 )
		)
		( inv-f SIZE! arr! high! item! low! mid! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f SIZE arr high item low mid  )
		( post-f SIZE arr high item low mid SIZE_0 SIZE_1 arr_0 high_0 high_1 high_2 high_3 high_4 item_0 item_1 low_0 low_1 low_2 low_3 low_4 mid_0 mid_1 mid_2 mid_3 mid_4 )
	)
))

