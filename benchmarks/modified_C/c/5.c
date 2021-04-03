int main()
{
   int x = 0;
   int size;
   int y;
   int z;
   // pre-conditions
   // scanf("%d", &size)
   assume((-10000 <= size && size <= 10000));
   // precheck
   // loopcond : (x < size)
   // loopstart
   while (x < size)
   // loop body
   {
      x += 1;
      if (z <= y)
      {
         y = z;
      }
   }
   // loopend
   // postcheck
   // post-condition
   if (size > 0)
   {
      assert(z >= y);
   }
}
