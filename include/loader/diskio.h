#ifndef __DISKIO_H__
#define __DISKIO_H__

#define MAX_DISKS 8
#define SECTOR_SIZE 512

struct CACHE_ENTRY {
	int      device;
	uint32_t lba;
	uint8_t  data[SECTOR_SIZE];
	struct CACHE_ENTRY* prev;
	struct CACHE_ENTRY* next;
};

unsigned int diskio_init();
struct CACHE_ENTRY* diskio_read(int disknum, uint32_t lba);
int diskio_read_bulk(int disknum, uint32_t lba, void* buffer);
int diskio_flush_bulk();
void diskio_discard_bulk();
const char* diskio_get_name(int device);
int diskio_find_disk(const char* name);
void diskio_stats();
void diskio_lsdev();

#endif /* __DISKIO_H__ */
