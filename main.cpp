#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <fstream>
#include <chrono>
#include <thread>
#include <atomic>
#include <termios.h>
#include <cstdlib>
#include <queue>
using namespace std;
pthread_mutex_t lockk[7];
int ind = -1;
int memory [100];
string tasks [100];
int counter = 0;
int harddisk, ram, cores;
bool checkIfKernel = false;
struct Task {
    int id;
    string name;
    int memoryRequirement;
};
queue<Task> readyQueue;    
queue<Task> waitingQueue;  
queue<Task> runningQueue; 
void menu();
void freeMemory (int &sum, int &size, string &var);
void freeMemory(int &sum, int &size, string &var) {
    for (int i = 0; i <= ind; i++) {
        memory[i] = 0;
        tasks[i] = "";
    }
    ind = -1;
    counter = 0;
    sum = 0;
    size = 0;
    var = "";
}
void addTaskToQueue(int id, string name, int memoryRequirement, int state) {
    Task task = {id, name, memoryRequirement};
    switch (state) {
        case 0: // Ready
            readyQueue.push(task);
            break;
        case 1: // Waiting
            waitingQueue.push(task);
            break;
        case 2: // Running
            runningQueue.push(task);
            break;
        default:
            cout << "Invalid state." << endl;
            break;
    }
}
void *taskManager(void *arg) {
    int choice;
    cout << endl << "Active Tasks       MB" << endl;
    for (int i = 0; i <= ind; i++) {
        if (memory[i] == 0) {
            continue;
        } else {
            cout << "Task " << i + 1 << " : " << tasks[i] << "      " << memory[i] << endl;
        }
    }
    cout << "Enter the task number to terminate (0 to cancel): ";
    cin >> choice;
    if (choice >= 1 && choice <= ind + 1) {
        memory[choice - 1] = 0;
        tasks[choice - 1] = "";
        cout << "Task " << choice << " terminated." << endl;
    } else if (choice != 0) {
        cout << "Invalid task number." << endl;
    }
    sleep(3);
    pthread_exit(NULL);
}


