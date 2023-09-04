#include "main.h"
#include <elf.h>
#include <stdio.h>

#if defined(__LP64__)
	#define ElfW(type) Elf64_ ## type
#else
	#define ElfW(type) Elf32_ ## type
#endif

/**
 * close_fd - closes file descriptor
 *
 * @fd: The file descriptor of the ELF file
 */
void close_fd(int fd)
{
	if (close(fd) == -1)
	{

		dprintf(STDERR_FILENO, "ERROR: Couldn't close file\n");
		exit(98);
	}
}

/**
 * check - checks for errors
 *
 * @value: flag
 * @filename: string - name of file
 * @fd: file descriptor
 * @error_code: code of error
 */
void check(int value, char *filename, int fd, int error_code)
{
	if (value != -1)
		return;

	if (fd != -1)
		close_fd(fd);

	if (error_code == 1)
		dprintf(STDERR_FILENO, "ERROR: couldn't open %s\n", filename);
	else if (error_code == 2)
		dprintf(STDERR_FILENO, "ERROR: couldn't read %s\n", filename);
	else if (error_code == 3)
		dprintf(STDERR_FILENO, "ERROR: %s is not an ELF File\n", filename);

	exit(98);
}

/**
 * isElf - checks whether a file is ELF or not
 *
 * @e_ident: the e_idnet of the file
 *
 * Return: bool - true if file is ELf, flase otherwise
 */
int isElf(unsigned char *e_ident)
{
	if (e_ident[0] != 127 ||
		e_ident[1] != 'E' ||
		e_ident[2] != 'L' ||
		e_ident[3] != 'F'
	)
		return (0);

	return (1);
}

/**
 * print_magic - prints the magic numbers of ELF file
 *
 * @e_ident: the e_idnet of the file
 */
void print_magic(unsigned char *e_ident)
{
	int i;

	printf("  Magic:  ");
	for (i = 0; i < EI_NIDENT; i++)
		printf(" %02x", e_ident[i]);
	printf("\n");
}

/**
 * print_class - prints the class of ELF File
 *
 * @e_ident: the e_ident of the file
 */
void print_class(unsigned char *e_ident)
{
	printf("  Class:                             ");
	if (e_ident[EI_CLASS] == ELFCLASSNONE)
		printf("none\n");
	else if (e_ident[EI_CLASS] == ELFCLASS32)
		printf("ELF32");
	else if (e_ident[EI_CLASS] == ELFCLASS64)
		printf("ELF64");
	else
		printf("<unknown: %x>", e_ident[EI_CLASS]);
	printf("\n");
}

/**
 * print_data - prints the data format of elf header
 *
 * @e_ident: the ident of the file
 */
void print_data(unsigned char *e_ident)
{
	printf("  Data:                              ");
	if (e_ident[EI_DATA] == ELFDATANONE)
		printf("none");
	else if (e_ident[EI_DATA] == ELFDATA2LSB)
		printf("2's complement, little endian");
	else if (e_ident[EI_DATA] == ELFDATA2MSB)
		printf("2's complement, big endian");
	else
		printf("<unknown: %x>", e_ident[EI_DATA]);
	printf("\n");
}

/**
 * print_version - version number of the ELF  specification
 *
 * @e_ident: the ident of the file
 */
void print_version(unsigned char *e_ident)
{
	printf("  Version:                           %d",
		e_ident[EI_VERSION]);
	if (e_ident[EI_VERSION] == EV_CURRENT)
		printf(" (current)");
	printf("\n");
}

/**
 * print_osapi - operating system and ABI to which the object is targeted.
 *
 * @e_ident: e_ident of file
 */
void print_osapi(unsigned char *e_ident)
{
	printf("  OS/ABI:                            ");
	switch (e_ident[EI_OSABI])
	{
		case ELFOSABI_NONE:
			printf("UNIX - System V\n");
			break;
		case ELFOSABI_HPUX:
			printf("UNIX - HP-UX\n");
			break;
		case ELFOSABI_NETBSD:
			printf("UNIX - NetBSD\n");
			break;
		case ELFOSABI_LINUX:
			printf("UNIX - Linux\n");
			break;
		case ELFOSABI_SOLARIS:
			printf("UNIX - Solaris\n");
			break;
		case ELFOSABI_IRIX:
			printf("UNIX - IRIX\n");
			break;
		case ELFOSABI_FREEBSD:
			printf("UNIX - FreeBSD\n");
			break;
		case ELFOSABI_TRU64:
			printf("UNIX - TRU64\n");
			break;
		case ELFOSABI_ARM:
			printf("ARM\n");
			break;
		case ELFOSABI_STANDALONE:
			printf("Standalone App\n");
			break;
		default:
			printf("<unknown: %x>\n", e_ident[EI_OSABI]);
	}
}

/**
 * print_apiv - the version of the ABI to which the object is targeted.
 *
 * @e_ident: the ident of the file
 */
void print_apiv(unsigned char *e_ident)
{
	printf("  ABI Version:                       %d\n",
			e_ident[EI_ABIVERSION]);
}

/**
 * print_type - the object file type
 *
 * @e_type: the type of the file
 * @e_ident: the ident of the file
 */
void print_type(uint16_t e_type, unsigned char *e_ident)
{
	if (e_ident[EI_DATA] == ELFDATA2MSB)
		e_type >>= 8;

	printf("  Type:                              ");
	if (e_type == ET_NONE)
		printf("NONE (None)\n");
	else if (e_type == ET_REL)
		printf("REL (Relocatable file)\n");
	else if (e_type == ET_EXEC)
		printf("EXEC (Executable file)\n");
	else if (e_type == ET_DYN)
		printf("DYN (Shared object file)\n");
	else if (e_type == ET_CORE)
		printf("CORE (Core file)\n");
	else
		printf("<unknown: %x>\n", e_type);
}

/**
 * print_entry - prints the virtual address to which the system  first
 * transfers  control,  thus starting the process.
 *
 * @e_entry: entry point address
 * @e_ident: the ident of file
 */
void print_entry(unsigned long int e_entry, unsigned char *e_ident)
{
	printf("  Entry point address:               ");

	if (e_ident[EI_DATA] == ELFDATA2MSB)
	{
		e_entry = ((e_entry << 8) & 0xFF00FF00) |
			  ((e_entry >> 8) & 0xFF00FF);
		e_entry = (e_entry << 16) | (e_entry >> 16);
	}

	if (e_ident[EI_CLASS] == ELFCLASS32)
		printf("%#x\n", (unsigned int)e_entry);

	else
		printf("%#lx\n", e_entry);
}

/**
 * print_elf_header - extracts elf header from elf files
 *
 * @filename: string - name of the file
 */
void print_elf_header(char *filename)
{
	ElfW(Ehdr) header;
	int fd = open(filename, O_RDONLY), r;

	check(fd, filename, fd, 1);

	r = read(fd, &header, sizeof(header));
	check(r, filename, fd, 2);

	if (!isElf(header.e_ident))
		check(-1, filename, fd, 3);

	printf("ELF Header:\n");
	print_magic(header.e_ident);
	print_class(header.e_ident);
	print_data(header.e_ident);
	print_version(header.e_ident);
	print_osapi(header.e_ident);
	print_apiv(header.e_ident);
	print_type(header.e_type, header.e_ident);
	print_entry(header.e_entry, header.e_ident);

	close_fd(fd);
}

/**
 * main - entry point
 *
 * @argc: argument count
 * @argv: argument list
 *
 * Return: 0 on success, Error_code on failure
 */
int main(int argc, char **argv)
{
	(void)argc;
	print_elf_header(argv[1]);
	return (0);
}
