reset
set terminal postscript enhanced landscape font 'Times-Roman,12'
set output 'z_mu_ave.ps'

filename = "/home/denes/Documents/Labor/SpectrumAnalysis/spektrum_hordó/z_mu_ave.csv"
set style line 1 lc rgb 'black' pt 7 ps 1.0 lt 1 lw 0.6

set xlabel 'wavelength (nm)'
set ylabel 'count'

plot filename u 1:2 w l ls 1

