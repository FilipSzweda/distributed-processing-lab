import time
import multiprocessing as mp
import asyncio


def write_and_read_name_and_index():
    with open('name_and_index.txt', 'w') as f:
        f.write('Filip 184738')
    with open('name_and_index.txt', 'r') as f:
        return f.read()


def is_name_index(name: str, index: int):
    letter_count = len(name)
    return str(letter_count) in str(index)


def howmany_within_range(data):
    row = data[0]
    minimum = data[1]
    maximum = data[2]

    """Returns how many numbers lie within `maximum` and `minimum` in a given `row`"""
    count = 0
    for n in row:
        if minimum <= n <= maximum:
            count = count + 1
    return count


if __name__ == '__main__':
    start_a = time.time()
    start_b = time.perf_counter()
    string = write_and_read_name_and_index()
    words = string.split()
    result = is_name_index(words[0], int(words[1]))
    print(f'Time with time.time(): {time.time() - start_a}')
    print(f'Time with time.perf_counter(): {time.time() - start_b}')

    rows = [[[1, 5, 7, 3, 7, 8, 10, 22, 0]], [[3, 4, 5, 6, 1, 6, 45, 23, 12]], [[1, 0, 0, 18, 3]]]
    minimum = 0
    maximum = 10
    for row in rows:
        row.append(minimum)
        row.append(maximum)
    pool = mp.Pool(mp.cpu_count())
    results = pool.map_async(howmany_within_range, rows)
    print(results.get())
    pool.close()
    pool.join()
