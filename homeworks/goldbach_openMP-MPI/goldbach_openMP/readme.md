# Golbach_openMP
- Author: Juan Diego Soto Castro, C07722.
- E-mail: ```juan.sotocastro@ucr.ac.cr```

## Summary
This C program calculates Goldbach sums for a list of integer numbers provided via standard input. The Goldbach conjecture states that every even integer greater than 5 can be expressed as the sum of two prime numbers, and every odd integer greater than 5 can be expressed as the sum of three prime numbers.

Features
- Calculates Goldbach sums for both even and odd numbers.
- Handles negative input numbers by calculating sums for their absolute values.
- Uses OpenMP for parallel computation to improve performance over a serial implementation.
- Prints the total count of Goldbach sums for each input number.
- Lists all Goldbach sums for negative numbers.

## Analysis
To create a program that calculates the Goldbach sums, the first step is to generate prime numbers. There are many methods for doing this; the Sieve of Eratosthenes and Trial Division are the most popular methods for generating large sets of prime numbers. While there are numerous variations of these two methods, this program employs the classic Trial Division approach. However, it's worth noting that there are various adaptations of these methods that can enhance performance and may be incorporated into the program in the future.

Furthermore, when computing Goldbach's sums, the task will be divided into two functions. One function will be responsible for calculating Goldbach sums for even numbers, while the other will handle sums for odd numbers. To find the sums, both methods employ brute force algorithms. Additionally, utilizing more efficient algorithms in terms of time, space and complexity, such as a backtracking algorithm, can lead to improved runtime. Also, it's worth noting that in the future, parallelizing these two tasks could lead to a significant performance improvement.

## How to use
- To compile: ```make```

- To run 1: ```./golbach_openMP < your_input.txt```

- To run 2: ```./golbach_openMP``` and then enter your numbers, when you're ready, press ```CTRL+D```

- Note: If you want to show the sums, you can enter the number in negative: ```-21```

- If you need help: ```./golbach_openMP --help```

## Notes
- It's important to note that if you don't provide an input.txt file and prefer to enter numbers one by one, you'll need to press ```CTRL+D``` to initiate the calculation process.

- The ```--help``` flag is the only option available. Entering --help will display information on how to use the program, and the execution will proceed as usual. If you enter any other flag, the program will notify you that the flag is invalid and continue execution.

- If you enter a number from 0 to 5 will always print NA.

- Negative numbers will display the sums.

## Credits
- In this section, I would like to acknowledge that Jeisson Hidalgo's videos were instrumental in adding robustness to my program. The implementation of arrays was made possible thanks to the tutorials from "Taller de C++ a C". https://jeisson.ecci.ucr.ac.cr/concurrente/2022b/#c_workshop. 

- I would also like to thank Professor Alberto Rojas' videos on "Arrays of Arrays." the videos helped me understand the creation of UML diagrams for this project. :)

- I would also like to bookmark and recommend this webpage about Trial Division. It provides various ways to implement this method and helped me program this algorithm. It would also be useful for a more efficient implementation in the future. https://literateprograms.org/trial_division__c_.html