using System;
using System.Collections.Generic;

//--- .net5.0 & c# 9.0 ---
//    ..no need of main, classes , for short demos - called top level statements

// a) using IEnumerable
//    VIP: we can use IEnumerable because we will not change the content of the list !!!
//
// b) Pre-defined delegates - via Func
//    -Func is built-in delegate type. 
//
// Func<T,TReturn>  -> e.g.: Func<T,bool>
//  T = input parameter
//  TReturn = return value
// 
// e.g.: from: IEnumerable<T> FilterHeroesFunc<T>(IEnumerable<T> items, Filter<T> f)
//             (*) where Filter<T> -> delegate bool Filter<T>(T a);
//                 a delegate that returns a bool and has T as input
//         The corresponding pre-defined delegate:
//         to: IEnumerable<T> FilterHeroesFunc<T>(IEnumerable<T> items, Func<T,bool> f)
//
// in VS is defined as:
// -C# includes built-in generic delegate types Func and Action
//  (so that you don't need to define custom delegates manually in most cases.)
// b1) Func:
//    ..Func is a generic delegate included in the System namespace.
//    ..It has zero or more input parameters and one out parameter.
//    ..The last parameter is considered as an out parameter.
//    b11) The Func delegate that takes one input parameter and one out parameter is defined
//         in the System namespace, as shown below:
//          namespace System
//          {
//              public delegate TResult Func<in T, out TResult>(T arg);
//          }
//    b12) A Func delegate takes two input parameters of int type and returns a value
//         of int type:
//         Func<int, int, int> sum;
//         (*) A Func delegate type can include 0 to 16 input parameters of different type
//             and MUST include the out parameter.
//             e.g.: Func with Zero Input Parameter
//                   Func<int> getRandomNumber;
//
//
// c) Func + lambda expressions:
//        Func<int> getRandomNumber = () => new Random().Next(1, 100);
//        and
//        Func<int, int, int> Sum = (x, y) => x + y;
//
// d) Delegate type Action
//    Action = pre-defined delegate that receives NOTHING and returns NOTHING
//      E.g.:
//      delegate void Something(); -> the pre-defined value is:  Action Something
// 

var heroes = new List<Hero>
{
    new ( "F1", "L1", "Batman", true),
    new ( "F3", "L3", "Mandrake", false),
    new ( "F2", "L2", "Robin", true),
    new ( "F4", "L4", "Robin Hood", false),
    new ( "F5", "L5", "Superman", true),
    new ( string.Empty, string.Empty, "TESTS ONLY", false),
    new ( string.Empty, string.Empty, "TESTS ONLY 2", true)
};

List<Hero> FilterHeroesCanFly1(List<Hero> heroes )
{
    List<Hero> res = new List<Hero>();

    foreach(var hero in heroes)
    {
        if (hero.CanFly)
            res.Add(hero);
    }

    return res;
}

//using IEnumerable
//VIP: we can use IEnumerable because we will not change the content of the list !!!
IEnumerable<Hero> FilterHeroesCanFly2(IEnumerable<Hero> heroes)
{
    foreach (var hero in heroes)
    {
        if (hero.CanFly)
            yield return hero;
    }
   
}

IEnumerable<Hero> FilterHeroesFnIsEmpty(IEnumerable<Hero> heroes)
{
    foreach (var hero in heroes)
    {
        if (String.IsNullOrEmpty(hero.FirsName))
            yield return hero;
    }
}


//using all generic - method + delegate    
IEnumerable<T> FilterHeroes<T>(IEnumerable<T> items, Filter<T> f) 
{
    foreach (var item in items)
    {
        if(f(item))
            yield return item;
    }
}

//using pre-defined delegate Func (returns a bool & has T as input)
IEnumerable<T> FilterHeroesFunc<T>(IEnumerable<T> items, Func<T,bool> f)
{
    foreach (var item in items)
    {
        if (f(item))
            yield return item;
    }
}

//action delegate
void PrintMessage()
{
    Console.WriteLine(">>>>>Hello from PrintMessage");
}

bool RunPrint(Action a)
{
    a();
    return true;
}


Console.WriteLine("__________________________________________");
Console.WriteLine(">>>>>using FilterHeroesCanFly1...");
var res = FilterHeroesCanFly1(heroes);
foreach( var hero in res)
{
    Console.WriteLine($"Fn={hero.FirsName}; Ln={hero.LastName}; Name={hero.HeroName}; CanFly={hero.CanFly}");
}

Console.WriteLine("__________________________________________");
Console.WriteLine(">>>>>using FilterHeroesCanFly2...");
var res2 = FilterHeroesCanFly2(heroes);
foreach (var hero in res2)
{
    Console.WriteLine($"Fn={hero.FirsName}; Ln={hero.LastName}; Name={hero.HeroName}; CanFly={hero.CanFly}");
}

Console.WriteLine("__________________________________________");
Console.WriteLine(">>>>>using FilterHeroesFnIsEmpty...");
var res3 = FilterHeroesFnIsEmpty(heroes);
foreach (var hero in res3)
{
    Console.WriteLine($"Fn={hero.FirsName}; Ln={hero.LastName}; Name={hero.HeroName}; CanFly={hero.CanFly}");
}

//using all generic - method + delegate    
Console.WriteLine("__________________________________________");
Console.WriteLine(">>>>>using Generics: FilterHeroes + FnIsEmpty ...");
var res4 = FilterHeroes<Hero>(heroes, h => String.IsNullOrEmpty(h.FirsName));
foreach (var hero in res4)
{
    Console.WriteLine($"Fn={hero.FirsName}; Ln={hero.LastName}; Name={hero.HeroName}; CanFly={hero.CanFly}");
}

Console.WriteLine("__________________________________________");
Console.WriteLine(">>>>>using Generics: FilterHeroes + CanFly ...");
var res5 = FilterHeroes<Hero>(heroes, h => h.CanFly);
foreach (var hero in res5)
{
    Console.WriteLine($"Fn={hero.FirsName}; Ln={hero.LastName}; Name={hero.HeroName}; CanFly={hero.CanFly}");
}

//using pre-defined delegate
Console.WriteLine("__________________________________________");
Console.WriteLine(">>>>>using pre-defined delegate + CanFly ...");
var res6 = FilterHeroesFunc<Hero>(heroes, h => h.CanFly);
foreach (var hero in res6)
{
    Console.WriteLine($"Fn={hero.FirsName}; Ln={hero.LastName}; Name={hero.HeroName}; CanFly={hero.CanFly}");
}

//using Action
Console.WriteLine("__________________________________________");
Console.WriteLine(">>>>>using Action delegate...");
var res7 = RunPrint(PrintMessage);

//IEnumerable<T> Filter<T>(IEnumerable<T> items, Filter<T> f)

//--- top level definitions after ---

// new feature - record (similar to classes + with auto features)
// ..no need to add properties/fields, constructors, etc - all is done automatically
// ..this is a new type of class in .net , that saves you a lot of work
record Hero (string FirsName, string LastName, string HeroName, bool CanFly);
//I could add after the (...) a {other constructors, etc - like a regular class} 

// delegate generic
delegate bool Filter<T>(T a);
