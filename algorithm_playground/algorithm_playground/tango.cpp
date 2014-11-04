1. 
void reverse_impl(char* pbeg, char* pend)
{
	if (!pbeg || !pend) { return; }
	
	while (pbeg < pend) {
		char tmp = *pbeg;
		*pbeg = *pend;
		*pend = tmp;
		
		++pbeg;
		--pend;
	}
}

void reverse_str(char* pstr)
{
	if (!pstr) { return 0; }

	while (*pstr == ' ')
		++pstr;
	
	char* pbeg = pstr, pend = pstr;
	while (*pend)
	{
		if (*pend == ' ')
		{
			reverse_impl(pbeg, pend-1);
			pbeg = pend + 1;
		}
		
		++pend;
	}
	
	reverse_impl(pbeg, pend-1);
}

2. 
1)
void shuffle(int* presult, int size)
{
	if (!presult) return;

	char* hash = new char[size];
		
	srand( (unsigned int)(time(NULL)) );
	for (int i = 0; i < size; i++)
	{
		int seed = rand() % size;
		
		while (hash[seed])
		{
			seed = rand() % size;
		}
		
		hash[seed] = 1;
		presult[i] = seed;
	}
	
	delete [] hash;
}
// int result[52];
// shuffle(result, 52);
