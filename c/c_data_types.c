#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i = 0;
	unsigned u = 0;
	short int si = 0;
	long l = 0;
	unsigned long ul = 0;
	char  c = 0;
	unsigned char uc = 0;
	float f = 0.0;
	double d = 0.0;
	long double ld = 0;
	size_t st = 0;

	int *pi = &i;
	unsigned *pu = &u;
	short int *psi = &si;
	long *pl = &l;
	unsigned long *pul = &ul;
	char  *pc = &c;
	unsigned char *puc = &uc;
	float *pf = &f;
	double *pd = &d;
	long double *pld = &ld;
	size_t *pst = &st;

	size_t s_i = sizeof(i);
	size_t s_u = sizeof(u);
	size_t s_si = sizeof(si);
	size_t s_l = sizeof(l);
	size_t s_ul = sizeof(ul);
	size_t s_c = sizeof(c);
	size_t s_uc = sizeof(uc);
	size_t s_f = sizeof(f);
	size_t s_d = sizeof(d);
	size_t s_ld = sizeof(ld);
	size_t s_st = sizeof(st);
	size_t s_pi = sizeof(pi);
	size_t s_pu = sizeof(pu);
	size_t s_psi = sizeof(psi);
	size_t s_pl = sizeof(pl);
	size_t s_pul = sizeof(pul);
	size_t s_pc = sizeof(pc);
	size_t s_puc = sizeof(puc);
	size_t s_pf = sizeof(pf);
	size_t s_pd = sizeof(pd);
	size_t s_pld = sizeof(pld);
	size_t s_pst = sizeof(pst);

	printf("the size of si is %lu\n", s_i);
	printf("the size of s_u is %lu\n", s_u);
	printf("the size of s_si is %lu\n", s_si);
	printf("the size of s_l is %lu\n", s_l);
	printf("the size of s_ul is %lu\n", s_ul);
	printf("the size of s_c is %lu\n", s_c);
	printf("the size of s_uc is %lu\n", s_uc);
	printf("the size of s_f is %lu\n", s_f);
	printf("the size of s_d is %lu\n", s_d);
	printf("the size of s_ld is %lu\n", s_ld);
	printf("the size of s_st is %lu\n", s_st);
	printf("the size of s_pi is %lu\n", s_pi);
	printf("the size of s_pu is %lu\n", s_pu);
	printf("the size of s_psi is %lu\n", s_psi);
	printf("the size of s_pl is %lu\n", s_pl);
	printf("the size of s_pul is %lu\n", s_pul);
	printf("the size of s_pc is %lu\n", s_pc);
	printf("the size of s_puc is %lu\n", s_puc);
	printf("the size of s_pf is %lu\n", s_pf);
	printf("the size of s_pd is %lu\n", s_pd);
	printf("the size of s_pld is %lu\n", s_pld);
	printf("the size of s_pst is %lu\n", s_pst);
/**/


	return(0);	
}


