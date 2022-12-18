
int test_sparseset(int argc, const char* argv[]);
int test_array(int argc, const char* argv[]);
int test_container(int argc, const char* argv[]);
int test_ordered_container(int argc, const char* argv[]);
int test_bitmap(int argc, const char* argv[]);
int test_hashmap(int argc, const char* argv[]);
int test_queue(int argc, const char* argv[]);
int test_vector(int argc, const char* argv[]);
int test_stack(int argc, const char* argv[]);
int test_list(int argc, const char* argv[]);

int main(int argc, const char* argv[]) {
	test_ordered_container(argc, argv);
	test_container(argc,argv);
	test_array(argc,argv);
	test_vector(argc,argv);
	test_bitmap(argc,argv);
	test_sparseset(argc,argv);
	test_hashmap(argc,argv);
	test_queue(argc,argv);
	test_stack(argc, argv);
	test_list(argc, argv);
	return 0;
}