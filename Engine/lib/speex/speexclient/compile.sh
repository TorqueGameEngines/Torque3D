#!/bin/sh
gcc -Wall -I../include speex_jitter_buffer.c speexclient.c alsa_device.c `pkg-config --cflags speexdsp` -o speexclient -lspeex -lspeexdsp -lasound -lm `pkg-config --libs speexdsp`

