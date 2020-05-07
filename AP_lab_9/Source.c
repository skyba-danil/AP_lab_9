#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LN 200

typedef struct sent
{
	int ind;
	char* rech;
}sent;

typedef struct full_list_elem
{
	sent inf;
	struct full_list_elem* next, * prev;
}FLIST;

typedef struct new_list
{
	sent inf;
	struct new_list* next;
}NLIST;

int InputData(sent* pinf);
void AddElem(sent data);
void PrintList();
int isPolindrom(FLIST* pel);
void CreateNewList(FLIST* pold);
void NPrintList();
void NPrintRevers(NLIST* pel);
void FreeFElemMem(FLIST* elem);
void FreeNList();
void DeleteFEll(FLIST* pel);
void FreeFList(FLIST* pfl);

FLIST* list_beg, * list_end;
NLIST* list;

int main()
{
	system("chcp 1251");
	sent info;
	while (InputData(&info))
	{
		AddElem(info);
	}
	PrintList();
	CreateNewList(list_beg);
	NPrintRevers(list);
	FreeFList(list_beg);
	FreeNList();
}

int InputData(sent* pinf)
{
	char buf[MAX_LN] = { 0 };
	static int n = 0;
	printf("\n%i речення: ", ++n);
	pinf->ind = n;
	fflush(stdin);	gets(buf);
	if (*buf != '\0')
	{
		pinf->rech = (char*)malloc(sizeof(buf) + 1);
		strcpy_s(pinf->rech, sizeof(buf) + 1, buf);
	}
	else
	{
		pinf->rech = NULL;
		return 0;
	}
	return 1;
}

void AddElem(sent data)
{
	FLIST* pel;
	pel = (FLIST*)malloc(sizeof(FLIST));
	pel->inf = data;
	if (list_beg == NULL)
	{
		pel->next = pel->prev = NULL;
		list_beg = list_end = pel;
		return;
	}
	list_end->next = pel;
	pel->prev = list_end;
	pel->next = NULL;
	list_end = pel;
}

void PrintList()
{
	FLIST* pel = list_beg;
	while (pel != NULL)
	{
		printf("\n%-8d%-70s", pel->inf.ind, pel->inf.rech);
		pel = pel->next;
	}
}

void NPrintList()
{
	NLIST* pel = list;
	while (pel != NULL)
	{
		printf("\n%-8d%-70s", pel->inf.ind, pel->inf.rech);
		pel = pel->next;
	}
}

void NPrintRevers(NLIST* pel)
{
	if (pel == NULL) return;
	NPrintRevers(pel->next);
	printf("\n%-8d%-70s", pel->inf.ind, pel->inf.rech);
}

int isPolindrom(FLIST* pel)
{
	char* chek = pel->inf.rech;
	int size = 1;
	while (*chek!='\0')
	{
		chek++;
		size++;
	}
	char* buf = (char*)malloc(size);
	strcpy_s(buf, size, pel->inf.rech);
	char* bufOnlyLet = (char*)malloc(size);
	char* pbol = bufOnlyLet;
	int nsize = 0;
	while (*buf!='\0')
	{
		if (isalpha(*buf))
		{
			*pbol = tolower(*buf);
			pbol++;
			nsize++;
		}
		buf++;
	}
	*pbol = '\0';
	for (int i = 0, k = nsize-1;i<nsize;i++, k--)
	{
		if (bufOnlyLet[i] != bufOnlyLet[k])
		{
			return 0;
		}
	}
	return 1;
}

void CreateNewList(FLIST* pold)
{
	if (pold == NULL) return;
	NLIST* pnew;
	pnew = (NLIST*)malloc(sizeof(NLIST));
	if (isPolindrom(pold))
	{
		pnew->inf = pold->inf;
		pnew->next = list;
		list = pnew;
		DeleteFEll(pold);
	}
	CreateNewList(pold->next);
}

void FreeFList(FLIST* pfl)
{
	if (pfl == NULL) return;
	list_beg = pfl->next;
	FreeFElemMem(pfl);
	FreeFList(list_beg);
}
void FreeNList()
{
	NLIST* pel = list;
	while (pel!=NULL)
	{
		list = list->next;
		free(pel->inf.rech);
		free(pel);
		pel = list;
	}
}

void FreeFElemMem(FLIST* elem)
{
	free(elem->inf.rech);
	free(elem);
}

void DeleteFEll(FLIST* pel)
{
	if (pel->prev == NULL)
	{
		list_beg = list_beg->next;
		list_beg->prev = NULL;
	}
	else if (pel->next == NULL)
	{
		list_end = list_end->prev;
		list_end->next == NULL;
	}
	else
	{
		pel->next->prev = pel->prev;
		pel->prev->next = pel->next;
	}
}