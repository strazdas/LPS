# coding: utf-8
from matplotlib import pyplot as plt
from matplotlib.ticker import MultipleLocator, FuncFormatter
from math import log


def read_data(filename='res/comb_part_omp3'):
    threads, time = [], []
    for l in open(filename):
        n, t = l.split(',')
        threads.append(int(n.strip()))
        time.append(float(t.strip()))
    return threads, time

def draw_time(threads, time):
    fig, ax = plt.subplots()
    plt.title(u"Hyperkūbo (n=10) kombinatorinio trianguliavimo trukmė")
    plt.xlabel(u'Procesorių skaičius')
    plt.ylabel(u'Veikimo laikas sekundėmis')
    plt.plot(threads, time)
    # ax.set_xscale('log')
    # plt.xticks([1, 2, 4, 8, 16, 32, 64, 128, 256])
    # ax.xaxis.set_major_locator(MultipleLocator(10))
    # ax.xaxis.set_major_locator(FuncFormatter(lambda x, pos: '{:0.1f}'.format(log(x))))
    plt.savefig(u'../results/img/time_comb_part_omp.png')

def draw_spartinimas(threads, time, clr):
    t1 = time[0]
    S = [t1/float(t) for t in time]
    fig, ax = plt.subplots()
    plt.title(u"Hyperkūbo (n=10) kombinatorinio trianguliavimo spartinimas (MPI)")
    plt.xlabel(u'Procesorių skaičius')
    plt.ylabel(u'Spartinimo koeficientas')
    plt.plot(threads, S, clr)

    # ax.xaxis.set_major_locator(MultipleLocator(1))

    # ax.set_xscale('log')
    #plt.semilogx(basex=2)
    # plt.xlim([1, 256])
    # plt.xticks([1, 4, 8, 16, 32, 64, 128, 256])
    # ax.xaxis.set_major_locator(MultipleLocator(4))
    # plt.savefig(u'img/sparta_comb_part_omp.png')

def draw_efektyvumas(threads, time):
    t1 = time[0]
    fig, ax = plt.subplots()
    plt.title(u"Hyperkūbo (n=10) kombinatorinio trianguliavimo efektyvumas (MPI)")
    plt.xlabel(u'Procesorių skaičius')
    plt.ylabel(u'Efektyvumo koeficientas')
    plt.plot(threads, E)
    # plt.xlim([1, 256])
    # plt.ylim([0, 1])
    # ax.set_xscale('log')
    # plt.xticks([1, 4, 8, 16, 32, 64, 128, 256])
    # ax.xaxis.set_major_locator(MultipleLocator(1))


if __name__ == '__main__':
    fig, ax = plt.subplots()

    # files =  [('../results/mpi1', 'b'), ('../results/mpi2', 'r'), ('../results/mpi3', 'g')]
    # plt.xticks([1, 4, 8, 16, 32, 64, 128, 256])

    # files =  [('../results/omp1', 'b'), ('../results/omp2', 'r'), ('../results/omp3', 'g')]
    files =  [('../results/loop_omp1', 'b'), ('../results/loop_omp2', 'r'), ('../results/loop_omp3', 'g')]
    ax.xaxis.set_major_locator(MultipleLocator(1))

    for filename, clr in files:
        cpus, time = read_data(filename)
        t1 = time[0]
        # S = [t1/float(t) for t in time]
        # plt.plot(cpus, S, clr)

        E = [(t1/float(t))/n for n, t in zip(cpus, time)]
        plt.plot(cpus, E, clr)
    plt.xlabel(u'Procesorių skaičius')
    # plt.title(u"10'mačio hyperkūbo kombinatorinio trianguliavimo\n spartinimo koeficientas naudojant OpenMP", fontsize=14)
    # plt.ylabel(u'Spartinimo koeficientas')
    # plt.savefig(u'../results/img/loop_spartinimas_omp.png')
    plt.title(u"10'mačio hyperkūbo kombinatorinio trianguliavimo\n efektyvumo koeficientas naudojant OpenMP", fontsize=14)
    plt.ylabel(u'Efektyumo koeficientas')
    plt.savefig(u'../results/img/loop_efektyvumas_omp.png')
