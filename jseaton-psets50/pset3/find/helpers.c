/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (value < 0)
    {
        return false;
    }
    // initialization
    int left = 0;
    int right = n-1;
    while (right >= left)
    {
        // General. int rounds up
        int middle = (right + left)/2;
        
        // If Middle is the Needle
        if (values[middle] == value)
        {
            return true;
        }
        // Search
        else
        {
            if (values[middle] > value)
            {
                right = middle-1;
            }
            else
            {
                left = middle+1;
            }
        }
    
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int switched = 1;
    while (switched != 0)
    {
        switched = 0;
        for (int i = 0; i < n-1; i++)
        {
            if (values[i] > values[i+1])
            {
                    int temp;
                    temp = values[i];
                    values[i] = values[i+1];
                    values[i+1] = temp;
                    switched++;
            }
        }
    }
    printf("\nSorted:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\n", values[i]);
    }
}
