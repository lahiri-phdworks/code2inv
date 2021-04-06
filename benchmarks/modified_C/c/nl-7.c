long long int func(long long int a, long long int b)
{
	long long int c = 0;
	__asm__ __volatile__("addl %%ebx, %%eax;"
						 : "=a"(c)
						 : "a"(a), "b"(b));
	return c;
}

int main()
{
	// variable declarations
	long long int x, y, z, w;
	// pre-conditions
	// scanf("%d", &x);
	// scanf("%d", &y);
	// scanf("%d", &z);
	// scanf("%d", &w);
	assume((x >= 0 && y >= x));
	(z = 0);
	(w = 0);
	// precheck
	// loopcond : (w < y)
	// loopstart
	while (w < y)
	{
		// loop body
		long long int temp_x = x;
		long long int temp_y = y;
		long long int temp_z = z;
		long long int temp_w = w;
		z = func(z, x);
		w = func(w, 1);
	}
	// loopend
	// postcheck
	// post-condition
	assert(z == x * y);
	return 0;
}
