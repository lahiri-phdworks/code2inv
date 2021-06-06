
int main() {
  // variable declarations
  int x;
  int y;

  // scanf("%d", &x);
  // pre-conditions
  (x = 1);
  // precheck
  // loopcond : (x <= 100)
  // loopstart
  while (x <= 100)
  // loop body
  {
    y = 100 - x;
    x = x + 1;
  }
  // loopend
  // postcheck
  // post-condition
  assert(y >= 0);
}
