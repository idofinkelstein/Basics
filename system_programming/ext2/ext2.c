
#define EX2_OS_LINUX

#include <stdio.h>
#include <unistd.h>
#include <ext2fs/ext2_fs.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BASE_OFFSET 1024  /* location of the super-block in the first group */


#define SECTOR_SIZE 512
#define BLOCK_OFFSET(block) (BASE_OFFSET + (block-1) * (1024))

static void read_inode(int fd,
 					   int inode_no,
					   const struct ext2_group_desc *group,
 					   struct ext2_inode *inode);

int main()
{
	struct ext2_super_block *sb;
	struct ext2_super_block sb2;
	int ram_fd = 0;
	char sb_buff[1024];
	int status = 0;
	unsigned int group_count;
	unsigned block_size;
	unsigned int descr_list_size;
	struct ext2_group_desc group_des;
	struct ext2_inode root;

	ram_fd = open("/dev/ram0", O_RDONLY);
	if (-1 == ram_fd)
	{
	    printf("open: %d\n", ram_fd);
		return 1;
	}

    status = lseek(ram_fd, SECTOR_SIZE * 2, SEEK_SET);
	if (status != SECTOR_SIZE * 2)
	{
		puts("could'nt seek");
		printf("lseek: %d\n", status);
		return 1;
	}
    read(ram_fd, sb_buff, SECTOR_SIZE * 2);

	sb = (struct ext2_super_block *)sb_buff;
	printf("%d\n", sb->s_inodes_count); 

	group_count = 1 + (sb->s_blocks_count-1) / sb->s_blocks_per_group;
	printf("%d\n", group_count); 

	block_size = 1024 << sb->s_log_block_size;
	printf("%d\n", block_size); 


	descr_list_size = group_count * sizeof(struct ext2_group_desc);
	printf("%d\n", descr_list_size); 

	status = lseek(ram_fd, block_size, SEEK_CUR);
	read(ram_fd, &group_des, sizeof(struct ext2_group_desc));
	printf("%d\n", group_des.bg_inode_table); 

	read_inode(ram_fd, 2, &group_des, &root);

	printf("%d\n",root.i_size);

	return 0;
}

static void read_inode(fd, inode_no, group, inode)
     int                           fd;        /* the floppy disk file descriptor */
     int                           inode_no;  /* the inode number to read  */
     const struct ext2_group_desc *group;     /* the block group to which the inode belongs */
     struct ext2_inode            *inode;     /* where to put the inode */
{
	lseek(fd, BLOCK_OFFSET(group->bg_inode_table)+(inode_no-1)*sizeof(struct ext2_inode), SEEK_SET);
	read(fd, inode, sizeof(struct ext2_inode));
}