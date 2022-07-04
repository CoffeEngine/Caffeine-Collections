#include "munit.h"
#include <stdlib.h>
#include <stdio.h>

extern MunitSuite array_suite;
extern MunitSuite vector_suite;
extern MunitSuite stack_suite;
extern MunitSuite queue_suite;
extern MunitSuite linked_list_suite;
extern MunitSuite hash_map_suite;

int main(int argc, char* const argv[])
{
	munit_suite_main(&array_suite, NULL, argc, argv);
	system("pause");
	munit_suite_main(&vector_suite, NULL, argc, argv);
	system("pause");
	munit_suite_main(&stack_suite, NULL, argc, argv);
	system("pause");
	munit_suite_main(&queue_suite, NULL, argc, argv);
	system("pause");
	munit_suite_main(&linked_list_suite, NULL, argc, argv);
	system("pause");
	munit_suite_main(&hash_map_suite, NULL, argc, argv);
	system("pause");

}