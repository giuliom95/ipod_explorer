// gcc -I/usr/include/gpod-1.0/gpod -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -lgpod -lglib-2.0 -Wall src/main.c -o bin/ipod

#include <stdio.h>

#include <itdb.h>

int main() {
	printf("Hello iPod!\n");
	GError *error;

	printf("Fetching data..."); fflush(stdout);
	Itdb_iTunesDB* db = itdb_parse("/run/media/giulio/IOLD", &error);	
	printf("DONE");

	int track_number = g_list_length(db->tracks);

	printf("Number of tracks: %d\n", track_number);

	for(GList* l = db->tracks; l != NULL; l = l->next) {
		Itdb_Track* track = (Itdb_Track*)(l->data);
		printf("%s %s\n", track->title, track->ipod_path);
	}

	return 0;
}