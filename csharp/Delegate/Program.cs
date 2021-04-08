using System;
using System.Diagnostics;


/*
    --- DELEGATES ---
    (*) VIP: delegates - not used anymore; it is OLD STYLE - replaced by LAMBDAS !
  
    a) delegates are TYPES (as classes, interfaces, etc) 
       ..they describe a common set of functions (a set of functions that has the
         same prototype)
    b) Any lambda expression can be converted to a delegate type
       ..The delegate type to which a lambda expression can be converted is defined by the types of its parameters and return value.
       ..If a lambda expression doesn't return a value, it can be converted to one of the Action delegate types
       ..otherwise, it can be converted to one of the Func delegate types. 
       ..For example:
         -a lambda expression that has two parameters and RETURNS NO VALU can be converted 
          to an Action<T1,T2> delegate.
         -A lambda expression that has one parameter and RETURNS A VALUE can be converted to a 
          Func<T,TResult> delegate.
         -In the following example, the lambda expression x => x * x, which specifies a parameter 
          that's named x and returns the value of x squared, is assigned to a variable of a 
          delegate type:
    c) delegate int MathOp(int x, int y); 
       ..this delegate is a TYPE - I can declare variables of this type, for instance
       ..this is a type definition for a category of functions

    d) CalculateAndPrint(2, 3, delegate(int a, int b){return a + b;});
       ..this delegate is different from (c) - it allow-us to write
         an anonymous function (lambda) - name is chosen by the compiler

    d1) transforming (d1) lambda:
        CalculateAndPrint(2, 3, (int a, int b) => {return a + b;});
        (*) it is very similar tho (d) - the only differences:
            ..does not use delegate keyword
            ..use =>   (fat arrow)
            ..HAS NO NAME (is anonymous) - the compiler will define the name !

        (**) simplification-1 -> if I have a single line of code in the lambda
             from: (int a, int b) => {return a + b;}
             to: (int a, int b) => a + b
             (*) if we have multiple lines in the code, we still need all {...}

        (**) simplification-2 -> CalculateAndPrint(2, 3, a,b => a + b);
             ..no need to add the types, as the compiler can deduce them from
               the prototype of the CalculateAndPrint function:
               -3rd parameter is a delegate that has 2 ints as input !!!
        (**) Now, we have a lambda function - it is just a delegate (simplified).

    e) Ildasm.exe and Ilasm.exe
       ..Ildasm    -> The IL(intermediate language) Disassembler
        -takes a portable executable (PE) file that contains intermediate language (IL) code and 
         creates a text file suitable as input to Ilasm.exe
        -use ILDASM to disassemble assembly (either exe or dll)
        -to view the code/content of the intermediate language,  in C#.NET format
        -will generate a text file with MANIFEST
        --will allow to generate the assembly metadata and IL code (export to a text file)

       ..Ilasm.exe -> IL Assembler
        -use ILASM to reassemble assembly
        -to rebuild an assembly from IL
        -to rebuild an assembly from a text file which contains manifest and IL
        
    f) What is Manifest for assembly (*.dll or *.exe)?
       ..Manifest contains metadata about the assembly like the name of the assembly, 
         the version number of the assembly, culture, OS, and strong name information, etc.

    g) IL - intermediate language
       ..machine and platform independent 
       ..just before running, IL is transformed to executable (machine language) according 
         to the platform
       ..JIT compiler transforms C# code in IL code 

    h) generic delegate:
       delegate T CombineGeneric<T>(T a, T b);

*/
class Program
{
    //-------------------------------------------------
    delegate int MathOp(int x, int y); //(1) - this delegate is a type - I can have vars. of it

    static int add(int x1, int y1)
    {
        return x1 + y1;
    }

    static int subtract(int a, int b)
    {
        return a - b;
    }

    //passing a delegate as a parameter
    static void CalculateAndPrint(int x, int y, MathOp f )
    {
        var res = f(x, y);
        Console.WriteLine("CalculateAndPrint({0},{1})={2}; f={3}", x,y,res,f.Method.ToString());
    }

    //--------------------------------------------------
    // Delegate + Generics !!!
    delegate T CombineGeneric<T>(T a, T b);

    static double add(double x1, double y1)
    {
        return x1 + y1;
    }

    static void CalculateAndPrintGen<T>(T x, T y, CombineGeneric<T> f)
    {
        var res = f(x, y);
        Console.WriteLine("CalculateAndPrintGen({0},{1})={2}; f={3}", x, y, res, f.Method.ToString());
    }

    //--------------------------------------------------
    static void Main(string[] args)
    {
        //using the delegate
        Console.WriteLine("__________________________________________");
        Console.WriteLine(">>>>>calling delegate...");
        MathOp f = add;
        var res = f(2, 3);
        Debug.Assert(res == 5);
        Console.WriteLine("f(2+3)={0}", res);

        Console.WriteLine("__________________________________________");
        Console.WriteLine(">>>>>calling delegate...");
        f = subtract;
        res = f(100, 90);
        Debug.Assert(res == 10);
        Console.WriteLine("f(100-90)={0}", res);

        //using the CalculateAndPrint
        //using the delegate
        Console.WriteLine("__________________________________________");
        Console.WriteLine(">>>>>passing delegate as parameter...");
        f = add;
        CalculateAndPrint(2, 3, f);
        Console.WriteLine("__________________________________________");
        Console.WriteLine(">>>>>passing delegate as parameter...");
        f = subtract;
        CalculateAndPrint(100, 90, f);

        //call using the DELEGATE INLINED !
        //return type can be deduced !!!
        Console.WriteLine("__________________________________________");
        Console.WriteLine(">>>>>using delegate - inline...");
        CalculateAndPrint(2, 3, delegate(int a, int b){return a + b;});

        Console.WriteLine("__________________________________________");
        Console.WriteLine(">>>>>using delegate - inline...");
        CalculateAndPrint(100, 10, delegate (int a, int b)
            {
                return a - b;
            }
        );

        //using lambdas - to inline method to call - to define the method (delegate parameter)
        Console.WriteLine("__________________________________________");
        Console.WriteLine(">>>>>using lambdas...");
        CalculateAndPrint(2, 3, (int a, int b) => { return a + b; });

        Console.WriteLine("__________________________________________");
        Console.WriteLine(">>>>>using lambdas...");
        CalculateAndPrint(100, 90, (int a, int b) => { return a - b; });

        //using delegate + generics
        Console.WriteLine("__________________________________________");
        Console.WriteLine(">>>>>calling delegate generic...");
        CombineGeneric<int> gn = add;
        res = gn(2, 3);
        Debug.Assert(res == 5);
        Console.WriteLine("gn(2+3)={0}", res);

        Console.WriteLine("__________________________________________");
        Console.WriteLine(">>>>>calling delegate generic (double)...");
        CombineGeneric<double> gnd = add;
        double resd = gnd(2.5, 3.5);
        Console.WriteLine("gn(2.5+3.5)={0}", resd);

        Console.WriteLine("__________________________________________");
        Console.WriteLine(">>>>>using CalculateAndPrintGen<int>...");
        CalculateAndPrintGen<int>(100, 90, (a, b) => { return a + b; });

        Console.WriteLine("__________________________________________");
        Console.WriteLine(">>>>>using CalculateAndPrintGen<double>...");
        CalculateAndPrintGen<double>(10.0, 20.0, (a, b) => a + b);

        Console.WriteLine("__________________________________________");
        Console.WriteLine(">>>>>using CalculateAndPrintGen - boolean...");
        CalculateAndPrintGen(true, false, (a, b) => a && b);

    }

}


/*
namespace Delegate
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
        }
    }
}
*/
