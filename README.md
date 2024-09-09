# vga-calculator

[Original Soruce](https://tomverbeure.github.io/video_timings_calculator)

## Build

```sh
$ cc -o timing_calc timing_calc.c
```

## Run
```sh
$ ./timing_calc
hpixel vpixel fps margin interlaced> 640 480 60 0 0
Aspect Ratio: 4:3 (1.333333)
Pixel Clock: 23750000.000000 MHz
H Total: 800 pixels
H Active: 640 pixels
H Margin: 0 pixels
H Blank: 160 pixels
H Front Porch: 16 pixels
H Sync: 64 pixels
H Back Porch: 80 pixels
H Frequency: 29.687500 kHz
H Period: 33.367840 us
V Total: 500 lines
V Active: 480 lines
V Margin: 0 lines
V Blank: 20 lines
V Front Porch: 3 lines
V Sync: 4 lines
V Back Porch: 13 lines
V Frequency: 59.375000 Hz
V Period: 16.842105 ms

H Display End: 640
H Blanking Start: 640
H Retrace Start: 656
H Retrace End: 720
H Blanking End: 800
H Total: 800
V Display End: 480
V Blanking Start: 480
V Retrace Start: 483
V Retrace End: 487
V Blanking End: 500
V Total: 500
```
