(declare-const x Int)
(declare-const n Int)
(assert ( and ( or ( < x ( + 0 0 ) ) ( > x ( + 0 0 ) ) ) ( or ( >= x ( + n 0 ) ) ( > x 0 ) ) ) )
(apply (then simplify solve-eqs))
