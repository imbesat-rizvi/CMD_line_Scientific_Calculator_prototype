#ifndef __Calculator__
#define __Calculator__

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <complex>
#include <stack>

using namespace std;

class Calculator{
	private:
		enum token{ add, sub, mul, divi, power,
				um, 	/*Unary minus*/
				up,	/*Unary plus*/
				Sin, Cos, Tan, Log, Exp, Abs, Sqrt,
				l_s_br,	/*Left smaller bracket*/ 
				r_s_br, /*Right smaller bracket*/
				l_m_br, /*Left middle bracket*/
				r_m_br, /*Right middle bracket*/
				l_b_br, /*Left middle bracket*/
				r_b_br, /*Right middle bracket*/
				eos, 	/*End of string*/
				Max_num_ops,	/*Maximum No. of Operators*/
				val, 	/*Mathematical Value*/		
		};

		token Token;
		complex<long double> *TV;		/*Mathematical Value associated with Token*/

		stack<token> OS;		/*Operator Stack*/
		stack< complex<long double> > VS;	/*Value Stack*/

		bool First_token;

		char op_rel_table[Max_num_ops][Max_num_ops] = 

		{      /* +,  -,  *,  /,  ^,  u-, u+, Sin, Cos, Tan, Log, Exp, Abs, Sqrt, (,  ),  {,  },  [,  ], eos, */
		/* + */	{'E','E','H','H','H','H','H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','E','H','E','H','E','E' },
		/* - */	{'E','E','H','H','H','H','H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','E','H','E','H','E','E' },
		/* * */	{'E','E','E','E','H','H','H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','E','H','E','H','E','E' },
		/* / */	{'E','E','E','E','H','H','H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','E','H','E','H','E','E' },
		/* ^ */	{'E','E','E','E','H','H','H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','E','H','E','H','E','E' },
		/* u-*/	{'E','E','E','E','H','H','H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','E','H','E','H','E','E' },
		/* u+*/	{'E','E','E','E','H','H','H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','E','H','E','H','E','E' },
		/*Sin*/	{'X','X','X','X','X','X','X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'H','E','H','E','H','E','E' },
		/*Cos*/	{'X','X','X','X','X','X','X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'H','E','H','E','H','E','E' },
		/*Tan*/	{'X','X','X','X','X','X','X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'H','E','H','E','H','E','E' },
		/*Log*/	{'X','X','X','X','X','X','X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'H','E','H','E','H','E','E' },
		/*Exp*/	{'X','X','X','X','X','X','X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'H','E','H','E','H','E','E' },
		/*Abs*/	{'X','X','X','X','X','X','X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'H','E','H','E','H','E','E' },
		/*Sqrt*/{'X','X','X','X','X','X','X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'H','E','H','E','H','E','E' },
		/* ( */	{'H','H','H','H','H','H','H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','H','H','X','H','X','X' },
		/* ) */	{'E','E','E','E','E','E','E', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X','E','X','E','X','E','E' },
		/* { */	{'H','H','H','H','H','H','H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','X','H','H','H','X','X' },
		/* } */	{'E','E','E','E','E','E','E', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X','E','X','E','X','E','E' },
		/* [ */	{'H','H','H','H','H','H','H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','X','H','X','H','H','X' },
		/* ] */	{'E','E','E','E','E','E','E', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X','E','X','E','X','E','E' },
		/*eos*/	{'H','H','H','H','H','H','H', 'H', 'H', 'H', 'H', 'H', 'H', 'H', 'H','X','H','X','H','X','A' }
		};

		void obtain_token(const char *s, int *ptr);
		int getNumLen(const char *s);
		token get_fun_token(const char *s, int *l);
		void hold(const char *s, int *ptr);
		void evaluate();

	public:
		Calculator();
		complex<long double> calculate(const char *s);
};

#endif
