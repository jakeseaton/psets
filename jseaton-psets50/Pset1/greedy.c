#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // Get Change
    float change;
    
    do
    {
        printf("How much change is owed?\n");
        change = GetFloat();
    }
    while (change < 0);
    
    // Round and Convert to Cents
    change = round(100 * change);
    int change1;
    change1 = (int) change;
    
    // Count Coins
    int counter = 0;
    
    // Quarters
    while (change >= 25)
    {
        change = change - 25;
        counter++;
    }
    
    // Dimes
    while (change < 25 && change >= 10)
    {
        change = change - 10;
        counter++;
    }
    
    // Nickels
    while (change < 10 && change >= 5)
    {
        change = change - 5;
        counter++;
    }
    
    // Pennies
    while (change < 5 && change > 0)
    {
        change = change - 1;
        counter++;
    }
    
    // Coins needed
    printf("%i\n", counter);
}
