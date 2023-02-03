set terminal png
set output 'im_p1.png'
set xlabel "station"
set ylabel "pression"
set title "p1 pression en fonction des stations"
set xtics rotate by 90 right
set yrange [10000:120000]
plot "datap1.dat" u 0:3:2:xticlabels(1) with filledcurves fc rgb "#8888FF" title "pression maximale/minimale", \
"" u 0:4:xticlabels(1) smooth mcspline lc rgb "#0000000" lw 2 title "pression moyenne"
