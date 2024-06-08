#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <string>
#include <thread>
using namespace std;
int main() {
    cout << "\e[1;35m\n";
   string filename;
   cout << "Enter the file name: ";
   cin >> filename;

    struct stat fileStat;
    
    // Retrieve file information
    if (stat(filename.c_str(), &fileStat) == 0) {
       cout << "File Permissions: ";
        // Check file permissions
       cout << ((fileStat.st_mode & S_IRUSR) ? "r" : "-");
       cout << ((fileStat.st_mode & S_IWUSR) ? "w" : "-");
       cout << ((fileStat.st_mode & S_IXUSR) ? "x" : "-");
       cout << ((fileStat.st_mode & S_IRGRP) ? "r" : "-");
       cout << ((fileStat.st_mode & S_IWGRP) ? "w" : "-");
       cout << ((fileStat.st_mode & S_IXGRP) ? "x" : "-");
       cout << ((fileStat.st_mode & S_IROTH) ? "r" : "-");
       cout << ((fileStat.st_mode & S_IWOTH) ? "w" : "-");
       cout << ((fileStat.st_mode & S_IXOTH) ? "x" : "-");
       cout <<endl;
        
        // Display other file information
       cout << "File Size: " << fileStat.st_size << " bytes" <<endl;
       cout << "Last Access Time: " << ctime(&fileStat.st_atime);
       cout << "Last Modification Time: " << ctime(&fileStat.st_mtime);
       cout << "Last Status Change Time: " << ctime(&fileStat.st_ctime);
    } else {
       cerr << "Error occurred while retrieving file information." <<endl;
    }
    sleep (4);
    return 0;
}
