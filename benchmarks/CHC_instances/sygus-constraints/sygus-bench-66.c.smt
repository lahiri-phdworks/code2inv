(set-info :original "/tmp/sea-aVHngw/66.pp.ms.o.bc")
(set-info :authors "SeaHorn v.0.1.0-rc3")
(declare-rel verifier.error (Bool Bool Bool ))
(declare-rel main@entry (Int ))
(declare-rel main@_bb (Int Int ))
(declare-rel main@verifier.error.split ())
(declare-var main@%_8_0 Bool )
(declare-var main@%_9_0 Bool )
(declare-var main@%_3_0 Bool )
(declare-var main@%_0_0 Int )
(declare-var @unknown_0 Int )
(declare-var main@%y.0.i_2 Int )
(declare-var main@entry_0 Bool )
(declare-var main@%_1_0 Int )
(declare-var main@_bb_0 Bool )
(declare-var main@%x.0.i_0 Int )
(declare-var main@%y.0.i_0 Int )
(declare-var main@%x.0.i_1 Int )
(declare-var main@%y.0.i_1 Int )
(declare-var main@_bb1_0 Bool )
(declare-var main@%_5_0 Int )
(declare-var main@%_6_0 Int )
(declare-var main@_bb_1 Bool )
(declare-var main@%x.0.i_2 Int )
(declare-var main@_bb2_0 Bool )
(declare-var main@_bb3_0 Bool )
(declare-var main@verifier.error_0 Bool )
(declare-var main@verifier.error.split_0 Bool )
(rule (verifier.error false false false))
(rule (verifier.error false true true))
(rule (verifier.error true false true))
(rule (verifier.error true true true))
(rule (main@entry @unknown_0))
(rule (=> (and (main@entry @unknown_0)
         true
         (= main@%_0_0 @unknown_0)
         (=> main@_bb_0 (and main@_bb_0 main@entry_0))
         main@_bb_0
         (=> (and main@_bb_0 main@entry_0) (= main@%x.0.i_0 1))
         (=> (and main@_bb_0 main@entry_0) (= main@%y.0.i_0 main@%_1_0))
         (=> (and main@_bb_0 main@entry_0) (= main@%x.0.i_1 main@%x.0.i_0))
         (=> (and main@_bb_0 main@entry_0) (= main@%y.0.i_1 main@%y.0.i_0)))
    (main@_bb main@%x.0.i_1 main@%y.0.i_1)))
(rule (let ((a!1 (and (main@_bb main@%x.0.i_0 main@%y.0.i_0)
                true
                (= main@%_3_0 (< main@%x.0.i_0 101))
                (=> main@_bb1_0 (and main@_bb1_0 main@_bb_0))
                (=> (and main@_bb1_0 main@_bb_0) main@%_3_0)
                (=> main@_bb1_0 (= main@%_5_0 (- 100 main@%x.0.i_0)))
                (=> main@_bb1_0 (= main@%_6_0 (+ main@%x.0.i_0 1)))
                (=> main@_bb_1 (and main@_bb_1 main@_bb1_0))
                main@_bb_1
                (=> (and main@_bb_1 main@_bb1_0) (= main@%x.0.i_1 main@%_6_0))
                (=> (and main@_bb_1 main@_bb1_0) (= main@%y.0.i_1 main@%_5_0))
                (=> (and main@_bb_1 main@_bb1_0)
                    (= main@%x.0.i_2 main@%x.0.i_1))
                (=> (and main@_bb_1 main@_bb1_0)
                    (= main@%y.0.i_2 main@%y.0.i_1)))))
  (=> a!1 (main@_bb main@%x.0.i_2 main@%y.0.i_2))))
(rule (let ((a!1 (and (main@_bb main@%x.0.i_0 main@%y.0.i_0)
                true
                (= main@%_3_0 (< main@%x.0.i_0 101))
                (=> main@_bb2_0 (and main@_bb2_0 main@_bb_0))
                (=> (and main@_bb2_0 main@_bb_0) (not main@%_3_0))
                (=> main@_bb2_0 (= main@%_8_0 (< main@%y.0.i_0 100)))
                (=> main@_bb2_0 (not main@%_8_0))
                (=> main@_bb2_0 (= main@%_9_0 (xor main@%_8_0 true)))
                (=> main@_bb3_0 (and main@_bb3_0 main@_bb2_0))
                (=> main@verifier.error_0
                    (and main@verifier.error_0 main@_bb3_0))
                (=> main@verifier.error.split_0
                    (and main@verifier.error.split_0 main@verifier.error_0))
                main@verifier.error.split_0)))
  (=> a!1 main@verifier.error.split)))
(query main@verifier.error.split)

