#include <stdio.h>
#include <stdlib.h>
#include <dayos/dayos.h>
#include <string.h>
#include <unistd.h>
#include "tinytest.h"

#include "stringtest.c"

// FIXME: Rather useless
void test_random()
{
	int seed = 0xCAFEBABE;
	srand(seed);

	for(int i = 0; i < 5; i++)
	{
		printf("Got random number: %d\n", rand());
	}
}

void test_optargs()
{
	int argc = 5;
	const char* argv[] = {"uname", "-a", "-v", "-f", "filename"};

	int a = 0, v = 0;
	const char* filename = NULL;
	
	int c = 0;
	while((c = getopt(argc, (char**) argv, ":avf:")) != -1)
	{
		switch(c)
		{
		case 'a':
			a = 1;
			break;

		case 'v':
			v = 1;
			break;

		case 'f':
			filename = optarg;
			break;
		}
	}

	ASSERT("Argument a was found", a);
	ASSERT("Argument v was found", v);
	ASSERT_STRING_EQUALS("filename", filename);
}

int main(int argc, char* argv[])
{
	printf("\n");
	printf(" _  _  _     ______               _____  _____   _____           _   \n"
		"| |(_)| |    |  _  \\             |  _  |/  ___| |_   _|         | |  \n"
		"| | _ | |__  | | | | __ _  _   _ | | | |\\ `--.    | |  ___  ___ | |_ \n"
		"| || || '_ \\ | | | |/ _` || | | || | | | `--. \\   | | / _ \\/ __|| __|\n"
		"| || || |_) || |/ /| (_| || |_| |\\ \\_/ //\\__/ /   | ||  __/\\__ \\| |_ \n"
		"|_||_||_.__/ |___/  \\__,_| \\__, | \\___/ \\____/    \\_/ \\___||___/ \\__|\n"
		"                            __/ |                                    \n"
		"                           |___/                                     \n"
		"\n\n");
	
	run_string_tests();
	RUN(test_optargs);
	//RUN(test_random);

	return TEST_REPORT();
}
