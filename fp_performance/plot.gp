set terminal png
set output 'compare.png'

set xlabel 'number of iterations'
set ylabel 'times (ns)'

plot 'integer.out' using 1:2 title "Integer", \
     'float.out'  using 1:2 title "Floating point"