#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "aac_parser.h"
#include <unistd.h>
#include <stdint.h>
typedef struct
{
    uint16_t syncword;
    uint8_t id;
    uint8_t layer;
    uint8_t protection_absent;
    uint8_t profile;
    uint8_t sf_index;
    uint8_t private_bit;
    uint8_t channel_configuration;
    uint8_t original;
    uint8_t home;
    uint8_t emphasis;
    uint8_t copyright_identification_bit;
    uint8_t copyright_identification_start;
    uint16_t aac_frame_length;
    uint16_t adts_buffer_fullness;
    uint8_t no_raw_data_blocks_in_frame;
    uint16_t crc_check;

    /* control param */
    uint8_t old_format;
} adts_header;
struct aac_parser_t{
	char *buf;
	uint32_t size;
	uint32_t adts_number;
	uint32_t *adts_offset_list;
	adts_header *adts_header_list;
};
int aac_parser_adts_fixed_header(char *buf, adts_header *header){

	return 0;
}
int aac_parser_adts_variable_header(char *buf, adts_header *header){

	return 0;
}
int aac_parser_adts_error_check(char *buf, adts_header *header){

	return 0;
}
int aac_parser_parse_adts_header(char *buf, adts_header *header){
	assert(buf != NULL);
	header->id = buf[1] & 0x0F;
	switch(header->id){
		case 0:
			break;
		case 1:
			break;
		default:
			return -1;
	}

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
			parser->adts_offset_list[adts_index++] = i;
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
	parser->adts_offset_list = malloc((file_size / 20) * sizeof(size_t));
	if(parser->adts_offset_list == NULL){
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
