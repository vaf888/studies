using System;
using System.Collections.Generic;
using System.Linq;

/*
    --- LINQ ---
    
a) IEnumerable interface
   ..this is: a readonly, forward only cursor through a collection
   ..current  -> get the corrent element
   ..movenext -> go to the next element (returns NULL if no more available!)
   (*) can't go back, can't access via an index, etc
   ..Is a pull base system -> The pull-based system waits for 
     a demand to push the data streams to the requestor
     (but Observar Pattern - is the contrary - is a push based system
      subject (observable) pushes its values to observers0

    -No memory used for huge data/list - as item are processed
     one by one!
b) VIP: The call to a method that returns an IEnumerable
        IS NOT immediately executed - is delayed - only
        when I try to access the content of the result
        (e.g.: inside a foreach) - the method will be called
        using yield - to process 1 item at time

   
*/

//--------------------------------------------------
IEnumerable<int> GenerateNumbers1(int maxValue)
{
    var result = new List<int>();

    for(var i=0; i <= maxValue; i++)
    {
        result.Add(i);
    }

    //I can return a list because LIST implements IEnumerable
    return result;
}

//--------------------------------------------------
//removing list
IEnumerable<int> GenerateNumbers2(int maxValue)
{
    //This method does not generate the entire sequence, only 
    //one at time
    for (var i = 0; i <= maxValue; i++)
    {
        // yield - returns the result to caller without
        // having to create a LIST
        // returns 1 item at time
        yield return i*5;
    }
}

//--------------------------------------------------
//linq-1 -> return even numbers only
IEnumerable<int> LinqEvenNumbersOnly()
{
    var result = GenerateNumbers2(5).Where(n => n % 2 == 0);
    return result;
}

//--------------------------------------------------
//DEBUG: How IEnumerable does its processing with LINQ
void LinqHowIEnumerableLinqWorks()
{
    //VIP: GenerateNumbers2(5) was NOT CALLED here
    //     it will be called ONLY in the line below
    //     foreach (var item in result)
    //     and 1 time for each item (10 times)
    //     The call to GenerateNumbers2 occurs INSIDE
    //     the foreach loop ONLY ! (is delayed)

    //each new item received from GenerateNumbers2 - via yield
    //runs the intire pipeline(*) (before getting a new value):
    //(*) for each item got via yield:
    //(1) ..runs the where
    //..runs the select
    //..return value after call in foreach
    //..write item
    //..RETURNS BACK AFTER the yield (inside for loop) - to get next value
    //..and process it (1)

    // ---normal version---
    //var result = GenerateNumbers2(5)
    //    .Where(n => n % 2 == 0)
    //    .Select(n =>  n * 3); // PROJECTION

    // ---for debug only - expanded lambdas ---
    var result = GenerateNumbers2(5)
        .Where(n =>
            {
                return n % 2 == 0;
            }
        )
        .Select(n => // PROJECTION
        {
            return n * 3;
        }
        );

    // only at this point, when we access result
    // is that GenerateNumbers2(5) will be called
    //VIP: this will call GenerateNumbers2(5) 10 times
    //     it means it will calculate ONE item at a time
    //     (the yield will run as part of each MoveNext in
    //      IEnumerable)
    //
    // When the foreach starts running the MoveNext method
    // of the IEnumerable is called for the first time ->
    // then, the GenerateNumbers2 is called (not before)

    foreach (var item in result)
    {
        Console.WriteLine($"{item}, ");
    }
}

//--------------------------------------------------
void LinqIEnumerableBreakingQuery()
{
    // Even if I break the query sequence - the result will
    // be the same - call to GenerateNumbers2 will be done
    // only in the foreach - when I need the content
    //e.g.

    // the same pipeline will be executed each time
    // we get a new value from GenerateNumbers2 + yield
    // (called in the foreach loop)

    //here I can control which query steps I will run
    // this is called query composition
    bool even = false;

    var result = GenerateNumbers2(5);
    if (even)
    {
        result = result.Where(n => n % 2 == 0);
    }
    result = result.Select(n => n * 3);

    // at this point - will use IEnumerable result (we need it),
    // will do calls to GenerateNumbers2(5) + yield to process
    // each value, one by one (so, it never load all results in memory
    // to process)
    foreach (var item in result)
    {
        Console.WriteLine($"{item}, ");
    }
}

//--------------------------------------------------
void LinqImmediateCalls()
{
    // Some methods will call immediately the function
    // (no delay); e.g.:

    //count

    bool even = true;

    // It seems it runs 3 x the query ??? check this:
    // 1-when start function + queries (pipeline) ???????????
    // 2-when count is called
    // 3-when foreach is called

    //because we use result.Count below - this time full
    //query was processed (updating content of result)
    var result = GenerateNumbers2(5);
    //e.g.: result=0,5,10,15,20,25
    if (even)
    {
        result = result.Where(n => n % 2 == 0);
    }
    result = result.OrderByDescending(n => n);
    result = result.Select(n => n * 7);
    //at this point: result content = 0,30,60 and count = 3

    //at this point - result is already correct (with all values)
    //so that count can use it
    Console.WriteLine($"number of items={result.Count()}");

    //??? called function + pipeline again ???
    foreach (var item in result)
    {
        Console.WriteLine($"{item}, ");
    }
}

//--------------------------------------------------
void LinqImmediateCallsTest()
{
    // Some methods will call immediately the function
    // (no delay); e.g.:

    //count
    
    var result = GenerateNumbers2(5)
        .Where(n => n % 2 == 0)
        .OrderByDescending(n => n)
        .Select(n => n * 3);

    //so that count can use it
    Console.WriteLine($"number of items={result.Count()}");

    foreach (var item in result)
    {
        Console.WriteLine($"{item}, ");
    }
}


//--------------------------------------------------
//--------------------------------------------------
Console.WriteLine("_________________________________");
Console.WriteLine($">>>>>GenerateNumbers1(10)...");
foreach (var item in GenerateNumbers1(10))
{
    Console.WriteLine($"{item}, ");
}

//Console.WriteLine("_________________________________");
//Console.WriteLine($">>>>>GenerateNumbers2(5)...");
//foreach (var item in GenerateNumbers2(5))
//{
//    Console.WriteLine($"{item}, ");
//}

//Console.WriteLine("_________________________________");
//Console.WriteLine($">>>>>LinqEvenNumbersOnly()...");
//foreach (var item in LinqEvenNumbersOnly())
//{
//    Console.WriteLine($"{item}, ");
//}

Console.WriteLine("_________________________________");
Console.WriteLine($">>>>>LinqHowIEnumerableLinqWorks()...");
LinqHowIEnumerableLinqWorks();

Console.WriteLine("_________________________________");
Console.WriteLine($">>>>>LinqIEnumerableBreakingQuery()...");
LinqIEnumerableBreakingQuery();

Console.WriteLine("_________________________________");
Console.WriteLine($">>>>>LinqImmediateCalls()...");
LinqImmediateCalls();

Console.WriteLine("_________________________________");
Console.WriteLine($">>>>>LinqImmediateCallsTest()...");
LinqImmediateCallsTest();

