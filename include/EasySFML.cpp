#include "EasySFML.hpp"

EasySFML::EasySFML()
{

}

EasySFML::~EasySFML()
{
    //dtor
}

void EasySFML::initCB(){

    bool ok = true;
    string sfmlpath = "";
    string cbpath = "";

    SetColor(DARKGREEN);
    cout << "# Enter where is your sfml path:" << endl;
    cout << "# ex: C:/SFML 2.1" << endl;
    SetColor(WHITE);
    cout << "SFML path >> " ;
    getline(cin, sfmlpath);
    cout << endl;
//sfmlpath = "C:/Users/STEVE/Desktop/Cours/M1 2013-2014/SFML 2.1";
    if (!dirExist(sfmlpath+"/include/SFML")){
        SetColor(RED);
        cout << "ERROR: Folder '" << sfmlpath << "' isn't SFML."<< endl << endl;
        SetColor(WHITE);
        ok = false;
    }

    if (ok){

        SetColor(DARKGREEN);
        cout << "# Enter where is your project file (codeblock):" << endl;
        cout << "# ex: C:/MyCodeBlockProject/MyCodeBlockProject.cbp" << endl;
        SetColor(WHITE);
        cout << "Codeblock project >> " ;
        getline(cin, cbpath);
        cout << endl;
  //      cbpath = "C:/Users/STEVE/Desktop/Projet/testouille/testouille.cbp";
        if (!fileExist(cbpath)){
            SetColor(RED);
            cout << "ERROR: File '" << cbpath << "' dont exist."<< endl << endl;
            SetColor(WHITE);
            ok = false;
        }


    }

    if (ok){

        XMLNode xMainNode=XMLNode::openFileHelper(cbpath.c_str(),"CodeBlocks_project_file");
        XMLNode xProject=xMainNode.getChildNode("Project");
        XMLNode xBuild=xProject.getChildNode("Build");

        // Debug
        XMLNode xTarget= xBuild.getChildNode("Target",0);
        if (xTarget.getChildNode("Linker").isEmpty ()) xTarget.addChild("Linker");
        XMLNode xLinker=xTarget.getChildNode("Linker");



        // On enleve les add sfml
        /*int addDebug = xLinker.nChildNode();
        for (int i = 0; i < addDebug ; i++){
            //string tmp = xLinker.getChildNode("Add",i).getAttributeValue(0);
            //if (tmp == "sfml-graphics-d"){
                cout << "eeee  " <<xLinker.getChildNode("Add",i).getAttributeValue(0) << endl ;
                xLinker.getChildNode("Add",i).deleteNodeContent();
                Sleep(1000);
            //}
        }*/

        xLinker.addChild("Add").addAttribute("library","sfml-graphics-d");
        xLinker.addChild("Add").addAttribute("library","sfml-audio-d");
        xLinker.addChild("Add").addAttribute("library","sfml-window-d");
        xLinker.addChild("Add").addAttribute("library","sfml-network-d");
        xLinker.addChild("Add").addAttribute("library","sfml-system-d");

        xMainNode.writeToFile(cbpath.c_str(),"CodeBlocks_project_file");

        // Realease
        XMLNode xTargetR= xBuild.getChildNode("Target",1);
        if (xTargetR.getChildNode("Linker").isEmpty ()) xTargetR.addChild("Linker");
        XMLNode xLinkerR=xTargetR.getChildNode("Linker");

        xLinkerR.addChild("Add").addAttribute("library","sfml-graphics");
        xLinkerR.addChild("Add").addAttribute("library","sfml-audio");
        xLinkerR.addChild("Add").addAttribute("library","sfml-window");
        xLinkerR.addChild("Add").addAttribute("library","sfml-network");
        xLinkerR.addChild("Add").addAttribute("library","sfml-system");



        //Compiler
        if (xProject.getChildNode("Compiler").isEmpty ()) xProject.addChild("Compiler");
        XMLNode compiler= xProject.getChildNode("Compiler");
        string compilerInclude = sfmlpath+"/include";
        compiler.addChild("Add").addAttribute("directory",compilerInclude.c_str());

        //Linker
        if (xProject.getChildNode("Linker").isEmpty ()) xProject.addChild("Linker");
        XMLNode linker= xProject.getChildNode("Linker");
        string compilerLib = sfmlpath+"/lib";
        linker.addChild("Add").addAttribute("directory",compilerLib.c_str());


        // Ecriture
        xMainNode.writeToFile(cbpath.c_str(),"CodeBlocks_project_file");

    }
    cout << "config project " << sfmlpath << endl;

}

