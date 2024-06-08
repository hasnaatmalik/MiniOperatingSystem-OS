#include <iostream>
#include <fstream>
#include <string>
#include <pthread.h>
#include <SFML/Audio.hpp>

using namespace std;
void* createFile(void*);
void* displayFileContent(void*);
void* editFile(void*);
void* playBackgroundSong(void*);

int main() {
    string filename;
    int choice;
    cout << "\e[1;35m\n";
    sf::Music music;
    if (!music.openFromFile("background.wav")) {
        cout << "Error: Failed to load background song." << endl;
        return 1;
    }

    music.setLoop(true); 
    music.setVolume(100.f);

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Create file\n";
        cout << "2. Display file content\n";
        cout << "3. Edit file\n";
        cout << "4. Play background song\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        pthread_t tid;

        switch (choice) {
            case 1:
                cout << "Enter the filename: ";
                getline(cin, filename);
                pthread_create(&tid, nullptr, createFile, (void*)&filename);
                pthread_join(tid, nullptr);
                break;
            case 2:
                cout << "Enter the filename: ";
                getline(cin, filename);
                pthread_create(&tid, nullptr, displayFileContent, (void*)&filename);
                pthread_join(tid, nullptr);
                break;
            case 3:
                cout << "Enter the filename: ";
                getline(cin, filename);
                pthread_create(&tid, nullptr, editFile, (void*)&filename);
                pthread_join(tid, nullptr);
                break;
            case 4:
                cout << "Playing background song..." << endl;
                pthread_create(&tid, nullptr, playBackgroundSong, (void*)&music);
                pthread_join(tid, nullptr);
                break;
            case 5:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5.\n";
        }
    }

    return 0;
}

void* createFile(void* arg) {
    string filename = *((string*)arg);
    ofstream file(filename);
    if (file.is_open()) {
        cout << "File '" << filename << "' created successfully." << endl;
        file.close();
    } else {
        cout << "Error: Unable to create file '" << filename << "'." << endl;
    }
    return nullptr;
}

void* displayFileContent(void* arg) {
    string filename = *((string*)arg);
    ifstream file(filename);
    if (file.is_open()) {
        cout << "Content of file '" << filename << "':" << endl;
        cout << "-----------------------------------" << endl;
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Error: Unable to open file '" << filename << "' for reading." << endl;
    }
    return nullptr;
}

void* editFile(void* arg) {
    string filename = *((string*)arg);
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        cout << "Enter the content to append to '" << filename << "' (Enter '.' on a new line to stop):" << endl;
        string line;
        while (true) {
            getline(cin, line);
            if (line == ".") {
                break;
            }
            file << line << endl;
        }
        file.close();
        cout << "File '" << filename << "' edited successfully." << endl;
    } else {
        cout << "Error: Unable to open file '" << filename << "' for editing." << endl;
    }
    return nullptr;
}

void* playBackgroundSong(void* arg) {
    sf::Music* music = (sf::Music*)arg;
    music->play();
    return nullptr;
}
