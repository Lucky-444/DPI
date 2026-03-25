# 🛡️ DPI Packet Capture Project

Deep Packet Inspection (DPI) system built with C++17 to analyze network traffic from PCAP files.

---

## 🚀 Setup & Execution Guide

Follow these steps in order to compile and run the project on Windows using VS Code.

### Step 1: Set Environment Path
Compiler (g++) ko terminal mein enable karne ke liye ye command VS Code terminal (PowerShell) mein chalayein:
```powershell
# $env:Path += ";C:\msys64\ucrt64\bin" 
copy this whole path and pase it in the terminal and run it. This will allow you to use g++ from the terminal.
```
Verify the installation by running:
```powershell
# g++ --version

```

Compile the Project
```powershell
```
<!-- g++ -std=c++17 -o packet_capture src/main.cpp src/capture_engine.cpp -->
```
```

<!-- g++ -std=c++17 -I include src/*.cpp -o capture_service -->

<!-- g++ -std=c++17 -I include src/*.cpp -o capture_service -->
<!-- g++ -std=c++17 -I include src/main.cpp src/capture_engine.cpp src/pcap_reader.cpp src/sender.cpp src/serializer.cpp -o capture_service.exe -->
Run this command in the terminal to compile the project. It will create an executable named `capture_service.exe`.


### Step 3: Compile the Project

```
PowerShell
```
g++ -std=c++17 -I include src/*.cpp -o capture_service.exe
```
Note: -I include flag header files .
```

### Step 4: Run the Executable
```powershell
./capture_service.exe
```


