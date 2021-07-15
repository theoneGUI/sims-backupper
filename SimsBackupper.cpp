#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

std::vector < const char* > execute(const char* cte, bool showOutput, bool logging) {
    char command[2048];
    strcpy_s(command, cte);

    FILE* fp;
    int status;
    char path[1024];

    fp = _popen(command, "r");
    if (fp == NULL)
        exit(404);
    std::string spinny[] = { "/", "-", "|", "-", "\\", "-" };
    std::vector < const char* > bundle;
    int now = -1;
    while (fgets(path, 1024, fp) != NULL) {
        now += 1;

        if (showOutput == true) {
            printf("%s", path);
        }
        else {
            if (now == 6) { now = 0; }
            std::cout << "\b\b\b\b\b\b\b\b\b\b" << "Working: " << spinny[now] << std::flush;
        }
        if (logging == true) {
            bundle.push_back(path);
        }
    }

    status = _pclose(fp);
    if (status == -1) {;}
    else {;}
    return bundle;
}

void SDbackup() {
    std::vector < const char* > directory = execute("echo %HOMEPATH%", false, true);
    std::string userDir = directory[0];
    userDir.erase(userDir.length() - 1);
    userDir = userDir.c_str();
    std::string saveData = "robocopy \"C:" + userDir + "\\Documents\\Electronic Arts\\The Sims 4\" C:\\SimsBackup\\SaveData /E";
    const char* saveDataCmd = saveData.c_str();
    execute(saveDataCmd, false, false);
}

void GDrestore() {
    std::string saveData = "robocopy C:\\SimsBackup\\GameData \"C:\\Program Files (x86)\\Origin Games\\The Sims 4\" /E";
    const char* saveDataCmd = saveData.c_str();
    execute("robocopy \"C:\\Program Files (x86)\\Origin Games\\The Sims 4\"", false, false);
    execute(saveDataCmd, false, false);
}

void GDbackup() {
    std::string saveData = "robocopy \"C:\\Program Files (x86)\\Origin Games\\The Sims 4\" C:\\SimsBackup\\GameData /E";
    const char* saveDataCmd = saveData.c_str();
    execute(saveDataCmd, false, false);
}
void SDrestore() {
    std::vector < const char* > directory = execute("echo %HOMEPATH%", false, true);
    std::string userDir = directory[0];
    userDir.erase(userDir.length() - 1);
    userDir = userDir.c_str();
    std::string restoreSave = "robocopy C:\\SimsBackup\\SaveData \"C:" + userDir + "\\Documents\\Electronic Arts\\The Sims 4\" /E";
    //std::string makeDir = "mkdir \"C:" + userDir + "\\Documents\\Electronic Arts\\The Sims 4\"";
    const char* restoreSaveCmd = restoreSave.c_str();
    //const char* makeDirCmd = makeDir.c_str();
    //execute(makeDirCmd, false, false);
    execute(restoreSaveCmd, false, false);
}
int main()
{
    execute("mkdir \"C:\\SimsBackup\\SaveData\"", false, false);
    execute("mkdir \"C:\\SimsBackup\\GameData\"", false, false);
    std::cout << "\n---------The Sims 4 automatic backupper---------\n";
    std::cout << "WARNING: this is ONLY compatible with The Sims 4.\n  1: Back up all save data for the current user (you)\n  2: Restore OLD save data previously backed up\n  3: Back up all GAME DATA (very arduous task, not recommended)\n  4: Restore all OLD GAME DATA (very arduous task, not recommended)\n\n";
    std::cout << "Enter the number that corresponds with the action you wish to execute, then strike the [ENTER] key to begin: ";
    while (true) {
        std::string input;
        std::cin >> input;
        std::cout << std::endl;
        if (input[0] == '1') {
            std::cout << "Beginning Sims save data backup...\n";
            SDbackup();
            std::cout << "\b\b\b\b\b\b\b\b\b\b" << "          \n" << std::flush;
            std::cout << "Save data backup finished.\n\nPress Ctrl-C to quit.";
            std::cin >> input;
            break;
        }
        else if (input[0] == '2') {
            std::cout << "Beginning Sims save data restore...\n";
            SDrestore();
            std::cout << "\b\b\b\b\b\b\b\b\b\b" << "          \n" << std::flush;
            std::cout << "Save data restore finished.\n\nPress Ctrl-C to quit.";
            std::cin >> input;
            break;
        }
        else if (input[0] == '3') {
            std::cout << "Beginning Sims game data backup...\n";
            GDbackup();
            std::cout << "\b\b\b\b\b\b\b\b\b\b" << "          \n" << std::flush;
            std::cout << "Game data backup finished.\n\nPress Ctrl-C to quit.";
            std::cin >> input;
            break;
        }
        else if (input[0] == '4') {
            std::cout << "Beginning Sims game data restore...\n";
            GDrestore();
            std::cout << "\b\b\b\b\b\b\b\b\b\b" << "          \n" << std::flush;
            std::cout << "Game data restore finished.\n\nPress Ctrl-C to quit.";
            std::cin >> input;
            break;
        }
        else {
            std::cout << "Please type '1' or '2' or '3' or '4' to indicate your selection, then strike the [ENTER] key: ";
        }
    }
    
}