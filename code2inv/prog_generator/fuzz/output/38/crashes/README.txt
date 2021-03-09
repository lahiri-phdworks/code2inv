Command line used to find this crash:

/home/ha-useast-service/afl/afl-fuzz -i /home/ha-useast-service/Documents/Research/code2inv/code2inv/prog_generator/checkers/../fuzz/tests/38 -o /home/ha-useast-service/Documents/Research/code2inv/code2inv/prog_generator/checkers/../fuzz/output/38 -m 10G /home/ha-useast-service/Documents/Research/code2inv/code2inv/prog_generator/checkers/../fuzz/build/38

If you can't reproduce a bug outside of afl-fuzz, be sure to set the same
memory limit. The limit used for this fuzzing session was 10.0 GB.

Need a tool to minimize test cases before investigating the crashes or sending
them to a vendor? Check out the afl-tmin that comes with the fuzzer!

Found any cool bugs in open-source tools using afl-fuzz? If yes, please drop
me a mail at <lcamtuf@coredump.cx> once the issues are fixed - I'd love to
add your finds to the gallery at:

  http://lcamtuf.coredump.cx/afl/

Thanks :-)
