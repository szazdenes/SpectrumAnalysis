reset

set terminal postscript enhanced color landscape font 'Times-Roman,12'
set output 'spectrum_zebra_ave_rel.ps'

filename1 = "/home/denes/Documents/Labor/SpectrumAnalysis/spektrum_hordó/z_igazi_fekete_ave_rel.csv"
filename2 = "/home/denes/Documents/Labor/SpectrumAnalysis/spektrum_hordó/z_igazi_feher_ave_rel.csv"
filename3 = "/home/denes/Documents/Labor/SpectrumAnalysis/spektrum_hordó/z_mu_fekete_ave_rel.csv"
filename4 = "/home/denes/Documents/Labor/SpectrumAnalysis/spektrum_hordó/z_mu_feher_ave_rel.csv"

set style line 1 lc rgb "black" pt 7 ps 1 lt 1 lw 1
set style line 2 lc rgb "grey" pt 7 ps 1 lt 1 lw 1
set style line 3 lc rgb "red" pt 7 ps 1 lt 1 lw 1
set style line 4 lc rgb "green" pt 7 ps 1 lt 1 lw 1

set xlabel 'wavelength (nm)'
set ylabel 'count'
set key left top

plot filename1 u 1:2 w l ls 1 title "real zebra black", filename2 u 1:2 w l ls 2 title "real zebra white", filename3 u 1:2 w l ls 3 title "artificial zebra black", filename4 u 1:2 w l ls 4 title "artificial zebra white"
