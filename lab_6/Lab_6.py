import numpy as np

def read_matrix(filename):
    with open(filename, 'r') as file:
        matrix = [list(map(int, line.strip().split())) for line in file]
    return np.array(matrix)

def find(parent, i):
    if parent[i] != i:
        parent[i] = find(parent, parent[i])
    return parent[i]

def union(parent, rank, x, y):
    xroot = find(parent, x)
    yroot = find(parent, y)
    if rank[xroot] < rank[yroot]:
        parent[xroot] = yroot
    elif rank[xroot] > rank[yroot]:
        parent[yroot] = xroot
    else:
        parent[yroot] = xroot
        rank[xroot] += 1

def kruskal_mst(graph):
    edges = []
    size = len(graph)
    for i in range(size):
        for j in range(i + 1, size):
            if graph[i][j] != 0:
                edges.append((graph[i][j], i, j))

    edges.sort()
    parent = [i for i in range(size)]
    rank = [0] * size

    mst = []
    total_weight = 0

    for weight, u, v in edges:
        if find(parent, u) != find(parent, v):
            union(parent, rank, u, v)
            mst.append((u, v, weight))
            total_weight += weight

    return mst, total_weight

def mst_to_adjacency_matrix(mst, size):
    matrix = np.zeros((size, size), dtype=int)
    for u, v, weight in mst:
        matrix[u][v] = weight
        matrix[v][u] = weight 
    return matrix

def print_matrix(matrix):
    for row in matrix:
        print(' '.join(map(str, row)))

def operation(filename):
    graph = read_matrix(filename)

    print("Исходная матрица:")
    print_matrix(graph)

    mst, total_weight = kruskal_mst(graph)

    print(f"\nОбщий вес минимального остовного дерева: {total_weight}")
    print("Рёбра дерева:")
    for u, v, weight in mst:
        print(f"{u} - {v} вес: {weight}")

    mst_matrix = mst_to_adjacency_matrix(mst, len(graph))
    print("\nМатрица смежности дерева:")
    print_matrix(mst_matrix)


def main():
    operation('g1.txt')
    print("=========================================================================================================")
    operation('g2.txt')
    print("=========================================================================================================")
    operation('g3.txt')
    print("=========================================================================================================")
    operation('g4.txt')

if __name__ == "__main__":
    main()
