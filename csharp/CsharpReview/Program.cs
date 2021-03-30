using System;

namespace CsharpReview
{
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

        -nullable types:
         ..you can assign normal range of values as well as null values
           e.g.: 
           you can store any value from -2,147,483,648 to 2,147,483,647 or null in a Nullable<Int32> variable. 
           you can assign true, false, or null in a Nullable<bool> variable. 
         ..Syntax for declaring a nullable type:
           < data_type> ? <variable_name> = null;
           e.g.: double? num4 = 3.14157;
        ..The Null Coalescing Operator (??) -> used with the nullable value types and reference types
          If the value of the first operand is null, then the operator returns the value of the second operand, 
          otherwise it returns the value of the first operand; e.g.:
          double? num1 = null;
          double? num2 = 3.14157;
          double num3;
            num3 = num1 ?? 5.34;   // after execution, num3 = 5.34 as num1 IS null !!!
            num3 = num2 ?? 5.34;   // after execution, num3 = 3.14157, as num2 IS NOT null
    */

    class General
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

    }//class General - end !

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

    -structures:
     ..In C#, a structure is a value type data type.
     ..All structs are implicitly sealed -> To prevent unintended derivation
     ..Structures are used to represent a record. 
       Suppose you want to keep track of your books in a library. 
       You might want to track the following attributes about each book:
       Title, Author, Subject, Book ID

    -Class versus Structure:
    ..Classes and Structures have the following basic differences −
      classes are reference types and structs are value types
      structures do not support inheritance
      structures cannot have default constructor

    -Function Overloading
     ..multiple definitions for the same function name in the same scope. 
     ..they must differ from each other by:
       -the types and/or the number of arguments
       -you CANNOT overload function that DIFFER ONLY BY THE RETURN TYPE.

    -Polymorphism:
     ..The word polymorphism means having many forms. 
     ..In object-oriented programming paradigm, polymorphism is often expressed as 'one interface, 
       multiple functions'.
     ..Polymorphism can be static or dynamic. 
     ..static polymorphism:
       the response (decision which function to use)  to a function is determined 
        at compile time; e.g. via function overloading
     ..dynamic polymorphism:
       -also referred to as run-time or late binding polymorphism because of the decision about which method is 
        to be called is made at run time
       -we override the base class method in derived class using inheritance, and this can be 
        achieved using override and virtual keywords
        (*) overriding -> using the same method name and signature
       -Dynamic polymorphism is implemented by abstract classes and virtual functions.

    -Polymorhism (cont.):
    ..promotes extensibility
    ..sw that invokes polymorphic behaviour is independent of the
      the object types to which messages are sent
    ..New object types that can respond to existing method calls
      can be incorporated into a system without requiring modification
      of the polymorphic system logic
    ..only client code that instantiates new objects must be modified
      to accomodate new types.

       -Abstract classes in C# 
        ..are used to provide partial class implementation of an interface. 
        ..Implementation is completed when a derived class inherits from it. 
        ..Abstract classes contain abstract methods, which are implemented by the derived class. 
        ..The derived classes have more specialized functionality.
    
       -Abstract classes - rules:
        ..You cannot create an instance of an abstract class
        ..You cannot declare an abstract method outside an abstract class
        ..When a class is declared sealed, it cannot be inherited, abstract classes 
          cannot be declared sealed.

       -virtual functions:
        ..When you have a function defined in a class that you want to be implemented in an inherited class(es), 
          you use virtual functions.
        ..can be implemented differently in different inherited class, and the call to these functions will be 
          decided at runtime.
        ..Dynamic polymorphism is implemented by abstract classes and virtual functions.
        (*) A base-class variable that contains a reference
            to a derived-class object and is used to call a
            VIRTUAL method, actually calls the overriding
            derived-class version of the method.

        -Abstract Classes and Methods Abstract class: 
        a) abstract classes
           ..Abstract base classes are too general to create real objects—they
             specify only what is common among derived classes.
             (*) Concrete classes provide the specifics that make it reasonable 
                 to instantiate objects.
           ..Intended to be used as a base class
           ..The abstract modifier indicates that the thing being modified has a missing or 
             incomplete implementation -> Members marked as abstract, or included in an abstract class, 
             must be implemented by the derived classes.
           ..is a restricted class that cannot be used to create objects (instantiated) 
           ..to access it, it must be inherited from another class.
           ..Use the abstract modifier in a class declaration to indicate that a class is 
             intended only to be a base class of other classes, not instantiated on its own
           ..Sealed:
             It is not possible to modify an abstract class with the sealed modifier because the 
             two modifers have opposite meanings:
             -sealed modifier -> prevents a class from being inherited
             -abstract modifier -> requires a class to be inherited (+ derived classes implement abstract methods)
            ..We can use abstract base classes to declare variables that can hold references to objects of 
              any concrete classes derived from those abstract classes.
              You can use such variables to manipulate derived‐class objects polymorphically, and to invoke 
              static methods declared in those abstract base classes.


        b)Abstract method: 
          ..can only be used in an abstract class, and it does not have a body. 
          ..An abstract method is implicitly a virtual method.
          ..The body is provided by the derived class (inherited from) - using override keyword !
          e.g.:
	        public abstract class Shape
    	    {...
        	   public abstract double Area();
             ...
            }
         
        -Abstract & virtual methods:
         a) abstract methods:
            ..do not provide an implementation and force the derived classes to override the method. 
            ..they have NO CODE inside it, and subclasses HAVE TO override the method
            ..they must be declared inside an ABSTRACT CLASS
              e.g.:
              public abstract double Area();

         b) virtual methods:
            ..Virtual methods have an implementation and provide the derived classes 
              with the option of overriding it. Abstract methods do not provide an implementation and force the derived classes to override the method. So, abstract methods have no actual code in them, and subclasses HAVE TO override the method
        
        -A sealed class cannot be used as a base class. 
         For this reason, it cannot also be an abstract class

        -Interfaces:
         ..An interface defines a contract. 
         ..Any class or struct that implements that contract must provide an implementation 
           of the members defined in the interface.
         ..An interface may not declare instance data such as fields, auto-implemented properties, 
           or property-like events.
         ..An interface may define static methods, which must have an implementation
         ..Beginning with C# 8.0, an interface may define a default implementation for members
         ..C# because the language doesn't support multiple inheritance of classes -> use Interfaces
           to include behaviour from multiple sources
         ..you must use an interface if you want to simulate inheritance for structs, 
           because they can't actually inherit from another struct or class.
         ..A class or struct can implement multiple interfaces, but a class can 
           only inherit from a single class.
         ..Interface members are public by default
           -you can explicitly specify accessibility modifiers, such as public, protected, internal, 
            private, protected internal, or private protected. 
           -A private member must have a default implementation.
         ..When a class or struct implements an interface, the class or struct must provide an 
           implementation for all of the members that the interface declares 
           but doesn't provide a default implementation for
         ..A class that implements an interface but does not implement all its members is an abstract class
           and it must be declared abstract and must contain an abstract declaration for each unimplemented 
           member of the interface.
         ..An interface is typically used when unrelated classes need to share common methods,  so that they 
           can be processed polymorphically
           You can create an interface that describes the desired functionality, then implement this interface 
           in any classes requiring that functionality.
         ..An interface often is used in place of an abstract class when there is no default implementation 
          to inherit —> that is, no fields and no default method implementations.
         ..Is a C# construct with all abstract functions(implicitly) and no data members. 
         ..Its purpose is to establish a contract for services that can be implemented
           by any concrete derived class.
           e.g:
            public interface IDelete
            {
                void Delete();
            }

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

        //--- static polymorphism - execution decision via overload and at compilation time ---
        public void print(int val) { Console.WriteLine(">>>>>val=" + val); }
        public void print(double val) { Console.WriteLine(">>>>>val=" + val); }
    }

    public abstract class Shape
    {
        protected int width, height;

        public Shape(int w = 0, int h = 0)
        {
            width = w;
            height = h;
        }

        public abstract double Area();
    }

    public class Rectangle : Shape
    {
        public Rectangle(int w, int h) : base(w,h)
        {
            Console.WriteLine(">>>>>in Rectangle.Rectangle - width={0} ; height={1}",width, height);
        }

        public override double Area()
        {
            Console.WriteLine(">>>>>in Rectangle.Area - width={0} ; height={1}", width, height);

            double area = (width * height) / 2;

            Console.WriteLine(">>>>>in Rectangle.Area - area={0}", area);

            return area;
        }
    }

    //--- Interface---
    public interface IDelete
    {
        void Delete();
    }
    public class TextBox : IDelete
    {
        public void Delete()
        {
            Console.WriteLine(">>>>>in TextBox.Delete() !!!");
        }
    }
    public class Car : IDelete
    {
        public void Delete()
        {
            Console.WriteLine(">>>>>in Car.Delete() !!!");
        }
    }

    /*
    // SOLID PRINCIPLES:
        -SOLID is an acronym for 5 important design principles when doing OOP (Object Oriented Programming).
        -intention of these principles -> to make your code easier to extend, to understand, to maintain.

        Single responsibility principle
            ..A class should have only one reason to change
            ..Strive for cohesion
            ..Do one thing and do it well
            ..responsibility = ‘reason to change’ -> a class/module should have one, and only one, reason to be changed.

        Open/closed principle
            ..Classes should be open for extension, but closed for modification
            ..Design modules that never change

        Liskov substitution principle
            ..Derived classes must be substitutable/switchable for their base classes
            ..The base class should not have to know about all of its derivatives

        Interface segregation principle
            ..Clients should not be forced to depend upon interface that they do not use
            ..no client should be forced to depend on methods it does not use
            ..We don't want "fat" or "polluted" interfaces
              (*) Interfaces that are not specific to a single client leads to unnecessary coupling
                  between clients that would otherwise be isolated
            ..Put more simply: Do not add additional functionality to an existing interface by 
              adding new methods -> Instead, create a new interface and let your class implement 
              multiple interfaces if needed

        Dependency inversion principle
            ..Depend on abstractions. Do not depend upon concrete classes
            ..High-level components should not depend on low-level components, both should depend 
              on abstractions
              (*) Abstract classes should not depend upon concrete classes & vice-versa
            ..is a way to decouple software modules.
            ..High-level modules should not depend on low-level modules. Both should depend on abstractions.
            ..Abstractions should not depend on details. Details should depend on abstractions
            ..we need to use: design pattern known as a dependency inversion pattern -> aka dependency injection.
              (*) Typically, dependency injection is used simply by ‘injecting’ any dependencies of a class 
                  through the class’ constructor as an input parameter.
    */

    //-----------------------------------------------------------------------
    class Program
    {
        static void Main(string[] args)
        {
            General g = new General();

            Console.WriteLine("__________________________________");
            g.HelloWorld();

            //Console.WriteLine("__________________________________");
            //g.GetUserInput();

            Console.WriteLine("__________________________________");
            g.TestStrings();

            Console.WriteLine("__________________________________");
            g.TestArrays();

            Console.WriteLine("__________________________________");
            g.Variables();

            Console.WriteLine("__________________________________");
            Student s = new Student();
            s.Name = "Antonio";
            s.Age = 20;
            Console.WriteLine(s.AsString());

            Console.WriteLine("__________________________________");
            //using static polymorphism
            s.print(5);
            s.print(123.45);

            Console.WriteLine("__________________________________");
            //dynamic polymorphism
            Shape sh = new Rectangle(10,20);
            Console.WriteLine("-> Area={0}", sh.Area());

            Console.WriteLine("__________________________________");
            //interfaces
            TextBox tb = new TextBox();
            IDelete iDel = tb;
            iDel.Delete();

            Car c = new Car();
            iDel = c;
            iDel.Delete();

        }
    }

}
