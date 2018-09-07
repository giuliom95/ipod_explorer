// gcc -I/usr/include/gpod-1.0/gpod -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -lgpod -lglib-2.0 -Wall src/main.c -o bin/ipod

#include <stdio.h>
#include <string.h>
#include <itdb.h>
#include <time.h>
#include <stdlib.h>

int shuffle_cmpfn(const void* a, const void* b) {
	const Itdb_Track* track_a = (Itdb_Track*)a;
	const Itdb_Track* track_b = (Itdb_Track*)b;

	return track_a->unk132 - track_b->unk132;
}

GList* shuffle(GList* tracks) {
	for(GList* l = tracks; l != NULL; l = l->next) {
		Itdb_Track* track = (Itdb_Track*)(l->data);
		track->unk132 = (guint32)rand();
	}
	return g_list_sort(tracks, &shuffle_cmpfn);
}

int main(int argc, char** argv) {
	srand(time(NULL));
	printf("Hello iPod!\n");
	if(argc == 1) {
		fprintf(stderr, "ERROR: Please specify iPod mounting path.\n");
		return -1;
	}

	char* ipod_path = argv[1];
	GError *error = NULL;

	printf("Fetching data..."); fflush(stdout);
	Itdb_iTunesDB* db = itdb_parse(ipod_path, &error);	
	printf("DONE\n");

	{
		char* last = strrchr(ipod_path, '/');
		if(*(last + sizeof(char)) == '\0')
			*last = '\0';
	}

	GList* l = shuffle(db->tracks);
	for(; l != NULL; l = l->next) {
		Itdb_Track* track = (Itdb_Track*)(l->data);
		char* track_path = track->ipod_path;

		fprintf(stdout, "%s", ipod_path);
		for(char* c = track_path; *c != '\0'; ++c) {
			if(*c == ':') 
				fputc('/', stdout);
			else {
				if(*c == ' ' || *c == '(' || *c == ')') 
					fputc('\\', stdout);

				fputc(*c, stdout);
			}
		}
		fputc('\n', stdout);
	}

	return 0;
}