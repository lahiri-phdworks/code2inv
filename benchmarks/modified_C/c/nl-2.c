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
	long long int x;
	long long int y;
	// pre-conditions
	// scanf("%d", &x);
	// scanf("%d", &y);
	assume((x >= 0));
	(y = x * x);
	// precheck
	// loopcond : (unknown())
	// loopstart
	while (unknown())
	// loop body
	{
		long long int temp_x = x;
		long long int temp_y = y;
		x = x + 1;
		y = y + 1;
	}
	// loopend
	// postcheck
	// post-condition
	assert((y <= func(x, x)));
	return 0;
}
