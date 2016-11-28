#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
struct aac_parser_t{
	char *buf;
	int size;
	int adts_number;
	size_t *adts_offset;
};
int aac_parser_parse_adts_header(char *buf){
	assert(buf != NULL);
	return 0;
}
int aac_parser_update_adts_header_list(struct aac_parser_t *parser){
	assert(parser != NULL);
	int i = 0;
	unsigned char *header = NULL;
	int adts_index = 0;
	for(i = 0; i < parser->size; i++){
		header = (unsigned char *)(parser->buf+i);
		//printf("header ->%X %X\n", *header,*(header+i));
		if(*header  == 0xFF && (*(header+1) & 0xF0) == 0xF0){
			parser->adts_offset[adts_index++] = i;
			printf("find header ->%d\n", i);
		}
		//break;
	}
}
struct aac_parser_t *aac_parser_init(char *filename){
	FILE *fd = NULL;
	fd = fopen(filename, "r");
	if(fd == NULL){
		printf("open aac file error\n");
		return NULL;
	}
	fseek(fd, 0, SEEK_END);
	size_t file_size = ftell(fd);
	if(file_size <= 0){
		printf("empty aac file\n");
		return NULL;
	}
	printf("aac file size ->%ld\n", file_size);
	rewind(fd);
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
	int result = fread(parser->buf, 1, file_size, fd);
	if(result != file_size){
		printf("read aac to memory error ->%d:%d\n", file_size, result);
	}
	fclose(fd);
	parser->adts_offset = malloc((file_size / 20) * sizeof(size_t));
	if(parser->adts_offset == NULL){
		printf("malloc adts offset list error\n");
		return NULL;
	}
	aac_parser_update_adts_header_list(parser);
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
