# 🛡️ DPI Packet Capture Project

Deep Packet Inspection (DPI) system built with C++17 to analyze network traffic from PCAP files.

---

## 🚀 Setup & Execution Guide

Follow these steps in order to compile and run the project on Windows using VS Code.

### Step 1: Set Environment Path
Compiler (g++) ko terminal mein enable karne ke liye ye command VS Code terminal (PowerShell) mein chalayein:
```powershell
# $env:Path += ";C:\msys64\ucrt64\bin" 
````


### If you Still get an error, try this command:
```powershell
g++ -std=c++17 -I include src/main.cpp src/capture_engine.cpp src/pcap_reader.cpp src/packet_parser.cpp -o capture_service.exe -lws2_32
```


### Step 4: Run the Executable
```powershell
./capture_service.exe
```


