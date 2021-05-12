# Pytorch to C++ Library

- [Torch JIT Official](https://pytorch.org/tutorials/advanced/cpp_export.html)
- [C++ Pytorch Example](https://pytorch.org/tutorials/advanced/cpp_frontend.html#writing-a-basic-application)
- [Load Model](https://www.programmersought.com/article/25051445129/)

# Invariant Expression

```
sum = (((i / 10) * ((i / 10) + 1)) / 2)
```

where `i = 0..9` are images of `0`, `i = 10..19` are images of `1` and so on ...

black-box operation (function) : `pred(image_i)`
