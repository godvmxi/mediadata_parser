/*
 * Copyright (c) 2013 Stefano Sabatini
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/**
 * @file
 * libavformat/libavcodec demuxing and muxing API example.
 *
 * Remux streams from one container format to another.
 * @example remuxing.c
 */

#include <libavutil/timestamp.h>
#include <libavformat/avformat.h>


int main(int argc, char **argv)
{
    AVFormatContext *ifmt_ctx = NULL;
    AVPacket pkt;
    int index ;
    AVStream *stream = NULL;
    int timescale;
    uint64_t timestamp = 0;
    const char *in_filename;
    int ret, i;
    int index_filter = -1;
    if(argc < 2){
        printf("ussge %s file [index]\n", argv[0]);
    }

    in_filename  = argv[1];
    if(argc == 2){
        printf("display all stream\n");
        index_filter = -1;
    }
    else if(argc == 3){
        index_filter = atoi(argv[2]);
        if(index_filter <0  || index_filter > 4){
            printf("input stream index error\n");
            exit(0);
        }
        printf("set stream filter to ->%d\n", index_filter);
    }

    av_register_all();

    if ((ret = avformat_open_input(&ifmt_ctx, in_filename, 0, 0)) < 0) {
        fprintf(stderr, "Could not open input file '%s'", in_filename);
        goto end;
    }

    if ((ret = avformat_find_stream_info(ifmt_ctx, 0)) < 0) {
        fprintf(stderr, "Failed to retrieve input stream information");
        goto end;
    }

    av_dump_format(ifmt_ctx, 0, in_filename, 0);

    for (i = 0; i < ifmt_ctx->nb_streams; i++) {
        stream = ifmt_ctx->streams[i];
		printf("..............>%d %d\n",stream->index , stream->id);
		continue ;
    }
    int counter = 0;
    while (1) {
		counter++;
        AVStream *stream, *out_stream;

        ret = av_read_frame(ifmt_ctx, &pkt);
        index = pkt.stream_index;
        stream = ifmt_ctx->streams[index];
        timescale = stream->time_base.den / stream->time_base.num;
        timestamp =  pkt.dts * 1000/ timescale;
//        printf("info -> %d %d\n", index, timescale);
//        printf("filter ->%d :cur:%d\n", index_filter, pkt.stream_index);
        if(index_filter == -1){
            printf("frame -->%3d ts:%8lld index:%d size:%7d pts:%8lld pos:%8lld\n",\
                    counter, timestamp, pkt.stream_index, pkt.size ,pkt.pts, pkt.pos);
        }
        else if(index_filter == pkt.stream_index){
            printf("frame -->%3d ts:%8lld index:%d size:%7d pts:%8lld pos:%8lld\n",\
                    counter, timestamp, pkt.stream_index, pkt.size ,pkt.pts, pkt.pos);
        }
        if (ret < 0)
            break;
        av_packet_unref(&pkt);
    }

end:

    avformat_close_input(&ifmt_ctx);


    return 0;
}
