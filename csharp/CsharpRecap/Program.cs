using System;

/*
    -C# is designed for Common Language Infrastructure (CLI), which consists of the executable 
     code and runtime environment that allows use of various high-level languages on different 
     computer platforms and architectures.

    The following reasons make C# a widely used professional language −
    It is a modern, general-purpose programming language
    It is object oriented.
    It is component oriented.
    It is easy to learn.
    It is a structured language.
    It produces efficient programs.
    It can be compiled on a variety of computer platforms.
    It is a part of .Net Framework.

    Several C# features help create robust and durable applications:
    -Garbage collection automatically reclaims memory occupied by unreachable unused objects
    - Language Integrated Query (LINQ) syntax creates a common pattern for working with data from any source
    - Language support for asynchronous operations provides syntax for building distributed systems

    -C# programs run on .NET, a virtual execution system called the common language runtime (CLR) 
     and a set of class libraries
    -Source code written in C# is compiled into an intermediate language (IL) that conforms to 
     the CLI specification*
     (*) common language infrastructure (CLI), an international standard
         The CLI is the basis for creating execution and development environments in which 
         languages and libraries work together seamlessly.

    -When the C# program is executed:
     ..the assembly is loaded into the CLR. 
     ..The CLR performs Just-In-Time (JIT) compilation to convert the IL code to native machine 
       instructions. 
     ..The CLR provides other services related to automatic garbage collection, 
       exception handling, and resource management. 
     ..Code that's executed by the CLR is sometimes referred to as "managed code," in contrast 
       to "unmanaged code," which is compiled into native machine language 
       that targets a specific platform.
    
    -Language interoperability is a key feature of .NET:
     ..IL code produced by the C# compiler conforms to the Common Type Specification (CTS)
     ..IL code generated from C# can interact with code that was generated from the .NET 
       versions of F#, Visual Basic, C++, or any of more than 20 other CTS-compliant languages
     ..A single assembly may contain multiple modules written in different .NET languages

    -In addition to the run time services, .NET also includes extensive libraries:
     ..they support different workloads. 
     ..are organized into namespaces & provide a variety of functionality -> 
       from file input/output, string manipulation, XML parsing, web application 
       frameworks, Windows Forms controls. 
     ..A typical C# application uses the .NET class library extensively 
       to handle common "plumbing" chores.
*/

namespace MyNameSpace
{
    class Program
    { 
        static void HelloWorld()
        {
            Console.WriteLine("Hello, World");
        }
        static void Main(string[] args)
        {
            Console.WriteLine("__________________________________");
            HelloWorld();

            Console.ReadKey();
        }

    }
}

