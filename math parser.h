class parser {
	public:
	float parse(const char * expressions)
	{
		expressionToParse = expressions;
		return expression();
	}
	private:
	const char * expressionToParse;
	char peek() {return *expressionToParse;}
	char get() {return *expressionToParse++;}
	float number()
	{
		float result = get() - '0';
		while (peek() >= '0' && peek() <= '9')
		{
			result = 10*result + get() - '0';
		}
		return result;
	}

	float factor()
	{
		if (peek() >= '0' && peek() <= '9')
			return number();
		else if (peek() == '(')
		{
			get(); // '('
			float result = expression();
			get(); // ')'
			return result;
		}
		else if (peek() == '-')
		{
			get();
			return -factor();
		}
		return 0; // error
	}

	float term()
	{
		float result = factor();
		while (peek() == '*' || peek() == '/')
			if (get() == '*')
				result *= factor();
			else
				result /= factor();
		return result;
	}

	float expression()
	{
		float result = term();
		while (peek() == '+' || peek() == '-')
			if (get() == '+')
				result += term();
			else
				result -= term();
		return result;
	}
};