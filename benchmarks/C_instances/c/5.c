int main()
{
   int x = 0;
   int size;
   int y;
   int z;

   // scanf("%d", &size)
   // pre-conditions
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
   if (size > 0)
   {
      assert(z >= y);
   }
}
