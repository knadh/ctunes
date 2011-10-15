/* ============================

	cTunes 1.8
	C Programming exercise
	
	Kailash Nadh, http://kailashnadh.name

============================ */

#include "ctunes.h"

// == App version
const float VERSION = 1.8;
const int MAX_CHARS = 15;

const char* file_export = "output/ctunes";	// export file				(extensions are added within functions)
const char* file_metrics = "output/metrics";	// metrics file


void SortSelection(int opt, int *count, int *swaps, int *time);
void SortBubble(int opt, int *count, int *swaps, int *time);

// get a character from the keyboard
int getAchar() {
	int c, first;
	first = c = getchar();
	while (c != '\n' && c != EOF) {
		c = getchar();
	}
	return first;
}

// get a string
// :-s this took me about an hour to write, so long for 'bad functions' like scanf()
void getAstring(char *str, int len) {
	char c, first, x = 1;
	first = c = getchar();

	str[0] = first;
	while (c != '\n' && c != EOF) {
		c = getchar();

		if(x < len) {
			str[x] = c;
			x++;
		}
	}
	str[x-1] = '\0';
}

// print a separator
void PrintLine() {
	printf("\t\t");
	int i;
	for(i=0; i<35; i++) {
		printf("_");
	}
	PrintBr();
}
void PrintBr() {
	printf("\n\n");
}
void PrintMsg(char *str) {
	printf("%s\n", str);
	PrintLine();
}


// Simple hack to clear the screen
void clearScr() {
	// non-os dependent, dirty hack
	int i;
	for(i=0; i<100; i++) {
		printf("\n");
	}
}

// Print fixed with columns
void PrintTabs(int width, int length) {
	int rem = width - length;

	int i;
	for(i=0; i<rem; i++) {
		printf(" ");
	}
}

// Print the formatted column headers
void TunesHeaders() {
	printf("#"); PrintTabs(4, 1);
	printf("Artist"); PrintTabs(18, 6);
	printf("Title"); PrintTabs(19, 5);
	printf("Album"); PrintTabs(19, 5);
	printf("Genre"); PrintTabs(14, 5);
	printf("Year\n");
}

// concatenate the strings to be printed
char* strConcat(char *str) {

	char *newstr;
	newstr = strncat(str, "", 1);		// get a fresh copy of the string
	newstr[MAX_CHARS] = '\0';			// string termination character
	newstr[MAX_CHARS-1] = '.';
	newstr[MAX_CHARS-2] = '.';

	return newstr;
}

// convert a string to lowercase
void strLower(char *str, char *lower) {
	int len = strlen(str)+1;
	int i;

	for(i=0; i<len; i++) {
		lower[i] = tolower(str[i]);
	}
}

// get number of digits in an integer
int numDigits(const int number) {
	int digits = 0;
	int step = 1;
	while (step <= number) {
		digits++;
		step *= 10;
	}
	return digits ? digits : 1;
}

void TunesSort(int opt, int type) {

	int time = 0;

	if(type == 1) {	// selection

		metrics.select_size = dbSize();
		metrics.select_count = 0;
		metrics.select_swaps = 0;
		metrics.select_field = opt;
		metrics.select_time = 0;

		SortSelection(opt, &metrics.select_count, &metrics.select_swaps, &time);

		metrics.select_time = time / CLOCKS_PER_SEC;	// execution time

	} else {

		metrics.bubble_size = dbSize();
		metrics.bubble_count = 0;
		metrics.bubble_swaps = 0;
		metrics.bubble_field = opt;
		metrics.bubble_time = 0;

		SortBubble(opt, &metrics.bubble_count, &metrics.bubble_swaps, &time);

		metrics.bubble_time = time / CLOCKS_PER_SEC;	// execution time
	}
}

