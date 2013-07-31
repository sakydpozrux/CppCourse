#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>


struct cmp
{
    bool operator() (const std::string& s1, const std::string& s2) const 
    {
        auto p2 = s2.begin();
        for (auto p1 = s1.begin(); p1 != s1.end(); ++p1, ++p2)
        {
            if (p2 == s2.end()) return false; // s2 is a prefix of s1
            if (tolower(*p1) < tolower(*p2)) return true; // s1 < s2
            if (tolower(*p1) > tolower(*p2)) return false; // s2 < s1
        }
        if (p2 != s2.end()) return true; // s1 is a prefix of s2
        return false;  //s1 == s2
    }
};

struct hash
{
    unsigned int operator() (const std::string& str) const
    {
        int h = 0;
        for(auto p = str.begin(); p != str.end(); ++p)
            h = 131 * h + tolower(*p);

        return h;
    }
};

struct equals
{
    bool operator() ( const std::string& s1, const std::string& s2 ) const
    {
        cmp c;
        return !(c(s1,s2) || c(s2,s1));
    }
};

std::vector< std::string> readfile( const std::string& name )
{
    std::ifstream input( name. c_str( ));
    std::vector< std::string > vec;
    std::string word;
    
    while (input.good() && !input.eof())
    {
        int c = input.get();

        if ( (ispunct(c) || isspace(c)) && !word.empty())
            vec.push_back( std::move(word) );
        if ( !(ispunct(c) || isspace(c)) )
            word.push_back(c);
    }    
    return vec;
}

std::ostream& operator<< ( std::ostream& stream, const std::vector< std::string > & vect )
{
    for (auto p = vect.begin(); p != vect.end(); ++p)
        stream << *p << std::endl;
    return stream;
}

std::map< std::string, unsigned int, cmp > frequencytable( const std::vector< std::string > & text )
{
    std::map< std::string, unsigned int, cmp > table;
    for (auto p = text.begin(); p != text.end(); ++p)
        table[*p]++;
    return table;
}

std::ostream& operator<< ( std::ostream& stream, const std::map< std::string, unsigned int, cmp > & m )
{
    for(auto p = m.begin(); p != m.end(); ++p)
        stream << p->first << " " << p->second << std::endl;
    return stream;
}

std::unordered_map< std::string, unsigned int, hash, equals > frequencytable2( const std::vector< std::string > & text )
{
    std::unordered_map< std::string, unsigned int, hash, equals > table;
    for (auto p = text.begin(); p != text.end(); ++p)
        table[*p]++;
    return table;
}

std::ostream& operator<< ( std::ostream& stream, const std::unordered_map< std::string, unsigned int, hash, equals > & m )
{
    for(auto p = m.begin(); p != m.end(); ++p)
        stream << p->first << " " << p->second << std::endl;
    return stream;
}

int main()
{
    std::cout << "map:\n";
    std::cout << frequencytable( std::vector< std::string > { "AA", "aA", "Aa", "this", "THIS" } );
    std::cout << "\nunordered_map:\n";
    std::cout << frequencytable2( std::vector< std::string > { "AA", "aA", "Aa", "this", "THIS" } );

    std::cout << "\nhash generating test (\"xxx\",\"XXX\",\"aaa\",\"baa\",\"aba\"):\n";
    hash h;
    std::cout << h("xxx") << " " << h("XXX") << " " << h("aaa") << " " << h("baa") << " " << h("aba") << "\n";

    std::cout << "\nequality test (\"xxx\"==\"XXX\"):\n";
    equals e;
    std::cout << e( "xxx", "XXX" ) << "\n";



    std::vector< std::string > words = readfile("book.txt");

    std::cout << "\nFrequency table (map):\n";
    auto table =  frequencytable(words);
    std::cout << "magnus: " << table["magnus"] << std::endl;
    std::cout << "hominum: " << table["hominum"] << std::endl;
    std::cout << "memoria: " << table["memoria"] << std::endl;

    std::string top_word;
    unsigned int max_occ = 0;
    for( auto p = table.begin(); p != table.end(); ++p )
    {
        if(p->second > max_occ)
        {
            max_occ = p->second;
            top_word = p->first;
        }
    }
    std::cout << "Word with most occurrences: " << top_word << " " << max_occ << std::endl;


    std::cout << "\nFrequency table (unordered_map):\n";
    auto table2 =  frequencytable2(words);
    std::cout << "magnus: " << table2["magnus"] << std::endl;
    std::cout << "hominum: " << table2["hominum"] << std::endl;
    std::cout << "memoria: " << table2["memoria"] << std::endl;

    std::string top_word2;
    unsigned int max_occ2 = 0;
    for( auto p = table2.begin(); p != table2.end(); ++p )
    {
        if(p->second > max_occ2)
        {
            max_occ2 = p->second;
            top_word2 = p->first;
        }
    }
    std::cout << "Word with most occurrences: " << top_word2 << " " << max_occ << std::endl;

    return 0;
}
