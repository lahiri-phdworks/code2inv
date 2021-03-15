int main()
{
   int x = 0;
   int size;
   int y, z;
   assume((-10000 <= size && size <= 10000));
   while (x < size)
   {
      x += 1;
      if (z <= y)
      {
         y = z;
      }
   }

   if (size > 0)
   {
      assert(z >= y);
   }
}
