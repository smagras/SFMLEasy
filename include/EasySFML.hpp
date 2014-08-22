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


    protected:
    private:
};

#endif // EASYSFML_H
