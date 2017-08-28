reset

set terminal postscript enhanced color landscape font 'Times-Roman,12'
set output 'spectrum_ave.ps'

filename1 = "/home/denes/Documents/Labor/SpectrumAnalysis/spektrum_hordó/fekete_ave.csv"
filename2 = "/home/denes/Documents/Labor/SpectrumAnalysis/spektrum_hordó/feher_ave.csv"
filename3 = "/home/denes/Documents/Labor/SpectrumAnalysis/spektrum_hordó/lo_ave.csv"
filename4 = "/home/denes/Documents/Labor/SpectrumAnalysis/spektrum_hordó/szurkemarha_ave.csv"
filename5 = "/home/denes/Documents/Labor/SpectrumAnalysis/spektrum_hordó/z_mu_ave.csv"
filename6 = "/home/denes/Documents/Labor/SpectrumAnalysis/spektrum_hordó/z_igazi_ave.csv"

set style line 1 lc rgb "black" pt 7 ps 1 lt 1 lw 1
set style line 2 lc rgb "red" pt 7 ps 1 lt 1 lw 1
set style line 3 lc rgb "green" pt 7 ps 1 lt 1 lw 1
set style line 4 lc rgb "grey" pt 7 ps 1 lt 1 lw 1
set style line 5 lc rgb "orange" pt 7 ps 1 lt 1 lw 1
set style line 6 lc rgb "blue" pt 7 ps 1 lt 1 lw 1

set xlabel 'wavelength (nm)'
set ylabel 'count'

plot filename1 u 1:2 w l ls 1 title "black", filename2 u 1:2 w l ls 2 title "white", filename3 u 1:2 w l ls 3 title "horse", filename4 u 1:2 w l ls 4 title "grey cattle", filename5 u 1:2 w l ls 5 title "artificial zebra", filename6 u 1:2 w l ls 6 title "real zebra"

