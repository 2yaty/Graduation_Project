#include "FCW_App.h"
#include <math.h>
#include <stdint.h>

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
float FCW_u8TimeToCollision(uint8_t Copy_u8Speed, float Copy_u8Distance, float Copy_u8AccX)
{
	/*
	 * The second motion equation :
	 * 0.5at^2 + vt - s = 0 --> AccX(a) , calculated time (t) , speed(v), distance(s)
	 * */
    if(Copy_u8AccX < 0.01f)
    {
        // If acceleration is zero, use the simple time formula: distance / speed
        if(Copy_u8Speed == 0)
        {
            return MAX_TIME_IN_SEC ; // No movement; time to collision is infinite
        }
        else
        {
            return (Copy_u8Distance / Copy_u8Speed);
        }
    }

    /*
     * 0.5at^2 + vt - s = 0
     * a = 0.5a
     * b = v
     * c = -s
     */
    // Use the quadratic formula to get the time to collision
    float discriminant = (Copy_u8Speed * Copy_u8Speed) + (2 * Copy_u8AccX * Copy_u8Distance);

    if(discriminant < 0.0f)
    {
        // Negative discriminant indicates no real solutions; no collision likely
        return MAX_TIME_IN_SEC;
    }

    // Compute both possible solutions using the quadratic formula
    float t1 = (-Copy_u8Speed + sqrt(discriminant)) / Copy_u8AccX;
    //float t2 = (-Copy_u8Speed - sqrt(discriminant)) / Copy_u8AccX;

    // Return the positive solution, if exists
    if(t1 > 0.0f)
    {
        return t1;
    }
    /*
    else if (t2 > 0.0f)
    {
        return t2;
    }
    */
    else
    {
        // the solution is negative; implies collision has occurred or will not happen
        return MAX_TIME_IN_SEC;
    }
}


/**
 * @Function Name: FCW_enuIsWarning
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
enum_FC_Warnings_t FCW_enuIsWarning(float Copy_u8CalculatedTime)
{
    // Threshold time for warning in seconds
	enum_FC_Warnings_t Loc_enuReturWarning ;

    if(Copy_u8CalculatedTime >= LOW_WARNING_TH_TIME)
    {
        // If the calculated time is greater than or equal to the highest threshold time , NO COLLISION --- time >= 3 sec
    	Loc_enuReturWarning = No_Warning ;
    }
    else if((Copy_u8CalculatedTime < LOW_WARNING_TH_TIME) && (Copy_u8CalculatedTime >= MID_WARNING_TH_TIME)) 
    {
        /* If the calculated time is greater than the Mid threshold time and less than the highest threshold time 
        , Low level warning --- time ~ 2:3 sec */
    	Loc_enuReturWarning = Low_Warning ;
    }
    else if((Copy_u8CalculatedTime < MID_WARNING_TH_TIME) && (Copy_u8CalculatedTime >= HIGH_WARNING_TH_TIME)) 
    {
        /* If the calculated time is greater than the lowest threshold time and less than the mid threshold time 
        , Mid level warning --- time ~ 1:2 sec */
    	Loc_enuReturWarning = Middle_Warning ;
    }
    else if((Copy_u8CalculatedTime < HIGH_WARNING_TH_TIME) ) 
    {
        /* If the calculated time is less than the highest threshold time 
        , Low level warning --- time < 1 sec */
    	Loc_enuReturWarning = High_Warning ;
    }
    return Loc_enuReturWarning ;
}