// sort the tunes
void SortSelection(int opt, int *count, int *swaps, int *time) {

	clock_t clock_start = clock();

	int i=0, j=0, result=0;
	Tune *tmp = (Tune *) malloc(sizeof(Tune));

	for(i=0; i<dbSize()-1; i++) {
		for(j=i+1; j<dbSize(); j++) {

			switch(opt) {					// bad idea, putting switch inside the loops, but since this is a small app, it won't affect the performance

				case 1:		// artist
					result = strcmp(db_tunes[i]->artist, db_tunes[j]->artist);
				break;

				case 2:		// title
					result = strcmp(db_tunes[i]->title, db_tunes[j]->title);
				break;

				case 3:		// album
					result = strcmp(db_tunes[i]->album, db_tunes[j]->album);
				break;

				case 4:		// genre
					result = strcmp(db_tunes[i]->genre, db_tunes[j]->genre);
				break;

				case 5:		// year
					result = (db_tunes[j]->year < db_tunes[i]->year);
 				break;

			}

			// if the condition is met, do the swap
			if(result > 0) {
				memcpy(tmp, db_tunes[i], sizeof(Tune));
				memcpy(db_tunes[i], db_tunes[j], sizeof(Tune));
				memcpy(db_tunes[j], tmp, sizeof(Tune));

				*swaps = *swaps+1;
			}

			*count = *count+1;
		}
	}

	*time = (double)clock() - clock_start;
	free(tmp);
}




// sort the tunes
void SortBubble(int opt, int *count, int *swaps, int *time) {

	clock_t clock_start = clock();

	int i=0, j=0, result=0;
	bool sorted = false;

	Tune *tmp = (Tune *) malloc(sizeof(Tune));

	clock_start = clock();

	for(i=0; i<dbSize(); i++) {
		for(j=0; j<dbSize()-1; j++) {

			switch(opt) {					// bad idea, putting switch inside the loops, but since this is a small app, it won't affect the performance

				case 1:		// artist
					result = strcmp(db_tunes[j]->artist, db_tunes[i]->artist);
				break;

				case 2:		// title
					result = strcmp(db_tunes[j]->title, db_tunes[i]->title);
				break;

				case 3:		// album
					result = strcmp(db_tunes[j]->album, db_tunes[i]->album);
				break;

				case 4:		// genre
					result = strcmp(db_tunes[j]->genre, db_tunes[i]->genre);
				break;

				case 5:		// year
					result = (db_tunes[j]->year > db_tunes[i]->year);
 				break;

			}

			// if the condition is met, do the swap
			if(result > 0) {
				memcpy(tmp, db_tunes[i], sizeof(Tune));
				memcpy(db_tunes[i], db_tunes[j], sizeof(Tune));
				memcpy(db_tunes[j], tmp, sizeof(Tune));

				*swaps = *swaps+1;
			}

			*count = *count+1;
		}
	}
	*time = (double)clock() - clock_start;
	free(tmp);
}

// =====================================================================

