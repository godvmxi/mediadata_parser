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

static void log_packet(const AVFormatContext *fmt_ctx, const AVPacket *pkt, const char *tag)
{
    AVRational *time_base = &fmt_ctx->streams[pkt->stream_index]->time_base;

    printf("%s: pts:%s pts_time:%s dts:%s dts_time:%s duration:%s duration_time:%s stream_index:%d\n",
           tag,
           av_ts2str(pkt->pts), av_ts2timestr(pkt->pts, time_base),
           av_ts2str(pkt->dts), av_ts2timestr(pkt->dts, time_base),
           av_ts2str(pkt->duration), av_ts2timestr(pkt->duration, time_base),
           pkt->stream_index);
}

int main(int argc, char **argv)
{
    AVFormatContext *ifmt_ctx = NULL, *ofmt_ctx = NULL;
    AVPacket pkt;
    const char *in_filename;
    int stream_index = 0;
    int ret, i;
    if(argc < 3){
        printf("usage: %s stream_index  file\n", argv[0]);
        exit(1);
    }
    stream_index = atoi(argv[1]);
    in_filename  = argv[2];

    av_register_all();

    if ((ret = avformat_open_input(&ifmt_ctx, in_filename, 0, 0)) < 0) {
        fprintf(stderr, "Could not open input file '%s'", in_filename);
        goto end;
    }

    if ((ret = avformat_find_stream_info(ifmt_ctx, 0)) < 0) {
        fprintf(stderr, "Failed to retrieve input stream information");
        goto end;
    }
    int time_scale = 0;
    AVStream *stream;
    av_dump_format(ifmt_ctx, 0, in_filename, 0);
    for (i = 0; i < ifmt_ctx->nb_streams; i++) {
        stream = ifmt_ctx->streams[i];
		printf("..............>%d %d\n",stream->index , stream->id);
    }

    stream = ifmt_ctx->streams[stream_index];
    time_scale  = stream->time_base.den / stream->time_base.num;
    printf("timescale ->%d\n", time_scale);
	int counter = 0;
    uint64_t last_ts = 0;
    while (1) {
		counter++;

        ret = av_read_frame(ifmt_ctx, &pkt);
        if (pkt.stream_index == stream_index ) {
            printf("frame -->%8d : size:%8d ts:%8d pts: %8lld dur:%6lld",\
                    counter,pkt.size, pkt.pts*1000/time_scale, pkt.dts, pkt.pts - last_ts);
            if(pkt.pts - last_ts > 100){
                printf(" XXXX \n");
            }
            else{
                printf("\n");
            }
            last_ts = pkt.pts;
        }
        if (ret < 0)
            break;
        av_packet_unref(&pkt);
    }

end:

    avformat_close_input(&ifmt_ctx);


    return 0;
}
