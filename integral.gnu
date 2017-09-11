reset

set terminal postscript enhanced color landscape font 'Times-Roman,14'
set output 'integral.ps'

filename = '/home/denes/Documents/Labor/Hőkamera_zebra/SpectrumAnalysis/bin/integral.dat'

set arrow from 0.75, graph 0 to 0.75, graph 1 lt 2 lc rgb "black" lw 1.5 nohead

set datafile separator ","
set ylabel "relative intensity"
set style fill solid border -1
set style histogram
set style data histograms
set xtics rotate by 45 right
plot filename u 3:xtic(1) lt 1 lc rgb "black" notitle
