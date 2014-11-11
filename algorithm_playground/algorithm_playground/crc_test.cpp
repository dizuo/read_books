// g++ crc_test.cpp -o exec_crc_test  -L /usr/lib64/ -lz

#include <stdio.h>
#include <stdlib.h>
#include <zlib.h>
#include <string.h>

void CRC_Partial_Check_Test();
template<class Type> void CRC_Full_Check_Test();

// crc32 use uLong, typedef unsigned long uLong;
typedef uLong ulong_t;	// 32bit, 64bit.

int main()
{
	ulong_t code = 0xfc << 24;
	unsigned int ui_code = 0xfc << 24;
	printf("ulong_res = %lu, uint_res = %lu\n", code, ui_code);

	code = 0xfc << 8;
	ui_code = 0xfc << 8;
	printf("ulong_res = %lu, uint_res = %lu\n", code, ui_code);

	CRC_Partial_Check_Test();
	CRC_Full_Check_Test<unsigned int>();
	CRC_Full_Check_Test<ulong_t>();
	
	printf("any key pressed to exit...\n");
	getchar();
	
	return 0;
}

typedef union
{
	ulong_t val;
	unsigned char buf[sizeof(ulong_t)];
} trans_un_t;

void CRC_Partial_Check_Test()
{
	printf("=============================>>CRC_Partial_ChecK_Test\n");
	
	char* buffer = "hello world, i am renyafei";
	int buffer_sz = strlen(buffer);

	{
		FILE* fp = fopen("crc.dat", "wb");
		fwrite(buffer, 1, buffer_sz, fp);
		ulong_t crc_code = crc32(0, (const Bytef*)buffer, buffer_sz);
		
		printf("crc_code : %lu\n", crc_code);
		
		fwrite(&crc_code, 1, sizeof(ulong_t), fp);
		
		fflush(fp);
		fclose(fp);
	}

	{
		FILE* fp = fopen("crc.dat", "rb");
		unsigned char content[1024] = {0};
		int read_bytes = fread(content, 1, buffer_sz+sizeof(ulong_t), fp);
		ulong_t crc_code = 0;
		{
			// get crc code
			unsigned char* pch = content + buffer_sz;
			
			trans_un_t trans;
			for(int k=0; k<sizeof(ulong_t); k++)
			{
				printf("%d ", pch[k]);
				trans.buf[k] = pch[k];				
			} printf("\n");
			
			printf("crc_code : %lu\n", trans.val);
			crc_code = trans.val;
		}		
		
		if ( crc32(0, content, buffer_sz) != crc_code )
		{
			printf("ERROR content.\n");
		}
		else
		{
			printf("Good Content.\n");			
		}

		fclose(fp);
	}	
}

template<class Type>
void CRC_Full_Check_Test()
{
	printf("=============================>>CRC_Full_ChecK_Test\n");
	
	char* buffer = "hello world, i am renyafei";
	int buffer_sz = strlen(buffer);

	typedef Type dest_t;

	{
		FILE* fp = fopen("crc.dat", "wb");
		fwrite(buffer, 1, buffer_sz, fp);
		
		ulong_t crc = crc32(0, (const Bytef*)buffer, buffer_sz);
		dest_t rever_crc = (dest_t)~crc;
		
		printf("crc = %lu, reverse_crc_code : %lu\n", crc, rever_crc);
		
		fwrite(&rever_crc, 1, sizeof(dest_t), fp);
		fflush(fp);
		fclose(fp);
	}

	{
		FILE* fp = fopen("crc.dat", "rb");
		unsigned char content[1024] = {0};
		int read_bytes = fread(content, 1, buffer_sz+sizeof(dest_t), fp);
		{
			// get crc code
			unsigned char* pch = content + buffer_sz;

			trans_un_t trans;
			memcpy(trans.buf, pch, sizeof(ulong_t));
			
			printf("reverse_crc_code : %lu\n", trans.val);
			
		}

		ulong_t res = crc32(0, content, read_bytes);	printf("res = %lu\n", res);

		if ( res != 0xFFFFFFFF && res != 0xFFFFFFFFFFFFFFFF )
		{
			printf("ERROR content.\n");
		}
		else 
		{
			printf("Good Content.\n");
		}
		
		fclose(fp);
	}	
}
