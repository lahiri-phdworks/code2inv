int main() {
  // variable declarations
  int i;
  int j;
  // scanf("%d", &i);
  // pre-conditions
  (i = 1);
  (j = 20);
  // precheck
  // loopcond : (j >= i)
  // loopstart
  while ((j >= i))
  // loop body
  {
    {
      (i = (i + 2));
      (j = (j - 1));
    }
  }
  // loopend
  // postcheck
  // post-condition
  assert((j == 13));
}
