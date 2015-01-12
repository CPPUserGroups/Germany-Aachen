#include <iostream>

template <typename T>
class foo
{
public:
    T* m_some_member;
    foo();
    ~foo();

    void fooooooooooooooooooooo(int i, float bus, bool i_have_no_good_name,
                                std::string some_other_var,
                                unsigned long long very_long);

private:
    /* data */
};

int main(int argc, const char* argv[])
{
    if (argc > 3)
    {
        std::cout << "argv[0]" << argv[0] << " argv[1]" << argv[1] " argv[2]"
                  << argv[2] << std::endl;
    }
    else
    {
        std::cout << "Not enough arguments."
                  << " Please give some more."
                  << "Or go home." << std::endl;
    }

    return 0;
}
