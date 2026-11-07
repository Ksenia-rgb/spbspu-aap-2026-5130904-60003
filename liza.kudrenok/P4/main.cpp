#include <iostream>
#include <cctype>
#include <cstring>
namespace kudrenok
{
    const int successCode = 0;
    const int ErrorCode = 1;

    int yeschar(const char* str, char c)
    {
        while (*str != '\0')
        {
            if (*str == c) return 1;
            str++;
        }
        return 0;
    }

     int isglasnai(char c)
    {
        char lower = std::tolower(c);
        return (lower == 'a' || lower == 'e' || lower == 'i' ||
                lower == 'o' || lower == 'u' || lower == 'y');
    }

    char* finduncommonsym(const char* str1, const char* str2, char* output)
    {
        char* start = output;
        const char* p1 = str1;
        while (*p1 != '\0')
        {
            if (!yeschar(str2, *p1) && !yeschar(start, *p1))
            {
                *output = *p1;
                output++;
            }
            p1++;
        }

        const char* p2 = str2;
        while (*p2 != '\0')
        {
            if (!yeschar(str1, *p2) && !yeschar(start, *p2))
            {
                *output = *p2;
                output++;
            }
            p2++;
        }

        *output = '\0';
        return start;
    }

    char* removeglasnai(const char* src, char* output1)
    {
        char* start = output1;
        while (*src != '\0')
        {
            if (!isglasnai(*src))
            {
                *output1 = *src;
                output1++;
            }
            src++;
        }
        *output1 = '\0';
        return start;
    }
}

int main()
{
    int volume = 0;
    int length = 0;
    char* input_str = nullptr;

    int ch = 0;
    while ((ch = std::cin.get()) != '\n' && ch != EOF)
    {
        if (length + 1 >= volume)
        {
            volume = volume + 1;
            char* temp = new char[volume];

            if (temp == nullptr)
            {
                std::cerr << "Error\n";
                delete[] input_str;
                return kudrenok::ErrorCode;
            }
            for (int i = 0; i < length; ++i)
            {
                temp[i] = input_str[i];
            }

            delete[] input_str;
            input_str = temp;
        }

        input_str[length] = static_cast<char>(ch);
        length++;
    }
    if (length + 1 >= volume)
    {
        int volume = length + 1;
        char* const temp = new char[volume];
        if (temp != nullptr)
        {
            if (input_str !=nullptr)
            {
                for (int i = 0; i < length; ++i) temp[i] = input_str[i];
            }
            delete[] input_str;
            input_str = temp;
        }
    }
    input_str[length] = '\0';

   const char* const second_str = "abc_ef";
    char* const res_variant18 = new char[length + 1];
    char* const res_variant5 = new char[length + std::strlen(second_str) + 1];

    if (res_variant5 == nullptr || res_variant18 == nullptr)
    {
        std::cerr << "Error\n";
        delete[] input_str;
        delete[] res_variant5;
        delete[] res_variant18;
        return kudrenok::ErrorCode;
    }

    res_variant5[0] = '\0';
    res_variant18[0] = '\0';
    kudrenok::finduncommonsym(input_str, second_str, res_variant5);
    kudrenok::removeglasnai(input_str, res_variant18);
    std::cout << res_variant5 << std::endl;
    std::cout << res_variant18 << std::endl;
    delete[] input_str;
    delete[] res_variant5;
    delete[] res_variant18;
    return kudrenok::successCode;
}
