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
	long size;
	uint32_t adts_number;
	long *adts_offset_list;
	adts_header *adts_header_list;
};
int aac_parser_adts_fixed_header(uint8_t *buf, adts_header *header){

	return 0;
}
int aac_parser_adts_variable_header(uint8_t *buf, adts_header *header){

	return 0;
}
int aac_parser_adts_error_check(uint8_t *buf, adts_header *header){

	return 0;
}
int adts_parse_header(uint8_t *buf, adts_header *header){
	assert(buf != NULL);
	header->id = (buf[1] & 0x08) >> 3;
	switch(header->id){
		case 0:
			break;
		case 1:
			break;
		default:
			return -1;
	}
	header->layer = (buf[1] & 0x06) >> 1;
	if(header->layer != 0x00){
		return -1;
	}
	header->protection_absent = buf[1] * 0x1;
	header->profile = (buf[2] & 0xC0) >> 2;
	switch(header->profile){
		case 0:
		case 1:
		case 2:
		case 3:
			break;
		default:
			return -1;
	}


	return 0;
}
int aac_parser_update_adts_header_list(struct aac_parser_t *parser){
	assert(parser != NULL);
	int i = 0;
	uint8_t *header = NULL;
	int adts_index = 0;
	for(i = 0; i < parser->size; i++){
		header = (uint8_t *)(parser->buf+i);
		if(*header  == 0xFF && (*(header+1) & 0xF0) == 0xF0){
			printf("header ->%d -->%X %X\n", i, *header,*(header+1));
			if(adts_parse_header(header, parser->adts_header_list + adts_index) < 0){
				//printf("header ->%d %X %X\n", i, *header,*(header+i));
				continue;
			}
			parser->adts_offset_list[adts_index++] = i;
			printf("find header ->%d\n", i);
		}
		//break;
		if(i > 2500){
			break;
		}
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
	long file_size = ftell(fd);
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
	long result = fread(parser->buf, 1, file_size, fd);
	if(result != file_size){
		printf("read aac to memory error ->%ld:%ld\n", file_size, result);
	}
	fclose(fd);
	int adts_number = file_size / 20;
	parser->adts_offset_list = malloc(adts_number * sizeof(long));
	if(parser->adts_offset_list == NULL){
		printf("malloc adts offset list error\n");
		return NULL;
	}
	memset(parser->adts_offset_list, 0, adts_number * sizeof(long));
	parser->adts_header_list =  malloc(adts_number *sizeof(adts_header));
	if(parser->adts_header_list == NULL){
		printf("malloc adts_header_list error\n");
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
