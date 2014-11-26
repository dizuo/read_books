/* ****************************************************************************
   * Region Test                                                              *
   * -----------                                                              *
   *                                                                          *
   * Modified 6/6/2006 (D/M/YYYY)                                             *
   *                                                                          *
   * Written by Stuart McDonagh.                                              *
   * Use as you wish, just try not to rip this off verbatim, okay? :)         *
   ****************************************************************************/

// No Slim Fast for this mother
#define WIN32_LEAN_AND_MEAN

#include <stdlib.h>
#include <windows.h>

// Number of rectangles to exclude
#define EXCLUDES	6

// A linked list of rectangles
typedef struct TAGregion {
	RECT rcRegion;
	struct TAGregion *next;
} t_region;

// Globals
HBITMAP g_hbmp, g_hbmpOld;
HDC g_hdc;
RECT g_rcInclude = {0, 0, 302, 270};
RECT g_rcExclude[6] = { {24, 48, 278, 66}, {24, 78, 278, 96}, {24, 108, 278, 126}, {24, 138, 278, 156}, {24, 168, 278, 186}, {86, 198, 216, 216} };

// Linked list management functions
// Alloc an item
t_region *ralloc(t_region **list)
{
	t_region *item, *tail = NULL;

	if (list)
	{
		if (*list)
		{
			tail = (*list)->next;
			while (tail->next)
				tail = tail->next;

		}

	}

	if (item = malloc(sizeof(*item)))
	{
		item->next = NULL;
		if (tail)
			tail->next = item;
		else if (list)
			*list = item;

	}

	return item;
}

// Free a complete list
void rfree(t_region **list)
{
	t_region *next;

	if (list)
	{
		while (*list)
		{
			next = (*list)->next;
			free(*list);
			*list = next;
		}

	}

}

// Free a particular item in the list, returns next in the list
t_region *rfreerect(t_region **list, t_region *item)
{
	t_region *current, *next;

	if (list && item)
	{
		if (*list)
		{
			if (*list == item)
			{
				next = (*list)->next;
				free(*list);
				*list = next;
				return next;
			}
			else
			{
				current = *list;
				while (current)
				{
					next = current->next;
					if (next == item)
					{
						current->next = next->next;
						free(next);
						return current->next;
					}
					else
						current = current->next;

				}

			}

		}

	}

	return NULL;
}

// Create a single rectanglular region
t_region *create_rect_region(long x, long y, long right, long bottom)
{
	t_region *region;

	region = ralloc(NULL);
	SetRect(&region->rcRegion, x, y, right, bottom);
	return region;
}

// Append two regions together
t_region *append_regions(t_region *region1, t_region *region2)
{
	t_region *current;

	if (!region1)
		return region2;
	else
	{
		current = region1;
		while (current->next)
			current = current->next;

		current->next = region2;
	}

	return region1;
}

// Ensure that no rectangles in a region overlap
int deoverlap_region(t_region *region)
{
	int bOverlap = 0;
	RECT rcIntersect;
	t_region *rgn1, *rgn2;

	rgn1 = region;
	while (rgn1)
	{
		rgn2 = region;
		while (rgn2)
		{
			if (rgn1 != rgn2)
			{
				if (IntersectRect(&rcIntersect, &rgn1->rcRegion, &rgn2->rcRegion))
				{
					// Indicate that we've done something and replace the two regions with the intersection
					// WHY IS THIS RIGHT IN MOST CASES BUT NOT IN OTHERS?!?
					bOverlap = 1;
					CopyRect(&rgn1->rcRegion, &rcIntersect);
					rgn2 = rfreerect(&region, rgn2);
				}
				else
					rgn2 = rgn2->next;

			}
			else
				rgn2 = rgn2->next;

		}

		rgn1 = rgn1->next;
	}

	return bOverlap;
}

