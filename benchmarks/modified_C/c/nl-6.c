int main()
{
	// variable declarations
	long long int x, y, z, w;
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
			z = z * x;
		}
		x += 1;
	}
	// loopend
	// postcheck
	// post-condition
	assert(w == z * y);
	return 0;
}
