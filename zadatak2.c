#include <stdio.h>
#include <stdlib.h>

typedef void (*PTRFUN)(void);

 /* ==================================================
		UNARY_FUNCTION
    ================================================== */
typedef struct {
	PTRFUN* vtable;
	int lower_bound;
	int upper_bound;
} Unary_Function;

typedef double (*funptr)(Unary_Function*, double);

double negative_value_at(Unary_Function* obj, double x) {
	funptr fun = (funptr)obj->vtable[0];
    return -(fun(obj, x)); // Polimorfni poziv.
}
 void tabulate(Unary_Function* obj) {
	int x;
	funptr fun = (funptr)obj->vtable[0];
    for(x = obj->lower_bound; x <= obj->upper_bound; x++) {
		printf("f(%d)=%lf\n", x, fun(obj, (double)x)); // Polimorfni poziv.
    }
}
	
int same_function_for_ints(Unary_Function* f1, Unary_Function* f2, double tolerance) {
	if(f1->lower_bound != f2->lower_bound) return 0;
      if(f1->upper_bound != f2->upper_bound) return 0;
	  int x;
	  funptr fun1 = (funptr)f1->vtable[0];
	  funptr fun2 = (funptr)f2->vtable[0];
      for(x = f1->lower_bound; x <= f1->upper_bound; x++) {
        double delta = fun1(f1, (double)x) - fun2(f2, (double)x); // Polimorfni poziv.
        if(delta < 0) delta = -delta;
        if(delta > tolerance) return 0;
      }
      return 1;
}

funptr UnaryFunctionVTable[2] = {
	(funptr)negative_value_at,
	(funptr)NULL
};

void UnaryFunctionInit(Unary_Function* obj, int lb, int ub) {
	obj->vtable = (PTRFUN*)UnaryFunctionVTable;
	obj->lower_bound = lb;
	obj->upper_bound = ub;
}

 /* ==================================================
		SQUARE
    ================================================== */
typedef struct {
	funptr* vtable;
	int lower_bound;
	int upper_bound;
} Square;

double square_value_at(Unary_Function* obj, double x) {
	return x*x;
}

funptr SquareVTable[1] = {
	(funptr)square_value_at
}; 

void SquareInit(Square* obj, int lb, int ub) {
	UnaryFunctionInit((Unary_Function*)obj, lb, ub);
	obj->vtable = SquareVTable;
}

 /* ==================================================
		LINE
    ================================================== */
typedef struct {
	funptr* vtable;
	int lower_bound;
	int upper_bound;
	double a; 
	double b;
} Line;

double line_value_at(Unary_Function* obj, double x) {
	Line* line = (Line*)obj;
	return line->a*x + line->b;
}

funptr LineVTable[1] = {
	(funptr)line_value_at
};

void LineInit(Line* obj, int lb, int ub, double a, double b) {
	UnaryFunctionInit((Unary_Function*)obj, lb, ub);
	obj->vtable = LineVTable;
	obj->a = a;
	obj->b = b;
}


 /* ==================================================
		Program
    ================================================== */
int main() {
	Unary_Function *f1 = (Unary_Function*)malloc(sizeof(Square));
	SquareInit((Square*)f1, -2, 2);
	tabulate(f1);
	Unary_Function *f2 = (Unary_Function*)malloc(sizeof(Line));
	LineInit((Line*)f2, -2, 2, 5, -2);
	tabulate(f2);
	
	printf("f1==f2: %s\n", same_function_for_ints(f1, f2, 1E-6) ? "DA" : "NE");
	printf("neg_val f2(1) = %lf\n", negative_value_at(f2, 1.0));
	
	free(f1); free(f2);
	getchar();
	return 0;
}