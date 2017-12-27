#include <array>

size_t partition(int* input, size_t first, size_t last);

void quicksort(int* input, size_t first, size_t last)
{
    if (first < last)
    {
        // Partition the array by moving items less than the pivot value to the left of the pivot and greater to the right.
        int partition_index = partition(input, first, last);
        quicksort(input, first, partition_index);
        quicksort(input, partition_index + 1, last);
    }
}

size_t partition(int* input, size_t first, size_t last)
{
    // Pivot on the middle element. There are multiple schemes for choosing the pivot. See https://en.wikipedia.org/wiki/Quicksort.
    // If the pivot value chosen is a good pivot value, the result of partition() will be about the middle of the array.
    int pivot = input[(first + last) / 2];

    int i = first;
    int j = last;

    while (1)
    {
        while (input[i] < pivot)
        {
            i++;
        }

        while (input[j] > pivot)
        {
            j--;
        }

        // If the indices have converged, return. Otherwise swap the values.
        if (i >= j)
        {
            return j;
        }
        else
        {
            int temp = input[i];
            input[i] = input[j];
            input[j] = temp;
        }
    }
}

void doit(int* data, size_t count)
{
    printf("Before: [");

    for (size_t i = 0; i < count; i++)
    {
        printf("%d,", data[i]);
    }

    printf("]\n");

    quicksort(data, 0, count - 1);

    printf("After: [");

    for (size_t i = 0; i < count; i++)
    {
        printf("%d,", data[i]);
    }

    printf("]\n\n");
}

int main()
{
    std::array<int, 20> testcase_a = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9 };
    std::array<int, 7> testcase_b = { -1, -2, -3, -4, -5, -6, -7 };
    std::array<int, 11> testcase_c = { -10, 9, -8, 7, -6, 5, -4, 3, -2, 1, 0 };

    doit(testcase_a.data(), testcase_a.size() - 1);
    doit(testcase_b.data(), testcase_b.size() - 1);
    doit(testcase_c.data(), testcase_c.size() - 1);

    return 0;
}