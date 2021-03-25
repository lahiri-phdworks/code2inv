# Almost Verification

Verification using HonggFuzz Fuzzing.

### Running HonggFuzz Examples :

```
Usage: ./start.sh [-b] <build_dir> [-o] <output_dir> [-t] <test_dir> [-e] <EXAMPLE CODE>
```

Check the `python3` fuzzer file. `fuzz.py`

```
$ python3 fuzz.py <example_name> <timeout>
```

#### Run :

Fuzzes all three `loop`, `pre` & `post` programs in `persistence` and generates `counterexample` models at `program crash`.

```
$ python3 fuzz.py 32 5
```

#### Program Graphs

For generating program graphs use `code2inv` docker image.

```
$ docker pull code2inv/code2inv:latest
$ docker run --name alver -it -v $PWD:/project -m 8g code2inv/code2inv:latest
    ...
root@81e7fb45a46d:/project# ./generate.sh
```

### Auto-template generate:

```bash
python3 template.py "x m n" 18 "125 -965"
python3 template.py "n v1 v2 v3 x" 32 "0 0"
python3 template.py "x y z" 4 "30 70"
python3 template.py "x y z1 z2 z3" 12 "5 9"
python3 template.py "i j" 23 "-500"
python3 template.py "i j" 24 "-302"
python3 template.py "n x" 26 "6522"
python3 template.py "x" 30 "602"
python3 template.py "x y" 63 "41521"
python3 template.py "x y" 65 "-6325"
python3 template.py "x y z1 z2 z3" 85 "7935"
python3 template.py "i j k n" 94 "-652 5214"
python3 template.py "i j x y" 95 "2541 2322"
python3 template.py "i j x y" 96 "524 2523"
python3 template.py "n x y" 99 "6521"
python3 template.py "n x y" 100 "23526"
python3 template.py "n x" 101 "-6251"
python3 template.py "a c m j k" 108 "525 146"
python3 template.py "i sn" 121 "8"
python3 template.py "i j x y" 124 "6251 93621"
python3 template.py "d1 d2 d3 x1 x2 x3" 130 "-965 1421"
python3 template.py "a m j k" 106 "74563 1412"
python3 template.py "lock v1 v2 v3 x y" 89 "5221"
python3 template.py "i x y z1 z2 z3" 80 "9752"
python3 template.py "n v1 v2 v3 x y" 70 "5214 -9652"
python3 template.py "c n v1 v2 v3" 54 "5124 32514"
python3 template.py "c" 51 "521"
python3 template.py "c" 37 "214"
python3 template.py "c" 35 "3214"
python3 template.py "x m n z1 z2 z3" 21 "584 55 6245"
```
