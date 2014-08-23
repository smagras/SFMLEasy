#include "EasySFML.hpp"

EasySFML::EasySFML()
{

}

EasySFML::~EasySFML()
{
    //dtor
}
//easy config "C:\Program Files (x86)\CMake" "C:\MiGw" 2.1
void EasySFML::parse(string s){

    if (s == "easy config"){
        this->config();

    }else{
        SetColor(RED);
        cout << "Unreconized command" << endl << endl;
        SetColor(WHITE);
    }

}

void EasySFML::config(){

        string typeCompiler;
        string compiler;
        string cmake;
        bool ok = true;

        // Type de compiler
        SetColor(DARKGREEN);

        cout << "# Enter the number in the list to define your compiler." << endl;
        cout << "# ex: 1" << endl;

        XMLNode xMainNode=XMLNode::openFileHelper("conf/compiler.xml","PMML");
        XMLNode xcompilers=xMainNode.getChildNode("compilers");
        int n=xcompilers.nChildNode("compiler");
        for (int i = 0; i < n;i++ ){
        XMLNode xcompiler =xcompilers.getChildNode("compiler",i);
        cout << i << " : " << xcompiler.getChildNode("name").getText() << endl;
        }

        SetColor(WHITE);
        cout << "Compiler >> " ;
        getline(cin, compiler);
        cout << endl;

        int i = atoi(compiler.c_str());
        if (!(i >= 0 && i < n) || compiler == ""){
            ok = false;
            SetColor(RED);
            cout << "ERROR: Impossible to choose compiler '" << compiler << "' ."<< endl << endl;
            SetColor(WHITE);
        }

        // Compiler
        if(ok){
            XMLNode xcompiler =xcompilers.getChildNode("compiler",i);

            SetColor(DARKGREEN);
            cout << "# Enter your compiler path:" << endl;
            cout << "# ex: " << xcompiler.getChildNode("example").getText() << endl;
            SetColor(WHITE);
            cout << "Compiler path >> " ;
            getline(cin, compiler);
            cout << endl;



            string compExe = compiler+xcompiler.getChildNode("bin").getText();
            if (!fileExist(compExe)){
                ok = false;
                SetColor(RED);
                cout << "ERROR: Impossible to find '"<< compExe <<"' ." << endl << endl;
                SetColor(WHITE);
            }
        }

        // Cmake
        if(ok){
            SetColor(DARKGREEN);
            cout << "# Enter your cmake path or ENTER for automatic download:" << endl;
            cout << "# ex: C:\\Cmake" << endl;
            SetColor(WHITE);
            cout << "Cmake path >> " ;
            getline(cin, cmake);
            cout << endl;

            if (cmake == ""){
                XMLNode confxml = XMLNode::openFileHelper("conf/conf.xml","PMML");
                XMLNode xcmake = confxml.getChildNode("cmake");

                if (!fileExist(xcmake.getChildNode("zip").getText())){
                    cout << "Download: "<< xcmake.getChildNode("url").getText() << "..." << endl;
                    get_http_data(xcmake.getChildNode("url").getText(),xcmake.getChildNode("zip").getText());
                }

                if (!fileExist(xcmake.getChildNode("src").getText())){
                    cout << "Unzip: "<< xcmake.getChildNode("zip").getText() << "..." << endl;
                    extract_zip("download/cmake",xcmake.getChildNode("zip").getText());
                    cmake = xcmake.getChildNode("path").getText();
                }
                else{
                    cmake = xcmake.getChildNode("path").getText();
                }

            }

            string cmakeExe = cmake+"\\bin\\cmake.exe";
            if (!fileExist(cmakeExe)){
                ok = false;
                SetColor(RED);
                cout << "ERROR: Impossible to find '"<< cmakeExe <<"' ." << endl << endl;
                SetColor(WHITE);
            }
        }

        // End
        if (ok){
            SetColor(DARKGREEN);
            cout << "Configuration is succesfully done." << endl;
            SetColor(WHITE);
        }


}

void EasySFML::run(){
    SetColor(WHITE);
    cout << "+ ------------------------------------------------------------- +" << endl;
    cout << "+ SFMLEasy                                                      +" << endl;
    cout << "+ Author : Magras Steve                                         +" << endl;
    cout << "+ Version : "<< VERSION <<"                                                 +" << endl;
    cout << "+ ------------------------------------------------------------- +" << endl << endl;



    XMLNode xMainNode=XMLNode::openFileHelper("conf/version.xml","PMML");
    XMLNode versions=xMainNode.getChildNode("versions");
    int n=versions.nChildNode("version");
    for (int i = 0; i < n;i++ ){
        XMLNode version =versions.getChildNode("version",i);
        cout  << version.getChildNode("name").getText() << endl;
    }



    while(1){
        cout << "User >> " ;
        string res;
        getline(cin, res);
        parse(res);
    }


}



