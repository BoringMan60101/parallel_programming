/*
	Один из вариантов чётно-нечетной сортировки (параллельная)
	Здесь используется директива OpenMP 'sections'

	Из всех доступных потоков работают только два
	(за счёт директивы sections)

	В цикле число раз равное элементам массива выполняются два действия:
	  1.  Двум потокам даются чётные пары,
	  один из них обрабатывает некоторую их долю, а второй оставшуюся
      !!! Важно, что оба потока начинают обработку с элемента с чётным номером !!!

	  2.  Двум потокам даются НЕчётные пары,
	  один из них обрабатывает некоторую их долю, а второй оставшуюся
      !!! Важно, что оба потока начинают обработку с элемента с НЕчётным номером !!!
*/

/* !!! Это легко, но нужно напоминать себе
	#pragma omp parallel
	for(int step = 1; step <= size; step++)

	И

	#pragma omp parallel for
	for(int step = 1; step <= size; step++)

	Дают совсем разные результаты
*/

#include <cstdio>

void swap(int &, int &);

int main()
{
	const int size = 13;
	int arr[size] = {
		10, 9, 8, 7, 6, 5, 4, 3, 2, 1, -1, -2, -3
	};

	printf("Array:\n");
	for(int i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");

	// разделительный иднекс 'delim' всегда чётный
	const int delim = (size / 2) % 2 ? size / 2 - 1 : size / 2;
	
	// границы циклов для сортировки "вторых половин пар"
	const int b_even = size - (size % 2);
	const int b_odd = size - (size % 2 ? 0 : 1);
	printf("delim = %d\n", delim);

	#pragma omp parallel num_threads(2)
	for(int step = 1; step <= size; step++)
	{
		
		#pragma omp sections //для чётных пар
		{
			#pragma omp section
				for(int i = 0; i < delim; i += 2)
					if(arr[i] > arr[i+1])
						swap(arr[i], arr[i+1]);

			#pragma omp section
				for(int i = delim; i < b_even; i += 2)
					if(arr[i] > arr[i+1])
						swap(arr[i], arr[i+1]);
		}

		// #pragma omp barrier // явная синхронизация
		// точка неявной синхронизации
		#pragma omp sections //для НЕчётных пар
		{
			#pragma omp section
				for(int i = 1; i < delim; i += 2)
					if(arr[i] > arr[i+1])
						swap(arr[i], arr[i+1]);

			#pragma omp section // верхняя граница это size - 1 всегда т.к. delim чётное
				for(int i = delim+1; i < b_odd; i += 2)
					if(arr[i] > arr[i+1])
						swap(arr[i], arr[i+1]);
		}
	}

	printf("Sorted array:\n");
	for(int i = 0; i < size; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}

void swap(int & a, int & b)
{
	int buf = a;
	a = b;
	b = buf;
}
