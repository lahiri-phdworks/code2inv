int main()
{
	int x = 0;
	int y = 0;

	while (unknown())
	{
		y = y + 1;
		x = y * y + 2 * y + 1;
	}

	assert((x == (y + 1) * (y + 1)));
	return 0;
}
