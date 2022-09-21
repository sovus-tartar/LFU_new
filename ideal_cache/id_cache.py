

def find_first(a : list, num : int, start : int):
    temp = start
    for i in range(start, len(a)):
        if (a[i] == num):
            return i

    return len(a) + 1
    
def print_progressbar(curr : int, max : int):   
    print("\r", end = '')
    progress = curr * 100 / max
    print("[", end = '')
    for i in range(int(progress/10)):
        print("#", end = '')
    for i in range(int(10 - progress/10)):
        print("-", end = '')
    print(f"] {round(progress, 2)}%", end = '')

def main():
    N = int(input()) #cache_sz
    M = int(input()) #requests_num
    list_req = [int(value) for value in input().split()]
    cache_ = []
    succ_count = 0

    for i in range(M):
        temp = list_req[i]

        if temp in cache_:
            succ_count +=1 
        else:
            if(len(cache_) < N):
                cache_.append(temp)
            else:
                to_remove = -1
                last_count = find_first(list_req, temp, i + 1)
                for j in range(N):
                    k = find_first(list_req, cache_[j], i)
                    if (k > last_count):
                        to_remove = j
                        last_count = k

                if (to_remove != -1):                           #checking if it is the only entrance of requested element
                    cache_.remove(cache_[to_remove])
                    cache_.append(temp)
        
        print_progressbar(i, M)

    print(f"\nLfu hit: {int(input())}, id_cache hit: {succ_count}")
        

main()