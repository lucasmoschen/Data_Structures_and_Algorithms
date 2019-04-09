import numpy as np
import time
import timeit
import pandas as pd
import matplotlib.pyplot as plt

def insert_sort(a):
    '''
    Function that uses the insertion sort algorithm to sort a list 
    '''
    n = len(a)
    for i in range (1,n):               #walk in the array, to sort a[0:i+1]
        key = a[i]                      #atribute to key the current value of the list, to compare with the sublist in the left
        j = i-1
        while j>=0 and a[j] > key:      #the sublist a[0:i] is sorted, so it's enough to compare with the antecessors first. 
            a[j+1] = a[j]
            j -= 1
        a[j+1] = key
    return a


def merge(a,b):
    '''
    Auxiliar function to merge sort. It pick 2 lists and create a sorted one, with the elements of the 2 lists.
    '''
    if len(a) == 0: return b             #in the case of one list is empty, return the other
    elif len(b) == 0: return a
    merged_list = []                     #creates th final list
    i, j = 0, 0                          #inicialize the iteretors
    while len(a) != i and len(b) != j:   #while the iterador doesn't finish the list, it continues
        if a[i] <= b[j]:                 #compare the values
            merged_list.append(a[i])
            i += 1
        else:
            merged_list.append(b[j])
            j += 1
    merged_list.extend(a[i:])             #extend the list if necessary, for a and b. 
    merged_list.extend(b[j:])
    return merged_list

def merge_sort(a):
    '''
    Function that uses the merge sort algorithm to sort a list (divide and conquer)
    '''
    if len(a) == 1 or len(a) == 0:     #the base case
        return a
    half = int(len(a)/2)               #divides the list in two parts, a left e a_right
    a_left = merge_sort(a[0:half])
    a_right = merge_sort(a[half:])
    a = merge(a_left,a_right)          #merge the sublists  
    return a


def is_sorted(a):
    '''
    Function that compare the elements, one by one. If find a[i] > a[i+1], return false. Return True if the list is sorted
    '''
    for i in range(len(a)-1): 
        if a[i] > a[i+1]:
            return False
    return True

def main():
    ns = np.linspace(10000, 100000, 10)   ##create the set of 10 numbers
    f = open('times_insert.csv','w',encoding = 'UTF-8')
    g = open('times_merge.csv','w',encoding = 'UTF-8')
    cont = 0 #to put the informations in the CSV file
    time_insert = []  #lists with tuples(len(list), random time, asc time and desc time)
    time_merge = []
    for i in ns:
    
    ##########Create the lists#############
        lista = np.linspace(1,int(i),int(i))
    #############Random Lists##############
        random_insert_list = lista.copy()
        np.random.shuffle(random_insert_list)
        random_merge_list = random_insert_list.copy()                                     
    #############Ascending Lists###########
        asc_insert_list = lista.copy()
        asc_merge_list = asc_insert_list.copy()
    ###########Desscending Lists###########
        desc_insert_list = np.linspace(int(i),1,int(i))
        desc_merge_list = desc_insert_list.copy()
        
        
    #############Sorting###################
    
    ###########Insertion Sort##############
                    
                                                  #Reference: https://docs.python.org/3/library/timeit.html#timeit.default_timer
        start = timeit.default_timer()                       #starts the timer, using the default. In Python 3, it's perf_couter
        sorted_by_insert = insert_sort(random_insert_list)#random list              
        t_insert1 = timeit.default_timer() - start
                
        if not is_sorted(sorted_by_insert):
            print("ERROR IN INSERT")
            return "Error"
        
        start = timeit.default_timer()                   
        sorted_by_insert = insert_sort(asc_insert_list) #ascending list          
        t_insert2 = timeit.default_timer() - start
                
        if not is_sorted(sorted_by_insert):
            print("ERROR IN INSERT")
            return "Error"
        
        start = timeit.default_timer()                   
        sorted_by_insert = insert_sort(desc_insert_list) #descending list         
        t_insert3 = timeit.default_timer() - start
                
        if not is_sorted(sorted_by_insert):
            print("ERROR IN INSERT")
            return "Error" 
        
        time_insert.append((int(i),t_insert1,t_insert2,t_insert3))
            
    ###############Merge Sort##############

        start = timeit.default_timer()                       
        sorted_by_merge = merge_sort(random_merge_list)#random list              
        t_merge1 = timeit.default_timer() - start
                
        if not is_sorted(sorted_by_merge):
            print("ERROR IN MERGE")
            return "Error"
        
        start = timeit.default_timer()                   
        sorted_by_merge = merge_sort(asc_merge_list) #ascending list          
        t_merge2 = timeit.default_timer() - start
                
        if not is_sorted(sorted_by_merge):
            print("ERROR IN MERGE")
            return "Error"
        
        start = timeit.default_timer()                   
        sorted_by_merge = merge_sort(desc_merge_list) #descending list         
        t_merge3 = timeit.default_timer() - start
                
        if not is_sorted(sorted_by_merge):
            print("ERROR IN MERGE")
            return "Error"
        
        time_merge.append((int(i),t_merge1,t_merge2,t_merge3))
        
        print("%d %f %f %f %f %f %f" % (i, t_insert1, t_insert2,t_insert3,t_merge1,t_merge2,t_merge3))
        
        f.write(str(time_insert[cont])[1:-1])
        f.write('\n')

        g.write(str(time_merge[cont])[1:-1])
        g.write('\n')
        
        cont += 1
        
    f.close()
    g.close()
    return time_insert, time_merge
    
if __name__ == "__main__":
    print("Iniciating")
    main()
    print("Finished")
    
##reading CSV file and ploting
    
rows_names = ['N_elements','Random_list','Asc_list','Desc_list']
Insert = pd.read_csv('times_insert.csv',names = rows_names)
Merge = pd.read_csv('times_merge.csv',names = rows_names)
Insert = Insert.set_index('N_elements')
Merge = Merge.set_index('N_elements')

plt.figure(figsize=(14,14))

plt.subplot(2,2,1)
plt.plot(Insert.Random_list)
plt.plot(Merge.Random_list)
plt.title('Random Order List')
plt.xlabel('Number of Elements of the list')
plt.ylabel('Duration of the programam (seconds)')
plt.legend(('Insert Sort','Merge Sort'))

plt.subplot(2,2,2)
plt.plot(Insert.Asc_list)
plt.plot(Merge.Asc_list)
plt.title('Ascending Order List')
plt.xlabel('Number of Elements of the list')
plt.ylabel('Duration of the programam (seconds)')
plt.legend(('Insert Sort','Merge Sort'))

plt.subplot(2,2,3)
plt.plot(Insert.Desc_list)
plt.plot(Merge.Desc_list)
plt.title('Descending Order List')
plt.xlabel('Number of Elements of the list')
plt.ylabel('Duration of the programam (seconds)')
plt.legend(('Insert Sort','Merge Sort'))

plt.savefig('Graphics_sorts.png')
plt.show()