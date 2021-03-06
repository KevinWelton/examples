// Adapted from cppcon 2016 talk https://www.youtube.com/watch?v=8C8NnE1Dg4A&list=LLQ5jRYUW9xUGdimCyKlTWNg&index=3&t=9s
// Built using VS 15.5

#include <experimental\generator>

std::experimental::generator<size_t> noisy_generator()
{
    for (size_t i = 0; i < SIZE_MAX; ++i)
    {
        co_yield i;
    }
}

std::experimental::generator<size_t> limiting_generator(std::experimental::generator<size_t> gen, const size_t sentinel)
{
    for (auto v : gen)
    {        
        co_yield v;

        if (v == sentinel)
        {
            break;
        }
    }
}

int main()
{
    const size_t sentinel = 10;

    // Use a generator with logic to limit the yield to constrain noisy_generator.
    // This will all run on the same thread.
    for (auto v : limiting_generator(noisy_generator(), sentinel))
    {
        printf("print until sentinel of %zu. Current value: %zu\n", sentinel, v);
    }

    return 0;
}