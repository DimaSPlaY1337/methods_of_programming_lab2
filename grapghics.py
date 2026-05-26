import matplotlib.pyplot as plt
import numpy as np

# 1. Задаем размерности массивов (ось X)
sizes = [100, 500, 1000, 5000, 10000, 50000, 100000, 500000, 1000000]

# БЛОК 1: ДАННЫЕ ДЛЯ КОЛЛИЗИЙ
# Замени этот массив на реальное количество коллизий из твоего C++ кода
# Здесь мы имитируем, что число коллизий растет линейно вместе с размером массива
collisions = [int(s * np.random.uniform(0.15, 0.25)) for s in sizes]

plt.figure(figsize=(10, 6))
plt.plot(sizes, collisions, marker='o', linestyle='-', color='b', linewidth=2)
plt.title('Зависимость числа коллизий хэш-таблицы от размерности массива', fontsize=14)
plt.xlabel('Размерность массива (кол-во элементов)', fontsize=12)
plt.ylabel('Количество коллизий', fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)
plt.ticklabel_format(style='plain', axis='x') # Отключаем научный формат (1e6)

# Сохраняем первый график
plt.savefig('collisions.png', dpi=300, bbox_inches='tight')
plt.show()

# БЛОК 2: ДАННЫЕ ДЛЯ ВРЕМЕНИ ПОИСКА
# Замени эти массивы на реальное время (в секундах) из твоего C++ кода
# Имитация времени:
# Линейный поиск - O(N)
time_linear = [s * np.random.uniform(1e-7, 1.5e-7) for s in sizes]
# Бинарное дерево - O(log N)
time_bst = [np.log2(s) * np.random.uniform(2e-6, 3e-6) for s in sizes]
# Красно-черное дерево - O(log N) (чуть быстрее обычного дерева за счет балансировки)
time_rbt = [np.log2(s) * np.random.uniform(1.5e-6, 2.5e-6) for s in sizes]
# std::multimap - O(log N)
time_multimap = [np.log2(s) * np.random.uniform(1.8e-6, 2.8e-6) for s in sizes]
# Хэш-таблица - O(1) в среднем
time_hash = [np.random.uniform(5e-7, 1e-6) for s in sizes]

plt.figure(figsize=(12, 7))

plt.plot(sizes, time_linear, marker='o', label='Линейный поиск (O(N))')
plt.plot(sizes, time_bst, marker='s', label='Бинарное дерево поиска (O(log N))')
plt.plot(sizes, time_rbt, marker='^', label='Красно-черное дерево (O(log N))')
plt.plot(sizes, time_multimap, marker='d', label='std::multimap (O(log N))')
plt.plot(sizes, time_hash, marker='x', label='Хэш-таблица (O(1))')

plt.title('Сравнение времени поиска для различных структур данных', fontsize=14)
plt.xlabel('Размерность массива (кол-во элементов)', fontsize=12)
plt.ylabel('Время поиска (секунды)', fontsize=12)

plt.xscale('log')
plt.yscale('log')

plt.grid(True, which="both", ls="--", alpha=0.5)
plt.legend(fontsize=11)

plt.savefig('search_times.png', dpi=300, bbox_inches='tight')
plt.show()