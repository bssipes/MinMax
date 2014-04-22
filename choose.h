/* Written by Ben Sipes, except where specifically sourced
CS404 Algorithms
April 22, 2014
*/

char choose(bool min, int U, int R)
{
	char result;
	if (min == true)
	{
		if (U < R)
		{
			result = 'U';
		}
		else // if R is less than or equal, choose R
		{
			result = 'R';
		}
	}
	else if (min == false)
	{
		if (U > R)
		{
			result = 'U';
		}
		else //if R is larger or equal, choose R
		{
			result = 'R';
		}
	}
	return result;
}

char choose(bool min, float U, float R)
{
	char result;
	if (min == true)
	{
		if (U < R)
		{
			result = 'U';
		}
		else // if R is less than or equal, choose R
		{
			result = 'R';
		}
	}
	else if (min == false)
	{
		if (U > R)
		{
			result = 'U';
		}
		else //if R is larger or equal, choose R
		{
			result = 'R';
		}
	}
	return result;
}