void *calculator (void *arg) {
    pthread_mutex_lock(&lockk[0]);
    system ("g++ calculator.cpp -o calculator");
    system("osascript -e 'tell application \"Terminal\" to do script \"./calculator\"'");
    pthread_mutex_unlock(&lockk[0]);
    pthread_exit(NULL);
}
void *ticTacToe (void *arg) {
    pthread_mutex_lock(&lockk[1]);
    system ("g++ tictactoe.cpp -o tictactoe");
    system("osascript -e 'tell application \"Terminal\" to do script \"./tictactoe\"'");
    pthread_mutex_unlock(&lockk[1]);
    pthread_exit(NULL);
}
void *moveFile (void *arg) {
    pthread_mutex_lock(&lockk[2]);
    system ("g++ movefile.cpp -o movefile `pkg-config --cflags --libs gtk+-3.0`");
    system("osascript -e 'tell application \"Terminal\" to do script \"./movefile\"'");
    pthread_mutex_unlock(&lockk[2]);
    pthread_exit(NULL);
}
void *guessGame (void *arg) {
    pthread_mutex_lock(&lockk[3]);
    system ("g++ guessgame.cpp -o guessgame `pkg-config --cflags --libs gtk+-3.0`");
    system("osascript -e 'tell application \"Terminal\" to do script \"./guessgame\"'");
    pthread_mutex_unlock(&lockk[3]);
    pthread_exit(NULL);
}
void *createEditFile (void *arg) {
    pthread_mutex_lock(&lockk[4]);
    system ("g++ -o createeditfile createeditfile.cpp -lsfml-audio -lsfml-system");
    system("osascript -e 'tell application \"Terminal\" to do script \"./createeditfile\"'");
    pthread_mutex_unlock(&lockk[4]);
    pthread_exit(NULL);
}
void *fileinfo (void *arg) {
    pthread_mutex_lock(&lockk[5]);
    system ("g++ fileinfo.cpp -o fileinfo");
    system("osascript -e 'tell application \"Terminal\" to do script \"./fileinfo\"'");
    pthread_mutex_unlock(&lockk[5]);
    pthread_exit(NULL);
}
void start () {
    system ("clear");
    cout << "\e[1;35m\n";
    cout << "  _   _       _       _____" << endl; 
    cout << " | | | |     / \\     |   /" << endl;
    cout << " | |_| |    /   \\       /  " << endl;
    cout << " |  _  |   /_____\\     /   " << endl;
    cout << " |_| |_|  /       \\   /____|" << endl;
    cout << endl;
    cout << "Operating system by 22F-3389, 22F-8776, 21F-9237  " << endl << endl;
    const int width = 20;

    cout << "Loading...\n";
    for (int i = 0; i <= width; i++)
    {
        cout << "(";
        for (int j = 0; j < width; j++)
        {
            if (j < i)
            {
                cout << "$";
            }
            else
            {
                cout << ".";
            }
        }
        cout << ") " << int(i / (float)width * 100.0) << " %\r";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    cout << endl
         << "Loading complete!\n";
    sleep(5);
    system("clear");
}
void userMode()
{
    ram = 2 * 1024;
    harddisk = 250 * 1024;
    checkIfKernel = false;
}
void kernelMode()
{
    cout << "\e[1;31m\n";
    cout << "Enter the amount of Ram(GB) : ";
    cin >> ram;
    cout << "Enter the amount of Hardisk(GB) : ";
    cin >> harddisk;
    cout << "Enter the amount of cores : ";
    cin >> cores;
    ram = ram * 1024;
    harddisk = harddisk * 1024;
    checkIfKernel = true;
}
void resources () {
    cout << "RAM Available: " << ram << "MB" << endl;
    cout << "Hard Disk Avaiable: " << harddisk << "MB" << endl;
    cout << endl;
}
void bootmenu () {
    cout << "\e[1;34m\n";
    cout << "Select the mode you want to boot in:" << endl;
    cout << "1. User Mode" << endl;
    cout << "2. Kernel Mode" << endl;
    cout << "3. Exit" << endl;
    cout << "Enter your choice: ";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            userMode();
            break;
        case 2:
            kernelMode();
            break;
        case 3:
            exit(0);
        default:
            cout << "Invalid choice!" << endl;
            bootmenu();
    }
}
void setNonBlocking(bool nonBlocking) {
    struct termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);
    if (nonBlocking) {
        ttystate.c_lflag &= ~ICANON;
        ttystate.c_cc[VMIN] = 0;
        ttystate.c_cc[VTIME] = 0;
    } else {
        ttystate.c_lflag |= ICANON;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}
