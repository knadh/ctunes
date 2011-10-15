/* ============================

	cTunes 1.8
	C Programming exercise
	
	Kailash Nadh, http://kailashnadh.name

============================ */

#ifndef CTUNES_H
#define CTUNES_H

	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <time.h>

	// ==============
	#define TRUE  1	#define YES 1
	#define FALSE 0	#define NO  0

	typedef enum {false, true} bool;


	extern const float VERSION;

	// == The tune' data structure (it is not a good idea to put the defintion in the header file, but sometimes it kills complexity)
	typedef struct ctune {
		char title[50];
		char artist[50];
		char album[50];
		char genre[30];
		int year;
	} Tune;

	// == holds metrics
	struct {
		// bubble sort
		int bubble_size;
		int bubble_count;
		int bubble_swaps;
		int bubble_field;
		float bubble_time;

		// selection sort
		int select_size;
		int select_count;
		int select_swaps;
		int select_field;
		float select_time;
	} metrics;



	// =============== lib.c

	int getAchar();
	void getAstring(char *str, int len);
	void PrintLine();
	void PrintBr();
	void PrintMsg(char *str);
	void PrintTabs(int width, int length);
	void clearScr();
	void TunesHeaders();
	char* strConcat(char *str);
	void strLower(char *str, char *lower);
	int numDigits(const int number);
	void exportData(int opt);
	void TunesSort(int opt, int type);
	void exportMetrics(int opt);
	char* fieldByIndex(int opt);

	// =============== db.c
	extern Tune **db_tunes;
	extern int db_size;

	void dbOpen();
	void dbDelete();
	void dbAdd(Tune *newtune);
	void dbSave();
	void dbClose();
	const char* dbFile();
	int dbSize();
	float dbDataSize();

#endif

