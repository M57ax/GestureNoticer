# What is GestureNoticer?

GestureNoticer is a small side project I started for fun and to learn more about C++, OpenCV and computer vision :D

The goal is to create a program that can recognize hand gestures through a webcam and display fitting memes for each gesture.

## My personal setup in german below

## GestureNoticer – Setup & Build-Anleitung

Dieses Projekt erkennt Gesten mit OpenCV in C++.  
Hier sind die Schritte, um das Projekt unter Windows zu kompilieren und auszuführen.

---

## Voraussetzungen

- **CMake** (≥ 3.20)
- **Visual Studio 2022** mit C++-Buildtools
- **OpenCV 4.x** (vorzugsweise das Windows-Pack, gebaut mit MSVC)
- **x64 Native Tools Command Prompt for VS 2022**

---

## Einmalige Einrichtung

1. Stelle sicher, dass dein OpenCV-Pfad korrekt ist:
   Darin muss die Datei `OpenCVConfig.cmake` liegen.

2. Wenn du das Projekt neu aufsetzt oder etwas an `CMakeLists.txt` änderst, konfiguriere neu:

cd C:\Users\maxis\Desktop\VSCprojekte\gestureNoticer
rmdir /s /q build 2>nul
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 ^
-DOpenCV_DIR="C:/Users/maxi2/Desktop/VSCprojekte/opencv/build"

## nach Änderungen neu kompilieren

1. Wenn du das Projekt mit Änderungen neu Kompilieren willst dann:
   wechsel mit dem x64 Tool in: C:\Users\maxis\Desktop\VSCprojekte\gestureNoticer
   und dort: 'cmake --build build --config Debug' eingeben

2. dann in /gestureNoticer/build/Debug ".exe" ausführen
   Falls ein Fehler mit den dll files kommt, die 3 .dll files aus dem opencv und dort unter x64 herauskopieren und in den Debug Ordner kopieren

## Momentaner Stand

ich habe die nlohmann Bibliothek eingebunden mit der JSON files geparsed bzw. erstellt werden können
Ich hab das jetzt nur soweit getestet ob es funktioniert, in dem in der CMakeLists ein custom command hinzugefügt wurde, welches ein Meme beim öffnen anzeigt.
Das Funktioniert soweit.
