long long int func(long long int a, long long int b)
{
	return a - b;
}

int main()
{
	// variable declarations
	long long int x;
	long long int y;
	long long int z;
	// pre-conditions
	// scanf("%d", &x);
	// scanf("%d", &y);
	// scanf("%d", &z);
	assume((x >= 0 && y >= 0));
	(z = x * y);
	// precheck
	// loopcond : (x > 0)
	// loopstart
	while (x > 0)
	{
		long long int temp_x = x;
		long long int temp_y = y;
		long long int temp_z = z;
		x = func(x, 1);
		z = func(z, y);
	}
	// loopend
	// postcheck
	// post-condition
	assert((z == 0));
	return 0;
}
