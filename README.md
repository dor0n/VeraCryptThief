VeraCryptThief
==========

VeraCryptThief by itself is a standalone DLL that when injected in the `VeraCrypt.exe` process, will perform API hooking via [Detours](https://github.com/microsoft/Detours), extract the clear-text credentials and save them to a file.

An injector program makes use of [sRDI](https://www.netspi.com/blog/technical/adversary-simulation/srdi-shellcode-reflective-dll-injection/) technique to generate a reflective DLL shellcode and inject it into the target process with the help of [DInvoke](https://thewover.github.io/Dynamic-Invoke/) API.

> **DISCLAIMER.** All information contained in this repository is provided for educational and research purposes only. The author is not responsible for any illegal use of this tool.

## Demo

![demo](https://user-images.githubusercontent.com/23141800/149635968-ab383065-e59d-4082-bea5-429a95f22361.gif)

## Credits

* SEKTOR7 Institute ([@SEKTOR7net](https://twitter.com/sektor7net)) for the RED TEAM Operator: Malware Development Intermediate Course.
* @0x09AL for his [RdpThief](https://github.com/0x09AL/RdpThief).
* @monoxgas for his [sRDI](https://github.com/monoxgas/sRDI).
* @TheWover and @FuzzySecurity for their [DInvoke](https://github.com/TheWover/DInvoke).
