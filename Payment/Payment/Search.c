#include "DataTypes.h"
void BubbleSort(uint32_t *array, uint8_t size)
{
  // loop to access each array element
  for (int step = 0; step < size - 1; ++step) {

    // loop to compare array elements
    for (int i = 0; i < size - step - 1; ++i) {

      // compare two adjacent elements
      // change > to < to sort in descending order
    if (array[i] > array[i + 1])
    {
        // swapping occurs if elements
        // are not in the intended order
        int temp = array[i];
        array[i] = array[i + 1];
        array[i + 1] = temp;
      }
    }
  }
}
int8_t binarySearch(uint32_t * pau32_Array,uint8_t u8_Size, uint32_t Num)
{
    uint8_t u8_start=0;
    uint8_t u8_End=u8_Size-1;
    uint8_t u8_Mid=0;

    uint8_t u8_I=0;
    for(u8_I=0;u8_I<u8_Size;u8_I++)
    {
        u8_Mid=(u8_start+u8_End)/2;
        if(pau32_Array[u8_Mid]== Num)
        {
            return  u8_Mid;
        }
        else if(pau32_Array[u8_Mid]> Num)
        {
            u8_End=u8_Mid-1;
        }
        else if(pau32_Array[u8_Mid]< Num)
        {
            u8_start=u8_Mid+1;
        }
        if(u8_End < u8_start)
        {
            return -1;
        }
        else
        {

        }

    }

}
