// (Constraint 1) 1! (팩토리얼)부터 20!까지의 숫자를 계산한다. 여기서, 정수 n 에 대해 n!을 계산하는
// 수식은 다음과 같다. Calculates a number from 1! (factorial) to 20!. The formula for calculating the n! for
// an integer n is as follows:
// 1! = 1
// n! = n * (n-1)! if n > 1
// (Constraint 2) 다음 형식으로 출력한다. The output format is as follow:
//                    1 =  1!
//                    2 =  2!
//                    6 =  3!
//                   24 =  4!
//                  120 =  5!
//                  720 =  6!
//                 5040 =  7!
//                40320 =  8!
//               362880 =  9!
//              3628800 = 10!
//             39916800 = 11!
//            479001600 = 12!
//           6227020800 = 13!
//          87178291200 = 14!
//        1307674368000 = 15!
//       20922789888000 = 16!
//      355687428096000 = 17!
//     6402373705728000 = 18!
//   121645100408832000 = 19!
//  2432902008176640000 = 20!

#include <stdio.h>

int main()
{
    const int max = 20;
    long int factorial = 1;

    for (int i = 1; i <= max; i++)
    {
        factorial *= i;
        printf("%20ld = %2d!\n", factorial, i);
    }
}
