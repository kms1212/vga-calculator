// original source from https://tomverbeure.github.io/video_timings_calculator
// translated to c

#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdint.h>

int main()
{
    int hpixel, vpixel, margin, interlaced;
    double fps;

    printf("hpixel vpixel fps margin interlaced> ");

    scanf("%u %u %lf %d %d", &hpixel, &vpixel, &fps, &margin, &interlaced);

    double aratio, pxclk, hfreq, hperiod, vfreq, vperiod;
    int htotal, hblank, hfporch, hsync, hbporch;
    int vtotal, vblank, vfporch, vsync, vbporch;
    char *aratio_str = "unknown";

    double clock_step = 0.25;
    double hsync_per = 0.08;
    int min_vporch = 3;
    int min_vbporch = 6;
    int min_vsync_bp = 550;
    double margin_per = 1.8;
    double c_prime = 30;
    double m_prime = 300;
    int cell_gran = 8;

    double vfield_rate = interlaced ? fps * 2 : fps;
    int hpixel_rnd = floor(hpixel / cell_gran) * cell_gran;

    int hmargin = margin ? floor((double)hpixel_rnd * margin_per / 100) / cell_gran : 0;
    int hactive = hpixel_rnd + hmargin * 2;

    if (interlaced) vpixel /= 2;

    int vmargin = margin ? floor((double)vpixel * margin_per / 100) : 0;
    int vactive = vpixel + vmargin * 2;

    aratio = (double)hpixel / (double)vpixel;

    if (fabs(aratio - (4.0 / 3.0)) <= DBL_EPSILON) {
        vsync = 4;
        aratio_str = "4:3";
    } else if (fabs(aratio - (16.0 / 9.0)) <= DBL_EPSILON) {
        vsync = 5;
        aratio_str = "16:9";
    } else if (fabs(aratio - (16.0 / 10.0)) <= DBL_EPSILON) {
        vsync = 6;
        aratio_str = "16:10";
    } else if (fabs(aratio - (5.0 / 4.0)) <= DBL_EPSILON) {
        vsync = 7;
        aratio_str = "5:4";
    } else if (fabs(aratio - (15.0 / 9.0)) <= DBL_EPSILON) {
        vsync = 7;
        aratio_str = "15:9";
    } else {
        vsync = 10;
    }

    hperiod = (1 / vfield_rate) - (double)min_vsync_bp / 1000000.0;
    hperiod /= vactive + min_vporch + (interlaced ? 0.5 : 0);
    hperiod *= 1000000.0;

    int vsync_bp = floor((double)min_vsync_bp / hperiod) + 1;
    if (vsync_bp < (vsync + min_vbporch)) {
        vsync_bp = vsync + min_vbporch;
    }

    vblank = vsync_bp + min_vporch;
    vfporch = min_vporch;
    vbporch = vsync_bp - vsync;

    vtotal = vactive + vsync_bp + (interlaced ? 0.5 : 0) + min_vporch;
    
    double ideal_duty_cycle = c_prime - (m_prime * hperiod / 1000);
    if (ideal_duty_cycle < 20) ideal_duty_cycle = 20;

    hblank = floor(hactive * ideal_duty_cycle / (100 - ideal_duty_cycle) / (2 * cell_gran)) * (2 * cell_gran);
    htotal = hactive + hblank;

    hsync = floor(hsync_per * htotal / cell_gran) * cell_gran;
    hbporch = hblank / 2;
    hfporch = hblank - hsync - hbporch;

    pxclk = clock_step * floor(htotal / hperiod / clock_step);
    hfreq = 1000 * pxclk / htotal;
    double field_rate = 1000 * hfreq / vtotal;
    vfreq = interlaced ? field_rate / 2 : field_rate;
    
    vperiod = 1 / vfreq;

    printf("Aspect Ratio: %s (%lf)\n", aratio_str, aratio);
    printf("Pixel Clock: %lf MHz\n", pxclk * 1000000);
    printf("H Total: %d pixels\n", htotal);
    printf("H Active: %d pixels\n", hactive);
    printf("H Margin: %d pixels\n", hmargin);
    printf("H Blank: %d pixels\n", hblank);
    printf("H Front Porch: %d pixels\n", hfporch);
    printf("H Sync: %d pixels\n", hsync);
    printf("H Back Porch: %d pixels\n", hbporch);
    printf("H Frequency: %lf kHz\n", hfreq);
    printf("H Period: %lf us\n", hperiod);
    printf("V Total: %d lines\n", vtotal);
    printf("V Active: %d lines\n", vactive);
    printf("V Margin: %d lines\n", vmargin);
    printf("V Blank: %d lines\n", vblank);
    printf("V Front Porch: %d lines\n", vfporch);
    printf("V Sync: %d lines\n", vsync);
    printf("V Back Porch: %d lines\n", vbporch);
    printf("V Frequency: %lf Hz\n", vfreq);
    printf("V Period: %lf ms\n\n", vperiod * 1000);

    printf("H Display End: %d\n", hpixel);
    printf("H Blanking Start: %d\n", hpixel + hmargin);
    printf("H Retrace Start: %d\n", hpixel + hmargin + hfporch);
    printf("H Retrace End: %d\n", hpixel + hmargin + hfporch + hsync);
    printf("H Blanking End: %d\n", hpixel + hmargin + hfporch + hsync + hbporch);
    printf("H Total: %d\n", hpixel + hmargin * 2 + hfporch + hsync + hbporch);

    printf("V Display End: %d\n", vpixel);
    printf("V Blanking Start: %d\n", vpixel + vmargin);
    printf("V Retrace Start: %d\n", vpixel + vmargin + vfporch);
    printf("V Retrace End: %d\n", vpixel + vmargin + vfporch + vsync);
    printf("V Blanking End: %d\n", vpixel + vmargin + vfporch + vsync + vbporch);
    printf("V Total: %d\n", vpixel + vmargin * 2 + vfporch + vsync + vbporch);

    return 0;
}
