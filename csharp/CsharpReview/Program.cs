using System;

namespace CsharpReview
{
    class Topic
    {
        public void HelloWorld()
        {
            Console.WriteLine("Hello World!");
        }

        public void GetUserInput()
        {
            Console.WriteLine("What is your name?");
            string name = Console.ReadLine();
            Console.WriteLine(">>>>>your name is:" + name);
        }

        public void TestStrings()
        {
            string s1 = "12345ABCDEFGaaaaabbbbb";
            Console.WriteLine(">>>>>s1=" + s1);
            Console.WriteLine(">>>>>s1.Length=" + s1.Length);

            s1.ToUpper();
            Console.WriteLine(">>>>>s1.ToUpper()=" + s1.ToUpper());

            var s2 = s1.Substring(5);
            Console.WriteLine(">>>>>s1.Substring(5)=" + s1.Substring(5));
        }

        public void TestArrays()
        {
            string[] cars = { "Volvo", "BMW", "Ford", "Mazda" };

            Console.WriteLine(">>>>>cars=");
            foreach (var car in cars)
            {
                Console.Write(car + " ");
            }
        }

    }//class - end !

    /*
        Procedural programming is about writing procedures or methods 
        that perform operations on the data, while object-oriented 
        programming is about creating objects that contain both data 
        and methods.

    Access modifiers ->used to set access level/visibility for classes,
                       fields, methods and properties
    Modifier 	Description
    public 	    The code is accessible for all classes
    private 	The code is only accessible within the same class
    protected 	The code is accessible within the same class, or 
                in a class that is inherited from that class. 
    internal 	The code is only accessible within its own assembly,
                but not from another assembly. 
    (*) Default access modifiers:
        for classes         ->  is Internal
        for class members   -> private

    */

    class Program
    {
        static void Main(string[] args)
        {
            Topic t = new Topic();

            Console.WriteLine("__________________________________");
            t.HelloWorld();

            //Console.WriteLine("__________________________________");
            //t.GetUserInput();

            Console.WriteLine("__________________________________");
            t.TestStrings();

            Console.WriteLine("__________________________________");
            t.TestArrays();

            Console.WriteLine();
            Console.WriteLine();


        }
    }

}
