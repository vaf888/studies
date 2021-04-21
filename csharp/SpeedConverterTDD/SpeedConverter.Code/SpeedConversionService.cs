using System;

namespace SpeedConverter.Code
{
    public class SpeedConversionService
    {
        public int ConvertToMilesPerHour(int kilometersPerHour)
        {
            // to make the test fail, initially
            //return -1;

            //making test pass
            //return 0;

            //if (kilometersPerHour == 10)
            //    return 6;

            //if (kilometersPerHour == 11)
            //    return 7;

            //final version
            return (int)Math.Round(kilometersPerHour * 0.62137);
        }

    }
}
