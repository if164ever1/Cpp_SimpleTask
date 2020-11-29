#include <iostream>
#include <array>
#include <string>
#include <sstream>    

class ipv4
{
    
    std::array<unsigned char, 4> data;
    public:
    constexpr ipv4(): data {{0}} {}
    constexpr ipv4(unsigned char const a, unsigned char const b,
                    unsigned char const c, unsigned char const d):
    data{{a,b,c,d}} {}
    explicit constexpr ipv4(unsigned long a):
        data{{static_cast<unsigned char>((a>>24)& 0xFF),
                static_cast<unsigned char>((a>>16)& 0xFF),
                static_cast<unsigned char>((a>>8)& 0xFF),
                static_cast<unsigned char>(a&0xFF)}} {}
    
    ipv4(ipv4 const &other) noexcept: data(other.data) {}
    ipv4& operator=(ipv4 const& other) noexcept
    {
        data = other.data;
        return *this;
    }
    std::string to_string() const
    {
        std::stringstream sstr;
        sstr << *this;
        return sstr.str();
    }
    constexpr unsigned long to_long() const noexcept
    {
        return  (static_cast<unsigned long>(data[0]) << 24)  |
                (static_cast<unsigned long>(data[1]) << 16)  |
                (static_cast<unsigned long>(data[2]) << 8)   |
                (static_cast<unsigned long>(data[3]));
    }

    friend std::ostream& operator << (std::ostream& os, const ipv4& a)
    {
        os  << static_cast<int>(a.data[0]) << '.'
            << static_cast<int>(a.data[1]) << '.'
            << static_cast<int>(a.data[2]) << '.'
            << static_cast<int>(a.data[3]);
    }

    friend std::istream& operator >> (std::istream& is, ipv4& a)
    {
        char d1,d2,d3;
        int b1,b2,b3,b4;
        is >> b1 >> d1 >> b2 >> d2 >> b3 >> d3 >> b4;
        if(d1 == '.' && d2 == '.' && d3 == '.')
            a = ipv4(b1,b2,b3,b4);
        else
            is.setstate(std::ios_base::failbit);
        return is;
    }

    ipv4& operator++()
    {
        *this = ipv4(1 + to_long());
        return *this;
    }
    ipv4& operator++(int)
    {
        ipv4 result(*this);
        ++(*this);
        return *this;
    }
    friend bool operator== (ipv4 const & a1, ipv4 const & a2) noexcept
    {
        return a1.data == a2.data;
    }
    friend bool operator!= (ipv4 const & a1, ipv4 const & a2) noexcept
    {
        return a1.data == a2.data;
    }
    friend bool operator< (ipv4 const & a1, ipv4 const & a2) noexcept
    {
        return a1.to_long() < a2.to_long();
    }
    friend bool operator> (ipv4 const & a1, ipv4 const & a2) noexcept
    {
        return a2 > a1;
    }
    friend bool operator<= (ipv4 const & a1, ipv4 const & a2) noexcept
    {
        return !(a1 > a2);
    }
    friend bool operator>= (ipv4 const & a1, ipv4 const & a2) noexcept
    {
        return !(a1 < a2);
    }
};


int main()
{
    ipv4 adress(168,192,0,1);
    std::cout << adress << std::endl;

    ipv4 ip;
    std::cout << ip << std::endl;
    std::cin >> ip;
    if(!std::cin.fail())
        std::cout << ip << std::endl;

    std::cout << "-----------------"<< std::endl;
    std::cout << "Input range";
    ipv4 a1,a2;
    std::cin >> a1 >> a2;
    if(a2>a1)
    {
        for (ipv4 a = a2; a <= a2; a++)
        {
            std::cout << a << std::endl;
        }
    }
    else
    {
        std::cerr<<"invalid range!"<< std::endl;
    }
    return 0;
}