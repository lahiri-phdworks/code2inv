(set-info :original "/tmp/sea-TxDulT/108.pp.ms.o.bc")
(set-info :authors "SeaHorn v.0.1.0-rc3")
(declare-rel verifier.error (Bool Bool Bool ))
(declare-rel main@entry (Int ))
(declare-rel main@_bb (Int Int Int Int ))
(declare-rel main@verifier.error.split ())
(declare-var main@%_14_0 Bool )
(declare-var main@%_17_0 Bool )
(declare-var main@%_12_0 Bool )
(declare-var main@%_0_0 Int )
(declare-var @unknown_0 Int )
(declare-var main@%_2_0 Int )
(declare-var main@%_4_0 Int )
(declare-var main@%_6_0 Int )
(declare-var main@%_8_0 Int )
(declare-var main@%_10_0 Bool )
(declare-var main@entry_0 Bool )
(declare-var main@%_1_0 Int )
(declare-var main@%_3_0 Int )
(declare-var main@%_5_0 Int )
(declare-var main@_bb_0 Bool )
(declare-var main@%m.0.i_0 Int )
(declare-var main@%k.0.i_0 Int )
(declare-var main@%m.0.i_1 Int )
(declare-var main@%k.0.i_1 Int )
(declare-var main@_bb1_0 Bool )
(declare-var main@%.m.0.i_0 Int )
(declare-var main@%_15_0 Int )
(declare-var main@_bb_1 Bool )
(declare-var main@%m.0.i_2 Int )
(declare-var main@%k.0.i_2 Int )
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
         (= main@%_2_0 @unknown_0)
         (= main@%_4_0 @unknown_0)
         (= main@%_6_0 @unknown_0)
         (= main@%_8_0 @unknown_0)
         (= main@%_10_0 (<= main@%_1_0 main@%_5_0))
         main@%_10_0
         (=> main@_bb_0 (and main@_bb_0 main@entry_0))
         main@_bb_0
         (=> (and main@_bb_0 main@entry_0) (= main@%m.0.i_0 main@%_5_0))
         (=> (and main@_bb_0 main@entry_0) (= main@%k.0.i_0 0))
         (=> (and main@_bb_0 main@entry_0) (= main@%m.0.i_1 main@%m.0.i_0))
         (=> (and main@_bb_0 main@entry_0) (= main@%k.0.i_1 main@%k.0.i_0)))
    (main@_bb main@%m.0.i_1 main@%_1_0 main@%k.0.i_1 main@%_3_0)))
(rule (let ((a!1 (and (main@_bb main@%m.0.i_0 main@%_1_0 main@%k.0.i_0 main@%_3_0)
                true
                (= main@%_12_0 (< main@%k.0.i_0 main@%_3_0))
                (=> main@_bb1_0 (and main@_bb1_0 main@_bb_0))
                (=> (and main@_bb1_0 main@_bb_0) main@%_12_0)
                (=> main@_bb1_0 (= main@%_14_0 (< main@%m.0.i_0 main@%_1_0)))
                (=> main@_bb1_0
                    (= main@%.m.0.i_0
                       (ite main@%_14_0 main@%_1_0 main@%m.0.i_0)))
                (=> main@_bb1_0 (= main@%_15_0 (+ main@%k.0.i_0 1)))
                (=> main@_bb_1 (and main@_bb_1 main@_bb1_0))
                main@_bb_1
                (=> (and main@_bb_1 main@_bb1_0)
                    (= main@%m.0.i_1 main@%.m.0.i_0))
                (=> (and main@_bb_1 main@_bb1_0) (= main@%k.0.i_1 main@%_15_0))
                (=> (and main@_bb_1 main@_bb1_0)
                    (= main@%m.0.i_2 main@%m.0.i_1))
                (=> (and main@_bb_1 main@_bb1_0)
                    (= main@%k.0.i_2 main@%k.0.i_1)))))
  (=> a!1 (main@_bb main@%m.0.i_2 main@%_1_0 main@%k.0.i_2 main@%_3_0))))
(rule (let ((a!1 (and (main@_bb main@%m.0.i_0 main@%_1_0 main@%k.0.i_0 main@%_3_0)
                true
                (= main@%_12_0 (< main@%k.0.i_0 main@%_3_0))
                (=> main@_bb2_0 (and main@_bb2_0 main@_bb_0))
                (=> (and main@_bb2_0 main@_bb_0) (not main@%_12_0))
                (=> main@_bb2_0 (= main@%_17_0 (> main@%_1_0 main@%m.0.i_0)))
                (=> main@_bb2_0 main@%_17_0)
                (=> main@_bb3_0 (and main@_bb3_0 main@_bb2_0))
                (=> main@verifier.error_0
                    (and main@verifier.error_0 main@_bb3_0))
                (=> main@verifier.error.split_0
                    (and main@verifier.error.split_0 main@verifier.error_0))
                main@verifier.error.split_0)))
  (=> a!1 main@verifier.error.split)))
(query main@verifier.error.split)

