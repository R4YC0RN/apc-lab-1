#include <stdio.h>
#include <math.h>
#include <time.h>

void cFunc(float a, float b, float d){
	float f, x;
	f = 0;
	for (x = a; x < b; x += d) {
		f += (sqrt(x) / (pow(x, 2) + 1));
	}
	printf("f = %f\n", f);
}

void asmFunc(float a, float b, float d) {
	float x, f;
	const float one = 1;
	float f1 = 0;
	_asm finit
	for (x = a; x < b; x += d) {
		_asm {
			fld x
			fsqrt
			fld x
			fmul x
			fadd one
			fdiv 
			fstp f

		}
		_asm fwait
		f1 += f;
	}
	printf("f1 = %f\n", f1);
}

int main() {
	char s;
	float a, b, d;
	clock_t start, end;
	do
	{
		system("cls");
		printf("Enter the 1st range of the interval: ");
		while (!scanf_s("%f", &a)) {
			printf("Error! You should enter number");
			rewind(stdin);
		}
		printf("Enter the 2nd range of the interval: ");
		while (!scanf_s("%f", &b)) {
			printf("Error! You should enter number");
			rewind(stdin);
		}
		printf("Enter the increment step: ");
		while (!scanf_s("%f", &d)) {
			printf("Error! You should enter number");
			rewind(stdin);
		}
		start = clock();
		cFunc(a, b, d);
		end = clock();
		printf("C: %f sec\n", (double)(end - start) / (double)(CLOCKS_PER_SEC));
		start = clock();
		asmFunc(a, b, d);
		end = clock();
		printf("Asm: %f sec\n", (double)(end - start) / (double)(CLOCKS_PER_SEC));
		printf("Do you want to continue? y/n\n");
		s = _getch();
	} while (s != 'n');
	return 0;
}