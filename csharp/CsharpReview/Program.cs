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

        /*
            --- variables ---
            categories: Value types, Reference types, Pointer types

            value types:
                ..can be assigned a value directly
                ..They are derived from the class System.ValueType.
                ..The value types directly contain data. 
                  Some examples are int, char, and float

            reference type:
                ..do not contain the actual data stored in a variable
                ..they contain a reference to the variables
                ..they refer to a memory location
                ..Using multiple variables, the reference types can refer to a memory location
                  If the data in the memory location is changed by one of the variables, the other variables 
                  automatically reflects this change in value. 
                ..Example of built-in reference types are: object, dynamic, and string.
                  (*) The Object Type is the ultimate base class for all data types in C# Common Type System (CTS). 
                      Object is an alias for System.Object class

                  (**) Object + convertion:
                       ..boxing   -> a value type is converted to object type
                       ..unboxing -> when an object type is converted to a value type, it is called unboxing.
                       ..E.g.:
                         the integer variable i is boxed and assigned to object o.
                         int i = 123;
                         object o = i;  // boxing

                        ..unboxing:
                          o = 123;
                          i = (int)o;  // unboxing

            -string is an alias for global::System.String, and object for global::System.Object
        
        */

        public void Variables()
        {
            // use sizeof to get the size of a variable; e.g.:
            Console.WriteLine(">>>>Size of int={0}", sizeof(int));

            //boxing
            int i = 123;
            Object o = i;
            Console.WriteLine(">>>>Type of o={0}", o.GetType());

            //unboxing
            int ii = (int)i;
            Console.WriteLine(">>>>Type of ii={0}", ii.GetType());
        }

    }//class - end !

    /*
     
    --- OOP ---
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

    -Fields:
     ..are declared in the class block by specifying the access level of the field
       are normal variables (members)  of a class; e.g.: _id, _name - below
     ..can be marked as public, private, protected, internal, protected internal, or private protected, STATIC
     ..readonly field:
       can only be assigned a value during initialization or in a constructor. 
       A static readonly field -> is very similar to a constant
     ..Generally, you should declare your fields as private, then provide properties/accessors
       for get & set operations(*)
       (*) since having public members violates the Encapsulation concept in OOP.
     ..A private field that stores the data exposed by a public property is called 
       a backing store or backing field.
     ..Fields are initialized immediately before the constructor; if the constructor assigns the value 
       of a field, it will overwrite any value given during field declaration.

    -Properties:
     ..is a member that provides a flexible mechanism to read, write, or compute the value of a private field
     ..can be used as if they are public data members, but they are actually special methods called accessors
     ..get property accessor is used to return the property value, and a set property accessor is used to assign a new value. 
    ..Properties can be:
      read-write -> they have both, a get and a set accessor
      read-only  -> they have a get accessor but no set accessor
      write-only -> they have a set accessor, but no get accessor
      (*) Write-only properties are rare and are most commonly used to restrict access 
      to sensitive data.
     ..used for indirect access to internal fields & guard against invalid input values
     ..They are actually special methods called “accessors”
     ..they offer a way to get and set a field (when you have a private field).
     ..They have two codes inside; set{}; and get{}; called “property accessors”.
     ..In Java, We declare getters and setters methods -> in C# we can define property for each field.

    -Auto-implemented properties for trivial get and set:
     ..Trivial properties, that include NO logic but ONLY setting and getting a backing field 
       should be converted to auto-implemented properties, yielding cleaner and more readable code.


    */
    public class Student
    {
        private int _age;
        //private string _name; -> NO NEED has a auto property (creates anonymous field) !!!
        
        // this is NOT a trivial property (having just simple get/set), has additional logic
        // so, this is OK - generate get + set properties
        public int Age
        {
            get { return _age; }
            set 
            {
                if (value > 0)
                    _age = value;
                else
                    throw new ArgumentException(String.Format("{0} is not a valid age", value), "age");
            }
        }

        // Auto-implemented properties for trivial get and set
        public string Name { get; set; }

        public string AsString()
        {
            string res = ">>>>>Student -> name=" + Name + "; Age=" + Age;
            return res;
        }
    }


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

            Console.WriteLine("__________________________________");
            t.Variables();

            Console.WriteLine("__________________________________");
            Student s = new Student();
            s.Name = "Antonio";
            s.Age = 20;
            Console.WriteLine(s.AsString());


            Console.WriteLine();
            Console.WriteLine();
        }
    }

}
