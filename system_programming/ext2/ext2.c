
#define EX2_OS_LINUX

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ext2fs/ext2_fs.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SECTOR_SIZE 512
#define BLOCK_SIZE 1024

#define BASE_OFFSET 1024  /* location of the super-block in the first group */
#define BLOCK_OFFSET(block) (BASE_OFFSET + (block-1) * (BLOCK_SIZE))

static void read_inode(int fd,
 					   int inode_no,
					   const struct ext2_group_desc *group,
 					   struct ext2_inode *inode);

static void read_dir(int fd, const struct ext2_inode *inode);
static void read_file(int fd, const struct ext2_inode *inode);
void PrintInodeData(struct ext2_inode *inode);



int main()
{
	struct ext2_super_block *sb;
	int ram_fd = 0;
	char sb_buff[1024];
	int status = 0;
	unsigned int group_count;
	unsigned block_size;
	unsigned int descr_list_size;
	struct ext2_group_desc group_des;
	struct ext2_inode root, header;

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

	
	lseek(ram_fd, BASE_OFFSET + block_size, SEEK_SET);
	read(ram_fd, &group_des, sizeof(struct ext2_group_desc));
	printf("bg inode table = %d\n", group_des.bg_inode_table); 

	read_inode(ram_fd, 2, &group_des, &root);
	read_inode(ram_fd, 110, &group_des, &header);

	printf("root.i_size = %d\n",root.i_size);
	printf("root.i_blocks = %d\n", root.i_blocks);

	printf("\nReading root inode\n"
	       "File mode: %hu\n"
	       "Owner UID: %hu\n"
	       "Size     : %u bytes\n"
	       "Blocks   : %u\n"
	       ,
	       root.i_mode,
	       root.i_uid,
	       root.i_size,
	       root.i_blocks);

	PrintInodeData(&root);
	PrintInodeData(&header);

	

	read_dir(ram_fd, &root);
	read_file(ram_fd, &header);
	return 0;
}

static void read_inode(fd, inode_no, group, inode)
     int                           fd;        /* the floppy disk file descriptor */
     int                           inode_no;  /* the inode number to read  */
     const struct ext2_group_desc *group;     /* the block group to which the inode belongs */
     struct ext2_inode            *inode;     /* where to put the inode */
{
	lseek(fd, BLOCK_OFFSET(group->bg_inode_table)
			+ (inode_no-1)*sizeof(struct ext2_inode), SEEK_SET);
	read(fd, inode, sizeof(struct ext2_inode));
}

static void read_dir(int fd, const struct ext2_inode *inode)
{
	void *block;
	int i = 0;

	if (S_ISDIR(inode->i_mode)) 
	{
		struct ext2_dir_entry_2 *entry;
		unsigned int size = 0;

		if ((block = malloc(BLOCK_SIZE)) == NULL) { /* allocate memory for the data block */
			fprintf(stderr, "Memory error\n");
			close(fd);
			exit(1);
		}

		for (i = 0; i < 4; ++i)
		{
			lseek(fd, BLOCK_OFFSET(inode->i_block[i]), SEEK_SET);
			read(fd, block, BLOCK_SIZE);                /* read block from disk*/

			entry = (struct ext2_dir_entry_2 *) block;  /* first entry in the directory */
					/* Notice that the list may be terminated with a NULL
					entry (entry->inode == NULL)*/
			while(entry->inode && (size < inode->i_size) )
			{
				char file_name[EXT2_NAME_LEN+1];
				memcpy(file_name, entry->name, entry->name_len);
				file_name[entry->name_len] = 0;     /* append null character to the file name */
				printf("%10u %s\n", entry->inode, file_name);
				entry = (struct ext2_dir_entry_2 *)((char*) entry + entry->rec_len);
				/*printf("size = %d\n", size);*/
				size += entry->rec_len;
			}
		}
		

		free(block);
	}
}

static void read_file(int fd, const struct ext2_inode *inode)
{
	void *block;
	int i = 0;

	
		if ((block = malloc(BLOCK_SIZE)) == NULL) { /* allocate memory for the data block */
			fprintf(stderr, "Memory error\n");
			close(fd);
			exit(1);
		}

		for (i = 0; i < 13; ++i)
		{
			lseek(fd, BLOCK_OFFSET(inode->i_block[i]), SEEK_SET);
			read(fd, block, BLOCK_SIZE);                /* read block from disk*/
							
			if (i == 12)
			{
				

			}

			printf("%s\n", (char*)block);						
		}
		

		free(block);
	
}

void PrintInodeData(struct ext2_inode *inode)
{
	int i = 0;

	for(i=0; i<EXT2_N_BLOCKS; i++)
		if (i < EXT2_NDIR_BLOCKS)         /* direct blocks */
			printf("Block %2u : %u\n", i, (*inode).i_block[i]);
		else if (i == EXT2_IND_BLOCK)     /* single indirect block */
			printf("Single   : %u\n",(*inode).i_block[i]);
		else if (i == EXT2_DIND_BLOCK)    /* double indirect block */
			printf("Double   : %u\n",(*inode).i_block[i]);
		else if (i == EXT2_TIND_BLOCK)    /* triple indirect block */
			printf("Triple   : %u\n",(*inode).i_block[i]);
}