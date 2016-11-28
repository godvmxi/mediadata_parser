#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct aac_parser_t{
	char *buf;
	int size;
	int adts_number;
	size_t *adts_offset;
};

struct aac_parser_t *aac_parser_init(char *filename){
	FILE *fd = NULL;
	fd = fopen(filename, "r");
	if(fd == NULL){
		printf("open aac file error\n");
		return NULL;
	}
	size_t file_size = ftell(fd);
	if(file_size <= 0){
		printf("empty aac file\n");
		return NULL;
	}
	struct aac_parser_t *parser = malloc(sizeof(struct aac_parser_t));
	if(parser == NULL){
		printf("malloc aac_parser_t mem error");
		return NULL;
	}
	memset(parser, 0, sizeof(struct aac_parser_t));
	parser->size = file_size;
	parser->buf =  malloc(file_size+4);
	if(parser->buf == NULL){
		printf("malloc aac buffer error\n");
		free(parser);
		return NULL;
	}
	int result = fread(parser->buf, file_size, 1, fd);
	if(result != file_size){
		printf("read aac to memory error\n");
	}
	fclose(fd);
	return parser;
}
void aac_parser_deinit(struct aac_parser_t *parser){

	return ;
}

int main(int argc, char* argv[]){
	struct aac_parser_t *parser =  aac_parser_init(argv[1]);
	if(parser == NULL){
		printf("aac_parser init error\n");
		return -1;
	}
	return 0;
}
