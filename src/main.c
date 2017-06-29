#include "array.h"
#include "array_test.h"
#include "iter_test.h"
#include "list_test.h"
#include "hashtable_test.h"

int main() {
	run_iter_tests();
	run_array_tests();
	run_list_tests();
	run_hashtable_tests();
	return 0;
}
