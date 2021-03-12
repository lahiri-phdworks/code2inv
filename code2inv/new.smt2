(declare-const x Int)
(declare-const y Int)
(assert ( and ( <= y ( + 1 1 ) ) ( or ( <= x ( - 1 1 ) ) ( > x 0 ) ) ) )
(apply (then simplify solve-eqs))
