import random

def in_list(temp : int, l : list):
    for i in range(len(l)):
            node = l[i]
            if node[0] == temp:
                return i
    return -1

def remove_least_freq_used(cache: list):
    cache.remove[0]
    return 0

def cmp_(a1 : tuple):
    return a1[1]

def get_rand_in_range(max : int, m : int):
    random.seed()
    arr = []
    for i in range(m):
        arr.append(random.randint(0, max))

    return arr

def print_list(l : list):
    for i in range(len(l)):
        print(l[i], end=' ')

    print()

def seek_last(l : list, num : int):
    for i in range(len(l)):
        if ((l[i])[1] > num):
            return i
    return len(l)


def main():
    cache_ = [] 
    hit = 0
    num = 0
    N = int(input()) #cache_sz
    M = int(input()) #recdquests
    max = int(input()) #max
    print(N)
    print(M)
    req_list = get_rand_in_range(max, M)
    #print(req_list)
    print_list(req_list)
    
    for i in range(M):
        temp = req_list[i]
        count = in_list(temp, cache_)

        if ((count) != -1):
            (cache_[count]) [1] += 1
            place = seek_last(cache_, cache_[count][1])
            number = cache_[count]
            cache_.insert(place, cache_[count])
            cache_.remove(number)
            hit += 1
            #print("Success")
            #print(cache_)
        else:
            #print("Failed")
            if (num < N):
                place = seek_last(cache_, 0)
                cache_.insert(place, [temp, 0])
                num += 1
            else:
                cache_.pop(0)
                place = seek_last(cache_, 0)
                cache_.insert(place, [temp, 0])

            #print(cache_)

    print(hit)

main()


        

    