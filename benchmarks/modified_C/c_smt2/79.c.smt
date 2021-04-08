(set-logic LIA)

( declare-const i Int )
( declare-const i! Int )
( declare-const temp_i Int )
( declare-const temp_i! Int )
( declare-const temp_x Int )
( declare-const temp_x! Int )
( declare-const temp_y Int )
( declare-const temp_y! Int )
( declare-const x Int )
( declare-const x! Int )
( declare-const y Int )
( declare-const y! Int )
( declare-const tmp Int )
( declare-const tmp! Int )

( declare-const i_0 Int )
( declare-const i_1 Int )
( declare-const i_2 Int )
( declare-const i_3 Int )
( declare-const i_4 Int )
( declare-const temp_i_0 Int )
( declare-const temp_i_1 Int )
( declare-const temp_x_0 Int )
( declare-const temp_x_1 Int )
( declare-const temp_y_0 Int )
( declare-const temp_y_1 Int )
( declare-const x_0 Int )
( declare-const y_0 Int )

( define-fun inv-f( ( i Int )( temp_i Int )( temp_x Int )( temp_y Int )( x Int )( y Int )( tmp Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( i Int )( temp_i Int )( temp_x Int )( temp_y Int )( x Int )( y Int )( tmp Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( i_4 Int )( temp_i_0 Int )( temp_i_1 Int )( temp_x_0 Int )( temp_x_1 Int )( temp_y_0 Int )( temp_y_1 Int )( x_0 Int )( y_0 Int ) ) Bool
	( and
		( = i i_1 )
		( = x x_0 )
		( = y y_0 )
		( = i_1 0 )
		( >= x_0 0 )
		( >= y_0 0 )
		( >= x_0 y_0 )
	)
)

( define-fun trans-f ( ( i Int )( temp_i Int )( temp_x Int )( temp_y Int )( x Int )( y Int )( tmp Int )( i! Int )( temp_i! Int )( temp_x! Int )( temp_y! Int )( x! Int )( y! Int )( tmp! Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( i_4 Int )( temp_i_0 Int )( temp_i_1 Int )( temp_x_0 Int )( temp_x_1 Int )( temp_y_0 Int )( temp_y_1 Int )( x_0 Int )( y_0 Int ) ) Bool
	( or
		( and
			( = i_2 i )
			( = temp_i_0 temp_i )
			( = temp_x_0 temp_x )
			( = temp_y_0 temp_y )
			( = i_2 i! )
			( = temp_i_0 temp_i! )
			( = temp_x_0 temp_x! )
			( = temp_y_0 temp_y! )
			( = i i! )
			( = temp_i temp_i! )
			( = temp_x temp_x! )
			( = temp_y temp_y! )
			( = x x! )
			( = y y! )
			(= tmp tmp! )
		)
		( and
			( = i_2 i )
			( = temp_i_0 temp_i )
			( = temp_x_0 temp_x )
			( = temp_y_0 temp_y )
			( = temp_i_1 i_2 )
			( = temp_x_1 x_0 )
			( = temp_y_1 y_0 )
			( < i_2 y_0 )
			( = i_3  )
			( = i_4 i_3 )
			( = i_4 i! )
			( = temp_i_1 temp_i! )
			( = temp_x_1 temp_x! )
			( = temp_y_1 temp_y! )
			(= x x_0 )
			(= x! x_0 )
			(= y y_0 )
			(= y! y_0 )
			(= tmp tmp! )
		)
		( and
			( = i_2 i )
			( = temp_i_0 temp_i )
			( = temp_x_0 temp_x )
			( = temp_y_0 temp_y )
			( = temp_i_1 i_2 )
			( = temp_x_1 x_0 )
			( = temp_y_1 y_0 )
			( not ( < i_2 y_0 ) )
			( = i_4 i_2 )
			( = i_4 i! )
			( = temp_i_1 temp_i! )
			( = temp_x_1 temp_x! )
			( = temp_y_1 temp_y! )
			(= x x_0 )
			(= x! x_0 )
			(= y y_0 )
			(= y! y_0 )
			(= tmp tmp! )
		)
	)
)

( define-fun post-f ( ( i Int )( temp_i Int )( temp_x Int )( temp_y Int )( x Int )( y Int )( tmp Int )( i_0 Int )( i_1 Int )( i_2 Int )( i_3 Int )( i_4 Int )( temp_i_0 Int )( temp_i_1 Int )( temp_x_0 Int )( temp_x_1 Int )( temp_y_0 Int )( temp_y_1 Int )( x_0 Int )( y_0 Int ) ) Bool
	( or
		( not
			( and
				( = i i_2)
				( = temp_i temp_i_0)
				( = temp_x temp_x_0)
				( = temp_y temp_y_0)
				( = x x_0)
				( = y y_0)
			)
		)
		( not
			( and
				( >= i_2 x_0 )
				( > 0 i_2 )
				( not ( >= i_2 y_0 ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f i temp_i temp_x temp_y x y tmp i_0 i_1 i_2 i_3 i_4 temp_i_0 temp_i_1 temp_x_0 temp_x_1 temp_y_0 temp_y_1 x_0 y_0  )
		( inv-f i temp_i temp_x temp_y x y tmp )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f i temp_i temp_x temp_y x y tmp )
			( trans-f i temp_i temp_x temp_y x y tmp i! temp_i! temp_x! temp_y! x! y! tmp! i_0 i_1 i_2 i_3 i_4 temp_i_0 temp_i_1 temp_x_0 temp_x_1 temp_y_0 temp_y_1 x_0 y_0 )
		)
		( inv-f i! temp_i! temp_x! temp_y! x! y! tmp! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f i temp_i temp_x temp_y x y tmp  )
		( post-f i temp_i temp_x temp_y x y tmp i_0 i_1 i_2 i_3 i_4 temp_i_0 temp_i_1 temp_x_0 temp_x_1 temp_y_0 temp_y_1 x_0 y_0 )
	)
))

