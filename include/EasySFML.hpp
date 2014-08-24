#ifndef EASYSFML_H
#define EASYSFML_H


#include "../stdafx.hpp"

class EasySFML
{
    public:
        /** Default constructor */
        EasySFML();
        /** Default destructor */
        virtual ~EasySFML();


        void run();
        void parse(string s);
        void config();
        void install();

        void save();
        void load();

        void showConfig();

        string getCompiler();

    private:
        string _compilerpath;
        string _compilertype;
        string _cmakepath;
};

#endif // EASYSFML_H
