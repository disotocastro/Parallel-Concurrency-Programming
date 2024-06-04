# Golbach_Optimized
- Author: Juan Diego Soto Castro, C07722.
- E-mail: ```juan.sotocastro@ucr.ac.cr```

## Summary
This C program calculates Goldbach sums for a list of integer numbers provided via standard input. The Goldbach conjecture states that every even integer greater than 5 can be expressed as the sum of two prime for the even numbers or sum of three numbers if the number is odd.

The program sequentially processes each input number, finding all possible Goldbach sums and showing the total of sums. 

In this version, Golbach sums are calculated in a parallel manner, utilizing private memory and semaphores. Tasks are shared as evenly as possible among threads. Each thread is responsible for solving a similar or equal number of elements from the array entered by the user, thereby improving the program's performance with large and medium-sized inputs.

Additionally, the program prints a list of the input numbers along with the count of Goldbach sums for each number. If a negative number is entered, the program lists all Goldbach sums for the corresponding positive number.

## Analysis
To create a program that calculates the Goldbach sums, the first step is to generate prime numbers. There are many methods for doing this; the Sieve of Eratosthenes and Trial Division are the most popular methods for generating large sets of prime numbers. While there are numerous variations of these two methods, this program employs the classic Trial Division approach. However, it's worth noting that there are various adaptations of these methods that can enhance performance and may be incorporated into the program in the future.

After generating the array of prime numbers, threads are created for calculating the sums. The number of threads can be specified as an argument; otherwise, the number of threads will be equal to the maximum number allowed by the current computer. Once this is done, the threads will distribute the tasks almost equally and call the methods for calculating the sums individually. During printing, there are semaphores in place to ensure the correct printing of the numbers.

Furthermore, when computing Goldbach's sums, the task will be divided into two functions. One function will be responsible for calculating Goldbach sums for even numbers, while the other will handle sums for odd numbers. To find the sums, both methods employ brute force algorithms. Additionally, utilizing more efficient algorithms in terms of time, space and complexity, such as a backtracking algorithm, can lead to improved runtime.

## Version Update

Elimination of Redundant Conditions: In the original code, there were redundant checks to ensure prime numbers were non-zero (if (prime_1 != 0 && prime_2 != 0 && prime_3 != 0)), which is unnecessary since, by definition, elements in arr_prime_numbers must be prime and thus cannot be zero.

Search Space Reduction: The optimized code adds a break condition in the nested loops to avoid unnecessary iterations. If the sum of the first two primes (prime1 + prime2) or the total sum (prime1 + prime2 + prime3) exceeds the current number (current_num), the corresponding loop is broken. This significantly reduces the number of iterations, especially when the prime numbers are large. This improvement was crucial and introduced a speedup of 14.2.

In the Pthreads version of Goldbach, the code uses static mapping with semaphores and mutexes for synchronization during printing. While a fully functional dynamic mapping version was not implemented, several improvements were made to enhance efficiency and speedup compared to both the Pthreads and Serial versions, ensuring a fair comparison of different implementations.

The same corrections as added in the serial version.

Both goldbach_even and goldbach_odd functions now limit the search space using break conditions.

Additionally, the sum and comparison logic is grouped into a single operation to simplify the program flow.

Error handling is improved, enhancing the insertion time into arr_goldbach.


## How to use
- To compile: ```make```
  
- To run 1: ```./goldbach_optimized < your_input.txt```

- To run 2: ```./goldbach_optimized``` and then enter your numbers, when you're ready, press ```CTRL+D```

- To run 3 (pthread): ```./goldbach_optimized (num of threads) < your_input.txt```


- Note: If you want to show the sums, you can enter the number in negative: ```-21```

- If you need help: ```./goldbach_optimized --help```

## Notes
- It's important to note that if you don't provide an input.txt file and prefer to enter numbers one by one, you'll need to press ```CTRL+D``` to initiate the calculation process.

- The ```--help``` flag is the only option available. Entering --help will display information on how to use the program, and the execution will proceed as usual. If you enter any other flag, the program will notify you that the flag is invalid and continue execution.

- If you enter a number from 0 to 5 will always print NA.

- Negative numbers will display the sums.

## Credits
- In this section, I would like to acknowledge that Jeisson Hidalgo's videos were instrumental in adding robustness to my program. The implementation of arrays was made possible thanks to the tutorials from "Taller de C++ a C". https://jeisson.ecci.ucr.ac.cr/concurrente/2022b/#c_workshop. 

- I would also like to thank Professor Alberto Rojas' videos on "Arrays of Arrays." the videos helped me understand the creation of UML diagrams for this project. :)

- I would also like to bookmark and recommend this webpage about Trial Division. It provides various ways to implement this method and helped me program this algorithm. It would also be useful for a more efficient implementation in the future. https://literateprograms.org/trial_division__c_.html