void EasySFML::update(){
    cout << "download: " << "http://magrassteve.atspace.eu/EasySFML/compiler.xml" << "..." << endl;
    get_http_data("http://magrassteve.atspace.eu/EasySFML/compiler.xml","conf/compiler.xml");
    cout << "download: " << "http://magrassteve.atspace.eu/EasySFML/cmake.xml" << "..." << endl;
    get_http_data("http://magrassteve.atspace.eu/EasySFML/cmake.xml","conf/cmake.xml");
    cout << "download: " << "http://magrassteve.atspace.eu/EasySFML/version.xml" << "..." << endl;
    get_http_data("http://magrassteve.atspace.eu/EasySFML/version.xml","conf/version.xml");
    cout << "download: " << "http://magrassteve.atspace.eu/EasySFML/help.txt" << "..." << endl;
    get_http_data("http://magrassteve.atspace.eu/EasySFML/help.txt","conf/help.txt");
}

void EasySFML::parse(string s){

    if (s == "easy config"){
        this->config();
    }else if(s == "easy install"){
        this->install();
    }else if(s == "easy config -show"){
        this->showConfig();
    }else if(s == "easy update"){
        this->update();
    }else if(s == "help"){
        this->help();
    }else if(s == "easy init codeblock"){
        this->initCB();
    }else{
        SetColor(RED);
        cout << "Unreconized command" << endl << endl;
        SetColor(WHITE);
    }

}

void EasySFML::help(){
    cout << endl;
    string STRING;
	ifstream infile;
	infile.open ("conf/help.txt");
    while(!infile.eof()) // To get you all the lines.
    {
        getline(infile,STRING); // Saves the line in STRING.
        cout<<STRING << endl; // Prints our STRING.
    }
	infile.close();

    cout << endl << endl;
}

void EasySFML::install(){

    if (checkConfig()){

        SetColor(DARKGREEN);

        string version;
        bool ok=true;
        string finalpath;
        string command = "";

        // Final Path
        if(ok){

            SetColor(DARKGREEN);
            cout << "# Enter where you want to install sfml:" << endl;
            cout << "# ex: C:/" << endl;
            SetColor(WHITE);
            cout << "SFML path >> " ;
            getline(cin, finalpath);
            cout << endl;

            if (finalpath != ""){
                finalpath = clean_path(finalpath);
                if (!dirExist(finalpath)){
                    SetColor(RED);
                    cout << "ERROR: Impossible to find folder '" << finalpath << "' ."<< endl << endl;
                    SetColor(WHITE);
                    ok = false;
                }
            }
            else{
                SetColor(RED);
                cout << "ERROR: Impossible to find folder '" << finalpath << "' ."<< endl << endl;
                SetColor(WHITE);
                ok = false;
            }
        }

        if (ok){
            SetColor(DARKGREEN);
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



                cout << "Delete: "<< xversion.getChildNode("src").getText() << "..." << endl;
                command = xversion.getChildNode("src").getText();
                command = "rd /s /q \""+command+"\"";
                system( command.c_str() );
                cout << "Unzip: "<< xversion.getChildNode("zip").getText() << "..." << endl;
                extract_zip(xversion.getChildNode("path").getText(),xversion.getChildNode("zip").getText());

                // Compilation
                string mainpath = GetPath();
                string compiler = getCompiler();
                string src_sfml = xversion.getChildNode("src").getText();

                command = "";
                command += "cd " + src_sfml + " && ";
                command += "set PATH=\""+_compilerpath +"bin/\";%PATH%" + " && ";
                command += "set PATH=\""+_cmakepath +"bin/\";%PATH%" + " && ";
                command += "cmake -G \""+compiler+"\" -D CMAKE_BUILD_TYPE=Release -D BUILD_SHARED_LIBS=TRUE \"" + mainpath+"/"+src_sfml + "\" && ";
                command += "mingw32-make &&";
                command += "cmake -G \""+compiler+"\" -D CMAKE_BUILD_TYPE=Debug -D BUILD_SHARED_LIBS=TRUE \"" + mainpath+"/"+src_sfml + "\" && ";
                command += "mingw32-make && ";
                command += "cmake -G \""+compiler+"\" -D CMAKE_BUILD_TYPE=Release -D BUILD_SHARED_LIBS=FALSE \"" + mainpath+"/"+src_sfml + "\" && ";
                command += "mingw32-make && ";
                command += "cmake -G \""+compiler+"\" -D CMAKE_BUILD_TYPE=Debug -D BUILD_SHARED_LIBS=FALSE \"" + mainpath+"/"+src_sfml + "\" && ";
                command += "mingw32-make";
                //cout << command << endl;
                int resCMD = system(command.c_str());

                if (resCMD == 0 && errno == 0)
                {
                    cout << "Finalize installation..." << endl;
                    command = xversion.getChildNode("name").getText();
                    command = "xcopy  \""+ mainpath+"/"+src_sfml +"\" \""+finalpath+"/"+command+"\" /s /e /y /i";
                    cout << command << endl;
                    system(command.c_str());

                    cout << endl << "Installation complete." << endl;
                }
                else{
                    SetColor(RED);
                    cout << "ERROR: Impossible to cmake or compile." << endl;
                    SetColor(WHITE);
                }



            }
        }

    }



}

