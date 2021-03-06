set terminal png size 900, 500 background rgb 'white'
set output "img/both.png"
set xlabel "Matrix Dimension A: M=N"
set ylabel "MFLOPS"
set title "QR-Zerlegung mit Householder"
set key below 
set pointsize 0.5
plot "dat/blk.data" using 1:5 with linespoints lt 2 lw 1 pt 8 ps 1.5 title  "Eigene QR Blocked", \
     "dat/blk.data" using 1:8 with linespoints lt 3 lw 1 pt 2 ps 1.5 title  "MKL QR Blocked", \
     "dat/unblk.data" using 1:5 with linespoints lt 4 lw 1 pt 9 ps 1.5 title "Eigene unblk", \
     "dat/unblk.data" using 1:8 with linespoints lt 5 lw 1 pt 3 ps 1.5 title "MKL unblk", \
     "dat/blk.data" using 1:9 with line lw 3 lc rgb "red"title "Theo. Peak Performance"



