import pymongo
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style

from plotting.data_acquisition import get_experiment_data
from plotting.data_processor import DataProcessor


fig = plt.figure()
ax1 = fig.add_subplot(1, 1, 1)


def get_results(host: str, skill_class: str, tags: list):
    p = DataProcessor()
    results = get_experiment_data(host, skill_class, "ml_results", filter={"meta.tags": {"$all": tags}})
    cost, time = results.get_cost_per_time()
    cost_mon = p.get_monotonically_decreasing_cost(cost)
    return cost_mon, time


def start_plot():
    style.use('fivethirtyeight')

    ani = animation.FuncAnimation(fig, animate, interval=1000)
    plt.show()


def animate(i):
    xs = []
    ys = []
    cost, time = get_results("collective-panda-001.local", "insert_object", ["collective_experiment_shared","paper_run_1", "n3"])
    for i in range(len(cost)):
        xs.append(float(time[i]))
        ys.append(float(cost[i]))
    ax1.clear()
    ax1.plot(xs, ys)