void EasySFML::load(){
    if (!dirExist("download")) mkdir("download");
    if (!dirExist("download/cmake/")) mkdir("download/cmake/");
    if (!dirExist("download/versions/")) mkdir("download/versions/");
    if (!dirExist("download/conf/")) mkdir("download/conf/");

    string confFile = "";
    confFile += "<?xml version=\"1.0\" encoding=\"PMML\"?>";
    confFile += "<PMML version=\"3.0\" xmlns=\"http://www.dmg.org/PMML-3-0\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema_instance\">";
    confFile += "<cmakepath>undefined</cmakepath>";
    confFile += "<compilerpath>undefined</compilerpath>";
    confFile += "<compilertype>0</compilertype>";
    confFile += "</PMML>";

    if (!fileExist("conf/conf.xml")) createFile("conf/conf.xml",confFile);
    XMLNode confxml = XMLNode::openFileHelper("conf/conf.xml","PMML");
    _cmakepath = confxml.getChildNode("cmakepath").getText();
    _compilerpath = confxml.getChildNode("compilerpath").getText();
    _compilertype = confxml.getChildNode("compilertype").getText();


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

bool EasySFML::checkConfig(){

    XMLNode xMainNode=XMLNode::openFileHelper("conf/compiler.xml","PMML");
    XMLNode xcompilers=xMainNode.getChildNode("compilers");
    int i = atoi(_compilertype.c_str());
    XMLNode xcompiler =xcompilers.getChildNode("compiler",i);

    bool ok = true;
    if (!fileExist(_cmakepath+"bin/cmake.exe")){
        ok = false;
        SetColor(RED);
        cout << "ERROR: Impossible to find cmake '"<< _cmakepath <<"' ." << endl ;
        SetColor(WHITE);
    }

    if (!fileExist(_compilerpath+xcompiler.getChildNode("bin").getText())){
        ok = false;
        SetColor(RED);
        cout << "ERROR: Impossible to find compiler '"<< _compilerpath <<"' ." << endl << endl;
        SetColor(WHITE);
    }

    return ok;
}

string EasySFML::getCompiler(){
    XMLNode xMainNode=XMLNode::openFileHelper("conf/compiler.xml","PMML");
    XMLNode xcompilers=xMainNode.getChildNode("compilers");

    int i = atoi(_compilertype.c_str());
    XMLNode xcompiler =xcompilers.getChildNode("compiler",i);
    return xcompiler.getChildNode("makefile").getText();
}

void EasySFML::showConfig(){
    cout << "Compiler: " << _compilerpath << endl;
    cout << "Cmake: " << _cmakepath << endl;
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

        _compilerpath = clean_path(_compilerpath);

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

                XMLNode confxml = XMLNode::openFileHelper("conf/cmake.xml","PMML");
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
                cmake = GetPath()+"\\"+cmake+"\\";
// C:/Users/STEVE/Desktop/Projet/C++/download/cmake/cmake-2.8.12.2-win32-x86/bin/cmake.exe

            }

            cmake = clean_path(cmake);

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


    help();


    while(1){
        cout << "User >> " ;
        string res;
        getline(cin, res);
        parse(res);
    }


}



