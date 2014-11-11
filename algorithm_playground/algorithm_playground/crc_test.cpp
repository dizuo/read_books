#include "zlib.h"

void CRC_Partial_Check_Test()
{
	char* buffer = "hello world, i am renyafei";
	int buffer_sz = strlen(buffer);

	{
		FILE* fp = fopen("crc.dat", "wb");
		fwrite(buffer, 1, buffer_sz, fp);
		int crc_code = crc32(0, (const Bytef*)buffer, buffer_sz);
		printf("crc_code : %d\n", crc_code);
		fwrite(&crc_code, 1, 4, fp);
		fflush(fp);
		fclose(fp);
	}

	{
		FILE* fp = fopen("crc.dat", "rb");
		unsigned char content[1024] = {0};
		int read_bytes = fread(content, 1, buffer_sz+4, fp);
		int crc_code = 0;
		{
			// get crc code
			unsigned char* pch = content + buffer_sz;
			crc_code = pch[0] + (pch[1] << 8) + (pch[2] << 16) + (pch[3] << 24);	// little endian
			printf("crc_code : %d\n", crc_code);
		}		
		if ( crc32(0, content, buffer_sz) != crc_code )
		{
			printf("ERROR content.\n");
		}
		fclose(fp);
	}	
}

void CRC_Full_Check_Test()
{
	char* buffer = "hello world, i am renyafei";
	int buffer_sz = strlen(buffer);

	{
		FILE* fp = fopen("crc.dat", "wb");
		fwrite(buffer, 1, buffer_sz, fp);
		int rever_crc = ~crc32(0, (const Bytef*)buffer, buffer_sz);
		printf("reverse_crc_code : %d\n", rever_crc);
		// int code = 10;		fwrite(&code, 1, 4, fp);
		fwrite(&rever_crc, 1, 4, fp);
		fflush(fp);
		fclose(fp);
	}

	{
		FILE* fp = fopen("crc.dat", "rb");
		unsigned char content[1024] = {0};
		int read_bytes = fread(content, 1, buffer_sz+4, fp);
		{
			// get crc code
			unsigned char* pch = content + buffer_sz;
			int crc_code = pch[0] + (pch[1] << 8) + (pch[2] << 16) + (pch[3] << 24);
			printf("reverse_crc_code : %d\n", crc_code);
		}
		if ( crc32(0, content, read_bytes) != 0xFFFFFFFF )
		{
			printf("ERROR content.\n");
		}
		fclose(fp);
	}	
}