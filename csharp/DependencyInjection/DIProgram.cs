using System;
using DemoLibrary;
using Autofac;

/* dependency injection - using autofact */
/*
    Dependency Injection (DI):
    ..is a form of Inversion of control (*)
    ..is a design pattern that demonstrates how to create loosely coupled classes
    ..uses a builder object to initialize objects
    .. it allows developers to "inject" a dependency from outside the class
    ..Dependency Injection frameworks are designed to make use of DI and can define interfaces to make it easy to pass in the implementations.
       (*) Inversion of Control is a generic term:
           Rather than having the application call the methods in a framework, the framework calls 
           implementations provided by the application.
    ..DI - advantages:
      -helps class decoupling
      -DI + IoC make it simpler to manage dependencies between objects, 
      -code become more modularized, increases reusability, improves maintainability and testing.
    ..DI - downsides:
      -increases code complexity - more classes generated
      -takes a higher learning curve
      -Dependency Injection framework -> clients are dependent on the configuration data

    -Autofac - DI framework
     ..Autofac is an Inversion of Control (IOC) container for Microsoft .NET C#, versions 3.0 and above. 
       Licensed under MIT, it manages the dependencies among classes so that applications stay easy 
       to change as they grow in size and complexity.

*/

namespace DependencyInjection
{
    // we will now work on the principle of IoC - inversion of control
    // where the top level object - DIProgram - will control all
    // other dependencies
    // (dependencies provided via Autofac!!!)

    class DIProgram
    {
        //--- v1 ---
        //wire up the dependencies/container
        //via another class to setup the container !!!
        // and using Autofac
        static void Main(string[] args)
        {
            var container = DIContainerConfig.Configure();

            //typical use - only one scope in use - standard use
            using (var scope = container.BeginLifetimeScope())
            {
                // this is going to the scope(container) and getting
                // an DIApplication object
                var app = scope.Resolve<IDIApplication>();
                app.Run();
            }  
            

            Console.ReadLine();
        }

/*
        //--- inicial version: no DI used yet !!!
        static void Main(string[] args)
        {
            // no DI - using new ...
            IDIBusinessLogic businessLogic = new DIBusinessLogic();
            businessLogic.ProcessData();

            Console.ReadLine();
        }
*/

    }
}
