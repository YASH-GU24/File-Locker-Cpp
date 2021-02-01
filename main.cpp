#include <iostream>
#include <string>
#include <fstream>
#include <ctype.h>
#include <windows.h>
#include <limits.h>
#include <stdio.h>
using namespace std;
string cpassword,cusername,cfilePath,cfileName;
void inst(){
    cout<<"____INSTRUCTIONS___"<<endl;
    cout<<endl<<"# Username must be unique"<<endl;
    cout<<endl<<"# Your password must be 8-20 characters long."<<endl;
    cout<<endl<<"# You have to enter Filepath and Filename in different lines"<<endl;
    cout<<"     ** while entering Filepath, make sure that you enter '\\\\' in place of '\\'"<<endl;
    cout<<"     ** your Filepath should end on '\\\\'"<<endl;
}
class safe {
        private :
        string str;

        public : string encrypt(string s);
                int key;
                string decrypt(string s,int n);
                 int check(string s,int n);

};

safe obj;



//   function to encypt a message takes as a argument string to be encypted generates random key



string safe :: encrypt(string s)    {
    obj.str=s;
    int upper=5,lower=1;
    srand(time(0));
    string temp{};
     obj.key = 4;
     for(int i=0;i<s.size();++i)    {

           if(s[i]==' ')  temp+=' ';

           else   {


                int num=(int)(s[i])+obj.key;
             temp+=(char)(num);

           }



     }
    return temp;

}

  // function to decrypt a message takes as a argument string to be decrypted and the key

string safe :: decrypt(string s,int n)    {

    string temp{};
     for(int i=0;i<s.size();++i)    {

        if(s[i]==' ') temp+=' ';

         else {

            int num=(int)(s[i])-n;
            temp+=(char)(num);

         }
     }

     return temp;
}

// function which takes as a argument a string and checks whether that string matches with the encypted string

int safe :: check(string s,int n) {

    string temp{};
     for(int i=0;i<s.size();++i)    {

        if(s[i]==' ') temp+=' ';

        else  {

             int num=(int)(s[i])+n;
             temp+=(char)(num);

        }

     }

     if(obj.str==temp)  return 1;

     else return 0;

}
string getCurrentDir() {
    char buff[MAX_PATH];
    GetModuleFileName( NULL, buff, MAX_PATH );
    string::size_type position = string( buff ).find_last_of( "\\/" );
    return string( buff ).substr( 0, position);
}
string getpass(const char *prompt, bool show_asterisk=true)
{
  const char BACKSPACE=8;
  const char RETURN=13;

  string password;
  unsigned char ch=0;

  cout <<prompt<<endl;

  DWORD con_mode;
  DWORD dwRead;

  HANDLE hIn=GetStdHandle(STD_INPUT_HANDLE);

  GetConsoleMode( hIn, &con_mode );
  SetConsoleMode( hIn, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT) );

  while(ReadConsoleA( hIn, &ch, 1, &dwRead, NULL) && ch !=RETURN)
    {
       if(ch==BACKSPACE)
         {
            if(password.length()!=0)
              {
                 if(show_asterisk)
                     cout <<"\b \b";
                 password.resize(password.length()-1);
              }
         }
       else
         {
             password+=ch;
             if(show_asterisk)
                 cout <<'*';
         }
    }
  cout <<endl;
  return password;
}

