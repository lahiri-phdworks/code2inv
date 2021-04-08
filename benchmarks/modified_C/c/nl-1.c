long long int square(long long int a)
{
	return (a) * (a);
}

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
		// long long int temp_x = x;
		// long long int temp_y = y;
		y = y + 1;
		x = y * y + 2 * y + 1;
	}
	// loopend
	// postcheck
	// post-condition
	assert((x == square(y + 1)));
	return 0;
}
