// code-style.cpp 	// 13.file name

#define TEST_CASE (0)	// 1.define

namespace mynamespace 	// 9.namespace
{
	const int kDaysInAWeek = 7;	// 12. constant names.
	
	class MyClass 		// 10. class 
	{	// class
	public:
		enum SearchErrors	// enum names
		{
			OK = 0,
			ERROR_OUT_OF_MEMOTY,	// 2.enum values.
			ERROR_OTHER = 1,	// enum values.
		};

		typedef std::string str_t;	// 3.user define type

		MyClass();

		~MyClass();

		int num_entries() const { return num_entries_; }		// 4.class member function
		void set_num_entries(int num_entries) { num_entries_ = num_entries; }

		static int s_var;		// 5.static var	
		
	private:
		MyClass(const MyClass& obj);
		MyClass& operator=(const MyClass& obj);

		int _private_func_call();	// 11. private member function
		
		int num_entries_;		//  6.private member var
		
		
	};
}

int g_var;		// 7.global var

void test()
{
	int var;	// 8.local var
}