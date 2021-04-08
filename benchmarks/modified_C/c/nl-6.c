long long int func(long long int a, long long int b)
{
	long long int c = 0;
	__asm__ __volatile__("imull %%ebx, %%eax;"
						 : "=a"(c)
						 : "a"(a), "b"(b));
	return c;
}

int main()
{
	// variable declarations
	long long int x, y, z, w, d;
	// pre-conditions
	// scanf("%d", &x);
	// scanf("%d", &y);
	// scanf("%d", &z);
	// scanf("%d", &w);
	assume((x == 1 && x <= y));
	(w = 1);
	(z = 1);
	// precheck
	// loopcond : (x <= y)
	// loopstart
	while (x <= y)
	{
		// loop body
		long long int temp_x = x;
		long long int temp_y = y;
		long long int temp_z = z;
		long long int temp_w = w;
		w = w * x;
		if (x < y)
		{
			z = func(z, x);
		}
		x += 1;
	}
	// loopend
	// postcheck
	// post-condition
	__asm__ __volatile__("imull %%ebx, %%eax;"
						 : "=a"(d)
						 : "a"(z), "b"(y));
	assert(w == d);
	return 0;
}
