# Gnuplot script to plot data in the file func.dat

# set plotting style
set dgrid 50,50
set hidden3d
set pm3d


# set labels
set title "func.dat"
set xlabel "x"
set ylabel "y"
set zlabel "f(x,y)"

splot "func.dat" u 1:2:3 with lines


pause mouse key "Tab Taste drücken um zu Beenden"
if (MOUSE_KEY != 9) reread
