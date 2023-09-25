#include "sorter.h"
#include <stdbool.h>

// https://iq.opengenus.org/parallel-quicksort/

static int partition(struct fish *array, int l, int r)
{
	int i = l + 1;
	int j = r;
	double key = array[l].delta_f; //sort on delta_f
	struct fish temp;	
	while (true)
	{
		while (i < r && key >= array[i].delta_f)
			i++;
		while (key < array[j].delta_f)
			j--;
		if (i < j) 
		{
			temp = array[i];
			array[i] = array[j];
			array[j] = temp;
		} 
		else 
		{
			temp = array[l];
			array[l] = array[j];
			array[j] = temp;
			return j;
		}
	}
}

void seq_quick_sort(struct fish *array, int l, int r)
{
	if (l < r)
	{
		int p = partition(array, l, r);
		seq_quick_sort(array, l, p - 1);
		seq_quick_sort(array, p + 1, r);
	}
}

static void _par_quick_sort(struct fish *array, int l, int r)
{
	if (l < r)
	{
		int p = partition(array, l, r);
		#pragma omp task
		{
		_par_quick_sort(array, l, p - 1);
		}
		#pragma omp task
		{
		_par_quick_sort(array, p + 1, r);
		}
	}
}

void par_quick_sort(struct fish *array, int l, int r)
{
	#pragma omp parallel
	{
	#pragma omp single
	{
	_par_quick_sort(array, l, r);
	}
	}
}
