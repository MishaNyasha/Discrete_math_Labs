import re

def get_table(name):
    try:
        with open(name, 'r') as f:
            lines = f.readlines()
    except IOError:
        print("Ошибка открытия файла")
        return []
    table = [list(map(int, re.findall(r'\d+', line))) for line in lines]
    if not table:
        return []
    cols = len(table[0])
    if any(len(row) != cols for row in table):
        print("Матрица имеет строки разной длины")
        return []
    if cols != len(table):
        print(f"Матрица не квадратная: {len(table)}x{cols}")
        return []
    return table

def draw_table(table):
    n = len(table)
    widths = [max(len(str(table[r][c])) for r in range(n)) for c in range(n)]
    for row in table:
        print(' '.join(f"{val}{' ' * (widths[i] - len(str(val)) + 1)}" for i, val in enumerate(row)))
    print()

def shimbel(mat, mode, steps):
    n = len(mat)
    res = [row[:] for row in mat]
    for _ in range(steps - 1):
        tmp = [row[:] for row in res]
        for i in range(n):
            for j in range(n):
                vals = [tmp[i][k] + mat[k][j] for k in range(n) if tmp[i][k] and mat[k][j]]
                res[i][j] = (max(vals) if mode == 1 else min(vals)) if vals else 0
    return res

def main():
    name = 'h1.txt'
    print(f"Имя файла: {name}")
    mat = get_table(name)
    if not mat:
        return
    print("Матрица связности:")
    draw_table(mat)
    mode = 0
    while mode not in (1, 2):
        mode = int(input("1. Максимум\n2. Минимум\n"))
    steps = 0
    while steps <= 0:
        steps = int(input("Введите количество переходов\n"))
    res = shimbel(mat, mode, steps)
    draw_table(res)

if __name__ == "__main__":
    main()
