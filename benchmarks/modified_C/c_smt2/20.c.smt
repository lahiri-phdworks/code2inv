(set-logic LIA)

( declare-const m Int )
( declare-const m! Int )
( declare-const n Int )
( declare-const n! Int )
( declare-const temp_m Int )
( declare-const temp_m! Int )
( declare-const temp_n Int )
( declare-const temp_n! Int )
( declare-const temp_x Int )
( declare-const temp_x! Int )
( declare-const x Int )
( declare-const x! Int )
( declare-const tmp Int )
( declare-const tmp! Int )

( declare-const m_0 Int )
( declare-const m_1 Int )
( declare-const m_2 Int )
( declare-const m_3 Int )
( declare-const m_4 Int )
( declare-const n_0 Int )
( declare-const temp_m_0 Int )
( declare-const temp_m_1 Int )
( declare-const temp_n_0 Int )
( declare-const temp_n_1 Int )
( declare-const temp_x_0 Int )
( declare-const temp_x_1 Int )
( declare-const x_0 Int )
( declare-const x_1 Int )
( declare-const x_2 Int )
( declare-const x_3 Int )

( define-fun inv-f( ( m Int )( n Int )( temp_m Int )( temp_n Int )( temp_x Int )( x Int )( tmp Int ) ) Bool
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
)

( define-fun pre-f ( ( m Int )( n Int )( temp_m Int )( temp_n Int )( temp_x Int )( x Int )( tmp Int )( m_0 Int )( m_1 Int )( m_2 Int )( m_3 Int )( m_4 Int )( n_0 Int )( temp_m_0 Int )( temp_m_1 Int )( temp_n_0 Int )( temp_n_1 Int )( temp_x_0 Int )( temp_x_1 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int ) ) Bool
	( and
		( = m m_1 )
		( = x x_1 )
		( = x_1 0 )
		( = m_1 0 )
	)
)

( define-fun trans-f ( ( m Int )( n Int )( temp_m Int )( temp_n Int )( temp_x Int )( x Int )( tmp Int )( m! Int )( n! Int )( temp_m! Int )( temp_n! Int )( temp_x! Int )( x! Int )( tmp! Int )( m_0 Int )( m_1 Int )( m_2 Int )( m_3 Int )( m_4 Int )( n_0 Int )( temp_m_0 Int )( temp_m_1 Int )( temp_n_0 Int )( temp_n_1 Int )( temp_x_0 Int )( temp_x_1 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int ) ) Bool
	( or
		( and
			( = m_2 m )
			( = temp_m_0 temp_m )
			( = temp_n_0 temp_n )
			( = temp_x_0 temp_x )
			( = x_2 x )
			( = m_2 m! )
			( = temp_m_0 temp_m! )
			( = temp_n_0 temp_n! )
			( = temp_x_0 temp_x! )
			( = x_2 x! )
			( = n n_0 )
			( = n! n_0 )
			( = m m! )
			( = temp_m temp_m! )
			( = temp_n temp_n! )
			( = temp_x temp_x! )
			(= tmp tmp! )
		)
		( and
			( = m_2 m )
			( = temp_m_0 temp_m )
			( = temp_n_0 temp_n )
			( = temp_x_0 temp_x )
			( = x_2 x )
			( < x_2 n_0 )
			( = temp_x_1 x_2 )
			( = temp_m_1 m_2 )
			( = temp_n_1 n_0 )
			( = m_3 x_2 )
			( = x_3  )
			( = m_3 m! )
			( = temp_m_1 temp_m! )
			( = temp_n_1 temp_n! )
			( = temp_x_1 temp_x! )
			( = x_3 x! )
			(= n n_0 )
			(= n! n_0 )
			(= tmp tmp! )
		)
		( and
			( = temp_m_0 temp_m )
			( = temp_n_0 temp_n )
			( = temp_x_0 temp_x )
			( = x_2 x )
			( < x_2 n_0 )
			( = temp_x_1 x_2 )
			( = temp_m_1 m_2 )
			( = temp_n_1 n_0 )
			( = x_3  )
			( = temp_m_1 temp_m! )
			( = temp_n_1 temp_n! )
			( = temp_x_1 temp_x! )
			( = x_3 x! )
			(= m m_1 )
			(= m! m_1 )
			(= n n_0 )
			(= n! n_0 )
			(= tmp tmp! )
		)
	)
)

( define-fun post-f ( ( m Int )( n Int )( temp_m Int )( temp_n Int )( temp_x Int )( x Int )( tmp Int )( m_0 Int )( m_1 Int )( m_2 Int )( m_3 Int )( m_4 Int )( n_0 Int )( temp_m_0 Int )( temp_m_1 Int )( temp_n_0 Int )( temp_n_1 Int )( temp_x_0 Int )( temp_x_1 Int )( x_0 Int )( x_1 Int )( x_2 Int )( x_3 Int ) ) Bool
	( or
		( not
			( and
				( = m m_2)
				( = n n_0 )
				( = temp_m temp_m_0)
				( = temp_n temp_n_0)
				( = temp_x temp_x_0)
				( = x x_2)
			)
		)
		( not
			( and
				( not ( < x_2 n_0 ) )
				( > n_0 0 )
				( not ( >= m_2 0 ) )
			)
		)
	)
)
SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( pre-f m n temp_m temp_n temp_x x tmp m_0 m_1 m_2 m_3 m_4 n_0 temp_m_0 temp_m_1 temp_n_0 temp_n_1 temp_x_0 temp_x_1 x_0 x_1 x_2 x_3  )
		( inv-f m n temp_m temp_n temp_x x tmp )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( and
			( inv-f m n temp_m temp_n temp_x x tmp )
			( trans-f m n temp_m temp_n temp_x x tmp m! n! temp_m! temp_n! temp_x! x! tmp! m_0 m_1 m_2 m_3 m_4 n_0 temp_m_0 temp_m_1 temp_n_0 temp_n_1 temp_x_0 temp_x_1 x_0 x_1 x_2 x_3 )
		)
		( inv-f m! n! temp_m! temp_n! temp_x! x! tmp! )
	)
))

SPLIT_HERE_asdfghjklzxcvbnmqwertyuiop
( assert ( not
	( =>
		( inv-f m n temp_m temp_n temp_x x tmp  )
		( post-f m n temp_m temp_n temp_x x tmp m_0 m_1 m_2 m_3 m_4 n_0 temp_m_0 temp_m_1 temp_n_0 temp_n_1 temp_x_0 temp_x_1 x_0 x_1 x_2 x_3 )
	)
))