bool keyPressed() {
    fd_set rfds;
    struct timeval tv;
    FD_ZERO(&rfds);
    FD_SET(STDIN_FILENO, &rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    return select(STDIN_FILENO + 1, &rfds, NULL, NULL, &tv) > 0;
}

void sleepInterruptible(int seconds) {
    std::atomic<bool> interrupted(false); 
    setNonBlocking(true);

    auto startTime = std::chrono::steady_clock::now();
    auto targetTime = startTime + std::chrono::seconds(seconds);

    while (!interrupted && std::chrono::steady_clock::now() < targetTime) {
        if (keyPressed()) {
            cout << "Interrupted!" << endl;
            interrupted = true;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    setNonBlocking(false);
}
void menu () {
    pthread_t thread[7];
    for (int i = 0; i < 5; i++) {
        pthread_mutex_init(&lockk[i], NULL);
    }
    int sum = 0;
    int size = 0;
    bool check = false;
    string var = "";
    int choice;
    while (true) {
        system ("clear");
        cout << "\e[1;36m\n";
        cout << "Menu:" << endl;
        cout << "1. Task Manager" << endl;
        cout << "2. Calculator" << endl;
        cout << "3. Tic Tac Toe" << endl;
        cout << "4. Move File" << endl;
        cout << "5. Guess Game" << endl;
        cout << "6. Create/Edit File" << endl;
        cout << "7. File Info" << endl;
        cout << "8. ShutDown" << endl;
        cout << "9. Sleep" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                pthread_create(&thread[0], NULL, &taskManager, NULL);
                pthread_join(thread[0], NULL);
                break;
            case 2:
            for (int i = 0; i < counter; i++) {
                sum += memory[i];
            }
            if (sum > ram) {
                cout << "Not enough memory to run the program." << endl;
                cout << "Please free up some memory to run the program." << endl;
                check = true;
            }
            if (check == false) {
                var = "Calculator";
                size = 1000;
                ind++;
                memory[ind] = size;
                tasks[ind] = var;
                counter++;
                int f = fork();
                if (f > 0) {
                    wait(NULL);
                }
                else {
                    addTaskToQueue(1, "Calculator", 1000, 0);
                    pthread_create(&thread[1], NULL, &calculator, NULL);
                    pthread_join(thread[1], NULL);
                    exit(0);
                }
            }
                break;
            case 3:
            for (int i = 0; i < counter; i++) {
                sum += memory[i];
            }
            if (sum > ram) {
                cout << "Not enough memory to run the program." << endl;
                cout << "Please free up some memory to run the program." << endl;
            }
            if (check == false) {
                var = "Tic Tac Toe";
                size = 2000;
                ind++;
                memory[ind] = size;
                tasks[ind] = var;
                counter++;
                int f = fork();
                if (f > 0) {
                    wait(NULL);
                }
                else {
                    addTaskToQueue(2, "Tic Tac Toe", 2000, 0);
                    pthread_create(&thread[2], NULL, &ticTacToe, NULL);
                    pthread_join(thread[2], NULL);
                    exit(0);
                }
            }
                break;
            case 4:
            for (int i = 0; i < counter; i++) {
                sum += memory[i];
            }
            if (sum > ram) {
                cout << "Not enough memory to run the program." << endl;
                cout << "Please free up some memory to run the program." << endl;
            }
            if (check == false) {
                var = "Move File";
                size = 15;
                ind++;
                memory[ind] = size;
                tasks[ind] = var;
                counter++;
                int f = fork();
                if (f > 0) {
                    wait(NULL);
                }
                else {
                    addTaskToQueue(3, "Move File", 15, 0);
                    pthread_create(&thread[3], NULL, &moveFile, NULL);
                    pthread_join(thread[3], NULL);
                    exit(0);
                }
            }
                break;
            case 5:
            for (int i = 0; i < counter; i++) {
                sum += memory[i];
            }
            if (sum > ram) {
                cout << "Not enough memory to run the program." << endl;
                cout << "Please free up some memory to run the program." << endl;
                check = true;
            }
            if (check == false) {
                var = "Guess Game";
                size = 10;
                ind++;
                memory[ind] = size;
                tasks[ind] = var;
                counter++;
                int f = fork();
                if (f > 0) {
                    wait(NULL);
                }
                else {
                    addTaskToQueue(4, "Guess Game", 10, 0); 
                    pthread_create(&thread[4], NULL, &guessGame, NULL);
                    pthread_join(thread[4], NULL);
                    exit(0);
                }
            }
                break;
            case 6:
            for (int i = 0; i < counter; i++) {
                sum += memory[i];
            }
            if (sum > ram) {
                cout << "Not enough memory to run the program." << endl;
                cout << "Please free up some memory to run the program." << endl;
            }
            if (check == false) {
                var = "Create/Edit File";
                size = 15;
                ind++;
                memory[ind] = size;
                tasks[ind] = var;
                counter++;
                int f = fork();
                if (f > 0) {
                    wait(NULL);
                }
                else {
                    addTaskToQueue(5, "Create/Edit File", 15, 0);
                    pthread_create(&thread[5], NULL, &createEditFile, NULL);
                    pthread_join(thread[5], NULL);
                    exit(0);
                }
            }
                break;
            case 7:
                for (int i = 0; i < counter; i++) {
                    sum += memory[i];
                }
                if (sum > ram) {
                    cout << "Not enough memory to run the program." << endl;
                    cout << "Please free up some memory to run the program." << endl;
                }
                if (check == false) {
                    var = "Create Edit File";
                    size = 10;
                    ind++;
                    memory[ind] = size;
                    tasks[ind] = var;
                    counter++;
                    int f = fork();
                    if (f > 0) {
                        wait(NULL);
                    }
                    else {
                        addTaskToQueue(6, "File Info", 10, 0);
                        pthread_create(&thread[6], NULL, &fileinfo, NULL);
                        pthread_join(thread[6], NULL);
                        exit(0);
                    }
                }
                break;
            case 8:
                cout << "Shutting Down." << endl;
                for (int i = 0; i < 6; i++) {
                    pthread_mutex_destroy(&lockk[i]);
                }

                exit(0);
            case 9:
                cout << "Sleeping for 4000 seconds." << endl;
                cout << "Press any key to wake up." << endl;
                sleepInterruptible(4000);
                cout << "Done sleeping." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 7." << endl;
        }
        int Memory = 0;
	    if ( checkIfKernel == true )
	    {
		    if ( check == true )
		    {
		        Memory = 0;
		        cout << endl << "1. Free memory" << endl;
		        cout << "2. ShutDown";
		        cout << endl << "Choice : ";
		        cin >> Memory;
		        cout << endl;
		        if ( Memory == 1 ) {
		    	    system("clear");
		    	    cout << "Freeing up memory from the task manager ...." << endl << endl ;
		    	    sleep(3);
		    	    freeMemory(sum,size,var);
		    	    cout << "Memory freed successfully " << endl ;
		    	    cout << "Press 1 to continue to main page" << endl ;
		    	    cin >> Memory;
		    	    if (Memory == 1)
		    	    {
		    	        check = false;
		    	        continue;
		    	    }
		    	    else
		    	    {
		    	        check = false;
		    	        continue;
		    	    }
		    }
		    else
		    {
		    	check = false;
		        cout << "\e[1;32m\n";
            		system("clear");
            		cout << "Shutting Down" << endl;
            		sleep(3);
            		break;
		    }
		}
	}
	else
	{
	    if ( check == true )
	    {
	        cout << "Not enough rights to free up memory " << endl ;
	        sleep(3);
	        int key = 0 ;
	    	cout << "\e[1;32m\n";
            	cout << "Press any key to shutdown " << endl << endl ;
            	cin >> key;
            	system("clear");
            	cout << "Shutting Down" << endl;
            	sleep(3);
            	
            	break;
	    }
            
	}
        cout << endl
             << endl;
        cout << "1 to Close  || 2 to Minimize || 3 to multitask" << endl;
        int choice1;
        cout << "Choice : ";
        cin >> choice1;
        if (choice1 == 1)
        {
            int check = -1;
            cout << "You have Closed" << endl
                 << endl;

            if (choice == 0)
            {
                continue;
            }
            else
            {
                for (int i = 0; i < counter; i++)
                {
                    if (tasks[i] == var)
                    {
                        check = i;
                    }
                }
                memory[check] = 0;
                tasks[check] = " ";
                system("pause");
            }
        }
        else if (choice1 == 2)
        {
            cout << "You have Minimized!" << endl
                 << endl;
            system("pause");
        }
        else if (choice1 == 3)
        {
            continue;
        }
        else
        {
            cout << "Invalid Input" << endl;
        }
    }
}
int main()
{
    start();
    bootmenu();
    resources();
    menu();
    return 0;
}