// Compute the difference (A - B) of two overlapping rectangles.  Returns up to four rectangular regions describing the result
t_region *difference(long *x, long *y, long *right, long *bottom, long x1, long y1, long right1, long bottom1)
{
	t_region *regions = NULL;

	// Caveat: rectangles must intersect
	if (((*x > x1) ? *x : x1) >= ((*right < right1) ? *right : right1) || ((*y > y1) ? *y : y1) >= ((*bottom < bottom1) ? *bottom : bottom1))
		return NULL;
	
	if (*x < x1)
	{
		regions = append_regions(regions, create_rect_region(*x, *y, x1, *bottom));
		*x += x1 - *x;
	}

	if (*y < y1)
	{
		regions = append_regions(regions, create_rect_region(*x, *y, *right, y1));
		*y += y1 - *y;
	}

	if (*right > right1)
	{
		regions = append_regions(regions, create_rect_region((*x > right1) ? *x : right1, *y, *right, *bottom));
		*right -= *right - right1;
	}

	if (*bottom > bottom1)
		regions = append_regions(regions, create_rect_region(*x, (*y > bottom1) ? *y : bottom1, *right, *bottom));

	return regions;
}

// Compute the difference of two regions
t_region *difference_regions(t_region *region1, t_region *region2)
{
	t_region *rgn2, *rgnDiff = NULL, *rgnRet = NULL;

	while (region1)
	{
		rgn2 = region2;
		while (rgn2)
		{
			rgnDiff = append_regions(rgnDiff, difference(&region1->rcRegion.left, &region1->rcRegion.top, &region1->rcRegion.right, &region1->rcRegion.bottom, rgn2->rcRegion.left, rgn2->rcRegion.top, rgn2->rcRegion.right, rgn2->rcRegion.bottom));
			rgn2 = rgn2->next;
		}

		region1 = region1->next;
	}

	// Tidy up region
	while (deoverlap_region(rgnDiff));
	rgnRet = rgnDiff;

	return rgnRet;
}

BOOL DialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_CLOSE:
		{
			SelectObject(g_hdc, g_hbmpOld);
			DeleteObject(g_hbmp);
			DeleteDC(g_hdc);
			EndDialog(hDlg, 0);
			break;
		}
		case WM_INITDIALOG:
		{
			int i;
			t_region *region, *rgnExclude = NULL, *rgnNew;

			g_hdc = CreateCompatibleDC(NULL);
			g_hbmp = CreateCompatibleBitmap(GetDC(NULL), 640, 480);
			g_hbmpOld = SelectObject(g_hdc, g_hbmp);
			region = create_rect_region(g_rcInclude.left, g_rcInclude.top, g_rcInclude.right, g_rcInclude.bottom);
			for (i=0;i<EXCLUDES;i++)
				 rgnExclude = append_regions(rgnExclude, create_rect_region(g_rcExclude[i].left, g_rcExclude[i].top, g_rcExclude[i].right, g_rcExclude[i].bottom));

			rgnNew = difference_regions(region, rgnExclude);
			rfree(&region);
			rfree(&rgnExclude);
			region = rgnNew;
			while (region)
			{
				Rectangle(g_hdc, region->rcRegion.left, region->rcRegion.top, region->rcRegion.right, region->rcRegion.bottom);
				region = region->next;
			}

			rfree(&rgnNew);
			SendMessage(hDlg, WM_SETTEXT, 0, (LPARAM)"Region Test");
			break;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;

			BeginPaint(hDlg, &ps);
			BitBlt(ps.hdc, ps.rcPaint.left, ps.rcPaint.top, ps.rcPaint.right - ps.rcPaint.left, ps.rcPaint.bottom - ps.rcPaint.top, g_hdc, ps.rcPaint.left, ps.rcPaint.top, SRCCOPY);
			EndPaint(hDlg, &ps);
			break;
		}
		default:
			return FALSE;

	}

	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	DWORD dwData[6];
	LPDLGTEMPLATE lpTemplate;

	ZeroMemory(dwData, 6 * sizeof(*dwData));
	lpTemplate = (LPDLGTEMPLATE)dwData;
	lpTemplate->style = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
	lpTemplate->x = (short)0x8000;
	lpTemplate->y = (short)0x8000;
	lpTemplate->cx = (short)320;
	lpTemplate->cy = (short)240;
	return DialogBoxIndirect(hInstance, lpTemplate, NULL, (DLGPROC)DialogProc);
}