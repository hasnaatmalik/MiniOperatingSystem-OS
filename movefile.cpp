#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <thread>
using namespace std;
int main()
{
    cout << "\e[1;33m\n";
    int result = 1;
    char oldname[500];
    char newname[500];
    cout << "Enter the name of a file you want to move (include directory structure)" << endl;
    cin >> oldname;
    cout << "Enter the new location (include directory structure)" << endl;
    cin >> newname;

    result = rename(oldname, newname);
    if (result == 0)
        cout << "File successfully moved" << endl;
    else
        cout << "Error moving file" << endl;

    cin.get();
    cin.get();
    sleep (4);
    return 0;
}
