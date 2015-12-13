#include "Calculator.h"

Calculator::Calculator(){
	OS.push(eos);
	First_token = true;
}

void Calculator::obtain_token(const char *s, int *str_indx)
{
	static token prev_token;
	complex<long double> *z1;
	if(First_token == true)
	{
		First_token = false;
		prev_token = eos;
	}
	if(s[(*str_indx)] != '\0')
	{
		switch(s[(*str_indx)])
		{
			case '+': Token = add; (*str_indx)++ ; break;
			case '-': Token = sub; (*str_indx)++ ; break;
			case '*': Token = mul; (*str_indx)++ ; break;
			case '/': Token = divi; (*str_indx)++ ; break;
			case '^': Token = power; (*str_indx)++ ; break;
			case '(': Token = l_s_br; (*str_indx)++ ; break;
			case ')': Token = r_s_br; (*str_indx)++ ; break;
			case '{': Token = l_m_br; (*str_indx)++ ; break;
			case '}': Token = r_m_br; (*str_indx)++ ; break;
			case '[': Token = l_b_br; (*str_indx)++ ; break;
			case ']': Token = r_b_br; (*str_indx)++ ; break;
			case 's': 
			case 'c': 
			case 't': 
			case 'l': 
			case 'e': 
			case 'a': Token = get_fun_token(s+(*str_indx),str_indx); (*str_indx)++ ; break;
			case 'i': 
					if(!s[(*str_indx)+1] || !isdigit(s[(*str_indx)+1])){
						printf("ERROR\n");
						exit(0);
					}
					Token = val;
					z1 = new complex<long double>(0.0,atof(s+(*str_indx)+1));
					(*str_indx) = (*str_indx)+getNumLen(s+(*str_indx)+1)+1; TV = z1; break;
			default: 
					if(s[(*str_indx)]!='0' && atof(s+(*str_indx)) == 0.0){
						printf("ERROR\n");
						exit(0);
					}
					Token = val;
					z1 = new complex<long double>(atof(s+(*str_indx)),0.0);
					(*str_indx) = (*str_indx)+getNumLen(s+(*str_indx));
					TV = z1; break;
		}
	}
	else
		Token = eos;
	
	if(Token == sub && prev_token != val && prev_token != r_s_br && prev_token != r_m_br && prev_token != r_b_br)
		Token = um;
	else if(Token == add && prev_token != val && prev_token != r_s_br && prev_token != r_m_br && prev_token != r_b_br)
		Token = up;

	prev_token = Token;
}

int Calculator::getNumLen(const char *s)
{
	int i = 0;
	bool value = false;
	for (; isdigit(s[i]); i++)
		value = true;
	if (s[i] == '.')
		i++;
	for (; isdigit(s[i]); i++)
		value = true;
	if(i && !value)
	{
		i = 0;
		return i;
	}
	if(s[i] == 'e' )
	{ 
		if(s[i+1] && (s[i+1] == '+' || s[i+1] == '-') && s[i+2] && isdigit(s[i+2])) 
			i+=2;
		else
			i++;
	}
	for (; isdigit(s[i]); i++)
		value = true;

	if(i && !value)
		i = 0;
	return i;
}

Calculator::token Calculator::get_fun_token(const char *s, int *l)
{
	if(s[0]=='s' && s[1]=='i' && s[2]=='n' && !(isdigit(s[3])))
	{	*l = *l+2;	return Sin;	}

	else if(s[0]=='c' && s[1]=='o' && s[2]=='s' && !(isdigit(s[3])))
	{	*l = *l+2;	return Cos;	}

	else if(s[0]=='t' && s[1]=='a' && s[2]=='n' && !(isdigit(s[3])))
	{	*l = *l+2;	return Tan;	}

	else if(s[0]=='l' && s[1]=='o' && s[2]=='g' && !(isdigit(s[3])))
	{	*l = *l+2;	return Log;	}

	else if(s[0]=='e' && s[1]=='x' && s[2]=='p' && !(isdigit(s[3])))
	{	*l = *l+2;	return Exp;	}

	else if(s[0]=='a' && s[1]=='b' && s[2]=='s' && !(isdigit(s[3])))
	{	*l = *l+2;	return Abs;	}

	if(s[0]=='s' && s[1]=='q' && s[2]=='r' && s[3]=='t' && !(isdigit(s[4])))
	{	*l = *l+3;	return Sqrt;	}

	else
	{	printf("ERROR\n");	exit(0);	}
}

