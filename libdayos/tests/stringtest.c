#include <string.h>
#include <ctype.h>

void test_strcmp()
{
	ASSERT("String equality failed", !strcmp("TestWord", "TestWord"));
	ASSERT("String equality failed", strcmp("TestWordPrefix", "TestWord"));

	ASSERT_GREATER(0, strcmp("TestWorda", "TestWord"));
	ASSERT_SMALLER(0, strcmp("TestWor", "TestWord"));
}

void test_strcasecmp()
{
	ASSERT("String equality failed", !strcasecmp("TestWord", "TestWORD"));
	ASSERT("String equality failed", strcasecmp("TestWordPrefix", "TeStWOrd"));

	ASSERT_GREATER(0, strcasecmp("TeStWorda", "TestWord"));
	ASSERT_SMALLER(0, strcasecmp("TestWOr", "TestWord"));
}

void test_strncmp()
{
	ASSERT("Strings should be equal!", !strncmp("TestWord", "TestWord", 4));
	ASSERT("Strings should not be equal!", strncmp("TestWordPrefix", "TestWord", 10));
	ASSERT("Strings should not be equal!", strncmp("TestWorda", "TestWord", 9));
	ASSERT("Strings should not be equal!", strncmp("TestWord", "TestWorda", 9));
}

void test_strncasecmp()
{
	ASSERT("Strings should be equal!", !strncasecmp("TestWORD", "TestWord", 4));
	ASSERT("Strings should not be equal!", strncasecmp("TeStWoRdPreFix", "TesTWord", 10));
	ASSERT("Strings should not be equal!", strncasecmp("TeStWorDa", "TestWord", 9));
	ASSERT("Strings should not be equal!", strncasecmp("TestWoRd", "TestWorda", 9));
}

void test_strcpy()
{
	char to[20];
	strcpy(to, "FROM");
	
	ASSERT_STRING_EQUALS("FROM", to);
}

void test_strncpy()
{
	char to[20];
	
	// Zero out memory. This way we can check that
	// strncpy only copies the requested number of bytes
	// and never more since it does not add an implicit '\0'
	memset(to, 0, sizeof(to));
	
	strncpy(to, "FROM", 2);
	ASSERT_STRING_EQUALS("FR", to);
}

void test_strlen()
{
	ASSERT("String length test failed.", strlen("HELLO WORLD") == 11);
}

void test_toupper()
{
	ASSERT("Test failed.", toupper('a') == 'A');
	ASSERT("Test failed.", toupper('A') == 'A');
}

void test_tolower()
{
	ASSERT("Test failed.", tolower('A') == 'a');
	ASSERT("Test failed.", tolower('a') == 'a');
}

void test_sprintf()
{
	char buf[32];
	sprintf(buf, "%d", -123);
	ASSERT_STRING_EQUALS("-123", buf);
	
	sprintf(buf, "%d", 123);
	ASSERT_STRING_EQUALS("123", buf);
	
	sprintf(buf, "%x", 0xABC);
	ASSERT_STRING_EQUALS("ABC", buf);
	
	sprintf(buf, "%s", "asd");
	ASSERT_STRING_EQUALS("asd", buf);
}

void run_string_tests()
{
	RUN(test_toupper);
	RUN(test_tolower);
	RUN(test_strcmp);
	RUN(test_strcasecmp);
	RUN(test_strncasecmp);
	RUN(test_strncmp);
	RUN(test_strcpy);
	RUN(test_strncpy);
	RUN(test_strlen);
	RUN(test_sprintf);
}
