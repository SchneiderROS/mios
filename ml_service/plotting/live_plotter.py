import pymongo
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style

from plotting.data_acquisition import *
from plotting.data_processor import DataProcessor

def live_plot(robots, tags):
    tags = ["collective_experiment_shared","paper_run_1", "n3"]
    robots = ["collective-panda-001.local", "collective-panda-002.local", "collective-panda-003.local", "collective-panda-009.local"]
    cmap = plt.get_cmap('gist_rainbow')
    colors = [cmap(i) for i in np.linspace(0, 1, len(robots))]
    # calculating number of couloms:
    if len(robots) <= 24:
        n_cols = 4
    if len(robots) <= 12:
        n_cols = 3
    if len(robots) <= 6:
        n_cols = 2
    if len(robots) <= 3:
        n_cols = 1
    n_rows = int(np.ceil(len(robots)/n_cols))
    fig, axes = plt.subplots(n_rows, n_cols, sharex='col', sharey='row')
    if len(robots) > 1:
        axes = axes.reshape(-1)
    else:
        axes = [axes]
    plot_lines = []  # all 2D line objects representing the plotted data
    current_data_sets = []
    for i in range(len(robots)):
        axes[i].grid()
        line, = axes[i].plot([],[], lw=3, color=colors[i])
        plot_lines.append(line)
        current_data_sets.append({"x":[], "y":[]})  # keep track of current data



    def get_results( host: str, skill_class: str, tags: list):
            p = DataProcessor()
            try:
                results = get_experiment_data(host, skill_class, "ml_results", filter={"meta.tags": {"$all": tags}})
            except DataNotFoundError:
                return False, False
            cost, time = results.get_cost_per_time()
            cost_mon = p.get_monotonically_decreasing_cost(cost)
            return cost_mon, time

    #def init():  # only required for blitting to give a clean slate.
    #    return plot_lines

    def animate(data):
        for i in range(len(robots)):
            cost,time = get_results("collective-panda-001.local","insert_object",["collective_experiment_shared","paper_run_1", "n3"])
            new_data_index = len(current_data_sets[i]["x"]) - len(time)
            if new_data_index < 0:  # just update if new data is available
                current_data_sets[i]["x"].extend(time[new_data_index:])
                current_data_sets[i]["y"].extend(cost[new_data_index:])
                plot_lines[i].set_data(current_data_sets[i]["x"], current_data_sets[i]["y"])
                plot_lines[i].axes.set_xlim(0,max(time))
                if cost[-1] < 10:
                    plot_lines[i].axes.set_ylim(0,10)
                else:
                    plot_lines[i].axes.set_ylim(0,max(cost))
            
        return plot_lines

    def data_gen():
        steps = range(1,101)
        for i in steps:
            yield [x for x in range(1,i+1)], [x*x for x in range(1,i+1)]


    ani = animation.FuncAnimation(fig, animate, interval=1000) #, init_func=init, save_count=50, data_gen
    plt.show()
