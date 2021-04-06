long long int func(long long int a, long long int b)
{
	return a * b;
}

int main()
{
	long long int x, z, w;
	// pre-conditions
	// scanf("%d", &z);
	// scanf("%d", &x);
	// scanf("%d", &w);
	(z = w * x);
	// precheck
	// loopcond : (unknown())
	// loopstart
	while (unknown())
	{
		// loop body
		long long int temp_w = w;
		long long int temp_x = x;
		long long int temp_z = z;
		w = func(w, x);
		z = func(z, x);
	}
	// loopend
	// postcheck
	// post-condition
	assert((z == w * x));
	return 0;
}
