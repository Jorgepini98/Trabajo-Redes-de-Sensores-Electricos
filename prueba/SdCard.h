#ifndef SDCARD_H
#define SDCARD_H

#include <FS.h>
#include <SD.h>
#include <SPI.h>

void SdSetup();

void testFileIO(fs::FS &fs, const char * path);

void listDir(fs::FS &fs, const char * dirname, uint8_t levels);

void createDir(fs::FS &fs, const char * path);

void removeDir(fs::FS &fs, const char * path);

void readFile(fs::FS &fs, const char * path);

bool writeFile(fs::FS &fs, const char * path, const char * message);

void appendFile(fs::FS &fs, const char * path, const char * message);

void renameFile(fs::FS &fs, const char * path1, const char * path2);

void deleteFile(fs::FS &fs, const char * path);

#endif
