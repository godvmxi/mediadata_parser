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
			printf("wrong id\n");
			return -1;
	}
	header->layer = (buf[1] & 0x06) >> 1;
	if(header->layer != 0x00){
		printf("XXXX wrong layer->%d\n", header->layer);
		return -1;
	}
	header->protection_absent = buf[1] * 0x1;
	header->profile = (buf[2] >> 6) &0x03 ;
	switch(header->profile){
		case 0:
		case 1:
		case 2:
		case 3:
			break;
		default:
			printf("wrong profile ->%d\n", header->profile);
			return -1;
	}
	header->sf_index = (buf[2]>> 2) &0x0F;
	switch(header->sf_index){
		case  0:
		case  1:
		case  2:
		case  3:
		case  4:
		case  5:
		case  6:
		case  7:
		case  8:
		case  9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			break;
		default:
			printf("wrong sample index ->%d\n", header->sf_index);
			return -1;
	}
	printf("sf index ->%d\n",header->sf_index);
	header->private_bit = (buf[2] >> 1)  &1;
	header->channel_configuration = ((buf[2] & 1 ) << 2) | (buf[3] >> 6);
	switch(header->channel_configuration){
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			break;
		default:
			printf("wroing channel config ->%d\n", header->channel_configuration);
			return -1;
	}
	header->original = (buf[3] >> 5) & 1;
	header->home = (buf[3]>> 4)  & 1;

	//adts_variable header
	header->copyright_identification_bit = (buf[3] >> 3)&1;
	header->copyright_identification_start = (buf[3] >> 2) & 1;
	header->aac_frame_length = ( ((uint16_t)(buf[3] & 0x03)) << 11 ) |
							   ((uint16_t) buf[4]) << 3 |
							   ((uint16_t)  (buf[5] >> 5))
							   ;
	printf("adts size ->%d\n", header->aac_frame_length);
	header->adts_buffer_fullness = 0;
	header->no_raw_data_blocks_in_frame = 0;
	header->crc_check = 0;


	return header->aac_frame_length;
}
int aac_parser_update_adts_header_list(struct aac_parser_t *parser){
	assert(parser != NULL);
	int i = 0;
	uint8_t *header = NULL;
	int adts_index = 0;
	int adts_len  = 0;
	for(i = 0; i < parser->size; i++){
		header = (uint8_t *)(parser->buf+i);
		if(*header  == 0xFF && (*(header+1) & 0xF0) == 0xF0){
#if 1
			printf("header ->%8d -->%3X %3X : ", i, *header,*(header+1));
			int j = 0;
			for(; j < 7; j++){
				printf("%3X", header[j]);
			}
			printf("\n");
#endif
			adts_len = adts_parse_header(header, parser->adts_header_list + adts_index);
			if(adts_len < 0){
				//printf("header ->%d %X %X\n", i, *header,*(header+i));
				continue;
			}
			else{
				parser->adts_offset_list[adts_index++] = i;
				printf("\t!!!find header ->%d\n", i);
				i += adts_len;
				i--;

			}
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
