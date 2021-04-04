using System;
using System.Collections.Generic;
using System.Text;

namespace DemoLibrary.Utilities
{
    class DILogger : IDILogger
    {
        public void Log(string message)
        {
            Console.WriteLine($"Logging { message }");
        }
    }
}
