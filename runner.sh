
echo "Welcome to our DAA Bash Runner"
# for n in 500
# do
#     mkdir $n
#     python3 polygon_generator.py $n
#     g++ main.cpp
#     ./a.out
#     python3 python_visualizer_before.py $n
#     python3 python_visualizer_after.py $n
#     python3 plot_time.py $n
# done

# mkdir trial_plot
for n in {5..100..10}
do
    python3 polygon_generator.py $n
    g++ main_new.cpp -o a.out
    ./a.out
    # python python_visualizer_before.py $n trial_plot
    # python python_visualizer_after.py $n trial_plot
    # python plot_time.py $n trial_plot
done

python plot_time_vertices.py trial_plot