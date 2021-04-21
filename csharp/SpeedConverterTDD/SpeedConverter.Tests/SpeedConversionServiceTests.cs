using SpeedConverter.Code;
using System;
using Xunit;

namespace SpeedConverter.Tests
{
    public class SpeedConversionServiceTests : IDisposable
    {
        private SpeedConversionService speedConverter;

        //setup
        public SpeedConversionServiceTests()
        {
            speedConverter = new SpeedConversionService();
        }

        //using [Theory] attribute to run a set of tests
        [Theory]
        [InlineData(0, 0)]
        [InlineData(10, 6)]
        [InlineData(11, 7)]
        [InlineData(20, 12)]
        public void ConvertToMilesPerHour_Input_Expected(int input, int expected)
        {
            //arrange
            //via constructor

            //act
            var result = speedConverter.ConvertToMilesPerHour(input);

            //assert
            Assert.Equal(expected, result);
        }

        /* --- running each test individually ---
        [Fact]
        public void ConvertToMilesPerHour_0_0()
        {
            //arrange - using setup
            //var speedConverter = new SpeedConversionService();

            //act
            var milesPerHour = speedConverter.ConvertToMilesPerHour(0);

            //assert
            Assert.Equal(0, milesPerHour);
        }

        [Fact]
        public void ConvertToMilesPerHour_10_6()
        {
            //arrange - using setup
            //var speedConverter = new SpeedConversionService();

            //act
            var milesPerHour = speedConverter.ConvertToMilesPerHour(10);

            //assert
            Assert.Equal(6, milesPerHour);
        }

        [Fact]
        public void ConvertToMilesPerHour_11_7()
        {
            //arrange - using setup
            //var speedConverter = new SpeedConversionService();

            //act
            var milesPerHour = speedConverter.ConvertToMilesPerHour(11);

            //assert
            Assert.Equal(7, milesPerHour);
        }
        */

        //teardown 
        public void Dispose()
        {
            //no-op
        }
    }
}
