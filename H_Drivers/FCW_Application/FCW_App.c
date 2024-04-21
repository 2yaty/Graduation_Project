#include "FCW_App.h"
#include <math.h>
#include <stdint.h>

#define MAX_TIME_IN_SEC   100


/**
 * @Function Name: FCW_u8TimeToCollision
 *
 * @Description: This function calculates the time that the car model will take to reach an object
 *               using the 2nd motion equation.
 *
 * @Arguments:
 * 			  Speed , Distance , Acc :
 * 			  Takes the car speed, car acceleration, and the distance of the lidar
 * 			  between the car and the detected object.
 *
 * @Return:
 * 			float : The calculated time in seconds.
 **/
static float FCW_u8TimeToCollision(uint8_t Copy_u8Speed , float Copy_u8Distance , float Copy_u8AccX);

/**
 * @Function Name: FCW_tenuIsWarning
 *
 * @Description: This function decides if there is a warning or not according to
 * 				 the given time.
 *
 * @Arguments:
 * 			  Calculated time :
 * 			  takes the calculated time from FCW_u8TimeToCollision to decide a warning or not.
 *
 * @Return:
 * 			tenuErrorStatus : Returns an error status that indicates if this function decided a warning or not.
 **/
static tenuErrorStatus FCW_tenuIsWarning(float Copy_u8CalculatedTime);





/**
 * @Function Name: FCW_Task
 *
 * @Description: This task alerts the driver whenever there is an object
 * 				 in the front of the car.
 *
 * @Arguments:
 * 			  void :  takes nothing.
 * @Return:
 * 			void : Returns nothing.
 **/
void FCW_Task(void)
{

}





float FCW_u8TimeToCollision(uint8_t Copy_u8Speed, float Copy_u8Distance, float Copy_u8AccX)
{
	/*
	 * The second motion equation :
	 * 0.5at^2 + vt - s = 0 --> AccX(a) , calculated time (t) , speed(v), distance(s)
	 * */
    if (Copy_u8AccX == 0.0f)
    {
        // If acceleration is zero, use the simple time formula: distance / speed
        if (Copy_u8Speed == 0)
        {
            return MAX_TIME_IN_SEC ; // No movement; time to collision is infinite
        }
        else
        {
            return (Copy_u8Distance / Copy_u8Speed);
        }
    }

    // Use the quadratic formula to get the time to collision
    float discriminant = (Copy_u8Speed * Copy_u8Speed) - (4 * Copy_u8AccX * Copy_u8Distance);

    if (discriminant < 0.0f)
    {
        // Negative discriminant indicates no real solutions; no collision likely
        return MAX_TIME_IN_SEC;
    }

    // Compute both possible solutions using the quadratic formula
    float t1 = (-Copy_u8Speed + sqrt(discriminant)) / Copy_u8AccX;
    float t2 = (-Copy_u8Speed - sqrt(discriminant)) / Copy_u8AccX;

    // Return the positive solution, if exists
    if (t1 > 0.0f)
    {
        return t1;
    }
    else if (t2 > 0.0f)
    {
        return t2;
    }
    else
    {
        // Both solutions are negative; implies collision has occurred or will not happen
        return MAX_TIME_IN_SEC;
    }
}







tenuErrorStatus FCW_tenuIsWarning(float Copy_u8CalculatedTime)
{
    // Threshold time for warning in seconds
	tenuErrorStatus Loc_tenuReturned ;
    const float thresholdTime = 3.0f;

    if (Copy_u8CalculatedTime <= thresholdTime)
    {
        // If the calculated time is less than or equal to the threshold, collision is likely
    	Loc_tenuReturned = E_NOK ;
    }
    else
    {
        // If the calculated time is greater than the threshold, no imminent collision
    	Loc_tenuReturned = E_OK ;
    }
    return Loc_tenuReturned;
}































