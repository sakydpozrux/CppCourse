#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <cmath>




constexpr double pi()
{
    return std::atan(1)*4;
}

double len(double ax, double ay, double bx, double by)
{
    return sqrt( (ax - bx)*(ax - bx) + (ay - by)*(ay - by) );
}

class surf
{
public:
    virtual double area( ) const = 0;
    virtual double circumference( ) const = 0;
    virtual surf* clone( ) const = 0;
    virtual std::ostream& print( std::ostream& ) const = 0;
    virtual ~surf( ) = 0;
};

surf::~surf()
{ }

class rectangle : public surf
{
    double x1, y1;
    double x2, y2;

public:
    double area( ) const
    {
        return fabs(x2 - x1) * fabs(y2 - y1);
    }

    double circumference( ) const
    {
        return 2 * fabs(x1 - x2) + 2 * fabs(y1 - y2);
    }
    
    rectangle* clone( ) const
    {
        return new rectangle(x1, y1, x2, y2);
    }

    std::ostream& print( std::ostream& stream) const
    {
        stream << "rectangle.";
        return stream;
    }


    rectangle()
        : surf(), x1(0), y1(0), x2(0), y2(0)
    { }
    
    rectangle(double x1, double y1, double x2, double y2)
        : surf(), x1(x1), y1(y1), x2(x2), y2(y2)
    { }
};


class triangle : public surf
{
    double x1, y1; // Positions of corners.
    double x2, y2;
    double x3, y3;

public:
    double area( ) const
    {
        double a = len(x1, y1, x2, y2);
        double b = len(x1, y1, x3, y3);
        double c = len(x2, y2, x3, y3);

        double p = (a + b + c) / 2;

        return sqrt( p * (p - a) * (p - b) * (p - c) );

    }
    
    double circumference( ) const
    {
        double a = len(x1, y1, x2, y2);
        double b = len(x1, y1, x3, y3);
        double c = len(x2, y2, x3, y3);

        return a + b + c;
    }

    triangle* clone( ) const
    {
        return new triangle(x1, y1, x2, y2, x3, y3);
    }

    std::ostream& print( std::ostream& stream) const
    {
        stream << "triangle.";
        return stream;
    }


    triangle()
        : surf(), x1(0), y1(0), x2(0), y2(0), x3(0), y3(0)
    { }
    
    triangle(double x1, double y1, double x2, double y2, double x3, double y3)
        : surf(), x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3)
    { }

    triangle& operator=(triangle& r)
    {
        if (this != &r)
        {
            x1 = r.x1;
            y1 = r.y1;
            x2 = r.x2;
            y2 = r.y2;
            x3 = r.x3;
            y3 = r.y3;
        }
        return *this; 
    }

    ~triangle()
    { }
};


class circle : public surf
{
    double x; // Position of center.
    double y;
    double radius;

public:
    double area( ) const
    {
        return pi() * pow(radius, 2);
    }

    double circumference( ) const
    {
        return 2 * pi() * radius;
    }

    circle* clone( ) const
    {
        return new circle(x, y, radius);
    }

    std::ostream& print( std::ostream& stream) const
    {
        stream << "circle.";
        return stream;
    }

    circle()
        : surf(), x(0), y(0), radius(0)
    { }
    
    circle(double x, double y, double radius)
        : surf(), x(x), y(y), radius(radius)
    { }
    
    circle& operator=(circle& r)
    {
        if (this != &r)
        {
            x = r.x;
            y = r.y;
            radius = r.radius;
        }
        return *this;
    }

    ~circle()
    { }
};


struct surface
{
    surf* ref;

    surface( const surface& s )
    : ref( s. ref -> clone( ))
    { }

    surface( const surf& s )
    : ref( s. clone( ))
    { }

    void operator = ( const surface& s )
    {
        if( ref != s. ref )
        {
            delete ref;
            ref = s. ref -> clone( );
        }
        // I am not in favour of making assignment
        // return something.
    }
    
    ~surface()
    {
        delete ref;
    }

    const surf& getsurf( ) const
    // There is no non-const method, because
    // changing would be dangerous.
    {
        return *ref;
    }
};


std::ostream& operator << (std::ostream& stream, const surface& s)
{
    return (s.ref)->print(stream);
}

std::ostream& operator << (std::ostream& stream, const std::vector< surface > & table )
{
    for(unsigned int i = 0; i < table.size(); ++i)
    {
        stream << i << "-th element = " << table[i] << "\n";
    }

    return stream;
}

void print_statistics( const std::vector< surface > & table )
{
    double total_area = 0.0;
    double total_circumference = 0.0;

    for (auto p = table. begin( ); p != table. end( ); ++p)
    {
        total_area += p -> getsurf( ). area( );
        total_circumference += p -> getsurf( ). circumference( );
        std::cout << "adding info about " << *p << "\n";
    }

    std::cout << "total area is " << total_area << "\n";
    std::cout << "total circumference is " << total_circumference << "\n";
}


int main()
{
    std::vector< surface > vec;

    vec.push_back( rectangle(2.0,3.0,4.0,5.0) );
    vec.push_back( triangle(2.0,3.0,4.0,5.0,6.0,7.0) );
    vec.push_back( circle(2.0,3.0,4.0) );

    std::cout << vec;
    print_statistics(vec);

    return 0;
}
