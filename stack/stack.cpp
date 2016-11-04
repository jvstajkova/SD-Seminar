#include<iostream>
#include<stack>
using namespace std;
char pairs[4][2]{ { '(',')' },{ '[',']' },{ '{','}' },{ '<','>' } };
bool correct(const char* ex)
{
	int br = 0;
	while (*ex != '\0')
	{
		if (*ex == '(')
		{
			br++;
		}
		if(*ex==')')
		{
			br--;
		}
		if (br < 0)
		{
			return false;
		}
		++ex;
	}
	if (br == 0)

	{
		return true;
	}
	else return false;
}
bool isOpen(char c)
{
	for (int i = 0; i < 4; i++)
	{
		if (c == pairs[i][0])
		{
			return true;
		}
	}
	return false;
}
bool isClose(char c)
{
	for (int i = 0; i < 4; i++)
	{
		if (c == pairs[i][1])
		{
			return true;
		}
	}
	return false;
}
bool match(char open, char close)
{
	for (int i = 0; i < 4; i++)
	{
		if (open== pairs[i][0])
		{
			return close==pairs[i][1];
		}
	}
	return false;
}
bool cor(const char* ex)
{
	stack<char> s;
	while(*ex=='\0')
	{
		if (isOpen(*ex))
		{
			s.push(*ex);
		}
		else if (isClose(*ex))
		{
			if (!s.empty() && match(s.top(),*ex))
				s.pop();
			else
				return false;
		}

		
		++ex;
	}
	return s.empty();
}
int main()
{

	/*int num;
	cin >> num;
	stack<int> st;
	while (num != 0)
	{
		st.push(num % 2);
		num /= 2;
	}
	while (!st.empty())
	{
		cout << st.top();
		st.pop();
	}*/
	//stack<char> st;
	//cout<<boolalpha<<correct("((1+2)/2)*((3-2)*2)")<<"\n";
	cout<<boolalpha<<cor("((1+2)/2)*((3-2)*2)") << "\n";
	system("pause");
	return 0;
}
