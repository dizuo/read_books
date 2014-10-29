#include "xshare.h"

void deep_in_cpp();

#ifdef DEEP_IN_CPP
DECLARE_MAIN_ENTRY(deep_in_cpp);
#endif

class Test
{
public:

	Test() {}

	void print() { printf("Test::print()\n"); }
	void print1() { printf("Test::print1()\n");  }

	int v[10];
	float f;
	
};

void deep_in_cpp()
{
	Test t;
	Test ct(t);
	Test at = t;

	Test* p1 = &t;
	Test* p2 = &ct;
	Test* p3 = &at;

	t.print();
	ct.print1();

}

/* 
void deep_in_cpp()
{
	013E74C0  push        ebp
	013E74C1  mov         ebp, esp
	013E74C3  sub         esp, 184h
	013E74C9  push        ebx
	013E74CA  push        esi
	013E74CB  push        edi
	013E74CC  lea         edi, [ebp - 184h]
	013E74D2  mov         ecx, 61h				// 循环次数
	013E74D7  mov         eax, 0CCCCCCCCh		// 初始化值 
	013E74DC  rep stos    dword ptr es : [edi]	// 循环初始化
	013E74DE  mov         eax, dword ptr ds : [01412004h]
	013E74E3  xor         eax, ebp				// 
	013E74E5  mov         dword ptr[ebp - 4], eax	// ebp压栈
	
	Test t;
	013E74E8  lea         ecx, [t]				// 拷贝t地址到ecx，lea传递地址，构造函数中使用该ecx
	013E74EB  call        Test::Test(013E4112h)
	
	Test ct(t);
	013E74F0  mov         ecx, 0Bh				// 循环次数11个机器字
	013E74F5  lea         esi, [t]
	013E74F8  lea         edi, [ct]
	013E74FB  rep movs    dword ptr es : [edi], dword ptr[esi]	// 循环拷贝，sizeof(Test) == 11 * sizeof(int)
	
	Test at = t;
	013E74FD  mov         ecx, 0Bh
	013E7502  lea         esi, [t]
	013E7505  lea         edi, [at]
	013E750B  rep movs    dword ptr es : [edi], dword ptr[esi]

	Test* p1 = &t;
	013E750D  lea         eax, [t]
	013E7510  mov         dword ptr[p1], eax
	
	Test* p2 = &ct;
	013E7516  lea         eax, [ct]
	013E7519  mov         dword ptr[p2], eax
	
	Test* p3 = &at;
	013E751F  lea         eax, [at]
	013E7525  mov         dword ptr[p3], eax

	t.print();
	013E752B  lea         ecx, [t]
	013E752E  call        Test::print(013E3B22h)
	
	ct.print1();
	013E7533  lea         ecx, [ct]
	013E7536  call        Test::print1(013E4117h)

}

void deep_in_cpp()
{
	00A474C0  push        ebp
		00A474C1  mov         ebp, esp
		00A474C3  sub         esp, 118h
		00A474C9  push        ebx
		00A474CA  push        esi
		00A474CB  push        edi
		00A474CC  lea         edi, [ebp - 118h]
		00A474D2  mov         ecx, 46h				//	
		00A474D7  mov         eax, 0CCCCCCCCh		//
		00A474DC  rep stos    dword ptr es : [edi]	// 循环初始化，次数ecx，原始值eax
		00A474DE  mov         eax, dword ptr ds : [00A72004h]
		00A474E3  xor         eax, ebp
		00A474E5  mov         dword ptr[ebp - 4], eax	// ebp压入栈
		
		Test t;
		00A474E8  lea         ecx, [t]					// lea传地址，
		00A474EB  call        Test::Test(0A44112h)		
		
		Test ct(t);
		00A474F0  mov         eax, dword ptr[t]				// mov传地址指向的内容：两个机器字 dword = 2 * sizzeof(int)
		00A474F3  mov         dword ptr[ct], eax			// 
		00A474F6  mov         ecx, dword ptr[ebp - 0Ch]		// sizeof(Test) + 4 = 12
		00A474F9  mov         dword ptr[ebp - 1Ch], ecx
		
		Test at = t;
		00A474FC  mov         eax, dword ptr[t]
		00A474FF  mov         dword ptr[at], eax
		00A47502  mov         ecx, dword ptr[ebp - 0Ch]
		00A47505  mov         dword ptr[ebp - 2Ch], ecx

		Test* p1 = &t;
		00A47508  lea         eax, [t]
		00A4750B  mov         dword ptr[p1], eax
		Test* p2 = &ct;
		00A4750E  lea         eax, [ct]
		00A47511  mov         dword ptr[p2], eax
		Test* p3 = &at;
		00A47514  lea         eax, [at]
		00A47517  mov         dword ptr[p3], eax

		t.print();
		00A4751A  lea         ecx, [t]
		00A4751D  call        Test::print(0A43B22h)
		
		ct.print1();
		00A47522  lea         ecx, [ct]
		00A47525  call        Test::print1(0A44117h)

}
*/