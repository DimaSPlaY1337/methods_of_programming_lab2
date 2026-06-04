import pandas as pd
import matplotlib.pyplot as plt


def main():
    df = pd.read_csv('results_search.csv')

    plt.figure(figsize=(10, 6))
    plt.plot(df['Size'], df['Collisions'], marker='o', linewidth=2)
    plt.title('Зависимость числа коллизий от размерности массива')
    plt.xlabel('Размер массива')
    plt.ylabel('Число коллизий')
    plt.grid(True)
    plt.tight_layout()
    plt.savefig('hash_collisions.png', dpi=300)
    plt.close()

    plt.figure(figsize=(10, 6))
    plt.plot(df['Size'], df['Linear'], marker='o', label='Linear Search')
    plt.plot(df['Size'], df['BST'], marker='o', label='BST')
    plt.plot(df['Size'], df['RBT'], marker='o', label='RBT')
    plt.plot(df['Size'], df['HashTable'], marker='o', label='Hash Table')
    plt.plot(df['Size'], df['Multimap'], marker='o', label='Multimap')
    plt.title('Сравнение времени поиска')
    plt.xlabel('Размер массива')
    plt.ylabel('Время поиска, мкс')
    plt.legend()
    plt.grid(True)
    plt.tight_layout()
    plt.savefig('search_time_comparison.png', dpi=300)
    plt.close()


if __name__ == '__main__':
    main()