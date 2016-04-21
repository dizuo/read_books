#define _CRT_SECURE_NO_WARNINGS

#include "xshare.h"

void struct_mem_unit_test();

#ifdef STRUCT_MEMORY
DECLARE_MAIN_ENTRY(struct_mem_unit_test);
#endif

typedef unsigned short u16_t;

typedef struct Annotation_
{
	int flag;
	int name_cnt;
	u16_t name[1];
} Annotation;

typedef struct Point_
{
	float x;
	float y;
} Point;

void struct_mem_unit_test()
{
	int text_len = 3;
	u16_t text[] = { 123, 345, 678 };	
	u16_t angles[3] = { 35, 60, 90 };
	Point pnts[3] = { { 0, 0 }, { 1, 1 }, { 2, 2 } };

	Annotation* item = (Annotation*)malloc(sizeof(Annotation) +
		text_len * sizeof(u16_t) + 
		text_len * sizeof(u16_t) + 
		text_len * sizeof(Point) );

	memcpy(item->name, text, sizeof(u16_t) * text_len);	// copy text
	memcpy(item->name + text_len, angles, sizeof(u16_t) * text_len);	// copy angles.
	memcpy(&item->name[2 * text_len], pnts, sizeof(Point) * text_len);	// copy points.

	for (int k = 0; k < text_len; k++)
	{
		// access names.
		if (item->name[k] != text[k])
		{
			printf("bad text in [%d] \n", k);
		}

		// access angles.
		if (item->name[text_len + k] != angles[k])
		{
			printf("bad angle in [%d] \n", k);
		}

		// access positions.
		void* ptr = item->name + (text_len * 2) + (k * sizeof(Point) / 2);
		// 为何 sizeof(Point) / 2 
		// item->name是u16_t的指针，item->name + x，实际的偏移量是2x，而sizeof(Point) == 4

		Point* pp = (Point*)ptr;
		if (pp->x != pnts[k].x || pp->y != pnts[k].y)
		{
			printf("bad points in [%d]\n", k);
		}

		if (k == text_len - 1)
		{
			printf("check finished \n");
		}
	}

	free(item);
}
