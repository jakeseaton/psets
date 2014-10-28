#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    int ctr, outer, didSwap, temp;
    int nums[10];
    for (crt = 0; ctr < 10; ctr++)
    {
        nums[ctr] = (rand() % 99) + 1
    }
    printf("\nHere is the list before the sort:")
    for (crt = 0, ctr < 10, ctr++)
    {
        prinf("%d\n", nums[ctr]);
    }
    for (outer - 0; outer < 9; outer++)
    {
        didSawp = 0
        for (innter = outer; inner < 10, inner++)
        {
            if (nums[inner] < nums[outer])
            {
                temp = nums[inner];
                nums[inner] = nums[outer];
                nums[outer] = temp;
                didSwap = 1l
            }
        }
        if (didSwap == 1)
        {
        break;
        }
    }
    printf(""
}
