int main()
{
	// variable declarations
	long long int x;
	long long int y;
	// pre-conditions
	// scanf("%d", &x);
	// scanf("%d", &y);
	(x = 0);
	(y = 0);
	// precheck
	// loopcond : (unknown())
	// loopstart
	while (unknown())
	// loop body
	{
		long long int temp_x = x;
		long long int temp_y = y;
		y = y + 1;
		x = y * y;
	}
	// loopend
	// postcheck
	// post-condition
	assert((x == y * y));
	return 0;
}
