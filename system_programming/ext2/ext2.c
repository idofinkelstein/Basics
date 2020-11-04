
#define EX2_OS_LINUX

#include <stdio.h>
#include <unistd.h>
#include <ext2fs/ext2_fs.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define SECTOR_SIZE 512

int main()
{
	struct ext2_super_block *sb;
	struct ext2_super_block sb2;
	int ram_fd = 0;
	char sb_buff[1024];
	int status = 0;

	ram_fd = open("/dev/ram0", O_RDONLY);
	if (-1 == ram_fd)
	{
	    printf("open: %d\n", ram_fd);
		return 1;
	}

    status = lseek(ram_fd, SECTOR_SIZE, SEEK_SET);
	if (status != SECTOR_SIZE)
	{
		puts("could'nt seek");
		printf("lseek: %d\n", status);
		return 1;
	}
    read(ram_fd, sb_buff, SECTOR_SIZE);

	

	
	return 0;
}