void Calculator::hold(const char *s, int *str_indx)
{
	if(Token == val)
		VS.push(*TV);
	else
		OS.push(Token);		
	obtain_token(s,str_indx);
}

void Calculator::evaluate()
{
	complex<long double> z1,z2;
	switch(OS.top())
	{
		case add: 
				if(VS.size() < 2){	printf("ERROR\n"); exit(0);	}
				z1 = VS.top();	VS.pop();	z2 = VS.top();	VS.pop();
				VS.push(z1+z2);	break;
		
		case sub: 
				if(VS.size() < 2){	printf("ERROR\n"); exit(0);	}
				z1 = VS.top();	VS.pop();	z2 = VS.top();	VS.pop();
				VS.push(z2-z1);	break;

		case mul: 
				if(VS.size() < 2){	printf("ERROR\n"); exit(0);	}
				z1 = VS.top();	VS.pop();	z2 = VS.top();	VS.pop();
				VS.push(z2*z1);	break;
		
		case divi: 
				if(VS.size() < 2){	printf("ERROR\n"); exit(0);	}
				z1 = VS.top();	VS.pop();	z2 = VS.top();	VS.pop();
				VS.push(z2/z1);	break;

		case um:
				if(VS.empty()){	printf("ERROR\n"); exit(0);	}
				z1 = VS.top();	VS.pop();	VS.push(-z1);
				break;
		
		case up: 
				if(VS.empty()){	printf("ERROR\n"); exit(0);	}
				z1 = VS.top();	VS.pop();	VS.push(z1);
				break;
		
		case power:
				if(VS.size() < 2){	printf("ERROR\n"); exit(0);	}
				z1 = VS.top();	VS.pop();	z2 = VS.top();	VS.pop();
				VS.push(pow(z2,z1));	break;

		case Sin:
				if(VS.empty()){	printf("ERROR\n"); exit(0);	}
				z1 = VS.top();	VS.pop();	VS.push(sin(z1));
				break;

		case Cos:
				if(VS.empty()){	printf("ERROR\n"); exit(0);	}
				z1 = VS.top();	VS.pop();	VS.push(cos(z1));
				break;

		case Tan:
				if(VS.empty()){	printf("ERROR\n"); exit(0);	}
				z1 = VS.top();	VS.pop();	VS.push(tan(z1));
				break;

		case Log:
				if(VS.empty()){	printf("ERROR\n"); exit(0);	}
				z1 = VS.top();	VS.pop();	VS.push(log(z1));
				break;

		case Exp:
				if(VS.empty()){	printf("ERROR\n"); exit(0);	}
				z1 = VS.top();	VS.pop();	VS.push(exp(z1));
				break;

		case Abs:
				if(VS.empty()){	printf("ERROR\n"); exit(0);	}
				z1 = VS.top();	VS.pop(); VS.push(abs(z1));
				break;

		case Sqrt:
				if(VS.empty()){	printf("ERROR\n"); exit(0);	}
				z1 = VS.top();	VS.pop(); 
				if(z1.imag() == 0){	z1 = complex<long double>(z1.real(),0);	}
				VS.push(sqrt(z1));
				break;

		case r_s_br: 
		case r_m_br: 
		case r_b_br: OS.pop(); break;
	}
	OS.pop();
}

complex<long double> Calculator::calculate(const char *s)
{
	int str_indx = 0;	
	obtain_token(s,&str_indx);
	while(true)
	{
		if(Token == val)
		{
			hold(s,&str_indx);
			continue;
		}
		switch(op_rel_table[OS.top()][Token])
		{
			case 'E': evaluate(); break;
			case 'H': hold(s,&str_indx); break;
			case 'X': printf("ERROR\n"); exit(0);
			case 'A': 
				if(VS.size() !=1){ 
					printf("ERROR\n");
					exit(0);
				}
				break;
		}
		if(s[str_indx] == '\0' && OS.size()==1)
			break;
	}
	if(VS.size() !=1){
		printf("ERROR\n");
		exit(0);
	}
	return VS.top();
}
