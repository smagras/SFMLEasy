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
    }else if(s == "easy install"){
        this->install();
    }else{
        SetColor(RED);
        cout << "Unreconized command" << endl << endl;
        SetColor(WHITE);
    }

}

void EasySFML::install(){

    SetColor(DARKGREEN);

    string version;
    bool ok=true;

    cout << "# Enter the sfml version to install." << endl;
    cout << "# ex: 1" << endl;

    XMLNode xMainNode=XMLNode::openFileHelper("conf/version.xml","PMML");
    XMLNode xversions=xMainNode.getChildNode("versions");
    int n=xversions.nChildNode("version");
    for (int i = 0; i < n;i++ ){
        XMLNode xversion =xversions.getChildNode("version",i);
        cout << i << " : " << xversion.getChildNode("name").getText() << endl;
    }

    SetColor(WHITE);
    cout << "Version >> " ;
    getline(cin, version);
    cout << endl;

    int i = atoi(version.c_str());
    if (!(i >= 0 && i < n) || version == ""){
        ok = false;
        SetColor(RED);
        cout << "ERROR: Impossible to choose version '" << version << "' ."<< endl << endl;
        SetColor(WHITE);
    }
    else{
       // _compilertype = version;
       int i = atoi(version.c_str());
        XMLNode xversion =xversions.getChildNode("version",i);
        string sfmlPath = xversion.getChildNode("path").getText();
        if (!dirExist(sfmlPath)){
            cout << "Create new dir: '"<< sfmlPath <<"'" << endl;
            if (!dirExist("download/versions/")) mkdir("download/versions/");
            mkdir(sfmlPath.c_str());

        }

        if (!fileExist(xversion.getChildNode("zip").getText())){
            cout << "Download: "<< xversion.getChildNode("url").getText() << "..." << endl;
            get_http_data(xversion.getChildNode("url").getText(),xversion.getChildNode("zip").getText());
        }

        string command = "";
        cout << "Unzip: "<< xversion.getChildNode("zip").getText() << "..." << endl;
        cout << "Delete: "<< xversion.getChildNode("src").getText() << "..." << endl;
        command = xversion.getChildNode("src").getText();
        command = "rd /s /q \""+command+"\"";
        system( command.c_str() );
        extract_zip(xversion.getChildNode("path").getText(),xversion.getChildNode("zip").getText());

        // Compilation
        string mainpath = GetPath();
        string compiler = getCompiler();
        string src_sfml = xversion.getChildNode("src").getText();


        command = "";
        command += "cd " + src_sfml + " && ";
        command += "set PATH=\""+_compilerpath +"bin/\";%PATH%" + " && ";
        command += "set PATH=\""+_cmakepath +"bin/\";%PATH%" + " && ";
        command += "cmake -G \""+compiler+"\" -D CMAKE_BUILD_TYPE=Release -D BUILD_SHARED_LIBS=TRUE " + mainpath+"/"+src_sfml + " && ";
        command += "mingw32-make && ";
        command += "cmake -G \""+compiler+"\" -D CMAKE_BUILD_TYPE=Debug -D BUILD_SHARED_LIBS=TRUE " + mainpath+"/"+src_sfml + " && ";
        command += "mingw32-make && ";
        command += "cmake -G \""+compiler+"\" -D CMAKE_BUILD_TYPE=Release -D BUILD_SHARED_LIBS=FALSE " + mainpath+"/"+src_sfml + " && ";
        command += "mingw32-make && ";
        command += "cmake -G \""+compiler+"\" -D CMAKE_BUILD_TYPE=Debug -D BUILD_SHARED_LIBS=FALSE " + mainpath+"/"+src_sfml + " && ";
        command += "mingw32-make";
        //cout << command << endl;
        system(command.c_str());

    }


}

void EasySFML::load(){

    XMLNode confxml = XMLNode::openFileHelper("conf/conf.xml","PMML");
    _cmakepath = confxml.getChildNode("cmakepath").getText();
    _compilerpath = confxml.getChildNode("compilerpath").getText();
    _compilertype = confxml.getChildNode("compilertype").getText();
    cout <<"cm "<< _cmakepath << endl;
    cout <<"comp "<< _compilerpath << endl;
    cout <<"ty "<< _compilertype << endl;
}

void EasySFML::save(){

    XMLNode confxml = XMLNode::openFileHelper("conf/conf.xml","PMML");
    XMLNode confxml_cmakepath = confxml.getChildNode("cmakepath");
    confxml_cmakepath.updateText(_cmakepath.c_str());
    XMLNode confxml_compilerpath = confxml.getChildNode("compilerpath");
    confxml_compilerpath.updateText(_compilerpath.c_str());
    XMLNode confxml_compilertype = confxml.getChildNode("compilertype");
    confxml_compilertype.updateText(_compilertype.c_str());
    confxml.writeToFile("conf/conf.xml","PMML");

}

string EasySFML::getCompiler(){
    XMLNode xMainNode=XMLNode::openFileHelper("conf/compiler.xml","PMML");
    XMLNode xcompilers=xMainNode.getChildNode("compilers");

    int i = atoi(_compilertype.c_str());
    XMLNode xcompiler =xcompilers.getChildNode("compiler",i);
    return xcompiler.getChildNode("makefile").getText();
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
        else{
            _compilertype = compiler;
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
            }else{

                _compilerpath = compiler;
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
                if (!dirExist("download/cmake/")) mkdir("download/cmake/");
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


                cmake = xcmake.getChildNode("path").getText();
                cmake = clean_path(GetPath()+"\\"+cmake+"\\");
// C:/Users/STEVE/Desktop/Projet/C++/download/cmake/cmake-2.8.12.2-win32-x86/bin/cmake.exe

            }

            string cmakeExe = cmake+"bin/cmake.exe";
            if (!fileExist(cmakeExe)){
                ok = false;
                SetColor(RED);
                cout << "ERROR: Impossible to find '"<< cmakeExe <<"' ." << endl << endl;
                SetColor(WHITE);
            }
            else{
                _cmakepath = cmake;

            }
        }

        // End
        if (ok){
            SetColor(DARKGREEN);
            save();
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

    load();





    while(1){
        cout << "User >> " ;
        string res;
        getline(cin, res);
        parse(res);
    }


}



