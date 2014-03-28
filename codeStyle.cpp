#define TEST_CASE (0)	// 1.define

namespace mynamespace 	// 9.namespace
{
	class MyClass {	// class
	public:
		enum 
		{
			kTestCase = 0	// 2.enum
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

		int num_entries_;		//  6.class member var
		
		
	};
}

int g_var;		// 7.global var

void test()
{
	int var;	// 8.local var
}