set terminal png
set output 'im_t1.png'
set xlabel "station"
set ylabel "température C°"
set title "t2 température en fonction des stations"
set xtics rotate by 90 right
set yrange [-40:100]
plot "datat1.dat" u 0:3:2:xticlabels(1) with filledcurves fc rgb "#8888FF" title "température maximale", \
"" u 0:4:xticlabels(1) smooth mcspline lc rgb "#0000000" lw 2 title "température moyenne"
