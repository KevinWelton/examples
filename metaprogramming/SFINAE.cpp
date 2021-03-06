// SFINAE (Substitution Failure Is Not An Error) can be used for multiple purposes. All uses are based on the concept that invalid substitution of template
// parameters is not in itself an error. If there is an invalid substitution, the template under consideration is simply ignored.

// From http://en.cppreference.com/w/cpp/language/sfinae:
    // Function template parameters are substituted(replaced by template arguments) twice:
    // explicitly specified template arguments are substituted before template argument deduction
    // deduced arguments and the arguments obtained from the defaults are substituted after template argument deduction
    // Substitution occurs in
    // -all types used in the function type(which includes return type and the types of all parameters)
    // -all types used in the template parameter declarations
    // -all expressions used in the function type
    // -all expressions used in a template parameter declaration
    // A substitution failure is any situation when the type or expression above would be ill - formed(with a required diagnostic), if written using the substituted arguments.
    // Only the failures in the types and expressions in the immediate context of the function type or its template parameter types are SFINAE errors.

// Two common usages of SFINAE are 
// 1) Overload resolution
// 2) Determining if a trait is present (in this example, a static assert will be used instead of a missing trait.)

#include <iostream>
#include <cinttypes>
#include <type_traits>

// Print the value category. If SFINAE fails to substitute in the partial specializations, this default will be used which will static_assert.
template <typename T, typename Enable = void>
struct value_category
{
    static constexpr char* str() { static_assert(0, "vale_category is not specialized for this type."); }
};

template <typename T>
struct value_category<T, std::enable_if_t<std::is_integral_v<T>>>
{
    static constexpr char* str() { return "integral"; }
};

template <typename T>
struct value_category<T, std::enable_if_t<std::is_floating_point_v<T>>>
{
    static constexpr char* str() { return "floating point"; }
};

// Print whether the value is signed or unsigned. If SFINAE fails to substitute in the partial specialization, treat the sign_type as unsigned.
template <typename T, typename Enable = void>
struct sign_type 
{
    static constexpr char* str() { return "unsigned"; }
};

template <typename T>
struct sign_type<T, std::enable_if_t<std::is_signed_v<T>>>
{
    static constexpr char* str() { return "signed"; }
};

// Elipsis parameter has the lowest ranking for overload resolution. If SFINAE fails for overloads, this is our fallback.
void print(...)
{
    printf("Default print function. Couldn't successfully substitute any template paramters in overloads.\n");
}

template <typename T>
typename std::enable_if_t<std::is_scalar_v<T>> print(T value)
{
    std::cout << "Printing " << value_category<T>::str() << " " << sign_type<T>::str() << " value: " << value << std::endl;
}

int main()
{
    int32_t signed32 = -100;
    uint64_t unsigned64 = 2000000000;
    float_t signedFloat = 3.1415f;

    print(signed32);
    print(unsigned64);
    print(signedFloat);

    struct PodStruct
    { 
        int field; 
    };
    
    PodStruct t{};

    print(t);

    int32_t* signed32_ptr = nullptr;

    // With this line enabled, COMPILATION WILL FAIL with static assert "value_category is not specialized for this type."
    // Comment out this line to successfully build and see the expected output noted below.
    print(signed32_ptr);

    // Output:
    //   Printing integral signed value : -100
    //   Printing integral unsigned value : 2000000000
    //   Printing floating signed value : 3.1415
    //   Default print function.Couldn't successfully substitute any template paramters in overloads.

    return 0;
}

