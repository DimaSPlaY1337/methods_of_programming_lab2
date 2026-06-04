import pandas as pd
import matplotlib.pyplot as plt


def main():
    df = pd.read_csv('results_search.csv')

    plt.figure(figsize=(10, 6))
    plt.plot(df['Size'], df['Collisions'], marker='o', color='crimson', linewidth=2)
    plt.title('Зависимость числа коллизий хеш-функции от размерности массива')
    plt.xlabel('Размер массива')
    plt.ylabel('Число коллизий')
    plt.grid(True)
    plt.tight_layout()
    plt.savefig('hash_collisions.png', dpi=300)
    plt.show()


if __name__ == '__main__':
    main()