// export data
void exportData(int opt) {

	FILE *fp;
	char outfile[25];
	int i;

	strcpy(outfile, file_export);


	PrintBr(); PrintLine();

	switch(opt) {

		// export as csv
		case 1:
			strcat(outfile, ".csv");

			fp = fopen(outfile, "w");

			fprintf(fp, "#, Artist, Title, Album, Genre, Year\n");
			for(i=0; i < dbSize(); i++) {
				fprintf(fp, "\"%d\", \"%s\", \"%s\", \"%s\", \"%s\", \"%d\"\n", (i+1), db_tunes[i]->artist, db_tunes[i]->title, db_tunes[i]->album, db_tunes[i]->genre, db_tunes[i]->year);
			}
			fclose(fp);

			printf("Exported cTunes records as CSV to : %s\n", outfile);
		break;

		// export as xml
		case 2:
			strcat(outfile, ".xml");

			fp = fopen(outfile, "w");

			fprintf(fp, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<!-- generated by cTunes v%.2f | Developed by Kailash Nadh //-->\n", VERSION);
			fprintf(fp, "<ctunes>\n\t<total>%d</total>\n<version>%.2f</version>\n", dbSize(), VERSION);
			for(i=0; i < dbSize(); i++) {
				fprintf(fp, "\t<tune>\n");
					fprintf(fp, "\t\t<num>%d</num>\n", i+1);
					fprintf(fp, "\t\t<artist>%s</artist>\n", db_tunes[i]->artist);
					fprintf(fp, "\t\t<title>%s</title>\n", db_tunes[i]->title);
					fprintf(fp, "\t\t<album>%s</album>\n", db_tunes[i]->album);
					fprintf(fp, "\t\t<genre>%s</genre>\n", db_tunes[i]->genre);
					fprintf(fp, "\t\t<artist>%d</artist>\n", db_tunes[i]->year);
				fprintf(fp, "\t</tune>\n");
			}
			fprintf(fp, "</ctunes>");
			fclose(fp);

			printf("Exported cTunes records as XML to : %s\n", outfile);
		break;


		// export as html
		case 3:
			strcat(outfile, ".html");

			fp = fopen(outfile, "w");

			fprintf(fp, "<html>\n<head>\n<title>Tunes - cTunes v%.2f | Developed by Kailash Nadh</title>\n</head>\n<body>\n\n", VERSION);
			fprintf(fp, "<h1>cTunes tunes</h1><strong>%d records in total\n\n\n</strong><hr /><table cellpadding=\"2\" cellspacing=\"20\">\n", dbSize());
			fprintf(fp, "\t<tr style=\"font-weight: bold\">\n\t\t<td>#</td>\n\n\t\t<td>Artist</td>\n\t\t<td>Title</td>\n\t\t<td>Album</td>\n\t\t<td>Genre</td>\n\t\t<td>Year</td>\n\t</tr>\n");

			for(i=0; i < dbSize(); i++) {
				fprintf(fp, "\t<tr>\n");
					fprintf(fp, "\t\t<td>%d</td>\n", i+1);
					fprintf(fp, "\t\t<td>%s</td>\n", db_tunes[i]->artist);
					fprintf(fp, "\t\t<td>%s</td>\n", db_tunes[i]->title);
					fprintf(fp, "\t\t<td>%s</td>\n", db_tunes[i]->album);
					fprintf(fp, "\t\t<td>%s</td>\n", db_tunes[i]->genre);
					fprintf(fp, "\t\t<td>%d</td>\n", db_tunes[i]->year);
				fprintf(fp, "\t</tr>\n");
			}
			fprintf(fp, "</table>\n\n</body>\n</html>");
			fclose(fp);

			printf("Exported cTunes records as HTML to : %s\n", outfile);
		break;
	}

}


// export metrics
void exportMetrics(int opt) {

	FILE *fp;
	char outfile[25];

	strcpy(outfile, file_metrics);


	PrintBr(); PrintLine();

	switch(opt) {

		// export as csv
		case 1:
			strcat(outfile, ".csv");

			fp = fopen(outfile, "w");

			fprintf(fp, "Algorithm, Sorted by field, Data size, Iterations, Swaps, Execution time\n");
			fprintf(fp, "\"Selection sort\", \"%d\", \"%s\", \"%d\", \"%d\", \"%.3f\"\n", metrics.select_size, fieldByIndex(metrics.select_field), metrics.select_count, metrics.select_swaps, metrics.select_time);
			fprintf(fp, "\"Bubble sort\", \"%d\", \"%s\", \"%d\", \"%d\", \"%.3f\"\n", metrics.bubble_size, fieldByIndex(metrics.bubble_field), metrics.bubble_count, metrics.bubble_swaps, metrics.bubble_time);
			fclose(fp);

			printf("Exported sort algorithm-metrics as CSV to : %s\n", outfile);
		break;

		// export as xml
		case 2:
			strcat(outfile, ".xml");

			fp = fopen(outfile, "w");

			fprintf(fp, "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<!-- generated by cTunes v%.2f | Developed by Kailash Nadh //-->\n", VERSION);
			fprintf(fp, "<ctunes>");
				fprintf(fp, "\t<metrics>\n");
					fprintf(fp, "\t\t<sort algorithm=\"selection-sort\">\n");
						fprintf(fp, "\t\t\t<field>%s</field>\n", fieldByIndex(metrics.select_field));
						fprintf(fp, "\t\t\t<size>%d</size>\n", metrics.select_size);
						fprintf(fp, "\t\t\t<iterations>%d</iterations>\n", metrics.select_count);
						fprintf(fp, "\t\t\t<swaps>%d</swaps>\n", metrics.select_swaps);
						fprintf(fp, "\t\t\t<execution unit=\"seconds\">%.3f</execution>\n", metrics.select_time);
					fprintf(fp, "\t\t</sort>\n");
					fprintf(fp, "\t\t<sort algorithm=\"bubble-sort\">\n");
						fprintf(fp, "\t\t\t<field>%s</field>\n", fieldByIndex(metrics.bubble_field));
						fprintf(fp, "\t\t\t<size>%d</size>\n", metrics.bubble_size);
						fprintf(fp, "\t\t\t<iterations>%d</iterations>\n", metrics.bubble_count);
						fprintf(fp, "\t\t\t<swaps>%d</swaps>\n", metrics.bubble_swaps);
						fprintf(fp, "\t\t\t<execution unit=\"seconds\">%.3f</execution>\n", metrics.bubble_time);
					fprintf(fp, "\t\t</sort>\n");
				fprintf(fp, "\t</metrics>\n");

			fprintf(fp, "</ctunes>");
			fclose(fp);

			printf("Exported sort algorithm-metrics as XML to : %s\n", outfile);
		break;


		// export as html
		case 3:
			strcat(outfile, ".html");

			fp = fopen(outfile, "w");

			fprintf(fp, "<html>\n<head>\n<title>Tunes - cTunes v%.2f | Developed by Kailash Nadh</title>\n</head>\n<body>\n\n", VERSION);
			fprintf(fp, "<h1>Metrics (sorting)</h1><strong>%d records in total\n\n\n</strong><hr /><table cellpadding=\"2\" cellspacing=\"20\">\n", dbSize());
			fprintf(fp, "\t<tr style=\"font-weight: bold\">\n\t\t<td>Algorithm</td>\n\n\t\t<td>Field</td>\n\t\t<td>Data size</td>\n\t\t<td>Iterations</td>\n\t\t<td>Swaps</td>\n\t\t<td>Execution time</td>\n\t</tr>\n");

				fprintf(fp, "\t<tr>\n");
					fprintf(fp, "\t\t<td>Selection sort</td>\n");
					fprintf(fp, "\t\t<td>%s</td>\n", fieldByIndex(metrics.select_field));
					fprintf(fp, "\t\t<td>%d</td>\n", metrics.select_size);
					fprintf(fp, "\t\t<td>%d</td>\n", metrics.select_count);
					fprintf(fp, "\t\t<td>%d</td>\n", metrics.select_swaps);
					fprintf(fp, "\t\t<td>%.3f seconds</td>\n", metrics.select_time);
				fprintf(fp, "\t</tr>\n");

				fprintf(fp, "\t<tr>\n");
					fprintf(fp, "\t\t<td>Bubble sort</td>\n");
					fprintf(fp, "\t\t<td>%s</td>\n", fieldByIndex(metrics.bubble_field));
					fprintf(fp, "\t\t<td>%d</td>\n", metrics.bubble_size);
					fprintf(fp, "\t\t<td>%d</td>\n", metrics.bubble_count);
					fprintf(fp, "\t\t<td>%d</td>\n", metrics.bubble_swaps);
					fprintf(fp, "\t\t<td>%.3f seconds</td>\n", metrics.bubble_time);
				fprintf(fp, "\t</tr>\n");

			fprintf(fp, "</table>\n\n</body>\n</html>");
			fclose(fp);

			printf("Exported sort algorithm-metrics as HTML to : %s\n", outfile);
		break;
	}
}

// get a field name by its index
char* fieldByIndex(int opt) {

	char *field;

	switch(opt) {
		case 1:		// artist
			field = "Artist";
		break;

		case 2:		// title
			field = "Title";
		break;

		case 3:		// album
			field = "Album";
		break;

		case 4:		// genre
			field = "Genre";
		break;

		case 5:		// year
			field = "Year";
		break;
	}
	return field;
}


