import pandas as pd
import matplotlib.pyplot as plt

file_path = 'C:/Users/Артем/source//repos//Parallel//task2//task2//results.csv'
data = pd.read_csv(file_path)

def speedup():
    computationMethod = 1
    n_array = [10000, 100000,1000000,10000000,100000000] # Для computationMethod = 0 и 1
    #n_array = [1000, 5000, 10000, 50000, 100000]        # Для computationMethod = 2
    shuffle = False
    N = n_array[-1]


    plt.figure(figsize=(10, 6))
    # Расчёт теоретического ускорения по формуле Амдала
    # s - доля вычислений, которые невозможно распараллелить
    s = data[(data['computationMethod'] == computationMethod) & (data['N'] == N) & (data['M'] == 1) & (data['shuffle']==shuffle)]['S'].iloc[0]
    print(s)
    parallel_times = data[(data['computationMethod'] == computationMethod) & (data['M'].notna()) & (data['N'] == N) & (data['shuffle']==shuffle)]
    parallel_times['Amdahl'] = 1/(s + (1-s)/parallel_times['M'])
    #plt.plot(parallel_times['M'], parallel_times['Amdahl'], marker='o', linestyle=':', label=f'Теоретическое ускорение по формуле Амдала')
    print(parallel_times)

    for N in n_array:
        sequential_time = data[(data['computationMethod'] == computationMethod) & (data['M'].isna()) & (data['N'] == N)]['Time']
        parallel_times = data[(data['computationMethod'] == computationMethod) & (data['M'].notna()) & (data['N'] == N) & (data['shuffle']==shuffle)]
        parallel_times['Speedup'] = sequential_time.iloc[0]/parallel_times['Time']
        plt.plot(parallel_times['M'], parallel_times['Speedup'], marker='o', linestyle='-', label=f'N = {N}')


    plt.title(f'Зависимость ускорения от M (computationMethod = {computationMethod})')
    plt.xlabel('M')
    plt.ylabel('Ускорение (разы)')
    plt.xscale('log')  
    plt.yscale('log') 
    plt.grid(True)
    plt.legend()
    plt.show() 

def computation_time():
    computationMethod = 0
    m_array = [2, 5, 10, 30, 100]
    shuffle = True

    sequential = data[(data['computationMethod'] == computationMethod) & (data['M'].isna())]

    sequential['N'] = pd.to_numeric(sequential['N'])
    sequential['Time'] = pd.to_numeric(sequential['Time'])

    plt.figure(figsize=(10, 6))

    plt.plot(sequential['N'], sequential['Time'], marker='o', linestyle='-', color='black', label='Последовательное выполнение')

    for M in m_array:
        paralell = data[(data['computationMethod'] == computationMethod) & (data['M'] == M) & (data['shuffle'] == shuffle)]
        
        paralell['N'] = pd.to_numeric(paralell['N'])
        paralell['Time'] = pd.to_numeric(paralell['Time'])
        
        plt.plot(paralell['N'], paralell['Time'], marker='o', linestyle='-', label=f'M = {M}')

    plt.title(f'Зависимость времени выполнения от N для различных значений M (computationMethod = {computationMethod})')
    plt.xlabel('N')
    plt.ylabel('Время выполнения (секунды)')
    plt.xscale('log')  
    plt.yscale('log') 
    plt.grid(True)
    plt.legend()
    plt.show()


speedup()
#computation_time()