void getpath(string str)
{

    int k;
    for(int i=0;i<str.length();i++){
        if(str[i]=='\\'){
            k=i;
            str.insert(k,"\\");
        }
    }
    cout<<str<<endl;

}
string checkpassname(string user,string pass){
    string cpassword,cusername,cfilePath,cfileName;
    ifstream readdata("userData.txt");
    while(!readdata.eof()){
        readdata>>cusername;
        readdata>>cpassword;
        readdata>>cfilePath;
        readdata>>cfileName;
        readdata.close();
        if(strcmp(user.c_str(),cusername.c_str())==0 && strcmp((obj.encrypt(pass)).c_str(),cpassword.c_str())==0){
            return cfileName;
        }
        else{
                printf("No matching Username and Password\n");
            return "";
        }
    }

}
string checkpasspath(string user,string pass){
    string cpassword,cusername,cfilePath,cfileName;
    ifstream readdata("userData.txt");
    while(!readdata.eof()){
        readdata>>cusername;
        readdata>>cpassword;
        readdata>>cfilePath;
        readdata>>cfileName;
        readdata.close();
        if(strcmp(user.c_str(),cusername.c_str())==0 && strcmp((obj.encrypt(pass)).c_str(),cpassword.c_str())==0){
            return cfilePath;
        }
        else{
                //printf("No matching Username and Password");
            return "";
        }
    }

}
void fileMove (string file, string source, string destination)
{
    for (int i = 0; i < source.size(); i++)
    {
        if (source[i] == '\\')
            source[i] = '/';
    }
    for (int i = 0; i < destination.size(); i++)
    {
        if (destination[i] == '\\')
            destination[i] = '/';
    }
    if (source[source.size() -1 ] != '/')
        source.push_back('/');
    source = source + file;
    if (destination[destination.size() - 1] != '/')
        destination.push_back('/');
    destination = destination + file;
    ifstream sourceFile (source.c_str(), ios::binary);
    if (sourceFile)
    {
        ifstream idestination (destination.c_str());
        if (idestination)
        {


                idestination.close();
                ofstream destinationFile (destination.c_str(), ios::binary);
                string line;
                while (getline(sourceFile,line))
                {
                    destinationFile<<line<<endl;
                }
                destinationFile.flush();
                destinationFile.close();
                sourceFile.close();
                int status = remove(source.c_str());
                if (status == 0)
                    cout<<endl;
                else
                {
                    perror("[ERROR]:-\nNot able to lock file due to following error");
                }

        }
        else
        {
            idestination.close();
            ofstream destinationFile (destination.c_str(), ios::binary);
            string line;
            while (getline(sourceFile,line))
            {
                destinationFile<<line<<endl;;
            }
            destinationFile.flush();
            destinationFile.close();
            sourceFile.close();
            int status = remove(source.c_str());
            if (status == 0)
                cout<<endl;
            else
            {
                perror("[ERROR]:-\nNot able to move file due to following error");
            }
        }
        sourceFile.close();
    }
    else
    {
        cout<<endl<<"[ERROR]:-"<<endl;
        cout<<"The given file is not present at given path"<<endl;
    }
}
void search(){
    ifstream readdata("userData.txt");

    readdata>>cusername;
    readdata>>cpassword;
    readdata>>cfilePath;
    readdata>>cfileName;
    cout<<cfilePath<<endl<<cfileName<<endl;
    readdata.close();


}

class User {
public:
    string username;

    string password;
    string filePath;
    string fileName;
    void userRegister()
    {
        ofstream usersFile ("userData.txt");
        if (    !usersFile.is_open())

        {
            usersFile.open("userData.txt");
        }
            usersFile << username << "\n" << password << "\n"<<filePath<<"\n"<<fileName<<endl;
            usersFile.close();
    }
};
int main() {
    int keyPass,keyFile;
    int n;

do{
        cout << "------------------------------------------------------------------------------------------------------------------------\n\t\t\t\t\t\tFILE LOCKER\n------------------------------------------------------------------------------------------------------------------------\n\nPlease enter your choice:-\n1.LOCK A FILE\n2.UNLOCK A EXISTING UNLOCKED FILE\n3.INSTRUCTIONS\n";
    cin>>n;
        if(n==1)
            {
            User user1;
            cout << "WELCOME!\n-------------------------------\n\nPlease register.\nENTER A NEW USERNAME:\n";
            cin >> user1.username;
            string passTemp=getpass("CREATE A PASSWORD: ",true);
            keyPass=obj.key;
            user1.password=obj.encrypt(passTemp);
            cout << "ENTER THE FILE PATH:\n";
            cin >> user1.filePath;
            cout << "ENTER THE FILE NAME:\n";
            cin >> user1.fileName;
            user1.userRegister();
            //cout<<obj.encrypt(user1.fileName);
            string newFileName=obj.encrypt(user1.fileName);
            rename((user1.filePath+user1.fileName).c_str(),(user1.filePath+newFileName).c_str());
            //cout<<obj.decrypt(newFileName,4);
            fileMove(newFileName,(user1.filePath).c_str(),getCurrentDir());
            cout<<"FILE LOCKED SUCCESFULLY!";
                rename("userData.txt","temp.bat");
            }

        else if (n==2)
            {
                rename("temp.bat","userData.txt");
            string user;
            cout<<"ENTER USERNAME:"<<endl;
            cin>>user;
            string password=getpass("CREATE A PASSWORD: ",true);
            string file_name=checkpassname(user,password);
            string file_path=checkpasspath(user,password);
            if(strcmp(file_name.c_str(),""))
                cout<<"Your file is "<<file_name<<endl;
                if(strcmp(file_name.c_str(),""))
                fileMove(obj.encrypt(file_name),getCurrentDir(),(file_path).c_str());
                if(strcmp(file_name.c_str(),""))
                cout<<"FILE UNLOCKED SUCCESFULLY!";
                rename((file_path+obj.encrypt(file_name)).c_str(),(file_path+file_name).c_str());
                rename("userData.txt","temp.bat");
            }
            else if (n==3)
            {
                inst();
            }
            else
            {
                    cout<<"Please enter a valid choice\n"<<endl;
            }
}while(n!=1 && n!=2);
    return 0;
}
