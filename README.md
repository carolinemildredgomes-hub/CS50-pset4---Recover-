# 🔍 CS50 Recover

## 📘 Overview
**Recover** is a CS50 Problem Set 4 assignment.  
The task is to implement a program in C that **recovers JPEG images from a forensic image (raw memory card dump)**.  

This project introduces file I/O in C, working with raw binary data, and recognizing file signatures.  

---

## 📂 Project Structure
- `recover.c` → **your code goes here** (read raw file and recover JPEGs).  
- `card.raw` → sample forensic image (provided by CS50).  
- `Makefile` → build configuration.  

---

## 📝 How It Works
1. The program reads the raw memory card file in blocks of **512 bytes**.  
2. It looks for the **JPEG signature**:  
3. Each time a new JPEG header is found:
- Close the previous file (if any).  
- Create a new file (`000.jpg`, `001.jpg`, `002.jpg`, …).  
- Write blocks until the next JPEG header appears.  
4. Continue until the end of the memory card.  

---

## 🛠️ Steps to Solve
1. Open `recover.c`.  
2. Use `fread` to read 512-byte blocks.  
3. Check first 4 bytes for the JPEG signature.  
4. Use `fopen`, `fwrite`, and `fclose` to manage JPEG files.  
5. Keep track of filenames with a counter (e.g., `sprintf(filename, "%03i.jpg", count)`).  
6. Stop when all blocks are processed.  

---

## 🖥️ Compile & Run
```bash
make recover
./recover card.raw

The program will generate recovered JPEG files in the current directory.

Example output:
000.jpg
001.jpg
002.jpg
...
Skills Practiced

C file I/O (fopen, fread, fwrite, fclose).

Working with raw binary data.

Understanding file signatures.

Memory card forensics basics.

🎯 Goal

By the end of this project, you’ll be able to recover images from a corrupted memory card, just like digital forensics investigators do.
