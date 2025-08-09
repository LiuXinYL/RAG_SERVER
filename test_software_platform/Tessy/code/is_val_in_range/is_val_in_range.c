
#include "test.h"
struct range {int range_start; int range_len;};

typedef int value;
int c;
typedef enum {no, yes} result;

result is_value_in_range (struct range r1, value v1)
{
	if (v1 < r1.range_start)
		return no;

	if (v1 > (r1.range_start + r1.range_len))
		return no;

	return yes;

}
int test ()
{
	struct range a;
	result b;
	a.range_start = 1;
	a.range_len = 2;
	b = is_value_in_range(a,1);
	if(b == yes)
	{
		return 1;
	}else{
		return 0;
	}
}
