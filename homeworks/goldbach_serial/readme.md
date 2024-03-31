# Golbach_Serial
- Author: Juan Diego Soto Castro, C07722.
- E-mail: ```juan.sotocastro@ucr.ac.cr```

## Summary
This C program calculates Goldbach sums for a list of integer numbers provided via standard input. The Goldbach conjecture states that every even integer greater than 5 can be expressed as the sum of two prime for the even numbers or sum of three numbers if the number is odd.

The program sequentially processes each input number, finding all possible Goldbach sums and showing the total of sums. 

Additionally, the program prints a list of the input numbers along with the count of Goldbach sums for each number. If a negative number is entered, the program lists all Goldbach sums for the corresponding positive number.

## Analysis
To create a program that calculates the Goldbach sums, the first step is to generate prime numbers. There are many methods for doing this; the Sieve of Eratosthenes and Trial Division are the most popular methods for generating large sets of prime numbers. While there are numerous variations of these two methods, this program employs the classic Trial Division approach. However, it's worth noting that there are various adaptations of these methods that can enhance performance and may be incorporated into the program in the future.

Furthermore, when computing Goldbach's sums, the task will be divided into two functions. One function will be responsible for calculating Goldbach sums for even numbers, while the other will handle sums for odd numbers. It's worth noting that in the future, parallelizing these two tasks could lead to a significant performance improvement.

## How to use
- To compile: ```make```

- To run 1: ```./golbach_serial < your_input.txt```

- To run 2: ```./golbach_serial``` and then enter your numbers, when you're ready, press ```CTRL+D```

- Note: If you want to show the sums, you can enter the number in negative: ```-21```

- If you need help: ```./golbach_serial --help```

## Notes
- Is important to remark, if you don't bring an input.txt and you want to enter the numbers one by one, you need to press ```CTRL+D``` to start the calculation.

## Credits

