(set-logic LIA)

( declare-const a Int )
( declare-const a! Int )
( declare-const d Int )
( declare-const d! Int )
( declare-const power Int )
( declare-const power! Int )
( declare-const result Int )
( declare-const result! Int )
( declare-const x Int )
( declare-const x! Int )
( declare-const y Int )
( declare-const y! Int )
( declare-const y_power Int )
( declare-const y_power! Int )

( declare-const a_0 Int )
( declare-const a_1 Int )
( declare-const d_0 Int )
( declare-const d_1 Int )
( declare-const power_0 Int )
( declare-const power_1 Int )
( declare-const power_2 Int )
( declare-const power_3 Int )
( declare-const power_4 Int )
( declare-const result_0 Int )
( declare-const result_1 Int )
( declare-const x_0 Int )
( declare-const x_1 Int )
( declare-const x_2 Int )
( declare-const x_3 Int )
( declare-const y_0 Int )
( declare-const y_1 Int )
( declare-const y_power_0 Int )
( declare-const y_power_1 Int )
( declare-const y_power_2 Int )

( define-fun inv-f( ( a Int )( d Int )( power Int )( result Int )( x Int )( y Int )( y_power Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( a Int )( d Int )( power Int )( result Int )( x Int )( y Int )( y_power Int )( a_0 Int )( a_1 Int )( d_0 Int )( d_1 Int )( power_0 Int )( power_1 Int )( power_2 Int )( power_3 Int )( power_4 Int )( result_0 Int )( result_1 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int )( y_0 Int )( y_1 Int )( y_power_0 Int )( y_power_1 Int )( y_power_2 Int ) ) Bool
	( or
		( and
			( = a a_1 )
			( = d d_1 )
			( = power power_2 )
			( = result result_1 )
			( = x x_2 )
			( = y y_1 )
			( = y_power y_power_1 )
			( = a_1 7454 )
			( = d_1 13 )
			( = x_1 a_1 )
			( = y_1 d_1 )
			( = power_1 31 )
			( = result_1 0 )
			( = y_power_1 ( << y_1 power_1 ) )
			( = power_2 power_1 )
			( = x_2 x_1 )
			( >= x_2 y_1 )
		)
	)
)

( define-fun trans-f ( ( a Int )( d Int )( power Int )( result Int )( x Int )( y Int )( y_power Int )( a! Int )( d! Int )( power! Int )( result! Int )( x! Int )( y! Int )( y_power! Int )( a_0 Int )( a_1 Int )( d_0 Int )( d_1 Int )( power_0 Int )( power_1 Int )( power_2 Int )( power_3 Int )( power_4 Int )( result_0 Int )( result_1 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int )( y_0 Int )( y_1 Int )( y_power_0 Int )( y_power_1 Int )( y_power_2 Int ) ) Bool
	( or
		( and
			( = power_3 power )
			( = power_3 power! )
			( = y_power y_power_1 )
			( = y_power! y_power_1 )
			( = x x_2 )
			( = x! x_2 )
			( = a a! )
			( = d d! )
			( = power power! )
			( = result result! )
			( = y y! )
		)
		( and
			( = power_3 power )
			( > y_power_1 x_2 )
			( = power_4 ( - power_3 1 ) )
			( = power_4 power! )
			(= a a_1 )
			(= a! a_1 )
			(= d d_1 )
			(= d! d_1 )
			(= result result_1 )
			(= result! result_1 )
			(= x x_2 )
			(= x! x_2 )
			(= y y_1 )
			(= y! y_1 )
			(= y_power y_power_1 )
			(= y_power! y_power_1 )
		)
	)
)

( define-fun post-f ( ( a Int )( d Int )( power Int )( result Int )( x Int )( y Int )( y_power Int )( a_0 Int )( a_1 Int )( d_0 Int )( d_1 Int )( power_0 Int )( power_1 Int )( power_2 Int )( power_3 Int )( power_4 Int )( result_0 Int )( result_1 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int )( y_0 Int )( y_1 Int )( y_power_0 Int )( y_power_1 Int )( y_power_2 Int ) ) Bool
	( and
		( or
			( not
				( and
					( = a a_1)
					( = d d_1)
					( = power power_3)
					( = result result_1)
					( = x x_2)
					( = y y_1)
					( = y_power y_power_1)
				)
			)
			( not
				( and
					( not ( > y_power_1 x_2 ) )
					( = x_3 ( - x_2 y_power_1 ) )
					( = power_2 power_3 )
					( = x_2 x_3 )
					( not ( >= x_2 y_1 ) )
					( < ( <= 0 x_2 ) d_1 )
					( not ( and ( < ( <= 0 x_2 ) d_1 ) ( = a_1 ( + ( * result_1 d_1 ) x_2 ) ) ) )
				)
			)
		)
		( or
			( not
				( and
					( = a a_1)
					( = d d_1)
					( = power power_3)
					( = result result_1)
					( = x x_2)
					( = y y_1)
					( = y_power y_power_1)
				)
			)
			( not
				( and
					( not ( > y_power_1 x_2 ) )
					( = x_3 ( - x_2 y_power_1 ) )
					( = power_2 power_3 )
					( = x_2 x_3 )
					( not ( >= x_2 y_1 ) )
					( not ( < ( <= 0 x_2 ) d_1 ) )
					( not ( and ( < ( <= 0 x_2 ) d_1 ) ( = a_1 ( + ( * result_1 d_1 ) x_2 ) ) ) )
				)
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f a d power result x y y_power a_0 a_1 d_0 d_1 power_0 power_1 power_2 power_3 power_4 result_0 result_1 x_0 x_1 x_2 x_3 y_0 y_1 y_power_0 y_power_1 y_power_2  )
		( inv-f a d power result x y y_power )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f a d power result x y y_power )
			( trans-f a d power result x y y_power a! d! power! result! x! y! y_power! a_0 a_1 d_0 d_1 power_0 power_1 power_2 power_3 power_4 result_0 result_1 x_0 x_1 x_2 x_3 y_0 y_1 y_power_0 y_power_1 y_power_2 )
		)
		( inv-f a! d! power! result! x! y! y_power! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f a d power result x y y_power  )
		( post-f a d power result x y y_power a_0 a_1 d_0 d_1 power_0 power_1 power_2 power_3 power_4 result_0 result_1 x_0 x_1 x_2 x_3 y_0 y_1 y_power_0 y_power_1 y_power_2 )
	)
))

