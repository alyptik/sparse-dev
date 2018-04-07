#define is_constexpr(x) \
	(sizeof(int) == sizeof(*(8 ? ((void *)((long)(x) * 0l)) : (int *)8)))

int test(void)
{
	unsigned int s = 0, i = 0;
	void *ptr = &i;

	// OK
	s += sizeof i;
	s += sizeof &i;
	s += sizeof ptr;
	s += sizeof &ptr;

	// KO
	s += sizeof(void);
	s += sizeof *ptr;
	s += is_constexpr(1 + 1);
	s += is_constexpr((1, 1));
	s += is_constexpr(ptr + 1);
	s += is_constexpr(&ptr + 1);
	s += is_constexpr(*(((char *)&ptr) + 1));

	return s;
}

/*
 * check-name: sizeof-void
 * check-command: sparse -Wpointer-arith -Wno-decl -Wno-unused-value $file
 *
 * check-error-start
sizeof-void.c:16:14: warning: expression using sizeof(void)
sizeof-void.c:17:14: warning: expression using sizeof(void)
sizeof-void.c:19:14: warning: expression using sizeof(void)
sizeof-void.c:20:14: warning: expression using sizeof(void)
sizeof-void.c:21:14: warning: expression using sizeof(void)
sizeof-void.c:22:14: warning: expression using sizeof(void)
 * check-error-end
 */
