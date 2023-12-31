# =================================
# Define title and axis for the plot
# ---------------------------------
set title "Desempenho da multiplicação das matrizes" font ", 32"
set title offset 0,-0.95
set xlabel "Tamanho da matriz" font "helvetica, 24"
set xlabel offset 0,-1.8
set ylabel "Tempo de execução (em milissegundos)" font "helvetica, 24"
set ylabel offset +1.8,0

# =================================
# Line style definition
# ---------------------------------
set style line 1 lt 4 lw 3 dt 2
set style line 2 lt 3 lw 2
set style line 3 lc rgb 'red' dt 2 lt 1 lw 2
set style line 4 lc rgb 'black' dt 1 lt 1 lw 2
set style line 5 lc rgb 'blue' dt 2 lt 1 lw 2

# =================================
# Choose where the output should be sent to.
# In this case, we send it to a PNG image.
# ---------------------------------
set terminal png size 1920,1080
set o 'estudo_1.png'

# =================================
# Plot curves and outher stuff
# ---------------------------------
set grid                 # Do we want a grid?
set key top left         # Location of the keys
# set logscale y           # Use this if the curves are in different scale
set xrange [100:3200]    # Define range of X values to consider.
#set yrange [0:26]        # Define range of Y values to consider

# Finally, this is the plot command
plot 'tempos_sequencial.txt' u 1:2 title 'Sequencial' w lp ls 3, \
     'tempos_threads.txt' u 1:2 title 'Threads' w lp ls 4, \
     'tempos_processos.txt' u 1:2 title 'Processos' w lp ls 5

# Go back to interactive terminal
set out
