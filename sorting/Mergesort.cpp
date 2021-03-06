#include <vector>

void mergesort(std::vector<int>& input)
{
    auto midpoint = input.begin() + (input.size() / 2);

    std::vector<int> left(input.begin(), midpoint);
    std::vector<int> right(midpoint, input.end());
    
    if(left.size() > 1) mergesort(left);
    if(right.size() > 1) mergesort(right);

    // Combine sorted arrays.
    size_t left_index = 0;
    size_t right_index = 0;

    for (size_t main_index = 0; main_index < input.size(); ++main_index)
    {
        // Use left
        if (left_index < left.size() && (right_index == right.size() || left[left_index] <= right[right_index]))
        {
            input[main_index] = left[left_index++];
        }
        else
        {
            input[main_index] = right[right_index++];
        }
    }
}

void sort_and_print(std::vector<int>& data)
{
    printf("Before: [");

    for (size_t i = 0; i < data.size(); i++)
    {
        printf("%d,", data[i]);
    }

    printf("]\n");

    mergesort(data);

    printf("After: [");

    for (size_t i = 0; i < data.size(); i++)
    {
        printf("%d,", data[i]);
    }

    printf("]\n\n");
}

int main()
{
    std::vector<int> testcase_a = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9 };
    std::vector<int> testcase_b = { -1, -2, -3, -4, -5, -6, -7 };
    std::vector<int> testcase_c = { -10, 9, -8, 7, -6, 5, -4, 3, -2, 1, 0 };
    std::vector<int> testcase_d = { -10 };
    std::vector<int> testcase_e = { 10, -10 };
    
    sort_and_print(testcase_a);
    sort_and_print(testcase_b);
    sort_and_print(testcase_c);
    sort_and_print(testcase_d);
    sort_and_print(testcase_e);
    
    return 0;
}