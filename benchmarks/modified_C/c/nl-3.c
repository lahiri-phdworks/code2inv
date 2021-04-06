int main()
{
	// variable declarations
	long long int x;
	long long int y;
	// pre-conditions
	// scanf("%d", &x);
	// scanf("%d", &y);
	assume((x >= 0 && x <= 10));
	(y = x * x);
	// precheck
	// loopcond : (x * x <= 1000)
	// loopstart
	while (x * x <= 1000)
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
	assert((y <= 1000));
	return 0;
}
